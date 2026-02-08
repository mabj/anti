#include <windows.h>
#include <stdbool.h>

#define INT3 0xCC

bool my_func() {

    // Checks for INT3 (EXCEPTION_BREAKPOINT) at the return address of this function
    // and returns before executing its content;
    PVOID pRetAddress = __builtin_return_address(0);
    if (*(PBYTE)pRetAddress == INT3)
        return true;

    // Dummy content
    for(int i = 0; i< 10; i++) {
        unsigned int delay = rand() % 500 + 500;
        Sleep(delay); // 500ms < t < 1000ms
    }

    return false;
}

bool __is_debugged() {
    return my_func();
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 018", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 018", MB_OK);

    return 0;
}
