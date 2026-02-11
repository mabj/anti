#include <windows.h>
#include <winternl.h>
#include <stdbool.h>
#include <stdio.h>

typedef DWORD (WINAPI *TCsrGetProcessId)(VOID);

bool __is_debugged() { 
    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (!hNtdll)
        return false;
    
    TCsrGetProcessId pfnCsrGetProcessId = (TCsrGetProcessId)GetProcAddress(hNtdll, "CsrGetProcessId");
    if (!pfnCsrGetProcessId)
        return false;

    DWORD csrss_pid = pfnCsrGetProcessId();
    printf("[+] PID of csrss.exe is %lu\n", csrss_pid);
    HANDLE hCsr = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, csrss_pid);
    if (hCsr != NULL) {
        printf("[+] Managed to open the CSRSS.exe process.\n");
        CloseHandle(hCsr);
        return true;
    }

    return false;
}

int main (int argc, char *argv[]) {

    if (__is_debugged())
        MessageBoxA(NULL, "[+] The process is attached to a Debugger.", "Anti-debug 044", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT attached to a Debugger.", "Anti-debug 044", MB_OK);

    return 0;
}
