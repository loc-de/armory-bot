#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace offsets {
	constexpr uintptr_t X = 0x1987850;
	constexpr uintptr_t Y = 0x1987854;
	constexpr uintptr_t Z = 0x1987858;
	constexpr uintptr_t ROT = 0x1AAE884;
}

namespace vars {
	constexpr int GOAL_ID = 10010;
	constexpr double RANGE_RADIUS = 50;
	constexpr double ROT_FACTOR = 0.055;

	constexpr double DEG_PER_PIXEL = 0.055; // —к≥льки градус≥в за п≥ксель
	constexpr int UPDATE_RATE_MS = 5; // „ас м≥ж оновленн€ми (мс)
}

namespace mouse {
	constexpr int STEPS_COUNT = 20;
	constexpr double DELAY = 10;
}

namespace key {
	constexpr uintptr_t W = 0x57;
	constexpr uintptr_t C = 0x43;
	constexpr uintptr_t SPACE = 0x20;
}

#endif
