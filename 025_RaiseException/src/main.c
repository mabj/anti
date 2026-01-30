#include <windows.h>
#include <stdbool.h>

bool __is_debugged() {
    __try {
        RaiseException(DBG_CONTROL_C, 0, 0, NULL);
        return true;
    } __except(DBG_CONTROL_C == GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        return false;
    }
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 025", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 025", MB_OK);

    return 0;
}