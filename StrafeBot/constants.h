#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace offsets {
	constexpr uintptr_t X = 0x196E700;
	constexpr uintptr_t Y = 0x196E704;
	constexpr uintptr_t Z = 0x196E6A8;
	constexpr uintptr_t ROT = 0x1A932E4;
}

namespace vars {
	constexpr int GOAL_ID = 10010;
	constexpr double RANGE_RADIUS = 50;
}

namespace rot {
	constexpr double SPEED = 90.0 / 150.0;
	constexpr double ANG_PER_PIXEL = 0.055;
	constexpr int UPDATE_RATE_MS = 5;
	constexpr double MAX_ANG_PER_STEP = SPEED * UPDATE_RATE_MS;
}

namespace key {
	constexpr uintptr_t W = 0x57;
	constexpr uintptr_t C = 0x43;
	constexpr uintptr_t SPACE = 0x20;
}

#endif
