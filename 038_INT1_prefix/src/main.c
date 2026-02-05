#include <windows.h>
#include <stdbool.h>
#include <intrin.h>

static bool SwallowedException = true;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	SwallowedException = FALSE;
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

bool __is_debugged() {
    // Right way to go with __try/__excepts constructs from VS - directly setting VEH handlers.
	PVOID Handle = AddVectoredExceptionHandler(1, VectoredHandler); 
	SwallowedException = true;

	SYSTEM_INFO si;
    GetSystemInfo(&si);

	PBYTE shellcode = (PBYTE) VirtualAlloc(
		NULL,
		si.dwPageSize,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);

	shellcode[0] = '\xF3'; // INT 0x1 (ICEBP with Prefix) 
	shellcode[1] = '\x64';
	shellcode[2] = '\xF1';
	shellcode[3] = '\xC3'; // ret

	void (*foo)() = (void(*)())shellcode;
	foo();
	
	RemoveVectoredExceptionHandler(Handle);

	VirtualFree(shellcode, si.dwPageSize, MEM_FREE);
	return SwallowedException;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 038", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 038", MB_OK);

    return 0;
}