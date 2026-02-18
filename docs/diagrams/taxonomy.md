# Anti-Analysis Technique Taxonomy

This document contains visual diagrams showing the organization and relationships of anti-analysis techniques in this repository.

## Main Taxonomy

```mermaid
graph TB
    A[Anti-Analysis Techniques<br/>70 Total] --> B[Anti-Debugging<br/>57 techniques<br/>81.4%]
    A --> C[Anti-Sandbox<br/>13 techniques<br/>18.6%]
    A --> D[Anti-Reversing<br/>0 techniques<br/>0%]

    B --> B1[PEB/Process Checks]
    B --> B2[Exception-Based Detection]
    B --> B3[Memory/Breakpoint Detection]
    B --> B4[Self-Protection]
    B --> B5[Timing-Based Detection]

    C --> C1[Environment Detection]
    C --> C2[Hook Detection]
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
    "Anti-Debugging" : 57
    "Anti-Sandbox" : 13
    "Anti-Reversing" : 0
```

## Anti-Debugging Techniques (57)

```mermaid
graph LR
    AD[Anti-Debugging<br/>57 Techniques]

    AD --> PEB[PEB & Process Info<br/>12 techniques]
    AD --> EXC[Exception-Based<br/>14 techniques]
    AD --> MEM[Memory & Breakpoints<br/>7 techniques]
    AD --> SELF[Self-Protection<br/>5 techniques]
    AD --> TIME[Timing-Based<br/>6 techniques]
    AD --> OTHER[Other Detection<br/>13 techniques]

    PEB --> PEB1[AD001: CheckProcessDebugPort]
    PEB --> PEB2[AD002: IsDebuggerPresent]
    PEB --> PEB3[AD003: CheckRemoteDebuggerPresent]
    PEB --> PEB4[AD004: ProcessDebugObjectHandle]
    PEB --> PEB5[AD005: CheckPEB]
    PEB --> PEB6[AD015: NtQueryObject]
    PEB --> PEB7[AD040: ProcessDebugFlags]
    PEB --> PEB8[AD041: NtGlobalFlag]
    PEB --> PEB9[AD042: HeapFlags]
    PEB --> PEB10[AD047: SystemKernelDebuggerInformation]
    PEB --> PEB11[AD050: KUSER_SHARED_DATA]
    PEB --> PEB12[AD051: HEAP_TAIL_CHECKING_ENABLED]

    EXC --> EXC1[AD006: SetUnhandledExceptionFilter]
    EXC --> EXC2[AD007: CloseHandle]
    EXC --> EXC3[AD008: SetHandleInformation]
    EXC --> EXC4[AD011: DbgPrint]
    EXC --> EXC5[AD016: RaiseException]
    EXC --> EXC6[AD023: INT3]
    EXC --> EXC7[AD024: INT3_long]
    EXC --> EXC8[AD025: INT_2D]
    EXC --> EXC9[AD026: INT1]
    EXC --> EXC10[AD027: INT1_long]
    EXC --> EXC11[AD028: popfd_trap]
    EXC --> EXC12[AD029: INT1_prefix]
    EXC --> EXC13[AD052: InstructionCounting]
    EXC --> EXC14[AD053: StackSegment]

    MEM --> MEM1[AD012: GetWriteWatch]
    MEM --> MEM2[AD017: SoftwareBreakpoint]
    MEM --> MEM3[AD018: AntiStepOver]
    MEM --> MEM4[AD019: MemoryBreakpoint]
    MEM --> MEM5[AD020: NtQueryVirtualMemory]
    MEM --> MEM6[AD045: CodeChecksum]
    MEM --> MEM7[AD049: DetectAPIPatch]

    SELF --> SELF1[AD014: NtSetInformationThread]
    SELF --> SELF2[AD021: DbgBreakPoint_patch]
    SELF --> SELF3[AD022: DbgUiRemoteBreakin_hook]
    SELF --> SELF4[AD030: self_debugging]
    SELF --> SELF5[AD034: SwitchDesktop]

    TIME --> TIME1[AD035: GetLocalTime]
    TIME --> TIME2[AD036: GetSystemTime]
    TIME --> TIME3[AD037: GetTickCount]
    TIME --> TIME4[AD038: QueryPerformanceCounter]
    TIME --> TIME5[AD039: timeGetTime]
    TIME --> TIME6[AD043: RDTSC]

    OTHER --> OTH1[AD009: RtlQueryProcessHeapInformation]
    OTHER --> OTH2[AD010: RtlQueryProcessDebugInformation]
    OTHER --> OTH3[AD013: GetThreadContext]
    OTHER --> OTH4[AD031: GenerateConsoleCtrlEvent]
    OTHER --> OTH5[AD032: GetShellWindow]
    OTHER --> OTH6[AD033: FindWindow]
    OTHER --> OTH7[AD044: OpenProcess_CSRSS]
    OTHER --> OTH8[AD046: CreateFileA_Exclusive]
    OTHER --> OTH9[AD048: LoadLibrary]
    OTHER --> OTH10[AD054: EnumWindowsProc]
    OTHER --> OTH11[AD055: DbgSetDebugFilterState]
    OTHER --> OTH12[AD056: SwitchToThread]
    OTHER --> OTH13[AD057: TLSCallback]

    style AD fill:#ffebee
    style PEB fill:#ffcdd2
    style EXC fill:#ef9a9a
    style MEM fill:#e57373
    style SELF fill:#ef5350
    style TIME fill:#ff8a65
    style OTHER fill:#f44336
```

