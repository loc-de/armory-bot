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
	constexpr double RANGE_RADIUS = 40;
}

namespace mouse {
	constexpr int STEPS_COUNT = 20;
	constexpr double DELAY = 15;
}

namespace key {
	constexpr uintptr_t W = 0x57;
	constexpr uintptr_t C = 0x43;
	constexpr uintptr_t SPACE = 0x20;
}

#endif
