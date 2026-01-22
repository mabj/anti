# Context

This anti-debug technique detects debuggers by examining heap flags.

- Uses `RtlCreateQueryDebugBuffer` and `RtlQueryProcessHeapInformation` to access heap information
- Checks flags of the first heap in the process
- Detects if any non-`HEAP_GROWABLE` flags are set
- Based on the observation that debuggers modify heap flags when attaching to processes

## Build (Docker)

```
$ make build-image
$ make build
```

## References

- https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessheapinformation