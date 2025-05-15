#define _USE_MATH_DEFINES

#include "point.h"
#include <iostream>
#include <cmath>
#include "constants.h"
using namespace std;

Point::Point(float x, float y, float z)
	: _x(x), _y(y), _z(z) {}

Point::Point(const Point& p) 
	: _x(p.x()), _y(p.y()), _z(p.z()) {}

float Point::x() const {
	return _x;
}

float Point::y() const {
	return _y;
}

float Point::z() const {
	return _z;
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

Point& Point::operator=(const Point& p) {
	if (this == &p)
		return *this;

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

Point Point::projectionOnEdge(const Point& p1, const Point& p2) const {
	double A = p1.y() - p2.y();
	double B = p2.x() - p1.x();
	double C = p1.x() * p2.y() - p2.x() * p1.y();

	double x_proj = (B * (B * _x - A * _y) - A * C) / (A * A + B * B);
	double y_proj = (A * (-B * _x + A * _y) - B * C) / (A * A + B * B);

	if (x_proj >= min(p1.x(), p2.x()) && x_proj <= max(p1.x(), p2.x()) &&
		y_proj >= min(p1.y(), p2.y()) && y_proj <= max(p1.y(), p2.y())) {
		return Point(x_proj, y_proj);
	}
	else {
		double distB = hypot(_x - p1.x(), _y - p1.y());
		double distC = hypot(_x - p2.x(), _y - p2.y());

		if (distB < distC)
			return { p1.x(), p1.y()};
		else
			return { p2.x(), p2.y()};
	}
}

bool Point::isSame(const Point& p) const {
	return this->distanceTo(p) < vars::SMALL_MOVE_DIST;
}

ostream& operator<<(ostream& os, const Point& p) {
	return os << '(' << p.x() << ", " << p.y() << ", " << p.z() << ')';
}
