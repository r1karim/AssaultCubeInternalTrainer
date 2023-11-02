#include "pch.h"
#include "Utils.h"

void mem::Patch(BYTE* dst, BYTE* src, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	//WriteProcessMemory(dst, src, size, nullptr);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void mem::Nop(BYTE* dst, unsigned int size) {
	BYTE* nopArr = new BYTE[size];
	memset(nopArr, 0x90, size);
	mem::Patch(dst, nopArr, size);
	delete[] nopArr;
}

uintptr_t mem::findDMAAddy(uintptr_t ptr, std::vector<unsigned int>offsets) {
	uintptr_t addr = ptr;
	for (int i = 0; i < offsets.size(); i++) {
		addr = *(uintptr_t*)addr;
		addr += offsets[i];
	}
	return addr;
}