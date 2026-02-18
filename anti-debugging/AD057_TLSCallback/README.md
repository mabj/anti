# Context

TLS (Thread Local Storage) callbacks are functions that execute before the program's entry point (before `main()` or `WinMain()`). Malware uses TLS callbacks to perform anti-debugging checks or decrypt payloads before debuggers can set breakpoints at the conventional entry point.

Key characteristics:

- Executes before the main entry point, potentially before debugger initialization
- Registered in the PE file's `.CRT$XL*` section through linker directives
- Can be used to detect debuggers, decrypt code, or perform early environment checks
- Harder to intercept than normal entry points since many debuggers start at `main()`
- Multiple TLS callbacks can be chained in a single executable
- Uses `PIMAGE_TLS_CALLBACK` function pointer placed in TLS directory

## Build

### Using Docker (Recommended)

```bash
make build-image  # First time only
make build
```

### Alternative: MinGW

```bash
make
```

## References

- [TODO: Add references]
