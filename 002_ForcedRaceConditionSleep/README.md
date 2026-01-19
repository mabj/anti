# Observed ITW during analysis of Trik/Phorpiex spambot

## File Information
| Property | Value |
|----------|-------|
| File Size | 68096 bytes |
| File Type | PE32 executable (GUI) Intel 80386, for MS Windows |
| MD5 | 0330ca15737b3fb862072cfa22bafe01 |
| SHA1 | 633026b9467600e9617e76e3e8dfaebe5ac9f91f |
| SHA256 | cacec7cf35fc455c63afb772f3ef8084c2badfcd73d68d9d17878017eeaa21d8 |

## Technique Description
This method detects behavioral changes (caused by hooks) on sleep calls by forcing a race condition.

### Pseudo-code Implementation
```
sleep(n)
creates named mutex "12345"
terminates if mutex "12345" exists

if running version is inside persisted directory
    deletes original binary
    computes main payload
    delete mutex "12345"
    terminates
else
    persists itself in %APPDATA%
    executes persisted binary
    do some computation (just to cover the time taken for setup persisted version)
    terminates
```

## Technical Explanation
The outcome is that the main payload is not executed if Sleep() is shortcutted by hooks. Sleep() is hooked by default in many sandboxes as an attempt to trick malware families that purposely implement delays so automated analyses would timeout.
