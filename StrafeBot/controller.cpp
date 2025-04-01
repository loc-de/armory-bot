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
		_kb.release(key::W);

		waitDeath();
	}
}

void Controller::move(const vector<int>& way) {
	int last_z = _data.points().at(way[0]).z();

	for (const int id : way) {
		const Point& c_p = _data.points().at(id);
		moveToPoint(c_p, last_z);
		last_z = c_p.z();
	}

	moveToPoint(_goal.pos(), last_z);

	_trg_ang = _goal.ang();
}

void Controller::moveToPoint(const Point& p, double last_z) {
	while (!_bot.inRange(p)) {
		_bot.update();
		_trg_ang = _bot.pos().angleTo(p);

		if (p.z() < last_z) {
			jump();
		}

		this_thread::sleep_for(chrono::milliseconds(10));
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

		double speed_factor = abs(angle) < 20 ? 0.5 : 1.5;
		double max_step = rot::MAX_ANG_PER_STEP * speed_factor;

		double step = (angle < -max_step) ? -max_step : (angle > max_step) ? max_step : angle;

		int move_pixels = (int)(step / rot::ANG_PER_PIXEL);
		if (move_pixels != 0)
			_mouse.move(move_pixels, 0);

		this_thread::sleep_for(chrono::milliseconds(rot::UPDATE_RATE_MS));
	}
}

int Controller::nearest(const Point& p) const {
	int a_n_id = -1;
	int b_n_id = -1;
	double n_dis = (std::numeric_limits<double>::max)();

	for (const auto item : _data.graph().adj()) {
		for (const int id : item.second) {
			if (_data.points().at(id).z() != _data.points().at(item.first).z())
				continue;

			Point proj_p = p.projectionOnEdge(_data.points().at(item.first), _data.points().at(id));
			double dis = p.distanceTo(proj_p);
			if (dis < n_dis) {
				n_dis = dis;
				a_n_id = item.first;
				b_n_id = id;
			}
		}
	}
	return p.distanceTo(_data.points().at(a_n_id)) < p.distanceTo(_data.points().at(b_n_id)) ? a_n_id : b_n_id;
}

vector<int> Controller::findWay() {
	int n_id = nearest(_bot.pos());
	return _data.graph().pathTo(n_id, _goal.n_id());
}

void Controller::waitDeath() {
	while (_bot.inRange(_goal.pos())) {
		this_thread::sleep_for(chrono::milliseconds(400));
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
