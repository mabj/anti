#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <wchar.h>  // For wcslen

// Define necessary types and structures for NtCreateMutant
typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;
    PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

#define OBJ_CASE_INSENSITIVE    0x00000040L

// Function to generate random 6-character string
char* generate_random_string(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* random_string = malloc(length + 1);
    
    if (random_string) {
        for (size_t i = 0; i < length; i++) {
            int key = rand() % (int)(sizeof(charset) - 1);
            random_string[i] = charset[key];
        }
        random_string[length] = '\0';
    }
    return random_string;
}

int main() {
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Generate random 6-character filename
    char* random_name = generate_random_string(6);
    if (!random_name) {
        MessageBoxA(NULL, "Failed to generate random name", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    
    // Build destination path in TEMP directory
    char temp_path[MAX_PATH];
    GetTempPathA(MAX_PATH, temp_path);
    
    char dest_path[MAX_PATH];
    snprintf(dest_path, MAX_PATH, "%s%s.dll", temp_path, random_name);
    
    // Copy ntdll.dll to TEMP directory
    char system_dir[MAX_PATH];
    GetSystemDirectoryA(system_dir, MAX_PATH);
    
    char src_path[MAX_PATH];
    snprintf(src_path, MAX_PATH, "%s\\ntdll.dll", system_dir);
    
    if (!CopyFileA(src_path, dest_path, FALSE)) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Failed to copy ntdll.dll: Error %lu", GetLastError());
        MessageBoxA(NULL, error_msg, "Error", MB_OK | MB_ICONERROR);
        free(random_name);
        return 1;
    }
    
    // Load the copied DLL
    HMODULE hNtdllCopy = LoadLibraryA(dest_path);
    if (!hNtdllCopy) {
        char error_msg[100];
        snprintf(error_msg, sizeof(error_msg), "Failed to load DLL: Error %lu", GetLastError());
        MessageBoxA(NULL, error_msg, "Error", MB_OK | MB_ICONERROR);
        free(random_name);
        return 1;
    }
    
    // Get address of NtCreateMutant
    FARPROC pNtCreateMutant = GetProcAddress(hNtdllCopy, "NtCreateMutant");
    if (!pNtCreateMutant) {
        MessageBoxA(NULL, "Failed to get NtCreateMutant address", "Error", MB_OK | MB_ICONERROR);
        FreeLibrary(hNtdllCopy);
        free(random_name);
        return 1;
    }
    
    // Create the named Mutex "FLAG"
    UNICODE_STRING mutexName;
    WCHAR mutexNameBuffer[] = L"\\BaseNamedObjects\\FLAG";
    mutexName.Buffer = mutexNameBuffer;
    mutexName.Length = wcslen(mutexNameBuffer) * sizeof(WCHAR);
    mutexName.MaximumLength = mutexName.Length + sizeof(WCHAR);

    OBJECT_ATTRIBUTES objectAttributes = {0};
    objectAttributes.Length = sizeof(OBJECT_ATTRIBUTES);
    objectAttributes.ObjectName = &mutexName;
    objectAttributes.Attributes = OBJ_CASE_INSENSITIVE;

    HANDLE hMutex;
    NTSTATUS status = pNtCreateMutant(&hMutex, GENERIC_ALL, &objectAttributes, FALSE);
    if (status != 0) {
        char status_msg[100];
        snprintf(status_msg, sizeof(status_msg), "NtCreateMutant failed: 0x%lX", status);
        MessageBoxA(NULL, status_msg, "Error", MB_OK | MB_ICONERROR);
    } else {
        MessageBoxA(NULL, "Mutex 'FLAG' created successfully", "Success", MB_OK);
        CloseHandle(hMutex);
    }
    
    // Cleanup
    FreeLibrary(hNtdllCopy);
    free(random_name);
    
    return 0;
}