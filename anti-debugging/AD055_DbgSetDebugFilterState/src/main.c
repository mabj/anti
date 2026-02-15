#include <windows.h>
#include <stdbool.h>
#include <winternl.h>
#include <stdio.h>


typedef NTSTATUS(NTAPI * TNtSetDebugFilterState)(
    IN ULONG ComponentId,
    IN ULONG Level,
    IN BOOLEAN State
);

/**
 * AD055 - DbgSetDebugFilterState
 *
 * Anti-debugging technique using DbgSetDebugFilterState.
 */

bool __is_debugged(void) {
    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll) {
        TNtSetDebugFilterState pfnNtSetDebugFilterState = (TNtSetDebugFilterState)GetProcAddress(hNtdll, "NtSetDebugFilterState");
        if(pfnNtSetDebugFilterState) {
            return NT_SUCCESS(pfnNtSetDebugFilterState(0, 0, TRUE));
        }
    }

    return false;
}

int main(void) {
    if (__is_debugged()) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "AD055", MB_OK);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "AD055", MB_OK);
    }

    return 0;
}
