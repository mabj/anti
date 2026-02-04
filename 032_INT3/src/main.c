#include <windows.h>
#include <stdbool.h>
#include <intrin.h>


// Shamesly copied from the greatest: 
//      https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/Interrupt_3.cpp

static bool SwallowedException = true;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	SwallowedException = FALSE;
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT) {
		//Increase EIP/RIP to continue execution.
#ifdef _WIN64
		ExceptionInfo->ContextRecord->Rip++;
#else
		ExceptionInfo->ContextRecord->Eip++;
#endif
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

bool __is_debugged() {
    // Right way to go with __try/__excepts constructs from VS - directly setting VEH handlers.
	PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler); 
	SwallowedException = true;
	__debugbreak(); // INT3
	RemoveVectoredExceptionHandler(Handle);
	return SwallowedException;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 012", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 012", MB_OK);

    return 0;
}