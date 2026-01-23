#include <windows.h>
#include <stdbool.h>
#include <winternl.h>
#include "ntrtl.h"

bool __is_debugged() {
    PRTL_DEBUG_INFORMATION pDebugBuffer = (PRTL_DEBUG_INFORMATION)RtlCreateQueryDebugBuffer(0, FALSE);
    
    if (!SUCCEEDED(RtlQueryProcessDebugInformation(GetCurrentProcessId(), PDI_HEAPS | PDI_HEAP_BLOCKS, pDebugBuffer)))
        return false;

    ULONG dwFlags = ((PRTL_PROCESS_HEAPS)pDebugBuffer->HeapInformation)->Heaps[0].Flags;
    return dwFlags & ~HEAP_GROWABLE;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 017", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 017", MB_OK);

    return 0;
}