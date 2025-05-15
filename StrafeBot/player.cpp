#include "player.h"
#include "constants.h"
#include <cmath>
#include "config.h"

Player::Player() :
	_pos(Point()), _ang(0), _memory(Memory()) {}

const Point& Player::pos() const {
	return _pos;
}

const float Player::ang() const {
	return _ang;
}

void Player::update() {
	_pos.x() = _memory.memRead<float>(Config::get().offsets.X);
	_pos.y() = _memory.memRead<float>(Config::get().offsets.Y);
	_pos.z() = _memory.memRead<float>(Config::get().offsets.Z);
	_ang = _memory.memRead<float>(Config::get().offsets.ROT);
}

bool Player::inRange(const Point& p, const double r) const {
	if (_pos.distanceTo(p) >= r) 
		return false;
	return true;
}

bool Player::inRangeZ(const Point& p, const double r) const {
	if (abs(_pos.z() - p.z()) >= r)
		return false;
	return true;
}
