// @marcos_alvares
// build with "cl.exe main.c /link advapi32.lib"
// https://docs.microsoft.com/en-us/windows/win32/sysinfo/enumerating-registry-subkeys

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <ctype.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

// list restrieved from Smokeloader malware family
const char *BLACKLIST[] = {
    "qemu",
    "virt",
    "vmware",
    "vbox",
    "xen"
};

const char *REGISTRY_KEYS[] = {
    "System\\CurrentControlSet\\Enum\\IDE",
    "System\\CurrentControlSet\\Enum\\SCSI"
};

BOOL _check_tag(char *, char *);
BOOL _scan_key(HKEY, char *);

int main (int argc, char *argv[]) {
    for (unsigned int i=0; i < (sizeof(BLACKLIST)/sizeof(BLACKLIST[0])); i++)
        for (unsigned int u=0; u < (sizeof(REGISTRY_KEYS)/sizeof(REGISTRY_KEYS[0])); u++) {
            if (_check_tag((char *) REGISTRY_KEYS[u], (char *) BLACKLIST[i])) {
                printf("[+] Sandbox has been detected.\n");
                return 0;
            }
        }

    return 0;
}

BOOL _check_tag(char *registry, char *tag) {
    HKEY hTestKey;

    LONG lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT(registry),
        0,
        KEY_READ,
        &hTestKey
    );

    if (lResult == ERROR_SUCCESS)
        if (_scan_key(hTestKey, tag))
            return TRUE;

    RegCloseKey(hTestKey);
    return FALSE;
}

BOOL _scan_key(HKEY hKey, char *tag) {
    TCHAR    achKey[MAX_KEY_LENGTH];         // buffer for subkey name
    DWORD    cbName;                         // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;        // size of class string
    DWORD    cSubKeys=0;                     // number of subkeys
    DWORD    cbMaxSubKey;                    // longest subkey size
    DWORD    cchMaxClass;                    // longest class string
    DWORD    cValues;                        // number of values for key
    DWORD    cchMaxValue;                    // longest value name
    DWORD    cbMaxValueData;                 // longest value data
    DWORD    cbSecurityDescriptor;           // size of security descriptor
    FILETIME ftLastWriteTime;                // last write time

    DWORD i, retCode;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.
    if (cSubKeys) {
        for (i=0; i<cSubKeys; i++) {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey,
                     &cbName,
                     NULL,
                     NULL,
                     NULL,
                     &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS) {
                for(int i = 0; achKey[i]; i++)
                    achKey[i] = tolower(achKey[i]);

                if (strstr((char *)achKey, (char *)tag) != NULL)
                    return TRUE;
            }
        }
    }

    return FALSE;
}
