#include <windows.h>
#include <stdbool.h>

#ifndef STATUS_HANDLE_NOT_CLOSABLE
#define STATUS_HANDLE_NOT_CLOSABLE ((DWORD)0xC0000235)
#endif

static bool DebuggerDetected = false;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_HANDLE_NOT_CLOSABLE) {
		DebuggerDetected = true;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

bool __is_debugged() {
	HANDLE hMutex;

	hMutex = CreateMutexA(NULL, false, "RandomMutex");
	if (hMutex) {
		SetHandleInformation(hMutex, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
		PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler);
		DebuggerDetected = false;
		CloseHandle(hMutex);
		RemoveVectoredExceptionHandler(Handle);
	}

	return DebuggerDetected;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 008", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 008", MB_OK);

    return 0;
}
