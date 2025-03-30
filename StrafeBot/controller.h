#pragma once
#include "data.h"
#include "player.h"
#include "goal.h"
#include "mouse.h"
#include "keyboard.h"

class Controller {
private:
	Data _data;
	Player _bot;
	Goal _goal;
	Mouse _mouse;
	Keybd _kb;
	double _trg_ang;

public:
	Controller(const Goal&);

	const Goal& goal() const;
	//Goal& goal();

	void testMem() const;
	void run();
	void move(const vector<int>&);
	void moveToPoint(const Point&, double);
	void controlRot();
	//void loadData();
	int nearest(const Point&) const;
	vector<int> findWay();
	void waitDeath();
	void knife();
	void jump();
};