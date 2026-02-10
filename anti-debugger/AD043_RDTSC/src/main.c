#include <windows.h>
#include <stdbool.h>
#include <intrin.h>
#include <stdio.h>

#define PREVIOUSLY_MEASURED_ELAPSED_TIME 3299703928

ULARGE_INTEGER __fetch_time() {
    ULARGE_INTEGER _Time;
    __asm__ volatile
    (
        "xor ecx, ecx\n\t"
        "rdtsc\n\t"
        "mov %[s_low], eax\n\t"
        "mov %[s_high], edx\n\t"
        : [s_low] "=m" (_Time.LowPart), [s_high] "=m" (_Time.HighPart)     // output operands
        :                                                  // input operands
        : "eax", "edx", "ecx", "memory"                    // Clobbers
    );
    return _Time;
}

bool __is_debugged(unsigned long long qwNativeElapsed) {
    ULARGE_INTEGER Start = __fetch_time();

    for (int i = 0; i < 2; i++) {
        for (int u = 0; u < 20; u++) {
            printf("%03d %03d\r\r\r\r\r\r\r", i, u);
            Sleep(20);
        }
    }

    ULARGE_INTEGER End = __fetch_time();

    return (End.QuadPart - Start.QuadPart) > qwNativeElapsed;
}

int main() {
    if(__is_debugged(PREVIOUSLY_MEASURED_ELAPSED_TIME))
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 043", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 043", MB_OK);

    return 0;
}
