#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

bool __delay_execution(void);

int main(void) {
    if (__delay_execution()) {
        MessageBoxW(NULL, L"[+] Sandbox successfully delayed.", L"AS012_CreateTimerQueueTimer", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxW(NULL, L"[+] Sandbox NOT delayed.", L"AS012_CreateTimerQueueTimer", MB_OK | MB_ICONINFORMATION);
    }
}

HANDLE g_hEventCTQT = NULL;

VOID CALLBACK CallbackCTQT(PVOID lParam, BOOLEAN TimerOrWaitFired)
{
	if (TimerOrWaitFired == TRUE && lParam == (PVOID)(0xDEADBEEFULL))
	{
		SetEvent(g_hEventCTQT);
	}
}

bool __delay_execution(void) {
    unsigned int delay_in_millis = 10 * 1000; // (10 seconds)

	HANDLE hTimerQueue;
	HANDLE hTimerQueueTimer = NULL;
	bool bResult = false;

	g_hEventCTQT = CreateEvent(NULL, false, false, NULL);
	if (g_hEventCTQT == NULL)
		return false;

	hTimerQueue = CreateTimerQueue();
	if (hTimerQueue == NULL)
	{
		return false;
	}

	if (CreateTimerQueueTimer(
		&hTimerQueueTimer,
		hTimerQueue,
		&CallbackCTQT,
		(PVOID)(0xDEADBEEFULL),
		delay_in_millis,
		0,
		WT_EXECUTEDEFAULT) == false)
	{
		bResult = false;
	}
	else {

		// idea here is to wait only 10x the expected delay time
		// if the wait expires before the timer comes back, we fail the test
		if (WaitForSingleObject(g_hEventCTQT, delay_in_millis * 10) != WAIT_OBJECT_0) {
			bResult = true;
		}

	}

	// Delete all timers in the timer queue.
	DeleteTimerQueueEx(hTimerQueue, NULL);

	CloseHandle(g_hEventCTQT);

	return bResult;
}
