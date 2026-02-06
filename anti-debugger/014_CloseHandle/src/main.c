#include <windows.h>
#include <stdbool.h>

bool __is_debugged() {
    __try {
        CloseHandle((HANDLE)(ULONG_PTR)0xDEADBEEF);
    }
    __except (EXCEPTION_INVALID_HANDLE == GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        return true;
    }

    return false;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 014", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 014", MB_OK);

    return 0;
}