#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

namespace vars {
	constexpr double ARRIVAL_RADIUS = 45;
	constexpr double ARRIVAL_GOAL_RADIUS = 35;
	constexpr double JUMP_RADIUS = 100;
	constexpr double STUCK_RADIUS = 40;
	constexpr double SMALL_MOVE_DIST = 5;
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
	constexpr uintptr_t D = 0x44;
	constexpr uintptr_t A = 0x41;
	constexpr uintptr_t C = 0x43;

	constexpr uintptr_t SPACE = 0x20;
	constexpr uintptr_t BACKTICK = 0xC0;
	constexpr uintptr_t ENTER = 0x0D;

	constexpr uintptr_t S = 0x53;
	constexpr uintptr_t E = 0x45;
	constexpr uintptr_t N = 0x4E;
	constexpr uintptr_t I = 0x49;
	constexpr uintptr_t T = 0x54;
	constexpr uintptr_t V = 0x56;
	constexpr uintptr_t Y = 0x59;

	constexpr uintptr_t NUM_2 = 0x32;
	constexpr uintptr_t DOT = 0xBE;
	constexpr uintptr_t NUM_5 = 0x35;
}

#endif
