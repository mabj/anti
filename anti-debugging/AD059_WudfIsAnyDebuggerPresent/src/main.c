#include <windows.h>
#include <stdio.h>

// Define a function pointer signature matching the API
typedef BOOL (WINAPI *WudfIsAnyDebuggerPresentPtr)(VOID);

BOOL __wudf_is_any_debugger_present(void) {
    BOOL is_debugged = FALSE;

    // Load the library where the UMDF platform functions reside
    HMODULE hWudf = LoadLibraryA("WudfPlatform.dll");
    
    if (hWudf == NULL) {
        printf("UMDF Platform library not found. (Not a driver host or WDK not installed).\n");
        return 1;
    }

    // Locate the specific function
    WudfIsAnyDebuggerPresentPtr WudfIsAnyDebuggerPresent = 
        (WudfIsAnyDebuggerPresentPtr)GetProcAddress(hWudf, "WudfIsAnyDebuggerPresent");

    if (WudfIsAnyDebuggerPresent != NULL) {
        // Call the API
        if (WudfIsAnyDebuggerPresent()) {
            is_debugged = TRUE;
        } else {
            printf("[!] No debugger detected via UMDF API.\n");
        }
    } else {
        printf("[!] Could not locate WudfIsAnyDebuggerPresent in the DLL.\n");
    }

    FreeLibrary(hWudf);

    return is_debugged;
}

int main(void) {
    BOOL is_debugged = __wudf_is_any_debugger_present();

    if (is_debugged) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "WudfIsAnyDebuggerPresent", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "WudfIsAnyDebuggerPresent", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
