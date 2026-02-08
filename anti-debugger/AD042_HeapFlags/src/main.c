#include <windows.h>
#include <winternl.h>
#include <stdbool.h>

bool __is_debugged() { 
#ifndef _WIN64
    PPEB pPeb = (PPEB)__readfsdword(0x30);
    PVOID pHeapBase = !m_bIsWow64
        ? (PVOID)(*(PDWORD_PTR)((PBYTE)pPeb + 0x18))
        : (PVOID)(*(PDWORD_PTR)((PBYTE)pPeb + 0x1030));
    DWORD dwHeapFlagsOffset = IsWindowsVistaOrGreater()
        ? 0x40
        : 0x0C;
    DWORD dwHeapForceFlagsOffset = IsWindowsVistaOrGreater()
        ? 0x44 
        : 0x10;
#else
    PPEB pPeb = (PPEB)__readgsqword(0x60);
    PVOID pHeapBase = (PVOID)(*(PDWORD_PTR)((PBYTE)pPeb + 0x30));
    DWORD dwHeapFlagsOffset = IsWindowsVistaOrGreater()
        ? 0x70 
        : 0x14;
    DWORD dwHeapForceFlagsOffset = IsWindowsVistaOrGreater()
        ? 0x74 
        : 0x18;
#endif // _WIN64

    PDWORD pdwHeapFlags = (PDWORD)((PBYTE)pHeapBase + dwHeapFlagsOffset);
    PDWORD pdwHeapForceFlags = (PDWORD)((PBYTE)pHeapBase + dwHeapForceFlagsOffset);
    return (*pdwHeapFlags & ~HEAP_GROWABLE) || (*pdwHeapForceFlags != 0);    
}

int main (int argc, char *argv[]) {

    if (__is_debugged())
        MessageBoxA(NULL, "[+] The process is attached to a Debugger.", "Anti-debug 042", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT attached to a Debugger.", "Anti-debug 042", MB_OK);

    return 0;
}
