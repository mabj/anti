#include <windows.h>
#include <stdbool.h>
#include <intrin.h>
#include <stdio.h>

bool __is_debugged(unsigned int dwNativeElapsed) {
    DWORD dwStart = GetTickCount();

    for (int i = 0; i < 2; i++) {
        for (int u = 0; u < 20; u++) {
            printf("%03d %03d\r\r\r\r\r\r\r", i, u);
            Sleep(20);
        }
    }

    return (GetTickCount() - dwStart) > dwNativeElapsed;
}

int main() {
    if(__is_debugged(12960000))
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 037", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 037", MB_OK);

    return 0;
}