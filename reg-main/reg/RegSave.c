// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseSaveSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegSaveMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseSaveSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        return FAILURE;
    }

    // Acquire the necessary privileges
    if (EnableTokenPrivileges(pReg->lpMachineName, SE_BACKUP_NAME, SE_PRIVILEGE_ENABLED) != SUCCESS) {

        return FAILURE;
    }

    if ((dwResult = RegSaveKeyW(hKey, pReg->lpFileName, NULL)) != ERROR_SUCCESS) {

        if (dwResult == ERROR_ALREADY_EXISTS) { // Overwrite

            if (!(pReg->dwSwitches & SWITCH_NO_CONFIRM)) {

                while (TRUE) {

                    wprintf(L"File %s already exists. Overwrite (Yes/No)?", pReg->lpFileName);

                    WCHAR cResponse = getwchar();
                    if (cResponse == L'y' || cResponse == L'Y') break;
                    else if (cResponse == L'n' || cResponse == L'N') {

                        wprintf(L"The operation was canceled by the user.\r\n");

                        RegCloseKey(hKey);
                        return SUCCESS;
                    }
                }
            }

            // Delete previous file
            if (DeleteFileW(pReg->lpFileName) == FAILURE) {

                DisplayTextMessage(GetLastError(), NO_ARGS);
                return FAILURE;
            }

            if ((dwResult = RegSaveKeyW(hKey, pReg->lpFileName, NULL)) != ERROR_SUCCESS) {

                DisplayTextMessage(dwResult, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            DisplayTextMessage(dwResult, NO_ARGS);
            return FAILURE;
        }
    }

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseSaveSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"SAVE");
        return FAILURE;
    }
    else {

        // argv[1] = help or key name
        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_SAVE, NO_ARGS);
            return SUCCESS;
        }
        else {

            // Parse key name
            if (CHECKRETURN(ParseRegistryKeyName(pReg, argv[1])))
                return FAILURE;
        }

        //argv[2] = file name to save
        if (argc >= 3 && argv[2][0] != L'/' && argv[2][0] != L'-') {

            pReg->lpFileName = argv[2];
        }
        else {

            DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"EXPORT");
            return FAILURE;
        }

        for (int i = 3; i < argc; i++) {

            if (CHECKRETURN(StrCmpIW(argv[i], L"/y"))) {

                if (pReg->dwSwitches & SWITCH_NO_CONFIRM) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"SAVE");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_NO_CONFIRM;
            }
            else if (!StrCmpIW(argv[i], L"/reg:32")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG)
                    return FAILURE;

                pReg->dwSwitches |= SWITCH_SPECIFY_USE_32ARCH_REG;
            }
            else if (!StrCmpIW(argv[i], L"/reg:64")) {}
            else {

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"SAVE");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}
