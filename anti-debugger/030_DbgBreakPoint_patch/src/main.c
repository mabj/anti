#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

// This patch to ntdll.DbgBreakPoint impacts the ability to attach a
// process to a debugger. 
void __patch() {
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll)
        return;

    FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, "DbgBreakPoint");
    if (!pDbgBreakPoint)
        return;

    DWORD dwOldProtect;
    if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        return;

    *(PBYTE)pDbgBreakPoint = (BYTE)0xC3; // RET

    while(true) {
        printf("[+] Running ...\n");
        Sleep((rand() % 9000) + 1000 );
    }
}

int main() {
    __patch();
    return 0;
}