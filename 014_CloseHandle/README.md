# Context

The following property of the `CloseHandle` API (or `NtClose`) can be abused to detect if a process is running under a debugger. 

```[text]
If the application is running under a debugger, the function will throw an exception if it receives either a handle value that is not valid or a pseudo-handle value. This can happen if you close a handle twice, or if you call CloseHandle on a handle returned by the FindFirstFile function instead of calling the FindClose function.
```

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `__try` and `__except`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

![Tool Output](doc/images/close_handle_debugger.png)

## References

- <https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle>
- <https://anti-debug.checkpoint.com/techniques/object-handles.html#closehandle>