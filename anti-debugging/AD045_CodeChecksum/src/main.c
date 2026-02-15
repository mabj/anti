#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _WATCHDOG_PARAM {
    PBYTE addr;
    unsigned int _size;
    DWORD32 checksum;
} WATCHDOG_PARAM, *PWATCHDOG_PARAM;

DWORD32 crc32(PBYTE data, int size) {
    DWORD32 r = ~0; byte *end = data + size;

    while(data < end) {
        r ^= *data++;
        for(int i = 0; i < 8; i++) {
            u_int t = ~((r&1) - 1); 
            r = (r>>1) ^ (0xEDB88320 & t);
        }
    }
    return ~r;
}

size_t __calculate_function_size(PBYTE pMem) {
    size_t nFuncSize = 0;
    do {
        ++nFuncSize;
    } while (*(pMem++) != 0xC3);
    return nFuncSize;
}

void my_protected_function() {
    while(true) {
        printf("[+] Looping inside protected function.\n");
        Sleep(500 + rand() % 1000);
    }
}

static DWORD WINAPI _watchdog(LPVOID lpThreadParameter) {
    PWATCHDOG_PARAM wd_param = (PWATCHDOG_PARAM) lpThreadParameter;

    while (true) {
        if (crc32(wd_param->addr, wd_param->_size) != wd_param->checksum) {
            printf("[+] Tampering DETECTED!\n");
            ExitProcess(0);
        }
        Sleep(300);
    }
    return 0;
}

bool __is_debugged() {
    WATCHDOG_PARAM wp;
    
    wp.addr = (PBYTE)my_protected_function;
    wp._size = __calculate_function_size((PBYTE)my_protected_function);
    wp.checksum = crc32(wp.addr, wp._size);

    printf("[+] Protected function 0x%p (size %d bytes) has checksum %#x\n", wp.addr, wp._size, wp.checksum);

    // Starting watchdog thread
    DWORD tid = 0;
    HANDLE t_handle = CreateThread( 
        NULL,                       // default security attributes
        0,                          // use default stack size  
        _watchdog,                  // thread function name
        &wp,                        // argument to thread function 
        0,                          // use default creation flags 
        &tid                        // returns the thread identifier
    ); 

    if(t_handle == NULL) {
        printf("[!] Could not start watchdog thread.\n");
        return false;
    }

    // If any breakpoint is set in this function's code the whole process 
    // terminates
    my_protected_function();

    return true;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 045", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 045", MB_OK);

    return 0;
}
