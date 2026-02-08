#include <windows.h>
#include <stdbool.h>

bool __hide_from_debugger() {
    HDESK hNewDesktop = CreateDesktopA(
        "hidden_desktop", 
        NULL, 
        NULL, 
        0, 
        DESKTOP_CREATEWINDOW | DESKTOP_WRITEOBJECTS | DESKTOP_SWITCHDESKTOP, 
        NULL
    );

    if (!hNewDesktop)
        return FALSE;

    return SwitchDesktop(hNewDesktop);
}

int main() {
    if(__hide_from_debugger())
        MessageBoxA(NULL, "[+] Could hide process from debugger!", "Anti-debug 034", MB_OK);
    else
        MessageBoxA(NULL, "[+] Could NOT hide process from debugger!", "Anti-debug 034", MB_OK);

    return 0;
}