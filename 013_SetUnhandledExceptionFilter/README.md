# Context

There are four mechanisms to handle custom exceptions on Windows:

1. Debugger;
2. Vectored Exception Handlers (VEH): Global handlers to the whole process
3. Frame-based SEH: the try/except blocks of C++;
4. Unhandled Exception Filter (UEF): The "last resort" handler;

In this example, the sample sets a UEF handler and expects that the execution flows gets to the
end of the handling chain. If the process is getting debugged, the debugger will capture the the
INT3 (0xCC) exception before it gets to the UEF handler.

## References

- https://anti-debug.checkpoint.com/techniques/exceptions.html
- https://www.sonicwall.com/blog/guloader-demystified-unraveling-its-vectored-exception-handler-approach
- https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter
- https://wiki.osdev.org/Inline_Assembly
- https://billdemirkapi.me/exception-oriented-programming-abusing-exceptions-for-code-execution-part-1/
- https://www.ibm.com/think/x-force/using-veh-for-defense-evasion-process-injection
- https://momo5502.com/posts/2024-09-07-a-journey-through-kiuserexceptiondispatcher/
- https://blog.elmo.sg/posts/structured-exception-handler-x64/
