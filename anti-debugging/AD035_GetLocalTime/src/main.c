#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <intrin.h>

bool __is_debugged(unsigned int qwNativeElapsed) {
    SYSTEMTIME stStart, stEnd;
    FILETIME ftStart, ftEnd;
    ULARGE_INTEGER uiStart, uiEnd;

    GetLocalTime(&stStart);
    for (int i = 0; i < 2; i++) {
        for (int u = 0; u < 20; u++) {
            printf("%03d %03d\r\r\r\r\r\r\r", i, u);
            Sleep(20);
        }
    }
    GetLocalTime(&stEnd);

    if (!SystemTimeToFileTime(&stStart, &ftStart))
        return false;
    if (!SystemTimeToFileTime(&stEnd, &ftEnd))
        return false;

    uiStart.LowPart  = ftStart.dwLowDateTime;
    uiStart.HighPart = ftStart.dwHighDateTime;
    uiEnd.LowPart  = ftEnd.dwLowDateTime;
    uiEnd.HighPart = ftEnd.dwHighDateTime;
    printf("Elapsed TIme = %lld\n", uiEnd.QuadPart - uiStart.QuadPart);
    return (uiEnd.QuadPart - uiStart.QuadPart) > qwNativeElapsed;
}

int main() {
    if(__is_debugged(12960000))
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 035", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 035", MB_OK);

    return 0;
}