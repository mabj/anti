#include <windows.h>
#include <stdbool.h>
#include <intrin.h>
#include <stdio.h>

bool __is_debugged(unsigned int qwNativeElapsed) {
    SYSTEMTIME stStart, stEnd;
    FILETIME ftStart, ftEnd;
    ULARGE_INTEGER uiStart, uiEnd;

    GetSystemTime(&stStart);

    for (int i = 0; i < 2; i++) {
        for (int u = 0; u < 20; u++) {
            printf("%03d %03d\r\r\r\r\r\r\r", i, u);
            Sleep(20);
        }
    }

    GetSystemTime(&stEnd);

    if (!SystemTimeToFileTime(&stStart, &ftStart))
        return false;
    if (!SystemTimeToFileTime(&stEnd, &ftEnd))
        return false;

    uiStart.LowPart  = ftStart.dwLowDateTime;
    uiStart.HighPart = ftStart.dwHighDateTime;
    uiEnd.LowPart  = ftEnd.dwLowDateTime;
    uiEnd.HighPart = ftEnd.dwHighDateTime;
    return (uiEnd.QuadPart - uiStart.QuadPart) > qwNativeElapsed;
}

int main() {
    if(__is_debugged(12960000))
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 036", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 036", MB_OK);

    return 0;
}