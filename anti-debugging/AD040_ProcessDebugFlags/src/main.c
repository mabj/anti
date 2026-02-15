#include <windows.h>
#include <winternl.h>
#include <stdbool.h>

bool __is_debugged() {
    NTSTATUS status;

    DWORD dwProcessDebugFlags;
    const DWORD ProcessDebugFlags = 0x1f;

    status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessDebugFlags,
        &dwProcessDebugFlags,
        sizeof(DWORD),
        NULL
    );

    return NT_SUCCESS(status) && (0 == dwProcessDebugFlags); 
}

int main (int argc, char *argv[]) {

    if (__is_debugged())
        MessageBoxA(NULL, "[+] The process is attached to Debugger.", "Anti-debug 040", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT attached to Debugger.", "Anti-debug 040", MB_OK);

    return 0;
}
