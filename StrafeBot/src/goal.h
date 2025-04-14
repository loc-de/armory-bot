#pragma once
#include "point.h"

class Goal {
private:
	Point _p;
	float _ang;
	int _n_id = -1;

public:
	Goal(const Point&, float ang = 0);
	Goal(const Goal&);

	const Point& p() const;
	float ang() const;
	int n_id() const;
	int& n_id();
};