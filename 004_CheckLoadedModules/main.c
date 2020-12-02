// @marcos_alvares
// build with "cl.exe main.c"

#include <windows.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <stdio.h>

// list restrieved from Trik/Phorpiex malware family
const char *BLACKLIST[] = {
    "snxhk.dll",
    "SxIn.dll",
    "vmcheck.dll",
    "cmdvrt32.dll",
    "dbghelp.dll",
    "dir_watch.dll",
    "SbieDll.dll",
    "SbieDllX.dll",
    "pstorec.dll",
    "wpespy.dll",
    "api_log.dll",
    "Sf2.dll",
};

BOOL _check_if_module_is_loaded(char *);
BOOL _check_process(DWORD, char *);

int main (int argc, char *argv[]) {
    for(int i = 0; i < 11; i++) 
        if (_check_if_module_is_loaded((char *) BLACKLIST[i])) {
            printf("[+] Sandbox has been detected.\n");
            break;
        }

    return 0;
}

// https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
BOOL _check_if_module_is_loaded(char *module_name) {
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return FALSE;
    }

    do {
        if (_check_process(pe32.th32ProcessID, module_name))
            return TRUE;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return FALSE;
}

BOOL _check_process(DWORD dwPID, char *module_name) {
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return FALSE;

    me32.dwSize = sizeof(MODULEENTRY32);
    if (!Module32First(hModuleSnap, &me32)) {
        CloseHandle(hModuleSnap);
        return FALSE;
    }

    do {
        if (strcmp(me32.szModule, module_name) == 0)
            return TRUE;
    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return FALSE;
}
