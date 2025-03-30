#define _USE_MATH_DEFINES

#include "point.h"
#include <iostream>
#include <cmath>
using namespace std;

Point::Point(float x, float y, float z, unsigned int id)
	: _x(x), _y(y), _z(z), _id(id) {}

Point::Point(const Point& p) 
	: _x(p.x()), _y(p.y()), _z(p.z()), _id(p.id()) {
	//std::cout << "Point created!" << std::endl;
}

Point::Point(Point&& p) noexcept
	: _x(p.x()), _y(p.y()), _z(p.z()), _id(p.id())
{
	if (this == &p)
		return;
}

float Point::x() const {
	return _x;
}

float Point::y() const {
	return _y;
}

float Point::z() const {
	return _z;
}

unsigned int Point::id() const {
	return _id;
}

float& Point::x() {
	return _x;
}

float& Point::y() {
	return _y;
}

float& Point::z() {
	return _z;
}

unsigned int& Point::id() {
	return _id;
}

Point& Point::operator=(const Point& p) {
	if (this == &p)
		return *this;

	_id = p.id();
	_x = p.x();
	_y = p.y();
	_z = p.z();
	return *this;
}

Point& Point::operator=(Point&& p) noexcept {
	if (this == &p)
		return *this;

	_id = p.id();
	_x = p.x();
	_y = p.y();
	_z = p.z();
	return *this;
}

double Point::distanceTo(const Point& p) const {
	return sqrt(
		pow(_x - p.x(), 2) +
		pow(_y - p.y(), 2)
	);
}

double Point::angleTo(const Point& p) const {
	return atan2(_y - p.y(), _x - p.x()) * 180 / M_PI + 180;
}

ostream& operator<<(ostream& os, const Point& p) {
	return os << '(' << p.x() << ", " << p.y() << ", " << p.z() << ')';
}

//bool operator<(const Point& p1, const Point& p2) {
//	if (p1.x() != p2.x())
//		return p1.x() < p2.x();
//	if (p1.y() != p2.y())
//		return p1.y() < p2.y();
//	return p1.z() < p2.z();
//}

//bool operator<(const Point& p1, const Point& p2) {
//	if (p1.x() != p2.x())
//		return p1.x() < p2.x();
//	if (p1.y() != p2.y())
//		return p1.y() < p2.y();
//	return p1.z() < p2.z();
//}
