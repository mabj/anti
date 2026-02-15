#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

bool __is_debugged(void) {
    bool is_traced = false;

#ifdef _WIN64
    __asm__ volatile goto
    (
        "mov ax, ss\n\t"
        "push rax\n\t"            // ; Push SS (zero-extended)
        "pop rax\n\t"
        "mov ss, ax\n\t"          // ; Manually reloading SS to trigger the "trap inhibit"

        //; --- Flag check ---
        "pushfq\n\t"              // ; Push RFLAGS (64-bit version of PUSHF)
        
        //; In 64-bit, RFLAGS is 8 bytes. 
        // ; The Trap Flag (TF) is bit 8. 
        // ; This is located in the second byte (bits 8-15) of the pushed value.
        "test byte ptr [rsp+1], 1\n\t" 
        
        "jz %l[not_being_debugged]\n\t"       //; Logic check: if TF is set, we are being stepped
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
        : not_being_debugged                  // Label operands
    );
#else
    __asm__ volatile goto
    (
        "push ss\n\t"
        "pop ss\n\t"
        "pushf\n\t"
        "test byte ptr [esp+1], 1\n\t"
        "jz %l[not_being_debugged]\n\t"
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
        : not_being_debugged                  // Label operands
    );
#endif

    is_traced = true;

not_being_debugged:

#ifdef _WIN64
    __asm__ volatile
    (
        "popfq\n\t"
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
    );
#else
    __asm__ volatile
    (
        "popf\n\t"
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
    );
#endif
    return is_traced;
}

int main(void)
{
    if (__is_debugged()) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "AD053 - StackSegment", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "AD053 - StackSegment", MB_OK | MB_ICONINFORMATION);
    }
    return 0;
}
