#include <windows.h>

int main() {
    UINT uMode = 0x400;
    SetErrorMode(uMode);
    if (SetErrorMode(0) == uMode) {
        OutputDebugStringA("[+] All OK");
    } else {
        OutputDebugStringA("[+] Sandbox has been detected.");
    }

    return 0;
}
