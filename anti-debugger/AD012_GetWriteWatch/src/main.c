#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

const size_t PAGE_SIZE = 4096; 

const unsigned char SHELLCODE[] = {
#ifndef _WIN64
    0x55,                  // push ebp => x86 
#endif
    0x31, 0xC0, 0x50, 0x68, 0x63, 0x61, 0x6C, 0x63, 0x54, 0x59, 0x50, 0x40, 0x92, 0x74, 0x15, 0x51,
    0x64, 0x8B, 0x72, 0x2F, 0x8B, 0x76, 0x0C, 0x8B, 0x76, 0x0C, 0xAD, 0x8B, 0x30, 0x8B, 0x7E, 0x18,
    0xB2, 0x50, 0xEB, 0x1A, 0xB2, 0x60, 0x48, 0x29, 0xD4, 0x65, 0x48, 0x8B, 0x32, 0x48, 0x8B, 0x76,
    0x18, 0x48, 0x8B, 0x76, 0x10, 0x48, 0xAD, 0x48, 0x8B, 0x30, 0x48, 0x8B, 0x7E, 0x30, 0x03, 0x57,
    0x3C, 0x8B, 0x5C, 0x17, 0x28, 0x8B, 0x74, 0x1F, 0x20, 0x48, 0x01, 0xFE, 0x8B, 0x54, 0x1F, 0x24,
    0x0F, 0xB7, 0x2C, 0x17, 0x8D, 0x52, 0x02, 0xAD, 0x81, 0x3C, 0x07, 0x57, 0x69, 0x6E, 0x45, 0x75,
    0xEF, 0x8B, 0x74, 0x1F, 0x1C, 0x48, 0x01, 0xFE, 0x8B, 0x34, 0xAE, 0x48, 0x01, 0xF7, 0x99, 0xFF,
    0xD7,
#ifdef _WIN64
    0x48, 0x83, 0xC4, 0x78, // add rsp, 0x78 => x86_64
#else
    0x83, 0xC4, 0x08,	    // add esp, 8    => x86
    0x5D,                   // pop ebp
#endif
    0xC3                    // ret
};

DWORD WINAPI watchdog(LPVOID buffer) { 
    const int SIZE_TO_CHECK = 4096;

    PVOID* addresses = (PVOID*)VirtualAlloc(NULL, SIZE_TO_CHECK * sizeof(PVOID), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (addresses == NULL) {
        return false;
    }

    ULONG_PTR hits = SIZE_TO_CHECK;
    DWORD granularity;
    while(1) {
        if (GetWriteWatch(WRITE_WATCH_FLAG_RESET, buffer, PAGE_SIZE, addresses, &hits, &granularity) == 0) {
            if (hits == 1) {
                printf("[!] Buffer at %p got tampered!\n", buffer);
            }
        }
        hits = SIZE_TO_CHECK;
        Sleep(200);
    }
} 

int main() {
    char* buffer = (char *) VirtualAlloc(NULL, PAGE_SIZE, MEM_RESERVE | MEM_COMMIT | MEM_WRITE_WATCH, PAGE_EXECUTE_READWRITE);
    if (buffer == NULL) {
        return 1;
    }

    memcpy(buffer, SHELLCODE, sizeof(SHELLCODE));
   
    // https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-resetwritewatch
    ResetWriteWatch(buffer, PAGE_SIZE);

    DWORD tid = 0;
    // Starting watch dog
    HANDLE t_handle = CreateThread( 
        NULL,                   // default security attributes
        0,                      // use default stack size  
        watchdog,               // thread function name
        buffer,                 // argument to thread function 
        0,                      // use default creation flags 
        &tid                    // returns the thread identifier
    ); 

    if(t_handle == NULL) {
        printf("[!] Could not start watchdog thread.\n");
        VirtualFree(buffer, 0, MEM_RELEASE);
        return 1;
    }

    printf("[+] Watchdog thread (TID %ld) is running ...\n", tid);

    // Execute shellcode
    int (*func)();
    func = (int(*)()) buffer;
    (int)(*func)();

    while(1) Sleep(500);
    return 0;
}