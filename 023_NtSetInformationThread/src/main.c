#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <winternl.h>

NTSTATUS NTAPI NtSetInformationThread(
  HANDLE          ThreadHandle,
  THREADINFOCLASS ThreadInformationClass,
  PVOID           ThreadInformation,
  ULONG           ThreadInformationLength
);

int main() {
    NTSTATUS status = NtSetInformationThread(
        GetCurrentThread(), 
        0x11, // THREAD_INFORMATION_CLASS.ThreadHideFromDebugger, 
        NULL, 
        0
    );

    if NT_ERROR(status) {
        printf("[!] Could not change the property of the current thread.\n");
        return 1;
    }

    while(true) {
        printf("[+] Looping ... \n");
        Sleep(2000);
    }

    return 0;
}