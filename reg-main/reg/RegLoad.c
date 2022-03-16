// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseLoadSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegLoadMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseLoadSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        return FAILURE;
    }

    dwResult = RegLoadKeyW(hKey, pReg->lpSubKey, pReg->lpFileName);
    if (dwResult != ERROR_SUCCESS) return FAILURE;

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseLoadSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"LOAD");
        return FAILURE;
    }
    else {

        // argv[1] = help or key name
        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_LOAD, NO_ARGS);
            return SUCCESS;
        }
        else {

            // Parse key name
            if (CHECKRETURN(ParseRegistryKeyName(pReg, argv[1])))
                return FAILURE;
        }

        // argv[2] = file name to save
        if (argc >= 3 && argv[2][0] != L'/' && argv[2][0] != L'-') {

            pReg->lpFileName = argv[2];
        }
        else {

            DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"EXPORT");
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

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"LOAD");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}