#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <tlhelp32.h>

// TODO: Implement API patch detection for debugger detection
BOOL __is_debugged(void) {
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    if (!hKernel32)
        return false;

    FARPROC pIsDebuggerPresent = GetProcAddress(hKernel32, "IsDebuggerPresent");
    if (!pIsDebuggerPresent)
        return false;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot)
        return false;

    PROCESSENTRY32W ProcessEntry;
    ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hSnapshot, &ProcessEntry))
        return false;

    bool bDebuggerPresent = false;
    HANDLE hProcess = NULL;
    DWORD dwFuncBytes = 0;
    const DWORD dwCurrentPID = GetCurrentProcessId();
    do {
        if (dwCurrentPID == ProcessEntry.th32ProcessID)
            continue;

        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
        if (NULL == hProcess)
            continue;

        if (!ReadProcessMemory(hProcess, pIsDebuggerPresent, &dwFuncBytes, sizeof(DWORD), NULL))
            continue;

        if (dwFuncBytes != *(PDWORD)pIsDebuggerPresent)
        {
            bDebuggerPresent = true;
            break;
        }
        if (hProcess)
            CloseHandle(hProcess);

    } while (Process32NextW(hSnapshot, &ProcessEntry));


    if (hSnapshot)
        CloseHandle(hSnapshot);
    return bDebuggerPresent;
}

int main(void) {
    BOOL debugger_present = __is_debugged();

    if (debugger_present) {
        MessageBox(NULL, "[+] The process is in Debug mode.", "AD049_DetectAPIPatch", MB_OK | MB_ICONWARNING);
    } else {
        MessageBox(NULL, "[+] The process is NOT in Debug mode.", "AD049_DetectAPIPatch", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
