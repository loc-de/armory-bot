#pragma once
#include <iostream>

class Keybd {
public:
	//void press(const uintptr_t) const;
	void press(const std::uintptr_t) const;
	void release(const std::uintptr_t) const;
};
