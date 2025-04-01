#pragma once
#include <iostream>
using namespace std;

class Point {
private:
	float _x;
	float _y;
	float _z;
	unsigned int _id;

public:
	Point(float x = 0, float y = 0, float z = 0, unsigned int id = 1);
	Point(const Point&);
	Point(Point&&) noexcept;
	~Point() = default;

	float x() const;
	float y() const;
	float z() const;
	unsigned int id() const;
	float& x();
	float& y();
	float& z();
	unsigned int& id();

	Point& operator=(const Point&);
	Point& operator=(Point&&) noexcept;

	double distanceTo(const Point& p) const;
	double angleTo(const Point&) const;
	Point projectionOnEdge(const Point&, const Point&) const;
};

ostream& operator<<(ostream&, const Point&);
