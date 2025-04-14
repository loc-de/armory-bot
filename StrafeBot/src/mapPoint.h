#pragma once
#include "point.h"

class MapPoint {
private:
	Point _p;
	bool _jump;
	unsigned int _id;

public:
	MapPoint(const unsigned int id = 0, const Point& p = Point(), const bool jump = 0);
	MapPoint(const MapPoint&);

	const Point& p() const;
	Point& p();
	unsigned int id() const;
	unsigned int& id();
	bool jump() const;
	bool& jump();

	MapPoint& operator=(const MapPoint&);
};

ostream& operator<<(ostream&, const MapPoint&);
