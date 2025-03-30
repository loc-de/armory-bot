#pragma once
#include "memory.h"
#include "point.h"

class Player {
private:
	Point _pos;
	float _ang;
	Memory _memory;

public:
	Player();

	const Point& pos() const;
	const float ang() const;

	void update();
	//void normAng();
	bool inRange(const Point&) const;
	//double distanceTo(const Point&) const;
};