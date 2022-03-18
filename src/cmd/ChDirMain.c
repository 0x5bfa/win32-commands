// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

BOOL IsTheSameDrive(LPWSTR lpDrivePath);


int ChDirMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered ChDirMain() function\n");

    if (argc == 1) {

        WCHAR szCurrentDirectory[MAX_PATH] = L"";
        GetCurrentDirectoryW(MAX_PATH, szCurrentDirectory);
        wprintf(L"%s\n", szCurrentDirectory);
    }
    else {

        if (CHECKRETURN(StrCmpIW(argv[1], L"/?"))) {

            DisplayTextMessage(MSG_HELP_CHDIR, NO_ARGS);
            return SUCCESS;
        }
        else if (CHECKRETURN(StrCmpIW(argv[1], L"/D"))) {

            if (2 < argc) {

                SetCurrentDirectoryW(argv[2]);
                return SUCCESS;
            }
            else {

                DisplayTextMessage(ERROR_INVALID_NAME, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            if (2 < argc) {

                if (IsTheSameDrive(argv[2]) == TRUE) {

                    SetCurrentDirectoryW(argv[2]);
                }

                return SUCCESS;
            }
            else {

                DisplayTextMessage(ERROR_INVALID_NAME, NO_ARGS);
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}


BOOL IsTheSameDrive(LPWSTR lpDrivePath) {

    WCHAR szCurrentDirectory[MAX_PATH] = L"";
    GetCurrentDirectoryW(MAX_PATH, szCurrentDirectory);

    WCHAR szFullPath[MAX_PATH] = L"";
    GetFullPathNameW(lpDrivePath, MAX_PATH, szFullPath, NULL);

    if (szCurrentDirectory[0] == szFullPath[0]) {

        return TRUE;
    }

    return FALSE;
}
