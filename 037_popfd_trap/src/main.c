#include <windows.h>
#include <stdbool.h>
#include <intrin.h>

static bool SwallowedException = true;

static LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
	SwallowedException = FALSE;
	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
		//Increase EIP/RIP to continue execution.
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

	PBYTE shellcode = (PBYTE) VirtualAlloc(NULL, si.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	shellcode[0] = '\x9C'; // pushfd
    shellcode[1] = '\xC7'; // mov dword ptr [esp], 0x100
	shellcode[2] = '\x04';
	shellcode[3] = '\x24';
	shellcode[4] = '\x00';
	shellcode[5] = '\x01';
	shellcode[6] = '\x00';
	shellcode[7] = '\x00';
    shellcode[8] = '\x9D'; // popfd
    shellcode[9] = '\x90'; // nop
    shellcode[10] = '\xC3'; // ret


	void (*foo)() = (void(*)())shellcode;
	foo();
	
	RemoveVectoredExceptionHandler(Handle);

	VirtualFree(shellcode, si.dwPageSize, MEM_FREE);
	return SwallowedException;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 035", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 035", MB_OK);

    return 0;
}