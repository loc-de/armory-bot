#include "controller.h"
#include "constants.h"
#include <limits>
#include <exception>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <algorithm>

Controller::Controller(const Goal& goal) : 
	_data(), _bot(), _goal(goal), _mouse(), 
	_kb(), _sio_client(), _trg_ang(0), _trg_mp_id(-1), _src_mp_id(-1),
	_is_stuck(false)
{
	_data.load();
	_goal.n_id() = nearestMP(_goal.p());
	_sio_client.connect(vars::SERVER_URL);
}

void Controller::testMem() {
	_bot.update();
	cout << _bot.pos() << endl;
	cout << _bot.ang() << endl;
}

void Controller::activateWindow() const {
	const wchar_t* title = L"Counter-Strike 2";

	HWND hWnd = FindWindowW(nullptr, title);

	if (hWnd) {
		SetForegroundWindow(hWnd);
		cout << "cs2 window activated" << endl;
	}
	else {
		cout << "cs2 window not found" << endl;
	}
}

void Controller::run() {
	_rot_t = make_unique<thread>(&Controller::controlRot, this);
	_jump_t = make_unique<thread>(&Controller::controlJump, this);

	this_thread::sleep_for(chrono::milliseconds(100));

	while (true) {
		Path path = findWay();
		cout << path << endl;
		
		knife();
		_kb.press(key::W);
		move(path);
		_kb.release(key::W);

		_sio_client.send_command();
		waitDeath();
	}
}

void Controller::move(const Path& path) {
	_trg_mp_id = path.path[0];
	_src_mp_id = path.path[0];

	for (const int id : path.path) {
		_trg_mp_id = id;
		moveToPoint(_data.mapPoint(id).p());
		_src_mp_id = id;
	}

	moveToPoint(_goal.p());

	_trg_ang = _goal.ang();
}

void Controller::moveToPoint(const Point& p) {
	//Point last_p = _bot.pos();
	//size_t time = 0;

	while (!_bot.inRange(p, vars::ARRIVAL_RADIUS)) {
		//if (time >= 500) {
		//	if (_bot.inRange(last_p, vars::MOVE_RADIUS)) {
		//		_is_stuck = false;
		//		last_p = _bot.pos();
		//	}
		//	else {
		//		_is_stuck = true;
		//	}
		//	time = 0;
		//}

		_trg_ang = _bot.pos().angleTo(p);
		this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
		//time += vars::UPDATE_RATE_MS;
	}
}

void Controller::controlJump() {
	while (true) {
		//cout << "_is_stuck: " << boolalpha << _is_stuck << endl;

		if (_trg_mp_id == -1 || _src_mp_id == -1 || _trg_mp_id == _src_mp_id) {
			this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
			continue;
		}
		if (!_data.mapPoint(_src_mp_id).jump()) {
			this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
			continue;
		}
		if (!_bot.inRange(_data.mapPoint(_src_mp_id).p(), vars::JUMP_RADIUS)) {
			this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
			continue;
		}

		this_thread::sleep_for(chrono::milliseconds(100));

		double ang = _bot.ang() - _trg_ang;
		if (ang > 180)
			ang -= 360;
		if (ang < -180)
			ang += 360;
		if (abs(ang) > 5) {
			this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
			continue;
		}

		this_thread::sleep_for(chrono::milliseconds(50));
		jump();
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void Controller::controlRot() {
	while (true) {
		_bot.update();

		double angle = _bot.ang() - _trg_ang;
		if (angle > 180)
			angle -= 360;
		if (angle < -180)
			angle += 360;
		if (abs(angle) < 3) {
			this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
			continue;
		}

		double speed_factor = abs(angle) < 20 ? 0.5 : 1.5;
		double max_step = rot::MAX_ANG_PER_STEP * speed_factor;

		double step = (angle < -max_step) ? -max_step : (angle > max_step) ? max_step : angle;

		int move_pixels = (int)(step / rot::ANG_PER_PIXEL);
		if (move_pixels != 0)
			_mouse.move(move_pixels, 0);

		this_thread::sleep_for(chrono::milliseconds(vars::UPDATE_RATE_MS));
	}
}

vector<int> Controller::nearestVecMP(const Point& p) const {
	int a_n_id = -1;
	int b_n_id = -1;
	double n_dis = (std::numeric_limits<double>::max)();

	for (const pair<int, int>& edge : _data.graph().edges()) {
		const Point& first_p = _data.mapPoint(edge.first).p();
		const Point& second_p = _data.mapPoint(edge.second).p();

		Point proj_p = p.projectionOnEdge(first_p, second_p);
		double dis = p.distanceTo(proj_p);

		if (dis < n_dis || (a_n_id == -1 && b_n_id == -1)) {
			n_dis = dis;
			a_n_id = -1;
			b_n_id = -1;
			if (_bot.inRangeZ(first_p, vars::HEIGHT_RANGE))
				a_n_id = edge.first;
			if (_bot.inRangeZ(second_p, vars::HEIGHT_RANGE))
				b_n_id = edge.second;
		}
	}
	return vector<int>{a_n_id, b_n_id};
}

int Controller::nearestMP(const Point& p) const {
	int n_id = -1;
	double n_dis = (numeric_limits<double>::max)();

	for (const auto& i_mp : _data.mapPoints()) {
		double dis = p.distanceTo(i_mp.second.p());
		if (dis < n_dis) {
			n_dis = dis;
			n_id = i_mp.first;
		}
	}
	if (n_id == -1)
		throw runtime_error("cant found nearest point");
	return n_id;
}

Path Controller::findWay() {
	vector<int> n_ids = nearestVecMP(_bot.pos());
	double dis = (numeric_limits<double>::max)();
	Path path;

	for (const int id : n_ids) {
		if (id == -1)
			continue;

		const Path& path_to_id = _data.path(id, _goal.n_id());
		double dis_to_bot = _bot.pos().distanceTo(_data.mapPoint(id).p());
		if (path_to_id.dis + dis_to_bot < dis) {
			dis = path_to_id.dis + dis_to_bot;
			path = path_to_id;
		}
	}
	if (dis == (numeric_limits<double>::max)())
		throw runtime_error("cant found path");
	return path;
}

void Controller::waitDeath() {
	while (_bot.inRange(_goal.p(), vars::ARRIVAL_RADIUS)) {
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

void Controller::knife() {
	_kb.send(key::C);
}

void Controller::jump() {
	_kb.send(key::SPACE);
}
