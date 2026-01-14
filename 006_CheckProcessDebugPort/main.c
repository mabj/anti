// @marcos_alvares
// build with "cl.exe main.c /link ntdll.dll"

#include <windows.h>
#include <stdlib.h>
#include <winternl.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    NTSTATUS status;
    DWORD debug_port = 0;

    status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessDebugPort,
        &debug_port,
        sizeof(debug_port),
        NULL);

    if (status == 0x00000000 && debug_port != 0) {
        printf("[+] Debugger has been detected.\n");
        return 0;
    }
    return 0;
}
