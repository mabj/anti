#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include "hwbrk.h"

static LONG WINAPI InstructionCountingExeptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
    if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
    {
#ifdef _WIN64
        pExceptionInfo->ContextRecord->Rax += 1;
        pExceptionInfo->ContextRecord->Rip += 1;
#else
        pExceptionInfo->ContextRecord->Eax += 1;
        pExceptionInfo->ContextRecord->Eip += 1;
#endif
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

__declspec(naked) DWORD WINAPI InstructionCountingFunc(LPVOID lpThreadParameter) {

#ifdef _WIN64
    __asm__ volatile goto
    (
        "xor rax, rax\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "cmp al, 4\n\t"
        "jne %l[being_debugged]\n\t"
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
        : being_debugged                  // Label operands
    );
#else
    __asm__ volatile goto
    (
        "xor eax, eax\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "cmp al, 4\n\t"
        "jne %l[being_debugged]\n\t"
        :                                 // No output operands
        :                                 // No input operands
        :                                 // No clobbered registers
        : being_debugged                  // Label operands
    );
#endif

    ExitThread(false);

being_debugged:
    ExitThread(true);
}

#define OFFSET_TO_HWBRKS 0x2

BOOL __is_debugged(void) {
    PVOID hVeh = NULL;
    HANDLE hThread = NULL;
    bool bDebugged = false;
    int m_nInstructionCount = 4;
    HANDLE m_hHwBps[4] = {0,0,0,0};

    hVeh = AddVectoredExceptionHandler(true, InstructionCountingExeptionHandler);
    if (!hVeh)
        return false;

    hThread = CreateThread(0, 0, InstructionCountingFunc, NULL, CREATE_SUSPENDED, 0);
    if (!hThread)
        return false;

    PVOID pThreadAddr = InstructionCountingFunc;

    for (int i = 0; i < m_nInstructionCount; i++)
        m_hHwBps[i] = SetHardwareBreakpoint(
            hThread, HWBRK_TYPE_CODE, HWBRK_SIZE_1, (PVOID)((DWORD_PTR)pThreadAddr + OFFSET_TO_HWBRKS + i));

    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);

    for (int i = 0; i < m_nInstructionCount; i++) {
        if (m_hHwBps[i])
            RemoveHardwareBreakpoint(m_hHwBps[i]);
    }

    DWORD dwThreadExitCode;
    if (true == GetExitCodeThread(hThread, &dwThreadExitCode))
        bDebugged = (true == dwThreadExitCode);

    return bDebugged;
}

int main(void) {
    BOOL debugger_present = __is_debugged();

    if (debugger_present) {
        MessageBox(NULL, "[+] The process is in Debug mode.", "AD052_InstructionCounting", MB_OK | MB_ICONWARNING);
    } else {
        MessageBox(NULL, "[+] The process is NOT in Debug mode.", "AD052_InstructionCounting", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
