# Context

This technique uses the `RDTSC` (Read Time-Stamp Counter) x86 instruction to detect debugger presence by measuring CPU cycle counts around a known workload. Under normal execution the elapsed cycles fall within a predictable range, but single-stepping or breakpoints in a debugger inflate the count far beyond the threshold.

Key characteristics:

- Uses inline assembly to execute `RDTSC`, which returns the 64-bit timestamp counter in EDX:EAX
- Clears ECX before `RDTSC` to avoid stale state (some processors use ECX as an implicit operand)
- Measures cycles before and after a deterministic workload (nested loops with `Sleep(20)`)
- Compares the elapsed cycle delta against a pre-calibrated threshold (`PREVIOUSLY_MEASURED_ELAPSED_TIME`)
- Hardware-level timing source — cannot be easily hooked or patched from user mode
- x86-only (uses 32-bit inline assembly with Intel syntax via MinGW)

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

- [Check Point: RDTSC](https://anti-debug.checkpoint.com/techniques/timing.html#rdtsc)
- [Intel SDM: RDTSC — Read Time-Stamp Counter](https://www.felixcloutier.com/x86/rdtsc)
