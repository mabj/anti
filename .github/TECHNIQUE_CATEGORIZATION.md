# Technique Categorization (3 Categories)

This document maps all 39 techniques to the new 3-category taxonomy.

## Category Definitions

### Anti-Debugging
Techniques that specifically detect the presence of debuggers attached to or monitoring the process.

### Anti-Sandbox
Techniques that detect automated analysis environments, virtual machines, sandboxes, or analysis tools in the system.

### Anti-Reversing
Techniques that actively hinder reverse engineering by modifying code, hiding information, or protecting against analysis.

## Categorization

### Anti-Debugging (30 techniques)

| # | Technique Name | Reason |
|---|---|---|
| 006 | CheckProcessDebugPort | Queries ProcessDebugPort to detect debugger |
| 008 | IsDebuggerPresent | Checks PEB debug flag via API |
| 009 | CheckRemoteDebuggerPresent | Detects debugger attached to process |
| 011 | ProcessDebugObjectHandle | Queries ProcessDebugObjectHandle |
| 012 | CheckPEB | Directly checks PEB debug flags |
| 013 | SetUnhandledExceptionFilter | Detects debugger takeover of exception handling |
| 014 | CloseHandle | Detects debugger via exception behavior |
| 015 | SetHandleInformation | Uses handle protection to detect debugger |
| 016 | RtlQueryProcessHeapInformation | Detects debugger via heap flags |
| 017 | RtlQueryProcessDebugInformation | Checks heap debug flags |
| 020 | DbgPrint | Detects debugger via exception behavior |
| 021 | GetWriteWatch | Monitors memory for debugger modifications |
| 022 | GetThreadContext | Inspects hardware breakpoint registers |
| 023 | NtSetInformationThread | Hides thread from debugger |
| 024 | NtQueryObject | Looks for DebugObject presence |
| 025 | RaiseException | Detects exception interception by debugger |
| 026 | MemoryBreakpoint | Scans for software breakpoints (INT3) |
| 027 | AntiStepOver | Checks for breakpoint at return address |
| 028 | MemoryBreakpoint (Guard Page) | Uses guard pages to detect debugger |
| 029 | NtQueryVirtualMemory_WorkingSetList | Detects memory page modifications |
| 030 | DbgBreakPoint_patch | Patches DbgBreakPoint to prevent attachment |
| 031 | DbgUiRemoteBreakin_hook | Patches to block debugger attachment |
| 032 | INT3 | Uses INT3 exception to detect debugger |
| 033 | INT3_long | Long form INT3 for detection |
| 034 | INT_2D | Kernel debugger interrupt detection |
| 035 | INT1 | ICEBP instruction for detection |
| 036 | INT1_long | Two-byte INT1 for detection |
| 037 | popfd_trap | Trap flag manipulation to detect debugger |
| 038 | INT1_prefix | Prefixed ICEBP for detection |
| 039 | self_debugging | Attempts to debug itself |

### Anti-Sandbox (9 techniques)

| # | Technique Name | Reason |
|---|---|---|
| 001 | SetErrorMode | Detects sandbox by checking API behavior changes |
| 002 | ForcedRaceConditionSleep | Detects timing modifications in sandbox |
| 003 | CheckProcessList | Scans for analysis tools in process list |
| 004 | CheckLoadedModules | Detects injected analysis DLLs |
| 005 | CheckDeviceNames | Searches registry for VM artifacts |
| 007 | CopyOfNtdll | Loads clean ntdll to bypass sandbox hooks |
| 010 | FindWindow | Searches for analysis tool windows |
| 018 | FindWindow (Debugger Titles) | Searches for debugger windows |
| 019 | GetShellWindow | Checks parent process for sandbox detection |

### Anti-Reversing (0 techniques)

No anti-reversing techniques have been implemented yet. This category is reserved for future techniques that actively hinder reverse engineering through code obfuscation, anti-disassembly, control flow flattening, or other code protection mechanisms.

## Category Distribution

- **Anti-Debugging**: 30 techniques (77%)
- **Anti-Sandbox**: 9 techniques (23%)
- **Anti-Reversing**: 0 techniques (0%)
- **Total**: 39 techniques

## Notes

Some techniques could fit multiple categories:
- **AD054_EnumWindowsProc**: Reclassified from Anti-Sandbox (AS007) to Anti-Debugging as it primarily detects debugger windows
- **AS008_FindWindow**: Can detect both sandboxes and debuggers, categorized as Anti-Sandbox due to broader detection scope
- **AS006_CopyOfNtdll**: Bypasses API hooks commonly used by sandboxes and analysis tools
- **AD012_GetWriteWatch** and **AD020_NtQueryVirtualMemory**: Primarily detect debugger modifications to memory

## Usage in README

Use these categories to:
1. Update the main README technique index table
2. Group techniques in documentation
3. Create visual taxonomy diagrams
4. Filter and sort techniques

---

**Last Updated**: 2026-02-06
**Categories**: 3 (Anti-Debugging, Anti-Sandbox, Anti-Reversing)
