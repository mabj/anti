#include <windows.h>
#include <stdio.h>

VOID NTAPI __tls_callback(PVOID DllHandle, DWORD Reason, PVOID Reserved) {
    printf("[+] Inside TLS callback body\n");
}

// For MinGW/GCC: Use __attribute__ to place callback in .CRT$XLB section
#ifdef _WIN64
PIMAGE_TLS_CALLBACK p_tls_callback __attribute__((section(".CRT$XLB"))) = __tls_callback;
#else
PIMAGE_TLS_CALLBACK p_tls_callback __attribute__((section(".CRT$XLB"))) = __tls_callback;
#endif

int main(void)
{
    MessageBoxA(NULL, "[+] Main function executed.", "TLS Callback", MB_OK | MB_ICONINFORMATION);
    return 0;
}
