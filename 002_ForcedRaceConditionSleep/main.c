// @marcos_alvares
// build with "vc.exe main.c"
// https://docs.microsoft.com/en-us/windows/win32/sync/using-named-objects

#include <windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <stdio.h>

#define _EXTENSION ".persisted" 
#define _TIMER 6000
#define _MUTEX_NAME "12345"

int _execute_cmd(char *);
void _execute_main_payload(int, char **);
int _persist_file(char *, char **);
BOOL _check_if_process_exists(char *);

int main(int argc, char *argv[]) {
    Sleep(_TIMER);
    HANDLE mh = CreateMutex(NULL, FALSE, _MUTEX_NAME);
    if (mh == NULL) {
        printf("[!] Could not create Mutex.\n");
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        HANDLE tst = CreateMutex(NULL, FALSE, "SANDBOX_DETECTED");
        printf("[+] A sandbox has been detected.\n");
        OutputDebugStringA("[+] A sandbox has been detected.");
        CloseHandle(mh); 
        return 0;
    }

    char file_name[400];
    GetModuleFileName(NULL, file_name, 400);

    if (strstr(file_name, _EXTENSION) != NULL) {
        _execute_main_payload(argc, argv);
    } else {
        char *persisted_file;
        if (_persist_file(file_name, &persisted_file) == 0) {
            printf("[!] Could not persist file.\n");
            return 0;
        }
        char *cmd = (char *)malloc(strlen(persisted_file) + strlen(file_name) + 2);
        sprintf(cmd, "%s %s", persisted_file, file_name);
        if (_execute_cmd(cmd) == 0) {
            printf("[!] Could not create new process.\n");
            return 0;
        }
        // Doing some random processing
        for(int u = 0; u<180; u++)
            _check_if_process_exists("unknown.exe");
    }

    return 0;
}

int _execute_cmd(char *cmd) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    si.dwFlags = 0x1;
    si.wShowWindow = 0x5;
    ZeroMemory( &pi, sizeof(pi) );
    return CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0x20, NULL, NULL, &si, &pi);
}

void _execute_main_payload(int argc, char *argv[]) {
    printf("[+] Executing main payload...\n");
    OutputDebugStringA("[+] Executing main payload ...");
    Sleep(_TIMER * 5);
    if (argc == 2) DeleteFile(argv[1]);
}

int _persist_file(char *file_name, char **persisted_file) {
    *persisted_file = (char *)malloc(strlen(file_name) + strlen(_EXTENSION) + 2);
    sprintf(*persisted_file, "%s.persisted", file_name);
    return CopyFile(file_name, *persisted_file, FALSE);
}

// https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
BOOL _check_if_process_exists(char *p_name) {
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;

  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE ) {
    printf("[!] CreateToolhelp32Snapshot (of processes)\n");
    return FALSE ;
  }

  pe32.dwSize = sizeof( PROCESSENTRY32 );

  if( !Process32First( hProcessSnap, &pe32 ) ) {
    printf("[!] Process32First\n");
    CloseHandle( hProcessSnap );
    return FALSE ;
  }

  do {
    if (pe32.szExeFile == p_name)
        return TRUE;

    _list_process_modules( pe32.th32ProcessID );
  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return FALSE;
}

BOOL _list_process_modules( DWORD dwPID ) {
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  // Take a snapshot of all modules in the specified process.
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
  if( hModuleSnap == INVALID_HANDLE_VALUE ) {
    // printf("CreateToolhelp32Snapshot (of modules)");
    return FALSE ;
  }

  // Set the size of the structure before using it.
  me32.dwSize = sizeof( MODULEENTRY32 );

  // Retrieve information about the first module,
  // and exit if unsuccessful
  if( !Module32First( hModuleSnap, &me32 ) ) {
    // printf("Module32First");  // show cause of failure
    CloseHandle( hModuleSnap );           // clean the snapshot object
    return( FALSE );
  }

  // Now walk the module list of the process,
  // and display information about each module
  int i = 0;
  do
  {
    i++;
    // _tprintf( TEXT("\n\n     MODULE NAME:     %s"),   me32.szModule );
    // _tprintf( TEXT("\n     Executable     = %s"),     me32.szExePath );
    // _tprintf( TEXT("\n     Process ID     = 0x%08X"),         me32.th32ProcessID );
    // _tprintf( TEXT("\n     Ref count (g)  = 0x%04X"),     me32.GlblcntUsage );
    // _tprintf( TEXT("\n     Ref count (p)  = 0x%04X"),     me32.ProccntUsage );
    // _tprintf( TEXT("\n     Base address   = 0x%08X"), (DWORD) me32.modBaseAddr );
    // _tprintf( TEXT("\n     Base size      = %d"),             me32.modBaseSize );

  } while( Module32Next( hModuleSnap, &me32 ) );

  CloseHandle( hModuleSnap );
  return TRUE ;
}