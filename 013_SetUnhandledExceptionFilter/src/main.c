#include <windows.h>
#include <stdbool.h>

// If Debug is active this handler will not get executed and INT3 will be 
// captured by the debugger as a breakpoint.
LONG unhandled_exception_filter(PEXCEPTION_POINTERS pExceptionInfo) {
    PCONTEXT ctx = pExceptionInfo->ContextRecord;
    #if defined(__x86_64__)
        ctx->Rip += 3; // Skip \xCC\xEB\x??
    #else
        ctx->Eip += 3; // Skip \xCC\xEB\x??
    #endif
    return EXCEPTION_CONTINUE_EXECUTION;
}

// https://wiki.osdev.org/Inline_Assembly
bool __is_debugged() {
    __asm__ volatile goto
    (
        "INT 3\n\t"                        // CC
        "JMP %l[being_debugged]\n\t"      // EB ??  
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
        : being_debugged                  // Label operands
    );

    return false;

being_debugged:
    return true;
}

int main() {
    if (!SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)unhandled_exception_filter)) {
        MessageBoxA(NULL, "[!] Could not set Unhandled Exception Filter", "Anti-debug 001", MB_OK);
        return -1;
    }

    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 001", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 001", MB_OK);

    return 0;
}