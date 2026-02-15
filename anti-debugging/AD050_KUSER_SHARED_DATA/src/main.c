#include <windows.h>

// Though all known C-language definitions of KdDebuggerEnabled in NTDDK.H have it as a 
// BOOLEAN, it is in fact a pair of bit flags.
//
// https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/ntexapi_x/kuser_shared_data/index.htm
//
// Offset	Definition	Versions	Remarks
// 0x02D4	BOOLEAN     KdDebuggerEnabled;
BOOL __is_debugged(void) {
    unsigned char b = *(unsigned char*)0x7ffe02d4;
    return ((b & 0x01) || (b & 0x02));
}

int main(void) {
    BOOL debugger_present = __is_debugged();

    if (debugger_present) {
        MessageBox(NULL, "[+] The process is in Debug mode.", "AD050_KUSER_SHARED_DATA", MB_OK | MB_ICONWARNING);
    } else {
        MessageBox(NULL, "[+] The process is NOT in Debug mode.", "AD050_KUSER_SHARED_DATA", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
