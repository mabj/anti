#include <windows.h>
#include <stdbool.h>

#ifndef DBG_CONTROL_C
#define DBG_CONTROL_C ((DWORD)0x40010005)
#endif

static bool ExceptionCaught = false;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == DBG_CONTROL_C) {
		ExceptionCaught = true;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

bool __is_debugged() {
	PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler);
	ExceptionCaught = false;
	RaiseException(DBG_CONTROL_C, 0, 0, NULL);
	RemoveVectoredExceptionHandler(Handle);
	// If exception was caught by our handler, no debugger is present
	// If debugger intercepted the exception, debugger is present
	return !ExceptionCaught;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 025", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 025", MB_OK);

    return 0;
}
