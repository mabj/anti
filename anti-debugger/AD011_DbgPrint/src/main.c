/*  This technique does not work on Windows 10 64 bits
    Tryed DbgPrint, OutputDebugStringA OutputDebugStringW
    none of them raizes an exception when running under a debugger (x64dbg)
*/

#include <windows.h>
#include <stdbool.h>
#include <winternl.h>

bool __is_debugged() {
    // Declare DbgPrint as a function pointer
    typedef ULONG (__cdecl *DbgPrintPtr)(PCSTR Format, ...);
    
    // Resolve DbgPrint from ntdll.dll
    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (!hNtdll) {
        return false;
    }
    
    DbgPrintPtr pDbgPrint = (DbgPrintPtr)GetProcAddress(hNtdll, "DbgPrint");
    if (!pDbgPrint) {
        FreeLibrary(hNtdll);
        return false;
    }
    
    bool result = true;
    __try {
        pDbgPrint("anti-debug 020");
    }
    __except(GetExceptionCode() == DBG_PRINTEXCEPTION_C) {
        result = false;
    }
    
    FreeLibrary(hNtdll);
    return result;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 020", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 020", MB_OK);

    return 0;
}