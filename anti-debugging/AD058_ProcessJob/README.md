# Context

Windows Job Objects allow grouping processes for resource management and monitoring. Debuggers often place target processes in job objects to track and control them. This technique detects debugging by querying the job object the process belongs to and checking for unexpected additional processes.

Key characteristics:

- Queries job object information using `QueryInformationJobObject` with `JobObjectBasicProcessIdList`
- Enumerates all processes assigned to the current job object
- Validates that only the current process and `conhost.exe` are in the job
- Detects debuggers that create job objects to contain and monitor the target process
- Uses `GetProcessImageFileNameA` to identify process names in the job
- Reports debugging if unexpected processes are found in the same job object

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
