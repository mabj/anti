#include <windows.h>

int main() {
    UINT uMode = 0x400;
    SetErrorMode(uMode);
    if (SetErrorMode(0) == uMode) {
        MessageBoxA(NULL, "[+] Sandbox detected!", "Anti-sandbox 01", MB_OK);
    } else {
        MessageBoxA(NULL, "[+] Sandbox NOT detected!", "Anti-sandbox 01", MB_OK);
    }

    return 0;
}
