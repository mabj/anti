#include <windows.h>
#include <stdbool.h>

static bool DebuggerDetected = false;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_INVALID_HANDLE) {
		DebuggerDetected = true;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

bool __is_debugged() {
	PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler);
	DebuggerDetected = false;
	CloseHandle((HANDLE)(ULONG_PTR)0xDEADBEEF);
	RemoveVectoredExceptionHandler(Handle);
	return DebuggerDetected;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 007", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 007", MB_OK);

    return 0;
}
