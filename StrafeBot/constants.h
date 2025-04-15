#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace offsets {
	constexpr uintptr_t X = 0x196E7A0;
	constexpr uintptr_t Y = 0x196E7A4;
	constexpr uintptr_t Z = 0x1A89790;
	constexpr uintptr_t ROT = 0x1A933C4;
}

namespace vars {
	const string SERVER_URL = "http://13.50.171.67:19410";
	const string graph_path = "graph.txt";
	constexpr double ARRIVAL_RADIUS = 50;
	constexpr double JUMP_RADIUS = 100;
	//constexpr double STUCK_RADIUS = 250;
	//constexpr double MOVE_RADIUS = 500;
	constexpr double HEIGHT_RANGE = 60;
	constexpr int UPDATE_RATE_MS = 5;
}

namespace rot {
	constexpr double SPEED = 90.0 / 100.0;
	constexpr double ANG_PER_PIXEL = 0.055;
	constexpr double MAX_ANG_PER_STEP = SPEED * vars::UPDATE_RATE_MS;
}

namespace key {
	constexpr uintptr_t W = 0x57;
	constexpr uintptr_t C = 0x43;
	constexpr uintptr_t SPACE = 0x20;
}

#endif
