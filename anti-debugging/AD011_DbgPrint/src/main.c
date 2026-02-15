/*  This technique does not work on Windows 10 64 bits
    Tryed DbgPrint, OutputDebugStringA OutputDebugStringW
    none of them raizes an exception when running under a debugger (x64dbg)
*/

#include <windows.h>
#include <stdbool.h>

#ifndef DBG_PRINTEXCEPTION_C
#define DBG_PRINTEXCEPTION_C ((DWORD)0x40010006)
#endif

static bool ExceptionCaught = false;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == DBG_PRINTEXCEPTION_C) {
		ExceptionCaught = true;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

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

    PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler);
    ExceptionCaught = false;
    pDbgPrint("anti-debug 020");
    RemoveVectoredExceptionHandler(Handle);

    FreeLibrary(hNtdll);
    // If exception was caught, no debugger is present
    // If debugger swallowed the exception, debugger is present
    return !ExceptionCaught;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 020", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 020", MB_OK);

    return 0;
}
