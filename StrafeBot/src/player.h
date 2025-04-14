#pragma once
#include "memory.h"
#include "point.h"
#include <thread>

class Player {
private:
	Point _pos;
	float _ang;
	Memory _memory;

	unique_ptr<thread> _update_t;

public:
	Player();

	const Point& pos() const;
	const float ang() const;

	void update();
	bool inRange(const Point&, const double) const;
	bool inRangeZ(const Point&, const double) const;
};