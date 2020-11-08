// Author: @sandornemes

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// build with "i686-w64-mingw32-gcc -Os -s sem.c -o sem.exe -nostartfiles -nostdlib -lkernel32 -mwindows -m32 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-ident"

void _main() {
    UINT uMode = 0x400;
    SetErrorMode(uMode);
    if (SetErrorMode(0) == uMode) {
        OutputDebugStringA("[+] All OK");
    } else {
        OutputDebugStringA("[+] A sandbox has been detected.");
    }
    ExitProcess(0);
}
