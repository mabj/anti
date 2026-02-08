#include <windows.h>
#include <winternl.h>
#include <stdbool.h>

#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

bool __is_debugged() { 
    #ifndef _WIN64
        PPEB pPeb = (PPEB)__readfsdword(0x30);
        DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + 0x68);
    #else
        PPEB pPeb = (PPEB)__readgsqword(0x60);
        DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + 0xBC);
    #endif // _WIN64
    
    return (dwNtGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED);    
}

int main (int argc, char *argv[]) {

    if (__is_debugged())
        MessageBoxA(NULL, "[+] The process was created by Debugger.", "Anti-debug 041", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process was not created by Debugger.", "Anti-debug 041", MB_OK);

    return 0;
}
