#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <intrin.h>

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

	SYSTEM_INFO si;
    GetSystemInfo(&si);

	PBYTE shellcode = (PBYTE) VirtualAlloc(
		NULL,
		si.dwPageSize,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);

	if(!shellcode) {
		printf("[!] Could not allocate memory to INT2D shellcode.\n");
		return false;
	}

	#ifdef _WIN64
		shellcode[0] = '\x48'; // XOR rax, rax
		shellcode[1] = '\x31';
		shellcode[2] = '\xC0';
	#else
		shellcode[0] = '\x31'; // XOR eax, eax
		shellcode[1] = '\xC0';
		shellcode[2] = '\x90'; // NOP
	#endif
	shellcode[3] = '\xCD'; // INT 0x2D
	shellcode[4] = '\x2D';
	shellcode[5] = '\x90'; // NOP
	shellcode[6] = '\xC3'; //ret

	void (*foo)() = (void(*)())shellcode;
	foo();
	
	RemoveVectoredExceptionHandler(Handle);

	VirtualFree(shellcode, si.dwPageSize, MEM_FREE);
	return SwallowedException;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 034", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 034", MB_OK);

    return 0;
}