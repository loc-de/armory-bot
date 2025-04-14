#include "memory.h"

Memory::Memory() : 
	_processId(getProcess(L"cs2.exe")), 
	_baseAddress(getModuleBaseAddress(L"client.dll")),
	_processHandle(OpenProcess(PROCESS_VM_READ, FALSE, _processId))
{}

uintptr_t Memory::getModuleBaseAddress(const wchar_t* moduleTarget) {
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, _processId);

	if (snapshotHandle == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	MODULEENTRY32W moduleEntry = { };
	moduleEntry.dwSize = sizeof(MODULEENTRY32W);

	if (Module32FirstW(snapshotHandle, &moduleEntry)) {

		do {
			if (_wcsicmp(moduleEntry.szModule, moduleTarget) == 0) {
				CloseHandle(snapshotHandle);
				return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
			}
		} while (Module32NextW(snapshotHandle, &moduleEntry));
	}

	CloseHandle(snapshotHandle);
	return NULL;
}

DWORD Memory::getProcess(const wchar_t* target) {
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshotHandle == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	PROCESSENTRY32W processEntry = { };
	processEntry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(snapshotHandle, &processEntry)) {

		do {
			if (_wcsicmp(processEntry.szExeFile, target) == 0) {
				CloseHandle(snapshotHandle);
				return processEntry.th32ProcessID;
			}
		} while (Process32NextW(snapshotHandle, &processEntry));
	}

	CloseHandle(snapshotHandle);
	return NULL;
}
