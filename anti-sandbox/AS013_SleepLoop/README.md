# Context

This technique evades sandbox time acceleration by splitting a long delay into many short `Sleep()` calls inside a loop. Instead of calling `Sleep(10000)` once (which sandboxes easily detect and fast-forward), it calls `Sleep(10)` in a loop of 1000 iterations, accumulating the same 10-second total delay.

Key characteristics:

- Divides a large sleep duration into many small increments via a `for` loop
- Each individual `Sleep()` call is too short for sandboxes to reliably accelerate
- Sandboxes that hook and skip `Sleep()` will complete the loop almost instantly, failing to delay execution as intended
- Simple to implement and effective against basic time-acceleration heuristics
- Uses the Windows `Sleep()` API from `windows.h`

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

- [Unprotect Project - Delayed Execution](https://unprotect.it/technique/delayed-execution/)
