#include <windows.h>
#include <stdbool.h>

bool __is_hooked() {
    BOOL second_result = false;
    BlockInput(true);
    second_result = BlockInput(true);

    return second_result == true;
}

int main() {
    if(__is_hooked())
        MessageBoxA(NULL, "[+] user32.BlockInput API is hooked.", "Anti-sandbox 008", MB_OK);
    else
        MessageBoxA(NULL, "[+] user32.BlockInput API is NOT hooked.", "Anti-sandbox 008", MB_OK);

    return 0;
}
