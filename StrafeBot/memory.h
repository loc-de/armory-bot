#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <stdexcept>
using namespace std;

class Memory {
private:
	DWORD _processId;
	uintptr_t _baseAddress;
	HANDLE _processHandle;

	uintptr_t getModuleBaseAddress(const wchar_t*);
	DWORD getProcess(const wchar_t*);

public:
	Memory();

	template <typename type>
	type memRead(uintptr_t pointerStatic) {
		type value = {};
		if (!ReadProcessMemory(_processHandle, (LPVOID)(_baseAddress + pointerStatic), &value, sizeof(type), NULL)) {
			throw runtime_error("Failed to read memory.");
		}
		return value;
	}
};
