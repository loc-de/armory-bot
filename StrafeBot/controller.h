#pragma once
#include "data.h"
#include "player.h"
#include "goal.h"
#include "mouse.h"
#include "keyboard.h"
#include "sio.h"

class Controller {
private:
	Data _data;
	Player _bot;
	Goal _goal;
	Mouse _mouse;
	Keybd _kb;
	SioClient _sio_client;
	unique_ptr<thread> _rot_t, _jump_t;

	double _trg_ang;
	int _trg_mp_id;
	int _src_mp_id;
	bool _is_stuck;

	void move(const Path&);
	void moveToPoint(const Point&);
	void controlJump();
	void controlRot();
	vector<int> nearestVecMP(const Point&) const;
	int nearestMP(const Point&) const;
	Path findWay();
	void waitDeath();
	void knife();
	void jump();

public:
	Controller(const Goal&);

	void testMem();
	void activateWindow() const;
	void run();
};