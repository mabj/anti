#include <windows.h>
#include <stdbool.h>

// This technique only works on Ollydbg or ImunityDBG (not on x64dbg)
typedef void(*FUN)();

bool __is_debugged() {
    DWORD dwOldProtect = 0;
    SYSTEM_INFO SysInfo = { 0 };

    GetSystemInfo(&SysInfo);
    PVOID pPage = VirtualAlloc(NULL, SysInfo.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE); 
    if (NULL == pPage)
        return false; 

    PBYTE pMem = (PBYTE)pPage;
    *pMem = 0xC3; 

    // Make the page a guard page         
    if (!VirtualProtect(pPage, SysInfo.dwPageSize, PAGE_EXECUTE_READWRITE | PAGE_GUARD, &dwOldProtect))
        return false;

    __try {
        ((FUN)pPage)();
    }
    __except(GetExceptionCode() == STATUS_GUARD_PAGE_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) { 
        VirtualFree(pPage, 0, MEM_RELEASE);
        return false;
    }

    VirtualFree(pPage, 0, MEM_RELEASE);
    return true;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 025", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 025", MB_OK);

    return 0;
}