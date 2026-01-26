#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

bool __is_debugged() {
    // Check DR0-7 via GetThreadContext API

    HANDLE t_handle = GetCurrentThread();
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if(GetThreadContext(t_handle, &ctx)) {
        printf("[+] Dr0 = %d\n", (unsigned int)ctx.Dr0);
        printf("[+] Dr1 = %d\n", (unsigned int)ctx.Dr1);
        printf("[+] Dr2 = %d\n", (unsigned int)ctx.Dr2);
        printf("[+] Dr3 = %d\n", (unsigned int)ctx.Dr3);
        printf("[+] Dr6 = %d\n", (unsigned int)ctx.Dr6);
        printf("[+] Dr7 = %d\n", (unsigned int)ctx.Dr7);
        return (ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3 || ctx.Dr6 || ctx.Dr7);
    }

    return false;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 022", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 022", MB_OK);

    return 0;
}