// Definitions for the internal structures

#define PDI_HEAPS   0x04
#define PDI_HEAP_BLOCKS   0x10

// Use ULONG_PTR for fields that need to scale with architecture
typedef struct _RTL_HEAP_INFORMATION {
    PVOID Base;
    ULONG Flags;
    USHORT EntryOverhead;
    USHORT CreatorBackTraceIndex;
    SIZE_T BytesAllocated;
    SIZE_T BytesCommitted;
    ULONG NumberOfTags;
    ULONG NumberOfEntries;
    ULONG NumberOfPseudoTags;
    ULONG PseudoTagGranularity;
    ULONG Reserved[5];
    PVOID Tags;
    PVOID Blocks;
} RTL_HEAP_INFORMATION, *PRTL_HEAP_INFORMATION;

typedef struct _RTL_PROCESS_HEAPS {
    ULONG NumberOfHeaps;
#ifdef _WIN64
    ULONG Reserved; // 4-byte padding required for 64-bit alignment
#endif
    RTL_HEAP_INFORMATION Heaps[1];
} RTL_PROCESS_HEAPS, *PRTL_PROCESS_HEAPS;

typedef struct _RTL_DEBUG_INFORMATION {
  HANDLE SectionHandle;
  PVOID  SectionBase;
  PVOID  RemoteSectionBase;
  ULONG  SectionBaseDelta;
  HANDLE EventPairHandle;
  SIZE_T Unknown[2];
  HANDLE RemoteThreadHandle;
  ULONG  InfoClassMask;
  SIZE_T SizeOfInfo;
  SIZE_T AllocatedSize;
  ULONG  SectionSize;
  PVOID  ModuleInformation;
  PVOID  BackTraceInformation;
  PVOID  HeapInformation;
  PVOID  LockInformation;
  PVOID  Reserved[8];
} RTL_DEBUG_INFORMATION, *PRTL_DEBUG_INFORMATION;

// Function Prototypes
PRTL_DEBUG_INFORMATION NTAPI RtlCreateQueryDebugBuffer(ULONG Size, BOOLEAN EventPair);
NTSTATUS NTAPI RtlQueryProcessHeapInformation(PRTL_DEBUG_INFORMATION DebugBuffer);
NTSTATUS NTAPI RtlQueryProcessDebugInformation(ULONG ProcessId, ULONG DebugInfoClassMask, PRTL_DEBUG_INFORMATION DebugBuffer);