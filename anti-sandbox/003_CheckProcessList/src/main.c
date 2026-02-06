// @marcos_alvares
// build with "cl.exe main.c"

#include <windows.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <stdio.h>

// list retrieved from Smokeloader
const char *BLACKLIST[] = {
    "python.exe",
    "python3.exe",
    "pythonw.exe",
    "Autoruns.exe",
    "procexp.exe",
    "procexp64.exe",
    "procmon.exe",
    "procmon64.exe",
    "Tcpview.exe",
    "Wireshark.exe",
    "processhacker.exe",
    "ollydbg.exe",
    "x32dbg.exe",
    "x64dbg.exe",
    "idaq.exe",
    "idaw.exe",
    "idaq64.exe",
    "idaw64.exe"
};


BOOL _check_if_process_exists(char *);

int main (int argc, char *argv[]) {
    for (unsigned int i=0; i < (sizeof(BLACKLIST)/sizeof(BLACKLIST[0])); i++)
        if (_check_if_process_exists((char *) BLACKLIST[i])) {
            printf("[+] Sandbox has been detected.\n");
            break;
        }

    return 0;
}

// https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
BOOL _check_if_process_exists(char *p_name) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return FALSE;
    }

    do {
        if (strcmp(pe32.szExeFile, p_name) == 0)
            return TRUE;
    } while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return FALSE;
}