## Anti-Sandbox Techniques (13)

```mermaid
graph LR
    AS[Anti-Sandbox<br/>13 Techniques]

    AS --> ENV[Environment Detection<br/>3 techniques]
    AS --> HOOK[Hook Detection<br/>3 techniques]
    AS --> TIME[Timing Detection<br/>7 techniques]

    ENV --> ENV1[AS003: CheckProcessList]
    ENV --> ENV2[AS004: CheckLoadedModules]
    ENV --> ENV3[AS005: CheckRegistryKeys]

    HOOK --> HOOK1[AS001: SetErrorMode]
    HOOK --> HOOK2[AS006: CopyOfNtdll]
    HOOK --> HOOK3[AS008: BlockInput]

    TIME --> TIME1[AS002: ForcedRaceConditionSleep]
    TIME --> TIME2[AS007: SetTimer]
    TIME --> TIME3[AS009: NtDelayExecution]
    TIME --> TIME4[AS010: WaitForSingleObject]
    TIME --> TIME5[AS011: CreateWaitableTimer]
    TIME --> TIME6[AS012: CreateTimerQueueTimer]
    TIME --> TIME7[AS013: SleepLoop]

    style AS fill:#fff3e0
    style ENV fill:#ffe0b2
    style HOOK fill:#ffcc80
    style TIME fill:#ffb74d
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
        Note over M,D: Runtime Detection (Anti-Debugging)
        M->>S: Check debug flags (PEB, ProcessDebugPort)
        M->>S: Test exception handling
        M->>S: Scan for breakpoints
        M->>S: Measure timing deltas

        alt Debugger Detected
            M->>M: Exit, crash, or decrypt fake payload
        else No Debugger
            M->>M: Continue malicious execution

            Note over M,D: Continuous Protection (Self-Protection)
            M->>M: Patch anti-attach functions
            M->>M: Hide threads
            M->>M: Monitor memory modifications
            M->>M: Switch desktop
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
    Timing-Based
      GetLocalTime
      GetSystemTime
      GetTickCount
      QueryPerformanceCounter
      timeGetTime
      RDTSC
    Behavioral
      Self-Debugging
      Window Enumeration
      Process List
      Console Control Events
      Desktop Switching
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
        C1[Anti-Debugging<br/>56 techniques]
        C2[Anti-Sandbox<br/>13 techniques]
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
        TIMING[Timing Analysis]
    end

    subgraph Specific Techniques
        T002[AD002: IsDebuggerPresent]
        T005[AD005: CheckPEB]
        T009[AD009: RtlQueryProcessHeapInformation]
        T010[AD010: RtlQueryProcessDebugInformation]
        T006[AD006: SetUnhandledExceptionFilter]
        T016[AD016: RaiseException]
        T023[AD023-029: INT Instructions]
        T017[AD017: SoftwareBreakpoint]
        T018[AD018: AntiStepOver]
        T020[AD020: NtQueryVirtualMemory]
        T035[AD035-039: Timing Checks]
    end

    PEB --> T002
    PEB --> T005
    HEAP --> T009
    HEAP --> T010
    EXC --> T006
    EXC --> T016
    EXC --> T023
    MEM --> T017
    MEM --> T018
    MEM --> T020
    TIMING --> T035

    style PEB fill:#e3f2fd
    style HEAP fill:#e8f5e9
    style EXC fill:#fff3e0
    style MEM fill:#fce4ec
    style TIMING fill:#f3e5f5
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

**Last Updated**: 2026-02-18
**Total Techniques**: 70
**Categories**: 3 (Anti-Debugging, Anti-Sandbox, Anti-Reversing)
