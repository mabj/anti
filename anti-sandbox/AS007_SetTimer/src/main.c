#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

bool bProcessed = false;

VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime) {
	// Malicious code is place here ....
	bProcessed = true;
}

// Forward declaration
bool __delay_execution(void);

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS007_SetTimer", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS007_SetTimer", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}

bool __delay_execution(void) {
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)
	MSG Msg;
	unsigned int iTimerID;

	// Set our timer without window handle
	iTimerID = SetTimer(NULL, 0, delay_in_millis, TimerProc);

	if (iTimerID == 0)
		return false;

	// Because we are running in a console app, we should get the messages from
	// the queue and check if msg is WM_TIMER
	while (GetMessage(&Msg, NULL, 0, 0) & !bProcessed) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	// Kill the timer
	KillTimer(NULL, iTimerID);

	return true;

}
