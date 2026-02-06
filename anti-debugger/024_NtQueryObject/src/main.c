#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <winternl.h>

enum { ObjectAllTypesInformation = 3 };

#define STATUS_INFO_LENGTH_MISMATCH 0xC0000004

bool __is_debugged() {
    bool bDebugged = false;
    NTSTATUS status;
    LPVOID pMem = NULL;
    ULONG dwMemSize;
    POBJECT_ALL_INFORMATION pObjectAllInfo;
    PBYTE pObjInfoLocation;
    HMODULE hNtdll;
    
    hNtdll = LoadLibraryA("ntdll.dll");
    if (!hNtdll)
        return false;
        
    status = NtQueryObject(
        NULL,
        (OBJECT_INFORMATION_CLASS)ObjectAllTypesInformation,
        &dwMemSize, sizeof(dwMemSize), &dwMemSize);
    if (STATUS_INFO_LENGTH_MISMATCH != (unsigned int)status)
        goto NtQueryObject_Cleanup;

    pMem = VirtualAlloc(NULL, dwMemSize, MEM_COMMIT, PAGE_READWRITE);
    if (!pMem)
        goto NtQueryObject_Cleanup;

    status = NtQueryObject(
        (HANDLE)-1,
        (OBJECT_INFORMATION_CLASS)ObjectAllTypesInformation,
        pMem, dwMemSize, &dwMemSize);
    if (!SUCCEEDED(status))
        goto NtQueryObject_Cleanup;

    pObjectAllInfo = (POBJECT_ALL_INFORMATION)pMem;
    pObjInfoLocation = (PBYTE)pObjectAllInfo->ObjectTypeInformation;

    for(UINT i = 0; i < pObjectAllInfo->NumberOfObjects; i++)
    {
        POBJECT_TYPE_INFORMATION pObjectTypeInfo =
            (POBJECT_TYPE_INFORMATION)pObjInfoLocation;

        if (wcscmp(L"DebugObject", pObjectTypeInfo->TypeName.Buffer) == 0)
        {
            if (pObjectTypeInfo->TotalNumberOfObjects > 0)
                bDebugged = true;
            break;
        }

		// Get the address of the current entries
		// string so we can find the end
		pObjInfoLocation = (unsigned char*)pObjectTypeInfo->TypeName.Buffer;

		// Add the size
		pObjInfoLocation += pObjectTypeInfo->TypeName.MaximumLength;

		// Skip the trailing null and alignment bytes
		ULONG_PTR tmp = ((ULONG_PTR)pObjInfoLocation) & -(int)sizeof(void*);

		// Not pretty but it works
		if ((ULONG_PTR)tmp != (ULONG_PTR)pObjInfoLocation)
			tmp += sizeof(void*);
        
        pObjInfoLocation = ((unsigned char*)tmp);
    }

NtQueryObject_Cleanup:
    if (pMem)
        VirtualFree(pMem, 0, MEM_RELEASE);

    return bDebugged;
}

int main() {
    if(__is_debugged())
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Anti-debug 024", MB_OK);
    else
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Anti-debug 024", MB_OK);

    return 0;
}