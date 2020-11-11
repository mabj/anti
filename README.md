# Anti-Analysis Technique Collection
Knowledge base of anti-analysis techniques found during malware analyses.

## [001_SetErrorMode] Sandbox detection technique by inspect SetErrorMode behavior. 
Uses calls to SetErrorMode to detect changes (hooks) in the default behavior or SetErrorMode windows API call. 

 - https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode
 - https://www.cyberbit.com/formbook-research-hints-large-data-theft-attack-brewing/

## [002_ForcedRaceConditionSleep] Forces a race condition in order to detect changes in sleep() call behavior
This method terminates the process if a mutex still exists by spawing the same process twice. The trick is that this mutex will still exist in the second process if the default behavior of sleep() is untouched. 

 - https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
 - https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
 - https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep
 - http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FThread%2FNtDelayExecution.
 - https://docs.microsoft.com/en-us/windows/win32/sync/using-named-objects

## [003_CheckProcessList] Checks host processes agains a list of pre-defined process names.
Iterates through the process list checking them against a "blacklist" and terminates analysis tools or the execution of the current process in case of a match.

 - https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes

## [004_CheckLoadedModules] Checks DLLs loaded in the current process against a pre-defined list.
Sometimes analysis tools and sandboxes injects DLLs in targetted processes in order to inspect their execution behaviour.

 - https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes

## [005_CheckDeviceNames] Check devices names in the Windows Registry.
This technique searches for specific keys in the Windows Registry regarding device names. Virtual machine technologies leaves a lot of traces if not fine tunned. Malware families use this technique to check if the main executable is running under a virtualized environment.

 - https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/

## [006_CheckProcessDebugPort] Fetches "ProcessDebugPort" data by calling "NtQueryInformationProcess".
Usually this technique is used together with technique #007 so this avoids hooks to this specfic API call ("NtQueryInformationProcess").

 - https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/

## [007_CopyOfNtdll] Loads a copy of ntdll.dll and uses it instead the original library.
This technique is used to hide behavioural data in case sandboxes do not propagate hooks. 

 - https://research.checkpoint.com/2019/2019-resurgence-of-smokeloader/

## [008_IsDebuggerPresent] Checks debug flag by using "IsDebuggerPresent" call
Checks if any debugger is attached to the current process by inspecting debug flag in PEB. There are many ways to achieve this and one of them is calling the "IsDebuggerPresent" call.

 - https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent

## [009_CheckRemoteDebuggerPresent] Checks debug flag by using "CheckRemoteDebuggerPresent" call
Checks if any debugger is attached to an specific process.

 - https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent

## [010_FindWindow] Checks open windows for known analysis tool names
Searches window names according to a list of pre-defined names used by analysis tools.

 - https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa