#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DELAY_MS 200

typedef struct _WATCHED_FUNCTION {
    PVOID addr;
    char* name;
    unsigned int _size;
} WATCHED_FUNCTION, *PWATCHED_FUNCTION;

typedef struct _MEMORY_WATCHDOG_PARAM {
    BYTE pattern;
    unsigned int number_of_watched;
    PWATCHED_FUNCTION functions;
} MEMORY_WATCHDOG_PARAM, *PMEMORY_WATCHDOG_PARAM;

bool __is_pattern_inside_function(BYTE pattern, PVOID func_addr, unsigned int func_size) {
    PBYTE func_addr_bytes = (PBYTE)func_addr; 
    for (SIZE_T i = 0; ; i++)
    {
        // Break on RET (0xC3) if we don't know the function's size
        if (((func_size > 0) && (i >= func_size)) ||
            ((func_size == 0) && (func_addr_bytes[i] == 0xC3)))
            break;

        if (func_addr_bytes[i] == (BYTE)pattern)
            return true;
    }
    return false;
}

DWORD WINAPI memory_breakpoint_watchdog(LPVOID param) {
    PMEMORY_WATCHDOG_PARAM wd_param = (PMEMORY_WATCHDOG_PARAM) param;

    while(true) {
        for(unsigned int i=0; i < wd_param->number_of_watched; i++ ) {
            WATCHED_FUNCTION wf = wd_param->functions[i];
            if(__is_pattern_inside_function(wd_param->pattern, wf.addr, wf._size)) {
                printf("[!] Found breakpoint inside %s (%p)!\n", wf.name, wf.addr);
            }

        }
        Sleep(DELAY_MS);
    }
}

void func_01() {
    for (int i = 0; i < rand() % 20; i++) {
        Sleep(1000);
    }
}

void func_02() {
    for (int i = 0; i < rand() % 5; i++) {
        Sleep(500);
    }
}

void func_03() {
    for (int i = 0; i < rand() % 15; i++) {
        Sleep(300);
    }
}

bool __is_debugged() {

    MEMORY_WATCHDOG_PARAM m_wd;
    
    m_wd.number_of_watched = 3;
    m_wd.pattern = 0xCC; // INT3
    m_wd.functions = (PWATCHED_FUNCTION)VirtualAlloc( NULL, sizeof(WATCHED_FUNCTION) * 3, MEM_COMMIT, PAGE_READWRITE);
    m_wd.functions[0].addr = func_01;
    m_wd.functions[0].name = "func_01";
    m_wd.functions[0]._size = 0;
    m_wd.functions[1].addr = func_02;
    m_wd.functions[1].name = "func_02";
    m_wd.functions[1]._size = 0;
    m_wd.functions[2].addr = func_03;
    m_wd.functions[2].name = "func_03";
    m_wd.functions[2]._size = 0;

    // Starting watchdog thread
    DWORD tid = 0;
    HANDLE t_handle = CreateThread( 
        NULL,                       // default security attributes
        0,                          // use default stack size  
        memory_breakpoint_watchdog, // thread function name
        &m_wd,                      // argument to thread function 
        0,                          // use default creation flags 
        &tid                        // returns the thread identifier
    ); 

    if(t_handle == NULL) {
        printf("[!] Could not start watchdog thread.\n");
        return false;
    }

    printf("[+] Watchdog thread (TID %ld) is running ...\n", tid);
    // Iterating through watched functions

    while(TRUE) {
        func_01();
        func_02();
        func_03();
    }

}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 022", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 022", MB_OK);

    return 0;
}