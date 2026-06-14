#include <windows.h>
#include <stdio.h>
#include <winternl.h>

#define ProcessBreakOnTermination 0x1D

typedef NTSTATUS(NTAPI * TRtlSetProcessIsCritical)(
    IN BOOLEAN          bNew,
    OUT BOOLEAN *       pbOld,
    IN BOOLEAN          bNeedScb
    );

typedef NTSTATUS(NTAPI * TNtQueryInformationProcess)(
    IN HANDLE           ProcessHandle,
    IN DWORD            ProcessInformationClass,
    OUT PVOID           ProcessInformation,
    IN ULONG            ProcessInformationLength,
    OUT PULONG          ReturnLength
    );

BOOL __enable_se_debug_privilege(void) {
    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return FALSE;

    if (!LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &luid)) {
        CloseHandle(hToken);
        return FALSE;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    BOOL adjusted = AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
    // AdjustTokenPrivileges returns TRUE even when the privilege was not assigned;
    // GetLastError() reports ERROR_NOT_ALL_ASSIGNED in that case.
    adjusted = adjusted && (GetLastError() == ERROR_SUCCESS);

    CloseHandle(hToken);
    return adjusted;
}

BOOL __rtl_set_process_is_critical(void) {
    BOOL is_sandboxed = FALSE;

    // RtlSetProcessIsCritical requires SeDebugPrivilege to flip the
    // BreakOnTermination flag in the EPROCESS structure.
    __enable_se_debug_privilege();

    HMODULE hNtdll = LoadLibraryA("ntdll.dll");
    if (!hNtdll)
        return FALSE;

    TRtlSetProcessIsCritical pfnRtlSetProcessIsCritical =
        (TRtlSetProcessIsCritical)GetProcAddress(hNtdll, "RtlSetProcessIsCritical");
    TNtQueryInformationProcess pfnNtQueryInformationProcess =
        (TNtQueryInformationProcess)GetProcAddress(hNtdll, "NtQueryInformationProcess");

    if (!pfnRtlSetProcessIsCritical || !pfnNtQueryInformationProcess)
        return FALSE;

    // Mark this process as critical. Internally this calls
    // NtSetInformationProcess(ProcessBreakOnTermination, TRUE).
    NTSTATUS setStatus = pfnRtlSetProcessIsCritical(TRUE, NULL, FALSE);

    // Read the BreakOnTermination flag back to confirm it was really applied.
    ULONG breakOnTermination = 0;
    ULONG returnLength = 0;
    NTSTATUS queryStatus = pfnNtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessBreakOnTermination,
        &breakOnTermination,
        sizeof(breakOnTermination),
        &returnLength);

    // A sandbox commonly hooks RtlSetProcessIsCritical / NtSetInformationProcess
    // into a silent no-op that still returns STATUS_SUCCESS, so the host machine
    // cannot be forced to bugcheck. We detect that here: the set claimed success
    // but the critical flag did not actually get set.
    if (NT_SUCCESS(setStatus) && (!NT_SUCCESS(queryStatus) || breakOnTermination == 0))
        is_sandboxed = TRUE;

    // SAFETY: clear the critical flag before returning. While it is set, terminating
    // this process would bugcheck the machine (CRITICAL_PROCESS_DIED, 0xEF).
    pfnRtlSetProcessIsCritical(FALSE, NULL, FALSE);

    return is_sandboxed;
}

int main(void) {
    BOOL is_sandboxed = __rtl_set_process_is_critical();

    if (is_sandboxed) {
        MessageBoxA(NULL, "[+] The process is executing under a sandbox.", "RtlSetProcessIsCritical", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT executing under a sandbox.", "RtlSetProcessIsCritical", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
