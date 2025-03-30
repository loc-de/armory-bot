#include "player.h"
#include "constants.h"
//#include "point.h"
#include <cmath>

Player::Player() :
	_pos(Point()), _ang(0), _memory(Memory()) 
{}

const Point& Player::pos() const {
	return _pos;
}

const float Player::ang() const {
	return _ang;
}

void Player::update() {
	_pos.x() = _memory.memRead<float>(offsets::X);
	_pos.y() = _memory.memRead<float>(offsets::Y);
	_pos.z() = _memory.memRead<float>(offsets::Z);
	_ang = _memory.memRead<float>(offsets::ROT);

	//normAng();
}

//void Player::normAng() {
//	if (_ang < 0)
//		_ang += 360;
//}

bool Player::inRange(const Point& p) const {
	if (_pos.distanceTo(p) >= vars::RANGE_RADIUS)
		return false;
	return true;
}
