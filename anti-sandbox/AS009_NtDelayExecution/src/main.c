#include <windows.h>
#include <winternl.h>
#include <stdbool.h>
#include <stdio.h>

typedef NTSTATUS(NTAPI * TNtDelayExecution)(
    IN BOOLEAN Alertable,
    IN PLARGE_INTEGER DelayInterval
);

bool __delay_execution(void) {
	// API to delay execution Sleep -> SleepEx -> NtDelayExecution.
    // It can be abused to timeout sandboxes
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)
	LARGE_INTEGER DelayInterval;
	LONGLONG llDelay = delay_in_millis * 10000LL;
	DelayInterval.QuadPart = -llDelay;

    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll) {
        TNtDelayExecution pfnNtDelayExecution = (TNtDelayExecution)GetProcAddress(hNtdll, "NtDelayExecution");
        if(pfnNtDelayExecution) {
            return NT_SUCCESS(pfnNtDelayExecution(FALSE, &DelayInterval));
        }
    }

    return false;
}

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS009_NtDelayExecution", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS009_NtDelayExecution", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
