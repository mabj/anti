#include <windows.h>
#include <stdbool.h>

// This technique only works on Ollydbg or ImunityDBG (not on x64dbg)
typedef void(*FUN)();

static bool ExceptionCaught = false;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION) {
		ExceptionCaught = true;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

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

    PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler);
    ExceptionCaught = false;
    ((FUN)pPage)();
    RemoveVectoredExceptionHandler(Handle);

    VirtualFree(pPage, 0, MEM_RELEASE);
    // If exception was caught, no debugger is present
    // If debugger suppressed the exception, debugger is present
    return !ExceptionCaught;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 019", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 019", MB_OK);

    return 0;
}
