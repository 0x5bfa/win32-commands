// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseDeleteSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegDeleteMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseDeleteSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    if (!(pReg->dwSwitches & SWITCH_NO_CONFIRM)) {

        while (TRUE) {

            // DisplayTextMessage(MSG_VALUE_OVERWRITE_YES_NO, NO_ARGS);
            wprintf(L"Permanently delete the registry key %s (Yes/No)? ", pReg->lpFullKey);

            WCHAR cResponse = getwchar();
            if (cResponse == L'y' || cResponse == L'Y') break;
            else if (cResponse == L'n' || cResponse == L'N') {

                wprintf(L"The operation was canceled by the user.\r\n");

                RegCloseKey(hKey);
                return SUCCESS;
            }
        }
    }

    // Delete
    if (pReg->dwSwitches & SWITCH_SPECIFY_EMPTY) {

        RegDeleteValueW(hKey, L"");
    }
    else if (pReg->dwSwitches & SWITCH_SPECIFY_VALUE) {

        RegDeleteValueW(hKey, pReg->lpValueName);
    }
    else if (pReg->dwSwitches & SWITCH_DELETE_ALL_VALUES) {

        RegDeleteTreeW(hKey, L"");
    }
    else {

        RegDeleteKeyW(hKey, L"");
    }

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseDeleteSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
        return FAILURE;
    }
    else {

        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_DELETE, NO_ARGS);
            return SUCCESS;
        }
        else {

            // Parse key name
            if (CHECKRETURN(ParseRegistryKeyName(pReg, argv[1])))
                return FAILURE;
        }

        for (int i = 2; i < argc; i++) {

            if (CHECKRETURN(StrCmpIW(argv[i], L"/v"))) {

                if (pReg->lpValueName) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                    return FAILURE;
                }

                if (i + 1 < argc) {

                    // Is serch parameter value
                    if (StrStrW(argv[i + 1], L"*") || StrStrW(argv[i + 1], L"?")) {

                        pReg->lpFindPattern = argv[i + 1];
                        pReg->dwSwitches |= SWITCH_SPECIFY_FIND_PATTERN;
                        pReg->dwSwitches |= SWITCH_FIND_DATA_ONLY;

                        // Delete L'*' or L'?'
                        for (int j = 0; j < wcslen(pReg->lpFindPattern); j++) {

                            if (pReg->lpFindPattern[j] == L'*' || pReg->lpFindPattern[j] == L'?') {

                                // Sort
                                for (int k = j; k < (wcslen(pReg->lpFindPattern) - j); k++)
                                    pReg->lpFindPattern[j] = pReg->lpFindPattern[j + 1];

                                j--;
                            }
                        }

                        pReg->lpFindPattern[wcslen(pReg->lpFindPattern) - 1] = L'\0';
                    }
                    else {

                        pReg->lpValueName = argv[i + 1];
                        pReg->dwSwitches |= SWITCH_SPECIFY_VALUE;
                    }

                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"DELETE");
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/ve"))) {

                if (pReg->lpValueName || pReg->dwSwitches & SWITCH_SPECIFY_EMPTY) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_EMPTY;
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/va"))) {

                if (pReg->lpValueName || pReg->dwSwitches & SWITCH_DELETE_ALL_VALUES) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_DELETE_ALL_VALUES;
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/f"))) {

                if (pReg->dwSwitches & SWITCH_NO_CONFIRM) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_NO_CONFIRM;
            }
            else if (!StrCmpIW(argv[i], L"/reg:32")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_USE_32ARCH_REG;
            }
            else if (!StrCmpIW(argv[i], L"/reg:64")) {}
            else {

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"DELETE");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}
