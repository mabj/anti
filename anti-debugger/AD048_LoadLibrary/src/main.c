#include <windows.h>
#include <stdio.h>

// TODO: Implement LoadLibrary-based debugger detection
BOOL __is_debugged(void) {
    CHAR szBuffer[] = { "C:\\Windows\\System32\\calc.exe" };
    LoadLibraryA(szBuffer);
    return INVALID_HANDLE_VALUE == CreateFileA(szBuffer, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
}

int main(void) {
    BOOL debugger_present = __is_debugged();

    if (debugger_present) {
        MessageBox(NULL, "[+] The process is in Debug mode.", "AD048_LoadLibrary", MB_OK | MB_ICONWARNING);
    } else {
        MessageBox(NULL, "[+] The process is NOT in Debug mode.", "AD048_LoadLibrary", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
