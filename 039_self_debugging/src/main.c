#include <windows.h>
#include <stdbool.h>
#include <intrin.h>
#include <stdio.h>

#define EVENT_SELFDBG_EVENT_NAME L"SelfDebugging"

bool __run_second_stage() {
    WCHAR wszFilePath[MAX_PATH], wszCmdLine[MAX_PATH];
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    HANDLE hDbgEvent;

    hDbgEvent = CreateEventW(NULL, FALSE, FALSE, EVENT_SELFDBG_EVENT_NAME);
    if (!hDbgEvent)
        return false;

    if (!GetModuleFileNameW(NULL, wszFilePath, _countof(wszFilePath)))
        return false;

    swprintf_s(wszCmdLine, MAX_PATH, L"%ls %d", wszFilePath, GetCurrentProcessId());
    if (CreateProcessW(NULL, wszCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return WAIT_OBJECT_0 == WaitForSingleObject(hDbgEvent, 0);
    }

    return false;
}

bool EnableDebugPrivilege() {
    bool bResult = false;
    HANDLE hToken = NULL;

    do {
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
            break;

        TOKEN_PRIVILEGES tp; 
        tp.PrivilegeCount = 1;
        if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
            break;

        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if( !AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
            break;

        bResult = true;
    }
    while (0);

    if (hToken) 
        CloseHandle(hToken);

    return bResult;
}

bool __is_debugged(int argc, char *argv[]){
    if (argc < 2)
    {        
        if (__run_second_stage())
            return true;
    }
    else
    {
        DWORD dwParentPid = atoi(argv[1]);
        HANDLE hEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, EVENT_SELFDBG_EVENT_NAME);
        if (hEvent && EnableDebugPrivilege())
        {
            if (!DebugActiveProcess(dwParentPid))
                SetEvent(hEvent);
            else
                DebugActiveProcessStop(dwParentPid);
        }
        return false;
    }
	return false;
}

int main(int argc, char *argv[]) {
    if(__is_debugged(argc, argv)) {
		if (argc == 1)
	        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 039", MB_OK);
	}
    else {
		if (argc == 1)
	        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 039", MB_OK);
	}

    return 0;
}