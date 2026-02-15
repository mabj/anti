#include <windows.h>
#include <winternl.h>
#include <stdbool.h>

bool __is_debugged() {
    NTSTATUS status;
    DWORD debug_port = 0;

    status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessDebugPort,
        &debug_port,
        sizeof(debug_port),
        NULL);
    
    return status == 0x00000000 && debug_port != 0;
}

int main (int argc, char *argv[]) {

    if (__is_debugged())
        MessageBoxA(NULL, "[+] The process is attached to Debugger.", "Anti-debug 040", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT attached to Debugger.", "Anti-debug 040", MB_OK);

    return 0;
}
