#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

bool __delay_execution(void) {
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)

    int delayInMillis_divided = delay_in_millis / 1000;

	/* Example: we want to sleep 300 seeconds, then we can sleep
	0.3s for 1000 times which is like: 300 seconds = 5 minues */
	for (int i = 0; i < 1000; i++) {
		Sleep(delayInMillis_divided);
	}

	// Malicious code goes here

	return true;
}

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS013_SleepLoop", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS013_SleepLoop", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
