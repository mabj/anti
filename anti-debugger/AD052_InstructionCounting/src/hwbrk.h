#ifndef HWBRK_H
#define HWBRK_H

#include <windows.h>
#include <stdbool.h>

enum HWBRK_TYPE
{
	HWBRK_TYPE_CODE,
	HWBRK_TYPE_READWRITE,
	HWBRK_TYPE_WRITE,
};

enum HWBRK_SIZE
{
	HWBRK_SIZE_1,
	HWBRK_SIZE_2,
	HWBRK_SIZE_4,
	HWBRK_SIZE_8,
};

HANDLE SetHardwareBreakpoint(HANDLE hThread, enum HWBRK_TYPE Type, enum HWBRK_SIZE Size, void* s);
bool RemoveHardwareBreakpoint(HANDLE hBrk);

#endif
