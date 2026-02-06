#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

bool g_is_debugged = false ;

static LONG WINAPI CtrlEventExeptionHandler(PEXCEPTION_POINTERS pExceptionInfo) {
    if (pExceptionInfo->ExceptionRecord->ExceptionCode == DBG_CONTROL_C) {
        g_is_debugged = true;
    }
    return EXCEPTION_CONTINUE_EXECUTION;
}

static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
        case CTRL_C_EVENT:
            return true;
        default:
            return false;
    }
}

bool __is_debugged() {
    if (!AddVectoredExceptionHandler(true, CtrlEventExeptionHandler))
        return false;

    if (!SetConsoleCtrlHandler(CtrlHandler, true))
        return false;

    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);

    int i = 5;
    while(i && g_is_debugged == false) {
        printf("[+] Waiting ...\n");
        Sleep(rand()%1000 + 500); // Sleeps randomly from 500ms to 1.5s 
        i--;
    }

    return g_is_debugged;
}

int main() {
    if(__is_debugged()) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 031", MB_OK);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 031", MB_OK);
    }
        
    return 0;
}
