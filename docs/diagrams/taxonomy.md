# Anti-Analysis Technique Taxonomy

This document contains visual diagrams showing the organization and relationships of anti-analysis techniques in this repository.

## Main Taxonomy

```mermaid
graph TB
    A[Anti-Analysis Techniques<br/>39 Total] --> B[Anti-Debugger<br/>30 techniques<br/>77%]
    A --> C[Anti-Sandbox<br/>9 techniques<br/>23%]
    A --> D[Anti-Reversing<br/>0 techniques<br/>0%]

    B --> B1[PEB/Process Checks]
    B --> B2[Exception-Based Detection]
    B --> B3[Memory/Breakpoint Detection]
    B --> B4[Self-Protection]

    C --> C1[Environment Detection]
    C --> C2[VM/Sandbox Artifacts]
    C --> C3[Timing Checks]

    D --> D1[Future: Code Obfuscation]
    D --> D2[Future: Anti-Disassembly]

    style A fill:#e1f5ff
    style B fill:#ffebee
    style C fill:#fff3e0
    style D fill:#f3e5f5
```

## Distribution Chart

```mermaid
pie title Technique Distribution by Category
    "Anti-Debugger" : 30
    "Anti-Sandbox" : 9
    "Anti-Reversing" : 0
```

## Anti-Debugger Techniques (30)

```mermaid
graph LR
    AD[Anti-Debugger<br/>30 Techniques]

    AD --> PEB[PEB & Process Info<br/>6 techniques]
    AD --> EXC[Exception-Based<br/>11 techniques]
    AD --> MEM[Memory & Breakpoints<br/>5 techniques]
    AD --> SELF[Self-Protection<br/>5 techniques]
    AD --> OTHER[Other Detection<br/>3 techniques]

    PEB --> PEB1[006: CheckProcessDebugPort]
    PEB --> PEB2[008: IsDebuggerPresent]
    PEB --> PEB3[009: CheckRemoteDebuggerPresent]
    PEB --> PEB4[011: ProcessDebugObjectHandle]
    PEB --> PEB5[012: CheckPEB]
    PEB --> PEB6[024: NtQueryObject]

    EXC --> EXC1[013: SetUnhandledExceptionFilter]
    EXC --> EXC2[014: CloseHandle]
    EXC --> EXC3[015: SetHandleInformation]
    EXC --> EXC4[020: DbgPrint]
    EXC --> EXC5[025: RaiseException]
    EXC --> EXC6[032: INT3]
    EXC --> EXC7[033: INT3_long]
    EXC --> EXC8[034: INT_2D]
    EXC --> EXC9[035: INT1]
    EXC --> EXC10[036: INT1_long]
    EXC --> EXC11[037: popfd_trap]
    EXC --> EXC12[038: INT1_prefix]

    MEM --> MEM1[021: GetWriteWatch]
    MEM --> MEM2[026: MemoryBreakpoint]
    MEM --> MEM3[027: AntiStepOver]
    MEM --> MEM4[028: Guard Page]
    MEM --> MEM5[029: NtQueryVirtualMemory]

    SELF --> SELF1[023: NtSetInformationThread]
    SELF --> SELF2[030: DbgBreakPoint_patch]
    SELF --> SELF3[031: DbgUiRemoteBreakin_hook]
    SELF --> SELF4[039: self_debugging]

    OTHER --> OTH1[016: RtlQueryProcessHeapInformation]
    OTHER --> OTH2[017: RtlQueryProcessDebugInformation]
    OTHER --> OTH3[022: GetThreadContext]

    style AD fill:#ffebee
    style PEB fill:#ffcdd2
    style EXC fill:#ef9a9a
    style MEM fill:#e57373
    style SELF fill:#ef5350
    style OTHER fill:#f44336
```

## Anti-Sandbox Techniques (9)

```mermaid
graph LR
    AS[Anti-Sandbox<br/>9 Techniques]

    AS --> ENV[Environment Detection<br/>5 techniques]
    AS --> HOOK[Hook Detection<br/>2 techniques]
    AS --> TIME[Timing Detection<br/>1 technique]
    AS --> PROC[Process Detection<br/>1 technique]

    ENV --> ENV1[003: CheckProcessList]
    ENV --> ENV2[004: CheckLoadedModules]
    ENV --> ENV3[005: CheckDeviceNames]
    ENV --> ENV4[010: FindWindow]
    ENV --> ENV5[018: FindWindow Debuggers]

    HOOK --> HOOK1[001: SetErrorMode]
    HOOK --> HOOK2[007: CopyOfNtdll]

    TIME --> TIME1[002: ForcedRaceConditionSleep]

    PROC --> PROC1[019: GetShellWindow]

    style AS fill:#fff3e0
    style ENV fill:#ffe0b2
    style HOOK fill:#ffcc80
    style TIME fill:#ffb74d
    style PROC fill:#ffa726
```

