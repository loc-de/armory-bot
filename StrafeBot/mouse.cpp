#include "mouse.h"
#include "constants.h"
#include <Windows.h>

void Mouse::move(int dx, int dy) const {
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::moveOn(int x, int y) const {
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dx = x * (65535 / GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = y * (65535 / GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::smoothMove(int x, int y) const {
    int step_x = (int)(x / mouse::STEPS_COUNT);
    int step_y = (int)(y / mouse::STEPS_COUNT);

    for (int i = 0; i < mouse::STEPS_COUNT; i++) {
        move(step_x, step_y);
        Sleep(mouse::DELAY);
        //Sleep(mouse::DELAY);
    }

    double rem_x = x % mouse::STEPS_COUNT;
    double rem_y = y % mouse::STEPS_COUNT;
    move(rem_x, rem_y);
}
