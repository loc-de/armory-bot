#include "keyboard.h"
#include <iostream>
#include <Windows.h>

void Keybd::press(const std::uintptr_t key) const {
	keybd_event(static_cast<BYTE>(key), 0, 0, 0);
}

void Keybd::release(const std::uintptr_t key) const {
	keybd_event(static_cast<BYTE>(key), 0, KEYEVENTF_KEYUP, 0);
}

void Keybd::send(const std::uintptr_t key) const {
	press(key);
	release(key);
}
