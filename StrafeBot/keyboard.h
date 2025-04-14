#pragma once
#include <iostream>

class Keybd {
public:
	void press(const std::uintptr_t) const;
	void release(const std::uintptr_t) const;
	void send(const std::uintptr_t) const;
};
