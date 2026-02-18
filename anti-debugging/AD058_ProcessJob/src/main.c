#include <windows.h>
#include <stdio.h>
#include <psapi.h>

BOOL __check_process_job(void) {
	BOOL is_debugged = FALSE;

	DWORD jobProcessStructSize = sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST) + sizeof(ULONG_PTR) * 1024;
	JOBOBJECT_BASIC_PROCESS_ID_LIST* jobProcessIdList = (JOBOBJECT_BASIC_PROCESS_ID_LIST *)(malloc(jobProcessStructSize));

	if (jobProcessIdList) {

		SecureZeroMemory(jobProcessIdList, jobProcessStructSize);

		jobProcessIdList->NumberOfProcessIdsInList = 1024;

		if (QueryInformationJobObject(NULL, JobObjectBasicProcessIdList, jobProcessIdList, jobProcessStructSize, NULL)) {
			DWORD ok_processes = 0;
			for (DWORD i = 0; i < jobProcessIdList->NumberOfAssignedProcesses; i++) {
				ULONG_PTR processId = jobProcessIdList->ProcessIdList[i];

				// is this the current process? if so that's ok
				if (processId == (ULONG_PTR)GetCurrentProcessId()) {
					ok_processes++;
				} else {
					HANDLE hJobProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, (DWORD)processId);
					if (hJobProcess != NULL) {
						const int processNameBufferSize = 4096;
						char *processName = (char *)(malloc(sizeof(char) * processNameBufferSize));
						if (processName) {
							SecureZeroMemory(processName, sizeof(char) * processNameBufferSize);

							if (GetProcessImageFileNameA(hJobProcess, processName, processNameBufferSize) > 0) {
								if (strstr(processName, "conhost.exe") != 0) {
									ok_processes++;
								}
							}
							free(processName);
						}
						CloseHandle(hJobProcess);
					}
				}
			}

			// if we found other processes in the job other than the current process and conhost, report a problem
			is_debugged = ok_processes != jobProcessIdList->NumberOfAssignedProcesses;
		}

		free(jobProcessIdList);
	}
	return is_debugged;
}

int main(void) {
    BOOL is_debugged = __check_process_job();

    if (is_debugged) {
        MessageBoxA(NULL, "[+] The process is in Debug mode.", "Process Job", MB_OK | MB_ICONWARNING);
    } else {
        MessageBoxA(NULL, "[+] The process is NOT in Debug mode.", "Process Job", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}
