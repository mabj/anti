#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// Forward declaration
BOOL __delay_execution(void);

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS011_CreateWaitableTimer", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS011_CreateWaitableTimer", MB_OK | MB_ICONINFORMATION);
    }
}

BOOL __delay_execution(void) {
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)
	HANDLE hTimer;
	LARGE_INTEGER dueTime;
	BOOL bResult = true;

	dueTime.QuadPart = delay_in_millis * -10000LL;
	hTimer = CreateWaitableTimer(NULL, true, NULL);

	if (hTimer == NULL) {
		return false;
	}

	if (SetWaitableTimer(hTimer, &dueTime, 0, NULL, NULL, false) == false) {
		bResult = false;
	}
	else {
		if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0) {
			bResult = false;
		}
	}

	CancelWaitableTimer(hTimer);
	CloseHandle(hTimer);
	return bResult;
}
