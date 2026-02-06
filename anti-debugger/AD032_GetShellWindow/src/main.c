#include <windows.h>
#include <stdbool.h>
#include <winternl.h>

typedef struct _PROCESS_BASIC_INFORMATION_CUSTOM
{
    NTSTATUS ExitStatus;                    // The exit status of the process. (GetExitCodeProcess)
    PPEB PebBaseAddress;                    // A pointer to the process environment block (PEB) of the process.
    KAFFINITY AffinityMask;                 // The affinity mask of the process. (GetProcessAffinityMask) (deprecated)
    KPRIORITY BasePriority;                 // The base priority of the process. (GetPriorityClass)
    HANDLE UniqueProcessId;                 // The unique identifier of the process. (GetProcessId)
    HANDLE InheritedFromUniqueProcessId;    // The unique identifier of the parent process.
} PROCESS_BASIC_INFORMATION_CUSTOM, *PPROCESS_BASIC_INFORMATION_CUSTOM;

bool __is_debugged() {
    HWND hExplorerWnd = GetShellWindow();
    if (!hExplorerWnd)
        return false;

    DWORD dwExplorerProcessId;
    GetWindowThreadProcessId(hExplorerWnd, &dwExplorerProcessId);

    PROCESS_BASIC_INFORMATION_CUSTOM ProcessInfo;
    NTSTATUS status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessBasicInformation,
        &ProcessInfo,
        sizeof(ProcessInfo),
        NULL);
    if (!NT_SUCCESS(status))
        return false;

    return (DWORD)ProcessInfo.InheritedFromUniqueProcessId != dwExplorerProcessId;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 032", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 032", MB_OK);

    return 0;
}