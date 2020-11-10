// @marcos_alvares
// build with "vc.exe main.c"

// snxhk.dll - Avast anti-virus;
// SxIn.dll - 360 Total Security;
// vmcheck.dll - Virtual PC;
// cmdvrt32.dll - COMODO Internet Security;
// dbghelp.dll - Debbuging Tools for Windows;
// dir_watch.dll - SunBelt SandBox;
// SbieDll.dll - Sandboxie from tzuk;
// SbieDllX.dll - Sandboxie from tzuk;
// pstorec.dll - rotected Storage COM interfaces;
// wpespy.dll - Winsock Packet Editor (used by sandboxes);
// api_log.dll - SunBelt SandBox;
// Sf2.dll - Avast anti-virus;

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

const char *BLACKLIST[] = {
    "snxhk.dll",
    "SxIn.dll",
    "vmcheck.dll",
    "cmdvrt32.dll",
    "dbghelp.dll",
    "dir_watch.dll",
    "SbieDll.dll",
    "SbieDllX.dll",
    "pstorec.dll",
    "wpespy.dll",
    "api_log.dll",
    "Sf2.dll",
}

int main (int argc, char *argv[]) {


    return 0;
}