// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"


int VolMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered VolMain() function\n");

    if (argc == 1) {

        wprintf(L"\n");
        return DisplayVolInfo(NULL);
    }
    else {

        for (int i = 1; i < argc;  i++) {

            if (argv[i][0] == L'/') {

                if (argv[i][1] == L'?') {

                    DisplayTextMessage(MSG_HELP_VOL, NO_ARGS);
                    return SUCCESS;
                }
                else {

                    DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                    return FAILURE;
                }
            }
            else {

                if (CHECKRETURN(DisplayVolInfo(argv[i])) && argc > 2) {

                    DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, argv[i]);
                }
            }
        }
    }

    return SUCCESS;
}


BOOL DisplayVolInfo(LPWSTR lpDrivePath) {

    WCHAR szSpecifiedRootDrive[MAX_PATH] = L"";

    if (lpDrivePath == NULL) {

        GetCurrentDirectoryW(MAX_PATH, szSpecifiedRootDrive);

        // Drive root only like "C:\\"
        szSpecifiedRootDrive[3] = L'\0';
    }
    else {

        if (wcslen(lpDrivePath) != 2) {

            DisplayTextMessage(ERROR_INVALID_DRIVE, NO_ARGS);
            return FAILURE;
        }
        else {

            StrCpyW(szSpecifiedRootDrive, lpDrivePath);
            StrCatW(szSpecifiedRootDrive, L"\\");
        }
    }

    WCHAR szVolumeLabel[MAX_PATH + 1] = L"";
    DWORD dwSerialNo = 0;
    WCHAR szFormattedSerialNo[] = L"0000-0000";

    if (CHECKRETURN(GetVolumeInformationW(szSpecifiedRootDrive, szVolumeLabel, MAX_PATH + 1, &dwSerialNo, NULL, NULL, NULL, NULL))) {

        if (GetLastError() == ERROR_INVALID_NAME) {

            DisplayTextMessage(ERROR_INVALID_DRIVE, NO_ARGS);
            return FAILURE;
        }
        else {

            DisplayTextMessage(GetLastError(), NO_ARGS);
            return FAILURE;
        }
    }

    swprintf(szFormattedSerialNo, 10, L"%04X-%04X", HIWORD(dwSerialNo), LOWORD(dwSerialNo));

    DbgPrint(L" Letter: '%c', Label: \"%s\", Serial: \"%s\"(%08X)\n", szSpecifiedRootDrive[0], szVolumeLabel, szFormattedSerialNo, dwSerialNo);

    // Drive letter only like "C"
    szSpecifiedRootDrive[1] = L'\0';

    if (szVolumeLabel[0] ==  L'\0') {

        DisplayTextMessage(MSG_HAS_NO_LABEL, ONE_ARG, szSpecifiedRootDrive);
    }
    else {

        DisplayTextMessage(MSG_DR_VOL_LABEL, TWO_ARGS, szSpecifiedRootDrive, szVolumeLabel);
    }

    DisplayTextMessage(MSG_DR_VOL_SERIAL, ONE_ARG, szFormattedSerialNo);

    return SUCCESS;
}
