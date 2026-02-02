# Anti-Analysis Technique Collection

Knowledge base of anti-analysis techniques found during malware analyses.

## [001_SetErrorMode] Sandbox detection technique by inspect SetErrorMode behavior

Uses calls to SetErrorMode to detect changes (hooks) in the default behavior or SetErrorMode windows API call.

- <https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode>
- <https://www.cyberbit.com/formbook-research-hints-large-data-theft-attack-brewing/>

## [002_ForcedRaceConditionSleep] Forces a race condition in order to detect changes in sleep() call behavior

This method terminates the process if a mutex still exists by spawing the same process twice. The trick is that this mutex will still exist in the second process if the default behavior of sleep() is untouched.

- <https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa>
- <https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499->
- <https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep>
- <http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FThread%2FNtDelayExecution>.
- <https://docs.microsoft.com/en-us/windows/win32/sync/using-named-objects>

## [003_CheckProcessList] Checks host processes agains a list of pre-defined process names

Iterates through the process list checking them against a "blacklist" and terminates analysis tools or the execution of the current process in case of a match.

- <https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes>

## [004_CheckLoadedModules] Checks DLLs loaded in the current process against a pre-defined list

Sometimes analysis tools and sandboxes injects DLLs in targetted processes in order to inspect their execution behaviour.

- <https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes>

## [005_CheckDeviceNames] Check devices names in the Windows Registry

This technique searches for specific keys in the Windows Registry regarding device names. Virtual machine technologies leaves a lot of traces if not fine tunned. Malware families use this technique to check if the main executable is running under a virtualized environment.

- <https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/>

## [006_CheckProcessDebugPort] Fetches "ProcessDebugPort" data by calling "NtQueryInformationProcess"

Usually this technique is used together with technique #007 so this avoids hooks to this specfic API call ("NtQueryInformationProcess").

- <https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/>

## [007_CopyOfNtdll] Loads a copy of ntdll.dll and uses it instead the original library

This technique is used to hide behavioural data in case sandboxes do not propagate hooks.

- <https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/>

## [008_IsDebuggerPresent] Checks debug flag by using "IsDebuggerPresent" call

Checks if any debugger is attached to the current process by inspecting debug flag in PEB. There are many ways to achieve this and one of them is calling the "IsDebuggerPresent" call.

- <https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent>

## [009_CheckRemoteDebuggerPresent] Checks debug flag by using "CheckRemoteDebuggerPresent" call

Checks if any debugger is attached to an specific process.

- <https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent>

## [010_FindWindow] Checks open windows for known analysis tool names

Searches window names according to a list of pre-defined names used by analysis tools.

- <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa>

## [011_ProcessDebugObjectHandle] Checks if a process is being debugged by querying the `ProcessDebugObjectHandle`

This anti-debug technique checks if a process is being debugged by querying the `ProcessDebugObjectHandle` using `NtQueryInformationProcess`.

- <https://ieeexplore.ieee.org/abstract/document/9186656>
- <https://github.com/gnxbr/Fully-Undetectable-Techniques/tree/main/user-imitating>

## [012_CheckPEB] Checks debug flags located inside PEB structure

Checks being debugged flag inside PEB structure.

- <https://docs.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb>

## [013_SetUnhandledExceptionFilter] Detects Debugger by setting handler to Unhandled Exception Filter (UEF)

Checks if debugger is taking over exception handling chain.

- <https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter>

## [014_CloseHandle] Detects Debugger by checking behavior of CloseHandle API

Chacks if CloseHandle is raising an exception in case of invalid handle is passed as parameter.

- <https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle>

## [015_SetHandleInformation] Detects Debugger by abusing the behavior of SetHandleInformation API

The implementation creates a handle to a mutex, protects it with `HANDLE_FLAG_PROTECT_FROM_CLOSE`, then attempts closure in a structured exception handling block.

- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/SetHandleInformation_API.cpp>

## [016_RtlQueryProcessHeapInformation] Detects Debugger by checking heap flags

This anti-debug technique detects debuggers by examining heap flags.

- <https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessheapinformation>

## [017_RtlQueryProcessDebugInformation] Detects Debugger by checking heap flags

This anti-debug technique detects debuggers by examining heap flags.

- <https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessdebuginformation>

