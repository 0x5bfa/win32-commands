// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseRestoreSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegRestoreMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseRestoreSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        return FAILURE;
    }

    // Acquire the necessary privileges
    if (CHECKRETURN(EnableTokenPrivileges(pReg->lpMachineName, SE_RESTORE_NAME, SE_PRIVILEGE_ENABLED))) {

        return FAILURE;
    }

    if ((dwResult = RegRestoreKeyW(hKey, pReg->lpFileName, 0)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseRestoreSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"RESTORE");
        return FAILURE;
    }
    else {

        // argv[1] = help or key name
        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_RESTORE, NO_ARGS);
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

            DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"RESTORE");
            return FAILURE;
        }

        for (int i = 3; i < argc; i++) {

            if (!StrCmpIW(argv[i], L"/reg:32")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG)
                    return FAILURE;

                pReg->dwSwitches |= SWITCH_SPECIFY_USE_32ARCH_REG;
            }
            else if (!StrCmpIW(argv[i], L"/reg:64")) {}
            else {

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"RESTORE");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}
