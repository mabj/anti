# Context

The following property of the CloseHandle API can be abused to detect if a process is running under a debugger. 

```
If the application is running under a debugger, the function will throw an exception if it receives either a handle value that is not valid or a pseudo-handle value. This can happen if you close a handle twice, or if you call CloseHandle on a handle returned by the FindFirstFile function instead of calling the FindClose function.
```

## References

- https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle
- https://anti-debug.checkpoint.com/techniques/object-handles.html#closehandle