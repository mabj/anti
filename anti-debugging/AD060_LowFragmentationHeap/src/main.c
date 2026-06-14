#include <windows.h>
#include <stdio.h>

// HeapCompatibilityInformation class value (defined in MinGW-w64 headers;
// guard kept in case of an older SDK).
#ifndef HeapCompatibilityInformation
#define HeapCompatibilityInformation 0
#endif

// Detect a debugger via the Low Fragmentation Heap (LFH).
//
// On modern Windows the default process heap uses the LFH front-end allocator.
// When a process is launched under a debugger, ntdll creates the debug heap
// (driven by the PEB BeingDebugged / NtGlobalFlag heap flags), which refuses to
// switch to the LFH. So if LFH cannot be activated, a debug heap is present.
BOOL __is_debugged_lfh(void) {
    HANDLE hHeap    = GetProcessHeap();
    ULONG  lfh      = 2;   // 2 = Low Fragmentation Heap
    ULONG  mode     = 0;
    SIZE_T returned = 0;

    // Ask the process heap to switch to the LFH front-end allocator.
    // Under a debugger the debug heap silently refuses this.
    HeapSetInformation(hHeap, HeapCompatibilityInformation, &lfh, sizeof(lfh));

    // Read back the heap's actual compatibility mode.
    if (HeapQueryInformation(hHeap, HeapCompatibilityInformation,
                             &mode, sizeof(mode), &returned)) {
        // 0 = standard, 1 = look-aside list, 2 = LFH active.
        if (mode != 2) {
            // LFH not active -> debug heap interfered.
            return TRUE;
        }
        printf("[!] LFH active (compatibility flag = %lu). No debugger.\n", mode);
    } else {
        printf("[!] HeapQueryInformation failed: %lu\n", (unsigned long)GetLastError());
    }

    // Note: bypassable by attaching to the process after it has started, since
    // the debug heap is only selected at process creation.
    return FALSE;
}

int main(void) {
    BOOL is_debugged = __is_debugged_lfh();

    if (is_debugged) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "LowFragmentationHeap", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "LowFragmentationHeap", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