## Technique Timeline (Execution Flow)

```mermaid
sequenceDiagram
    participant M as Malware
    participant S as System
    participant D as Debugger/Sandbox

    Note over M,D: Early Detection (Anti-Sandbox)
    M->>S: Check environment (VM, processes, modules)
    S-->>M: System information

    alt Sandbox Detected
        M->>M: Exit or behave normally
    else No Sandbox
        Note over M,D: Runtime Detection (Anti-Debugger)
        M->>S: Check debug flags (PEB, ProcessDebugPort)
        M->>S: Test exception handling
        M->>S: Scan for breakpoints

        alt Debugger Detected
            M->>M: Exit, crash, or decrypt fake payload
        else No Debugger
            M->>M: Continue malicious execution

            Note over M,D: Continuous Protection (Self-Protection)
            M->>M: Patch anti-attach functions
            M->>M: Hide threads
            M->>M: Monitor memory modifications
        end
    end
```

## Detection Method Categories

```mermaid
mindmap
  root((Anti-Analysis<br/>Detection Methods))
    API-Based
      IsDebuggerPresent
      CheckRemoteDebuggerPresent
      NtQueryInformationProcess
      NtQueryObject
    Direct Inspection
      PEB Flags
      Heap Flags
      Thread Context
      Memory Scanning
    Exception-Based
      INT3 Variants
      CloseHandle
      UnhandledExceptionFilter
      DbgPrint
    Behavioral
      Timing Checks
      Self-Debugging
      Window Enumeration
      Process List
    Protection
      Function Patching
      Thread Hiding
      Memory Monitoring
      Hook Bypass
```

## Effectiveness Matrix

```mermaid
graph TB
    subgraph Detection Targets
        T1[User-Mode Debuggers<br/>x64dbg, OllyDbg, WinDbg]
        T2[Kernel Debuggers<br/>WinDbg Kernel Mode]
        T3[Sandboxes<br/>Cuckoo, Any.run, Joe Sandbox]
        T4[VMs<br/>VirtualBox, VMware, Hyper-V]
        T5[Instrumentation<br/>PIN, DynamoRIO, Frida]
    end

    subgraph Technique Categories
        C1[Anti-Debugger<br/>30 techniques]
        C2[Anti-Sandbox<br/>9 techniques]
    end

    C1 -.High Effectiveness.-> T1
    C1 -.Medium Effectiveness.-> T2
    C1 -.Low Effectiveness.-> T5

    C2 -.High Effectiveness.-> T3
    C2 -.High Effectiveness.-> T4
    C2 -.Medium Effectiveness.-> T5

    style C1 fill:#ffebee
    style C2 fill:#fff3e0
```

## Related Techniques Network

```mermaid
graph TD
    subgraph Core Detection Methods
        PEB[PEB Inspection]
        HEAP[Heap Flags]
        EXC[Exception Handling]
        MEM[Memory Scanning]
    end

    subgraph Specific Techniques
        T008[008: IsDebuggerPresent]
        T012[012: CheckPEB]
        T016[016: RtlQueryProcessHeapInformation]
        T017[017: RtlQueryProcessDebugInformation]
        T013[013: SetUnhandledExceptionFilter]
        T025[025: RaiseException]
        T032[032-038: INT Instructions]
        T026[026: MemoryBreakpoint]
        T027[027: AntiStepOver]
        T029[029: NtQueryVirtualMemory]
    end

    PEB --> T008
    PEB --> T012
    HEAP --> T016
    HEAP --> T017
    EXC --> T013
    EXC --> T025
    EXC --> T032
    MEM --> T026
    MEM --> T027
    MEM --> T029

    style PEB fill:#e3f2fd
    style HEAP fill:#e8f5e9
    style EXC fill:#fff3e0
    style MEM fill:#fce4ec
```

## Usage Examples

### Including in README
```markdown
## Technique Taxonomy

![Taxonomy](docs/diagrams/taxonomy.md#main-taxonomy)
```

### Filtering by Category
- Use the categorization to filter techniques in documentation
- Group related techniques when discussing detection strategies
- Show progression from simple to complex methods

---

**Last Updated**: 2026-02-06
**Total Techniques**: 39
**Categories**: 3 (Anti-Debugger, Anti-Sandbox, Anti-Reversing)
