// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseAddSwitches(PREG pReg, int argc, LPWSTR argv[]);


BOOL RegAddMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;
    DWORD dwDisposition = 0;

    // Parse command line
    if (CHECKRETURN(ParseAddSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        if ((dwResult = RegCreateKeyExW(pReg->nHKey, pReg->lpValueName, 0, NULL, 0, KEY_WRITE | KEY_READ |
            ((pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) ? KEY_WOW64_32KEY : KEY_WOW64_64KEY), NULL, &hKey, &dwDisposition)) != ERROR_SUCCESS) {

            return FAILURE;
        }
    }

    if (pReg->dwSwitches & SWITCH_SPECIFY_EMPTY || pReg->dwSwitches & SWITCH_SPECIFY_VALUE) {

        PBYTE pData = NULL;

        // check existed value
        if (dwDisposition == REG_OPENED_EXISTING_KEY && pReg->dwSwitches & SWITCH_NO_CONFIRM) {

            // there is specified value already
            if ((dwResult = RegQueryValueExW(hKey, pReg->lpValueName, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS) {

                while (TRUE) {

                    // DisplayTextMessage(MSG_VALUE_OVERWRITE_YES_NO, NO_ARGS);
                    wprintf(L"Value %s exists, overwrite(Yes/No)? ", pReg->lpValueName);

                    WCHAR cResponse = getwchar();
                    if (cResponse == L'y' || cResponse == L'Y') break;
                    else if (cResponse == L'n' || cResponse == L'N') {

                        wprintf(L"The operation was canceled by the user.\r\n");

                        RegCloseKey(hKey);
                        return SUCCESS;
                    }
                }
            }
        }

        // Set value name
        if ((dwResult = RegSetValueExW(hKey, pReg->lpValueName, 0, 0, NULL, 0)) != ERROR_SUCCESS) {

            return FAILURE;
        }

        if (pReg->dwSwitches & SWITCH_SPECIFY_DATA) {

            switch (pReg->dwSpecifyDataType) {

            case REG_BINARY: {

                // Allocate memory for pData (byte size needed half size)
                DWORD dwSpecifyDataSize = wcslen(pReg->lpSpecifyData);
                if ((pData = (PBYTE)calloc((size_t)dwSpecifyDataSize / 2 + (size_t)dwSpecifyDataSize % 2, sizeof(BYTE))) == NULL) {

                    DisplayTextMessage(ERROR_NOT_ENOUGH_MEMORY, NO_ARGS);
                    RegCloseKey(hKey);
                    return FAILURE;
                }

                WCHAR szTwoDigitHexBuff[3] = L"";
                DWORD dwTwoDigitHex = 0;
                DWORD dwBytePosition = 0;
                LPWSTR lpAfterEndPoint = NULL;
                LPWSTR lpData = pReg->lpSpecifyData;

                // Convert every two characters to hex
                while (wcslen(lpData) > 0) {

                    // Save the string two characters at a time
                    szTwoDigitHexBuff[0] = lpData[0];
                    lpData++;

                    if (wcslen(lpData) > 0) {

                        szTwoDigitHexBuff[1] = lpData[0];
                        lpData++;
                    }
                    else szTwoDigitHexBuff[1] = L'0'; // Complement L'0' when half byte

                    // Convert the string to hex
                    dwTwoDigitHex = wcstol(szTwoDigitHexBuff, &lpAfterEndPoint, 16);

                    // Ignored data
                    if (lpAfterEndPoint == NULL) {

                        pData[dwBytePosition] = (BYTE)dwTwoDigitHex;
                        dwBytePosition++;
                    }
                    else {

                        DisplayTextMessage(dwResult, NO_ARGS);
                        if (pData) free(pData);
                        RegCloseKey(hKey);
                        return FAILURE;
                    }
                }

                if ((dwResult = RegSetValueExW(hKey, pReg->lpValueName, 0, pReg->dwSpecifyDataType, pData, dwBytePosition)) != ERROR_SUCCESS) {

                    DisplayTextMessage(dwResult, NO_ARGS);
                    if (pData) free(pData);
                    RegCloseKey(hKey);
                    return FAILURE;
                }

                if (pData) free(pData);
                break;
            }
            case REG_DWORD:
            case REG_DWORD_BIG_ENDIAN: {

                LPWSTR lpAfterEndPoint = NULL;

                // Convert the string to decimal, octal, hex
                DWORD dwDwordData = wcstoul(pReg->lpSpecifyData, &lpAfterEndPoint, 0);

                // Ignored data
                if (lpAfterEndPoint == NULL) {

                    if ((dwResult = RegSetValueExW(hKey, pReg->lpValueName, 0, pReg->dwSpecifyDataType, dwDwordData, sizeof(DWORD))) != ERROR_SUCCESS) {

                        RegCloseKey(hKey);
                        return FAILURE;
                    }
                }
                else {

                    RegCloseKey(hKey);
                    return FAILURE;
                }

                break;
            }
            case 0: // If omitted, REG_SZ is assumed
            case REG_SZ:
            case REG_EXPAND_SZ: {


                if ((dwResult = RegSetValueExW(hKey, pReg->lpValueName, 0, (pReg->dwSpecifyDataType == 0) ? (pReg->dwSpecifyDataType = REG_SZ) : pReg->dwSpecifyDataType,pReg->lpSpecifyData, (wcslen((LPWSTR)pReg->lpSpecifyData) + 1) * sizeof(WCHAR))) != ERROR_SUCCESS) {

                    RegCloseKey(hKey);
                    return FAILURE;
                }

                break;
            }
            case REG_MULTI_SZ: {

                BOOL  bErrorString = FALSE;
                DWORD nSeparator = wcslen(pReg->lpSeparator);
                BOOL bTrailing = FALSE;
                LPWSTR szData = NULL;
                LPWSTR pStart = pReg->lpSpecifyData;
                LPWSTR pEnd = NULL;

                // Replace separator "\0" with '\0' for MULTI_SZ
                DWORD nData = wcslen(pReg->lpSpecifyData);

                if (CHECKRETURN(szData = (LPWSTR)calloc((size_t)nData + 2, sizeof(TCHAR)))) {

                    DisplayTextMessage(ERROR_NOT_ENOUGH_MEMORY, NO_ARGS);
                    RegCloseKey(hKey);
                    return FAILURE;
                }

                LPWSTR pString = szData;

                while (wcslen(pStart) > 0) {

                    pEnd = wcsstr(pStart, pReg->lpSeparator);

                    if (pEnd) {

                        // Specifying double separators in the loaded data is error
                        bTrailing = FALSE;
                        if (pEnd == pStart) {

                            bErrorString = TRUE;
                            break;
                        }
                        else if (wcslen(pEnd) == nSeparator) bTrailing = TRUE;

                        *pEnd = 0;
                    }

                    // do the concatenate only if start is having valid buffer
                    StrCatW(pString, pStart);
                    pString += wcslen(pString) + 1;

                    if (pEnd && bTrailing == FALSE) pStart = pEnd + nSeparator;
                    else break;
                }

                // is empty
                if (CHECKRETURN(StrCmpIW(pReg->lpSpecifyData, pReg->lpSeparator))) {

                    pString = szData + 2;
                    bErrorString = FALSE;
                }
                else pString += 1; // double null terminated string

                if (bErrorString) return FAILURE;
                else {

                    DWORD dwByteToWrite = (DWORD)((pString - szData) * sizeof(TCHAR));

                    if ((dwResult = RegSetValueExW(hKey, pReg->lpValueName, 0, pReg->dwSpecifyDataType, (PBYTE)szData, dwByteToWrite)) != ERROR_SUCCESS) {

                        DisplayTextMessage(dwResult, NO_ARGS);
                        if (szData) free(szData);
                        RegCloseKey(hKey);
                        return FAILURE;
                    }
                }

                if (szData) free(szData);
                break;
            }
            default: return FAILURE;
            }
        }
    }

    RegCloseKey(hKey);
    return SUCCESS;
}

BOOL ParseAddSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
        return FAILURE;
    }
    else {

        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
         || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_ADD_1, NO_ARGS);
            DisplayTextMessage(MSG_HELP_REG_ADD_2, NO_ARGS);
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

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
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

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"ADD");
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/ve"))) {

                if (pReg->lpValueName || pReg->dwSwitches & SWITCH_SPECIFY_EMPTY) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_EMPTY;
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/t"))) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_DATA_TYPE || pReg->dwSpecifyDataType) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                if (i + 1 < argc) {

                    pReg->dwSpecifyDataType = GetRegDataType(argv[i + 1]);
                    pReg->dwSwitches |= SWITCH_SPECIFY_DATA_TYPE;
                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"ADD");
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/s"))) {

                if (pReg->lpSeparator != 0 || pReg->dwSwitches & SWITCH_SPECIFY_SEPATATOR) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                if (i + 1 < argc) {

                    pReg->lpSeparator = argv[i + 1];
                    pReg->dwSwitches |= SWITCH_SPECIFY_SEPATATOR;
                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"ADD");
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/d"))) {

                if (pReg->lpSpecifyData) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                if (i + 1 < argc) {

                    pReg->lpSpecifyData = argv[i + 1];
                    pReg->dwSwitches |= SWITCH_SPECIFY_DATA;
                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"ADD");
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"/f"))) {

                if (pReg->dwSwitches & SWITCH_NO_CONFIRM) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_NO_CONFIRM;
            }
            else if (!StrCmpIW(argv[i], L"/reg:32")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_USE_32ARCH_REG;
            }
            else if (!StrCmpIW(argv[i], L"/reg:64")) {}
            else {

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"ADD");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}
