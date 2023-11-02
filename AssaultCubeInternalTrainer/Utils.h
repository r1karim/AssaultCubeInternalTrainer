#ifndef UTILS_H
#define UTILS_H
#include<iostream>

#include<Windows.h>
#include<vector>

namespace mem {
	void Patch(BYTE* dst, BYTE* src, unsigned int);
	void Nop(BYTE* dst, unsigned int);
	uintptr_t findDMAAddy(uintptr_t ptr, std::vector<unsigned int>offsets);

};


#endif