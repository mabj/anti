#include <windows.h>
#include <stdio.h>

BOOL __is_debugged(void) {
    BYTE ucCounter = 1;
    for (int i = 0; i < 8; i++) {
        Sleep(0x0F);
        ucCounter <<= (1 - SwitchToThread());
    }

    printf("[+] ucCounter = %d\n", ucCounter);
    return ucCounter == 0;
}

int main(void) {
    BOOL debugger_detected = __is_debugged();

    if (debugger_detected) {
        MessageBoxW(NULL, L"[+] The process is in Debug mode.", L"AD056_SwitchToThread", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] The process is NOT in Debug mode.", L"AD056_SwitchToThread", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
