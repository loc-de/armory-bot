#include "goal.h"
//#include "point.h"

Goal::Goal(const Point& p, float ang) :
	_pos(Point(p)), _ang(ang) {}

Goal::Goal(const Goal& g) : 
	_pos(g.pos()), _ang(g.ang()), _n_id(g.n_id()) {}

const Point& Goal::pos() const {
	return _pos;
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
