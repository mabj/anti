#include <windows.h>
#include <stdbool.h>

bool __is_debugged() {
	HANDLE hMutex;

	hMutex = CreateMutexA(NULL, false, "RandomMutex");
	if (hMutex) {
		SetHandleInformation(hMutex, HANDLE_FLAG_PROTECT_FROM_CLOSE, HANDLE_FLAG_PROTECT_FROM_CLOSE);
		__try {
			CloseHandle(hMutex);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return true;
		}
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