// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseUnLoadSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegUnLoadMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseUnLoadSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        return FAILURE;
    }

    if ((dwResult = RegUnLoadKeyW(hKey, pReg->lpSubKey)) != ERROR_SUCCESS) return FAILURE;

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseUnLoadSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"LOAD");
        return FAILURE;
    }
    else {

        // argv[1] = help or key name
        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_UNLOAD, NO_ARGS);
            return SUCCESS;
        }
        else {

            // Parse key name
            if (CHECKRETURN(ParseRegistryKeyName(pReg, argv[1])))
                return FAILURE;
        }

        if (argc > 2) return FAILURE;
    }

    return SUCCESS;
}