#include <windows.h>
#include <stdbool.h>
#include <intrin.h>

// Forward declare PEB structure
typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[21];
} PEB, *PPEB;

bool __is_debugged() {
    // Get PEB address via TEB
#ifdef _WIN64
    PPEB pPeb = (PPEB)__readgsqword(0x60);
#else
    PPEB pPeb = (PPEB)__readfsdword(0x30);
#endif

    if (!pPeb) {
        // Handle error - couldn't get PEB address
        return false;
    }

    // Access BeingDebugged flag through PEB struct
    return pPeb->BeingDebugged != 0;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 012", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 012", MB_OK);

    return 0;
}