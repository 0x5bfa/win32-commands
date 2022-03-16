// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"


int VerMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered VerMain() function\n");

    BOOL bResult = FAILURE;

    if (argc == 1) {

        wprintf(L"\n");
        return GetWindowsVersion();
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_VER, NO_ARGS);
                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            wprintf(L"\n");
            return GetWindowsVersion();
        }

    }

    return SUCCESS;
}


BOOL GetWindowsVersion(void) {

#pragma warning(push)
#pragma warning (disable: 28159)

    // Get windows version
    DWORD dwVersion = GetVersion();

#pragma warning(pop)

    DWORD dwResult = ERROR_SUCCESS;
    DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    DWORD dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    DWORD dwBuildVersion = 0;
    if (dwVersion < 0x80000000) dwBuildVersion = (DWORD)(HIWORD(dwVersion));

    // Get minor build version from windows registry
    HKEY hKey = NULL;
    if ((dwResult = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_WOW64_64KEY | KEY_READ, &hKey)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    BYTE byUBR[4] = { 0 };
    DWORD cbData = sizeof(byUBR);

    if ((dwResult = RegQueryValueExW(hKey, L"UBR", NULL, NULL, &byUBR, &cbData)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    WCHAR szFormattedVersionString[64] = L"";
    swprintf(szFormattedVersionString, 64, L"%d.%d.%d.%d", dwMajorVersion, dwMinorVersion, dwBuildVersion, *(LPDWORD)byUBR);

    DbgPrint(L" Mj ver: %d, Mn ver: %d, Build ver: %d, Update build revision(UBR): %d\n", dwMajorVersion, dwMinorVersion, dwBuildVersion, *(LPDWORD)byUBR);

    DisplayTextMessage(MSG_MS_DOS_VERSION, TWO_ARGS, szFormattedVersionString);
    wprintf(L"\n");

    return SUCCESS;
}
