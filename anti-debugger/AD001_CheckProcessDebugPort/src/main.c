// @marcos_alvares
// build with "cl.exe main.c /link ntdll.dll"

#include <windows.h>
#include <winternl.h>

int main (int argc, char *argv[]) {
    NTSTATUS status;
    DWORD debug_port = 0;

    status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessDebugPort,
        &debug_port,
        sizeof(debug_port),
        NULL);

    if (status == 0x00000000 && debug_port != 0)
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 006", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 006", MB_OK);

    return 0;
}
