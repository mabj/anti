#include <windows.h>
#include <stdbool.h>
#include <winternl.h>

typedef NTSTATUS(NTAPI * TNtQueryInformationProcess)(
    IN HANDLE           ProcessHandle,
    IN DWORD            ProcessInformationClass,
    OUT PVOID           ProcessInformation,
    IN ULONG            ProcessInformationLength,
    OUT PULONG          ReturnLength
    );

bool __is_debugged() {
    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (hNtdll) {
        TNtQueryInformationProcess pfnNtQueryInformationProcess = (TNtQueryInformationProcess)GetProcAddress(
            hNtdll, "NtQueryInformationProcess");
        MessageBoxA(NULL, "[+] AQUI 1.", "Anti-debug 011", MB_OK);

        if (pfnNtQueryInformationProcess) {
            MessageBoxA(NULL, "[+] AQUI 2.", "Anti-debug 011", MB_OK);
            DWORD dwReturned;
            HANDLE hProcessDebugObject = 0;
            const DWORD ProcessDebugObjectHandle = 0x1e;
            NTSTATUS status = pfnNtQueryInformationProcess(
                GetCurrentProcess(),
                ProcessDebugObjectHandle,
                &hProcessDebugObject,
                sizeof(HANDLE),
                &dwReturned);
    

            MessageBoxA(NULL, "[+] AQUI 3.", "Anti-debug 011", MB_OK);
            if (NT_SUCCESS(status) && (0 != hProcessDebugObject))
                return true;
        }
    }
    return false;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 011", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 011", MB_OK);

    return 0;
}