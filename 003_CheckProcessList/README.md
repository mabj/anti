Many malware families implement this technique. Bellow is a Smokeloader sample which implements 
some mechanism similar to what is described in this report.

File Size  234 Kb
File Type  PE32 executable (GUI) Intel 80386, for MS Windows
MD5        4925A0176CCA9F642A21C5D456725194
SHA1       1915EDA9D9BE6B472D1836A85086ED428D8402A4
SHA256     65C1D759EE882CDD157346EB26F725B6BCD3B96443D8A37BF0CA53498DA20174

This method goes through the process list looking for known analysis tools. This same technique can
be implemented in many formats, the main ones are: 

    (i)  using a table of plain text process names; and 
    (ii) using a table of hashed process names. 

Usually it uses the following functions of "Kernel32.dll": "CreateToolhelp32Snapshot", "Process32First"
and "Process32Next".

References:
    - https://docs.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot
