#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// Forward declaration
bool __delay_execution(void);

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS010_WaitForSingleObject", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS010_WaitForSingleObject", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}

bool __delay_execution(void) {
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)
    HANDLE hEvent;

	// Create a nonsignaled event
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEvent == NULL) {
		return false;
	}

	// Wait until timeout 
	DWORD x = WaitForSingleObject(hEvent, delay_in_millis);
    if(x == WAIT_FAILED) {
        return false;
    }

	// Malicious code goes here

	return true;
}
