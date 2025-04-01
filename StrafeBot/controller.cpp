#include "controller.h"
#include "constants.h"
#include <limits>
#include <exception>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <algorithm>

Controller::Controller(const Goal& goal) : 
	_data(Data()), _bot(Player()), _goal(goal), _mouse(Mouse()), _kb(Keybd()), _trg_ang(0)
{
	_data.load();
	_goal.n_id() = nearest(_goal.pos());
	_bot.update();
}

const Goal& Controller::goal() const {
	return _goal;
}

//Goal& Controller::goal() {
//	return _goal;
//}

void Controller::testMem() const {
	cout << _bot.pos() << endl;
	cout << _bot.ang() << endl;
}

void Controller::run() {
	_kb.press(key::W);

	while (true) {
		_bot.update();
		vector<int> way = findWay();

		for (int i = 0; i < way.size(); ++i) {
			cout << way[i] << ", ";
		}
		cout << endl;
		
		knife();
		_kb.press(key::W);
		move(way);

		waitDeath();
	}
	_kb.release(key::W);
}

void Controller::move(const vector<int>& way) {
	int last_z = _data.points().at(way[0]).z();

	for (const int id : way) {
		const Point& c_p = _data.points().at(id);
		moveToPoint(c_p, last_z);
		last_z = c_p.z();
	}

	moveToPoint(_goal.pos(), last_z);

	_bot.update();
	//double angle = _bot.ang() - _goal.ang();
	_trg_ang = _goal.ang();
	//_mouse.move((int)(angle / 0.055), 0);
}

void Controller::moveToPoint(const Point& p, double last_z) {
	while (!_bot.inRange(p)) {
		_bot.update();

		_trg_ang = _bot.pos().angleTo(p);

		//if (-7 > angle || angle > 7) {
		//	_mouse.move((int)(angle / 0.055), 0);
		//}

		if (p.z() < last_z) {
			jump();
			//Sleep(100);
		}

		Sleep(10);
	}
}

void Controller::controlRot() {
	constexpr double ROTATION_SPEED = 90.0 / 150;

	while (true) {
		_bot.update();

		double angle = _bot.ang() - _trg_ang;
		if (angle > 180)
			angle -= 360;
		if (angle < -180)
			angle += 360;

		//if (std::abs(angle) < 3) {
		//	std::this_thread::sleep_for(std::chrono::milliseconds(vars::UPDATE_RATE_MS));
		//	continue;
		//}

		double max_step = ROTATION_SPEED * vars::UPDATE_RATE_MS;

		double speed_factor = std::abs(angle) < 20 ? 0.5 : 1.5;
		max_step *= speed_factor;

		//double step = std::clamp(_trg_ang, -max_step, max_step);
		double step = (angle < -max_step) ? -max_step : (angle > max_step) ? max_step : angle;

		int move_pixels = static_cast<int>(step / vars::DEG_PER_PIXEL);
		//cout << move_pixels << endl;
		if (move_pixels != 0) {
			_mouse.move(move_pixels, 0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(vars::UPDATE_RATE_MS));
	}
}

int Controller::nearest(const Point& p) const {
	int n_id = -1;
	double n_dis = (std::numeric_limits<double>::max)();
	for (const auto& i_p : _data.points()) {
		//cout << i_p.first << endl;
		double dis = p.distanceTo(i_p.second);
		//cout << endl;
		//cout << dis << endl << endl;
		if (dis < n_dis) {
			n_dis = dis;
			n_id = i_p.first;
		}
	}
	if (n_id == -1)
		throw runtime_error("cant found nearest point");
	return n_id;
}

vector<int> Controller::findWay() {
	int n_id = nearest(_bot.pos());
	return _data.graph().pathTo(n_id, _goal.n_id());
}

void Controller::waitDeath() {
	while (_bot.inRange(_goal.pos())) {
		Sleep(400);
		_bot.update();
		cout << "wait death" << endl;
	}
}

void Controller::knife() {
	_kb.press(key::C);
	_kb.release(key::C);
}

void Controller::jump() {
	_kb.press(key::SPACE);
	_kb.release(key::SPACE);
}
