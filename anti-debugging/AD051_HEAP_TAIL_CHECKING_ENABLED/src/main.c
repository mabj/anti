#include <windows.h>
#include <stdbool.h>


// https://unprotect.it/technique/heap-flag/
// https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-heap-protection
BOOL __is_debugged(void) {
    PROCESS_HEAP_ENTRY HeapEntry = { 0 };
    do {
        if (!HeapWalk(GetProcessHeap(), &HeapEntry))
            return false;
    } while (HeapEntry.wFlags != PROCESS_HEAP_ENTRY_BUSY);

    PVOID pOverlapped = (PBYTE)HeapEntry.lpData + HeapEntry.cbData;
    return ((DWORD)(*(PDWORD)pOverlapped) == 0xABABABAB);
}

int main(void) {
    BOOL debugger_present = __is_debugged();

    if (debugger_present) {
        MessageBox(NULL, "[+] The process is in Debug mode.", "AD051_HEAP_TAIL_CHECKING_ENABLED", MB_OK | MB_ICONWARNING);
    } else {
        MessageBox(NULL, "[+] The process is NOT in Debug mode.", "AD051_HEAP_TAIL_CHECKING_ENABLED", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
