#include "goal.h"

Goal::Goal(const Point& p, float ang) :
	_p(Point(p)), _ang(ang) {}

Goal::Goal(const Goal& g) : 
	_p(g.p()), _ang(g.ang()), _n_id(g.n_id()) {}

const Point& Goal::p() const {
	return _p;
}

float Goal::ang() const {
	return _ang;
}

int Goal::n_id() const {
	return _n_id;
}

int& Goal::n_id() {
	return _n_id;
}
