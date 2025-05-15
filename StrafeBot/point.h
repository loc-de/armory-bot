#pragma once
#include <iostream>
using namespace std;

class Point {
private:
	float _x;
	float _y;
	float _z;

public:
	Point(float x = 0, float y = 0, float z = 0);
	Point(const Point&);

	float x() const;
	float y() const;
	float z() const;
	float& x();
	float& y();
	float& z();

	Point& operator=(const Point&);

	double distanceTo(const Point& p) const;
	double angleTo(const Point&) const;
	Point projectionOnEdge(const Point&, const Point&) const;
	bool isSame(const Point&) const;
};

ostream& operator<<(ostream&, const Point&);
