#include <windows.h>
#include <stdbool.h>
#include <winternl.h>

#include <stdio.h>


#pragma pack(push, 1)
#ifdef _WIN64
typedef unsigned long long QWORD;
struct DbgUiRemoteBreakinPatch {
    BYTE  mov_rcx;
    WORD  rcx;
    DWORD CurrentPorcessHandle;
    BYTE  mov_rdx;
    WORD  rdx;
    DWORD ZERO;
    WORD  mov_rax;
    QWORD TerminateProcess;
    WORD  call_eax;
};
#else
struct DbgUiRemoteBreakinPatch {
    WORD  push_0;
    BYTE  push;
    DWORD CurrentPorcessHandle;
    BYTE  mov_eax;
    DWORD TerminateProcess;
    WORD  call_eax;
};
#endif
#pragma pack(pop)

void __patch_DbgUiRemoteBreakin() {
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll)
        return;

    FARPROC pDbgUiRemoteBreakin = GetProcAddress(hNtdll, "DbgUiRemoteBreakin");
    if (!pDbgUiRemoteBreakin)
        return;

    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    if (!hKernel32)
        return;

    FARPROC pTerminateProcess = GetProcAddress(hKernel32, "TerminateProcess");
    if (!pTerminateProcess)
        return;
    
    struct DbgUiRemoteBreakinPatch patch = { 0 };
    #ifdef _WIN64
        patch.mov_rcx              = '\x48';
        patch.rcx                  = '\xc1\xc7';
        patch.CurrentPorcessHandle = 0xffffffff;
        patch.mov_rdx              = '\x48';
        patch.rdx                  = '\xc2\xc7';
        patch.ZERO                 = 0x0;
        patch.mov_rax              = '\xB8\x48';
        patch.TerminateProcess     = (QWORD)pTerminateProcess;
        patch.call_eax             = '\xD0\xFF';
    #else
        patch.push_0               = '\x00\x6A';
        patch.push                 = '\x68';
        patch.CurrentPorcessHandle = 0xFFFFFFFF;
        patch.mov_eax              = '\xB8';
        patch.TerminateProcess     = (DWORD)pTerminateProcess;
        patch.call_eax             = '\xD0\xFF';
    #endif

    // printf("[!] Sizeof of unsigned long is %d\n", sizeof(unsigned long long));
    // printf("[!] Sizeof of DbgUiRemoteBreakinPatch struct is %d\n", sizeof(struct DbgUiRemoteBreakinPatch));

    DWORD dwOldProtect;
    if (!VirtualProtect(pDbgUiRemoteBreakin, sizeof(struct DbgUiRemoteBreakinPatch), PAGE_READWRITE, &dwOldProtect))
        return;

    memcpy_s(pDbgUiRemoteBreakin, sizeof(struct DbgUiRemoteBreakinPatch),
        &patch, sizeof(struct DbgUiRemoteBreakinPatch));

    VirtualProtect(pDbgUiRemoteBreakin, sizeof(struct DbgUiRemoteBreakinPatch), dwOldProtect, &dwOldProtect);
}

int main() {
    __patch_DbgUiRemoteBreakin();

    while(true) {
        printf("[+] Waiting after patching DbgUiRemoteBreakin() ... \n");
        Sleep(rand() % 1000 + 500);
    }

    return 0;
}