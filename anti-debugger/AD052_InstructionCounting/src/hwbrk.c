#include <windows.h>
#include <stdbool.h>
#include "hwbrk.h"

typedef struct _HWBRK {
    void *addr;
    HANDLE hThread;
    int iReg;
    enum HWBRK_TYPE type;
    enum HWBRK_SIZE size;
    bool inUse;
} HWBRK;

#define MAX_HWBRKS 4
static HWBRK s_hwbrks[MAX_HWBRKS] = {0};

static int GetFreeDebugRegister(CONTEXT *ctx) {
    for (int i = 0; i < 4; i++) {
        if (!(ctx->Dr7 & (1UL << (i * 2))))
            return i;
    }
    return -1;
}

static void SetDebugRegister(CONTEXT *ctx, int reg, void *addr) {
    switch (reg) {
        case 0: ctx->Dr0 = (DWORD_PTR)addr; break;
        case 1: ctx->Dr1 = (DWORD_PTR)addr; break;
        case 2: ctx->Dr2 = (DWORD_PTR)addr; break;
        case 3: ctx->Dr3 = (DWORD_PTR)addr; break;
    }
}

static void ClearDebugRegister(CONTEXT *ctx, int reg) {
    switch (reg) {
        case 0: ctx->Dr0 = 0; break;
        case 1: ctx->Dr1 = 0; break;
        case 2: ctx->Dr2 = 0; break;
        case 3: ctx->Dr3 = 0; break;
    }
}

HANDLE SetHardwareBreakpoint(HANDLE hThread, enum HWBRK_TYPE Type, enum HWBRK_SIZE Size, void *s) {
    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (!GetThreadContext(hThread, &ctx))
        return NULL;

    int reg = GetFreeDebugRegister(&ctx);
    if (reg < 0)
        return NULL;

    int slot = -1;
    for (int i = 0; i < MAX_HWBRKS; i++) {
        if (!s_hwbrks[i].inUse) {
            slot = i;
            break;
        }
    }
    if (slot < 0)
        return NULL;

    SetDebugRegister(&ctx, reg, s);

    ctx.Dr7 &= ~(0xFUL << (16 + reg * 4));

    DWORD condition = 0;
    switch (Type) {
        case HWBRK_TYPE_CODE:      condition = 0; break;
        case HWBRK_TYPE_WRITE:     condition = 1; break;
        case HWBRK_TYPE_READWRITE: condition = 3; break;
    }
    ctx.Dr7 |= (condition << (16 + reg * 4));

    DWORD size = 0;
    switch (Size) {
        case HWBRK_SIZE_1: size = 0; break;
        case HWBRK_SIZE_2: size = 1; break;
        case HWBRK_SIZE_4: size = 3; break;
        case HWBRK_SIZE_8: size = 2; break;
    }
    ctx.Dr7 |= (size << (18 + reg * 4));

    ctx.Dr7 |= (1UL << (reg * 2));
    ctx.Dr6 = 0;

    if (!SetThreadContext(hThread, &ctx))
        return NULL;

    s_hwbrks[slot].addr = s;
    s_hwbrks[slot].hThread = hThread;
    s_hwbrks[slot].iReg = reg;
    s_hwbrks[slot].type = Type;
    s_hwbrks[slot].size = Size;
    s_hwbrks[slot].inUse = true;

    return (HANDLE)(DWORD_PTR)(slot + 1);
}

bool RemoveHardwareBreakpoint(HANDLE hBrk) {
    int slot = (int)(DWORD_PTR)hBrk - 1;
    if (slot < 0 || slot >= MAX_HWBRKS || !s_hwbrks[slot].inUse)
        return false;

    CONTEXT ctx = {0};
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    if (!GetThreadContext(s_hwbrks[slot].hThread, &ctx))
        return false;

    int reg = s_hwbrks[slot].iReg;

    ctx.Dr7 &= ~(1UL << (reg * 2));
    ctx.Dr7 &= ~(0xFUL << (16 + reg * 4));
    ClearDebugRegister(&ctx, reg);

    if (!SetThreadContext(s_hwbrks[slot].hThread, &ctx))
        return false;

    s_hwbrks[slot].inUse = false;
    return true;
}
