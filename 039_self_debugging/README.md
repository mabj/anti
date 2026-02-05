# Context

The self-debugging technique detects debuggers by exploiting the Windows limitation that only one debugger can be attached to a process at a time. The program spawns a child instance of itself and attempts to attach it as a debugger to the parent process. If the attachment succeeds, no external debugger is present; if it fails, another debugger is already attached.

## Key Points

- **Process spawning**: Creates a child process of itself, passing the parent's PID as a command-line argument
- **DebugActiveProcess attempt**: Child process tries to attach as a debugger to the parent using [`DebugActiveProcess()`](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-debugactiveprocess)
- **Privilege elevation**: Enables [`SE_DEBUG_NAME`](https://learn.microsoft.com/en-us/windows/win32/secauthz/privilege-constants) privilege to allow debugging operations
- **Named event synchronization**: Uses a Windows event object (`SelfDebugging`) for communication between parent and child processes
- **Detection logic**: If attachment fails, signals that an external debugger is already attached; if successful, immediately detaches with [`DebugActiveProcessStop()`](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-debugactiveprocessstop)
- **Single debugger limitation**: Exploits the Windows restriction that prevents multiple debuggers from attaching to the same process simultaneously

## References

- <https://anti-debug.checkpoint.com/techniques/assembly.html#instruction_prefixes>
