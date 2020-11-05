# Anti Collection
Knowledge base of anti debug and analysis techniques found during malware analyses.

## [001_SetErrorMode] Sandbox detection technique by inspect SetErrorMode behavior. 
Uses calls to SetErrorMode to detect changes (hooks) in the default behavior or SetErrorMode windows API call. 

 - https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode
 - https://www.cyberbit.com/formbook-research-hints-large-data-theft-attack-brewing/

## [002_ForcedRaceConditionSleep] Forces a race condition in order to detect changes in sleep() call behavior
This method terminates the process if a mutex still exists by spawing the same process twice. The trick is that this mutex will still exist in the second process if the default behavior of sleep() is untouched. 

 - https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa
 - https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-