## [018_FindWindow] Detects debugging tools by checking for the presence of windows with titles associated with known debuggers

Uses the `FindWindowA` function to check for the existence of windows with titles that are commonly used by debuggers and analysis tools.

- <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa>

## [019_GetShellWindow] Detects debuggers by comparing the parent process ID against the shell window's process ID

This technique retrieves the shell window (typically the desktop) and gets its process ID (explorer). Then, it checks the parent process ID of the current process. If the parent process is not explorer, it assumes the process is being debugged.

- <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getshellwindow>
- <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid>
- <https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/ns-ntifs-_process_basic_information>

## [020_DbgPrint] Detects debuggers by checking for exceptions when calling DbgPrint

This technique detects debuggers by calling `DbgPrint` and checking if an exception (`DBG_PRINTEXCEPTION_C`) occurs. However, note that this method is ineffective on Windows 10 64-bit systems, as confirmed in testing.

## [021_GetWriteWatch] Detects debuggers by monitoring protected memory regions for unexpected writes

This technique allocates executable memory with special monitoring flags, then continuously checks for unexpected modifications to these memory regions. Analysis tools like debuggers often modify protected memory regions to insert breakpoints, which this technique can detect.

- <https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-getwritewatch>
- <https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-resetwritewatch>

## [022_GetThreadContext] Detects debuggers by checking hardware breakpoint registers

This technique uses the `GetThreadContext` API to inspect debug registers (Dr0-Dr7). If any registers are set, it indicates hardware breakpoints are active, suggesting debugger presence.

- <https://docs.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getthreadcontext>

## [023_NtSetInformationThread] Hides the current thread from debuggers using NtSetInformationThread

This technique uses the `NtSetInformationThread` function with `ThreadHideFromDebugger` (0x11) to make the current thread invisible to debuggers. If successful, the thread detaches from any attached debugger and continues execution normally.

- <https://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FThread%2FNtSetInformationThread.html>

## [024_NtQueryObject] Detects debuggers by querying for the presence of DebugObject

This technique uses the `NtQueryObject` function to enumerate all object types and checks for the presence of a "DebugObject". If such an object exists and has a count greater than zero, it indicates the presence of a debugger.

- <https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryobject>
- <https://anti-debug.checkpoint.com/techniques/misc.html#debugobject>

## [025_RaiseException] Detects debuggers by raising a DBG_CONTROL_C exception

This technique uses structured exception handling (SEH) to raise a `DBG_CONTROL_C` exception. If the exception is handled by the program's exception handler, it indicates the absence of a debugger. If the exception is intercepted by a debugger (and not passed to the program), the handler does not run and the function returns true (debugger present).

- <https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-raiseexception>

## [026_MemoryBreakpoint] Detects debuggers by scanning for breakpoints (INT3) in watched functions

This technique periodically scans the memory of specific functions for the presence of breakpoints (0xCC, the opcode for INT3). If found, it indicates that a debugger has set a breakpoint in the function.

- <https://en.wikipedia.org/wiki/INT_(x86_instruction)#INT3>
- <https://anti-debug.checkpoint.com/techniques/process-memory.html#software-breakpoints>

## [027_AntiStepOver] Detects debugger by checking for breakpoint at function return address

This technique uses the `_ReturnAddress` intrinsic to get the return address of the current function and checks if the instruction at that address is `INT3` (0xCC). If so, it indicates that a debugger has placed a breakpoint (for step-over) and the function returns early, avoiding the normal execution path.

- <https://docs.microsoft.com/en-us/cpp/intrinsics/returnaddress?view=msvc-170>
- <https://anti-debug.checkpoint.com/techniques/process-memory.html#anti-step-over>

## [028_MemoryBreakpoint] Detects debuggers using guard page exception behavior

This technique allocates executable memory, writes a RET instruction (0xC3) to it, and marks the page as a guard page. It then attempts to execute the memory location within a structured exception handler. If the guard page exception is caught (STATUS_GUARD_PAGE_VIOLATION), it indicates no debugger is present. If the code executes normally, it means a debugger intercepted and handled the exception.

> PS: This technique works only in OllyDbg and ImmunityDbg (not in x64dbg).

- <https://anti-debug.checkpoint.com/techniques/process-memory.html#memory-breakpoints>
- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/MemoryBreakpoints_PageGuard.cpp>
