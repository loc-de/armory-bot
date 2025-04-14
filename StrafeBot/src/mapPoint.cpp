#include "mapPoint.h"

MapPoint::MapPoint(const unsigned int id, const Point& p, const bool jump) :
	_id(id), _jump(jump), _p(p) {}

MapPoint::MapPoint(const MapPoint& mp) : 
	_id(mp.id()), _jump(mp.jump()), _p(mp.p()) {}

unsigned int MapPoint::id() const {
	return _id;
}

unsigned int& MapPoint::id() {
	return _id;
}

const Point& MapPoint::p() const {
	return _p;
}

bool MapPoint::jump() const {
	return _jump;
}

Point& MapPoint::p() {
	return _p;
}

bool& MapPoint::jump() {
	return _jump;
}

MapPoint& MapPoint::operator=(const MapPoint& mp) {
	if (this == &mp)
		return *this;

	_id = mp.id();
	_p = mp.p();
	_jump = mp.jump();
	return *this;
}

ostream& operator<<(ostream& os, const MapPoint& mp) {
	return os << '<' << mp.id() << ", " << mp.jump() << '>' << mp.p();
}
