# Context

The PEB (Process Execution Block) holds a Byte flag that indicates that the current process is attached to a debugger.

```[text]
typedef struct _PEB {
  BYTE                          Reserved1[2];
  BYTE                          BeingDebugged;    // <<<-------
  BYTE                          Reserved2[1];
  PVOID                         Reserved3[2];
  PPEB_LDR_DATA                 Ldr;
  PRTL_USER_PROCESS_PARAMETERS  ProcessParameters;
  PVOID                         Reserved4[3];
  PVOID                         AtlThunkSListPtr;
  PVOID                         Reserved5;
  ULONG                         Reserved6;
  PVOID                         Reserved7;
  ULONG                         Reserved8;
  ULONG                         AtlThunkSListPtr32;
  PVOID                         Reserved9[45];
  BYTE                          Reserved10[96];
  PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
  BYTE                          Reserved11[128];
  PVOID                         Reserved12[1];
  ULONG                         SessionId;
} PEB, *PPEB;
```

## References

- <https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb>
