#include <windows.h>
#include <stdbool.h>

static const char *WIN_BLACKLIST[] = {
    "antidbg",
    "ID",               // Immunity Debugger
    "ntdll.dll",        // peculiar name for a window class
    "ObsidianGUI",
    "OLLYDBG",
    "Rock Debugger",
    "SunAwtFrame",
    "Qt5QWindowIcon",
    "WinDbgFrameClass", // WinDbg
    "Zeta Debugger",
    "x64dbg",
    "x32dbg"
};
 

bool __is_debugged() {
    for (unsigned int i = 0; i < 12; i++)
        if (FindWindowA(WIN_BLACKLIST[i], NULL) != NULL)
            return true;

    return false; 
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] Could detect debugging tool!", "Anti-debug 018", MB_OK);
    else
        MessageBoxA(NULL, "[+] Could NOT detect debugging tool!", "Anti-debug 018", MB_OK);

    return 0;
}