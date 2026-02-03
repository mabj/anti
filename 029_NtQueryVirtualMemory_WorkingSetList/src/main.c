#include <windows.h>
#include <stdbool.h>
#include <winternl.h>
#include <stdio.h>

#include "ntrtl.h"

bool __is_debugged() {
    NTSTATUS status;
    PBYTE pMem = NULL;
    DWORD dwMemSize = 0;

    do {
        dwMemSize += 0x1000;
        pMem = (PBYTE)_malloca(dwMemSize);
        if (!pMem){
            printf("[!] Error when allocating memory.\n");
            return false;

        }

        memset(pMem, 0, dwMemSize);
        status = NtQueryVirtualMemory(
            GetCurrentProcess(), 
            NULL, 
            MemoryWorkingSetList, 
            pMem, 
            dwMemSize, 
            NULL);

        // if (!VirtualFree(pMem, dwMemSize, MEM_RELEASE)) {
        //     printf("[!] Error when allocating memory.\n");
        //     return false;
        // }
    } while ((unsigned int)status == STATUS_INFO_LENGTH_MISMATCH);

    #ifdef _DEBUG
        printf("[+] Alloated %ld Bytes to MemoryWorkingSet!\n\n", dwMemSize);
    #endif

    PMEMORY_WORKING_SET_LIST pWorkingSet = (PMEMORY_WORKING_SET_LIST)pMem;
    
    for (ULONG i = 0; i < pWorkingSet->NumberOfPages; i++) {
        size_t dwAddr = (pWorkingSet->WorkingSetList[i].VirtualPage << 0x0C) & 0xFFFFF000;
        size_t current_func_addr = ((size_t)(void *)__is_debugged) & 0xFFFFF000;
        #ifdef _DEBUG
            #ifdef _WIN64
                printf("[+] Inspecting VirtualPage %#llx - current function addr %#llx\n", dwAddr, current_func_addr);
            #else
                printf("[+] Inspecting VirtualPage %#x - current function addr %#x\n", dwAddr, current_func_addr);
            #endif
        #endif
        if (dwAddr == current_func_addr) {
            printf("[+] Shared: %d   ShareCount: %d\n", pWorkingSet->WorkingSetList[i].Shared, pWorkingSet->WorkingSetList[i].ShareCount);
            return (pWorkingSet->WorkingSetList[i].Shared == 0) || (pWorkingSet->WorkingSetList[i].ShareCount == 0);
        }
    }

    return false;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 029", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 029", MB_OK);

    return 0;
}