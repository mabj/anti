#include <windows.h>
#include <stdbool.h>
#include <string.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char title[256];
    if (GetWindowTextA(hwnd, title, sizeof(title))) {
        const char *debuggers[] = {"x64dbg", "x32dbg", "windbg"};
        
        for (long long unsigned i = 0; i < sizeof(debuggers)/sizeof(debuggers[0]); i++) {
            if (strstr(title, debuggers[i]) != NULL) {
                *((bool*)lParam) = true;
                return FALSE; // Stop enumeration when match found
            }
        }
    }
    return TRUE; // Continue enumeration
}

bool __is_debugged() {
    bool found = false;
    EnumWindows(EnumWindowsProc, (LPARAM)&found);
    return found;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 010", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 010", MB_OK);

    return 0;
}