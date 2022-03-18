// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "RegMain.h"

WCHAR szDefaultPattern[] = L"\0";

BOOL ParseQuerySwitches(PREG pReg, int argc, LPWSTR argv[]);
BOOL EnumRegistryKeysAndValues(PREG pReg, HKEY hKey, LPWSTR lpSubRoot);
BOOL QueryRegistryValue(PREG pReg, HKEY hKey, DWORD nValues, DWORD dwIndex);
BOOL GetRegEmptyValue(PREG pReg, HKEY hKey);
BOOL WildCardMatched(LPWSTR lpTarget, LPWSTR lpWildCard);


BOOL RegQueryMain(PREG pReg, int argc, LPWSTR argv[]) {

    HKEY hKey = NULL;

    // Parse command line
    if (CHECKRETURN(ParseQuerySwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_READ)))
        return FAILURE;

    // Specified empty value name known as "(defaut)"
    if (pReg->dwSwitches & SWITCH_SPECIFY_EMPTY) {

        return GetRegEmptyValue(pReg, hKey);
    }
    // Specified value name
    else if (pReg->lpValueName) {

        return QueryRegistryValue(pReg, hKey, 0, 0);
    }

    // Enumerate the key
    if (CHECKRETURN(EnumRegistryKeysAndValues(pReg, hKey, pReg->lpSubKey)))
        return FAILURE;

    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseQuerySwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
        return FAILURE;
    }
    else {

        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_QUERY_1, NO_ARGS);
            DisplayTextMessage(MSG_HELP_REG_QUERY_2, NO_ARGS);
            DisplayTextMessage(MSG_HELP_REG_QUERY_3, NO_ARGS);
            return SUCCESS;
        }
        else {

            // Parse key name
            if (CHECKRETURN(ParseRegistryKeyName(pReg, argv[1])))
                return FAILURE;
        }

        // Start parsing
        for (int i = 2; i < argc; i++) {

            if (!StrCmpIW(argv[i], L"/v")) {

                if (pReg->lpValueName) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                if (i < argc - 1) {

                    // Specified value containing wildcards for search
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
                        i++;
                    }
                    else {

                        pReg->lpValueName = argv[i + 1];
                        pReg->dwSwitches |= SWITCH_SPECIFY_VALUE;
                    }

                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"QUERY");
                    return FAILURE;
                }
            }
            else if (!StrCmpIW(argv[i], L"/ve")) {

                if (pReg->lpValueName != NULL || pReg->dwSwitches & SWITCH_SPECIFY_EMPTY) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_EMPTY;
            }
            else if (!StrCmpIW(argv[i], L"/s")) {

                if (pReg->dwSwitches & SWITCH_RECURSE) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_RECURSE;
            }
            else if (!StrCmpIW(argv[i], L"/se")) {

                if (pReg->lpSeparator != 0 || pReg->dwSwitches & SWITCH_SPECIFY_SEPATATOR) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                if (i < argc - 1) {

                    pReg->lpSeparator = argv[i + 1];
                    pReg->dwSwitches |= SWITCH_SPECIFY_SEPATATOR;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"QUERY");
                    return FAILURE;
                }
            }
            else if (!StrCmpIW(argv[i], L"/f")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                if (i < argc - 1) {

                    pReg->lpFindPattern = argv[i + 1];
                    pReg->dwSwitches |= SWITCH_SPECIFY_FIND_PATTERN;

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
                    i++;
                }
                else {

                    DisplayTextMessage(MSG_INVALID_KEY_NAME, ONE_ARG, L"QUERY");
                    return FAILURE;
                }
            }
            else if (!StrCmpIW(argv[i], L"/k")) {

                if (pReg->dwSwitches & SWITCH_FIND_KEY_ONLY || pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_FIND_KEY_ONLY;
            }
            else if (!StrCmpIW(argv[i], L"/d")) {

                if (pReg->dwSwitches & SWITCH_FIND_DATA_ONLY || pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_FIND_DATA_ONLY;
            }
            else if (!StrCmpIW(argv[i], L"/c")) {

                if (pReg->dwSwitches & SWITCH_CASE_SENSITIVE) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_CASE_SENSITIVE;
            }
            else if (!StrCmpIW(argv[i], L"/e")) {

                if (pReg->dwSwitches & SWITCH_EXACT_MATCHES_ONLY) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_EXACT_MATCHES_ONLY;
            }
            else if (!StrCmpIW(argv[i], L"/t")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_DATA_TYPE || pReg->dwSpecifyDataType) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSpecifyDataType = GetRegDataType(argv[i]);
                pReg->dwSwitches |= SWITCH_SPECIFY_DATA_TYPE;
            }
            else if (!StrCmpIW(argv[i], L"/z")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_NUMERIC_EQUAL) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_NUMERIC_EQUAL;
            }
            else if (!StrCmpIW(argv[i], L"/reg:32")) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) {

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                    return FAILURE;
                }

                pReg->dwSwitches |= SWITCH_SPECIFY_USE_32ARCH_REG;
            }
            else if (!StrCmpIW(argv[i], L"/reg:64")) {}
            else {

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"QUERY");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}


BOOL EnumRegistryKeysAndValues(PREG pReg, HKEY hKey, LPWSTR lpSubRoot) {

    DWORD dwResult = ERROR_SUCCESS;
    DWORD dwMaxKeyNameSize = 0;
    DWORD dwMaxValueNameSize = 0;
    DWORD nKeys = 0;
    DWORD nValues = 0;
    DWORD dwMatches = 0;
    DWORD dwType = 0;
    DWORD dwNeededValueNameSize = 0;

    // Get max key size
    if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, &nKeys, &dwMaxKeyNameSize, NULL, &nValues, &dwMaxValueNameSize, NULL, NULL, NULL) != ERROR_SUCCESS)
        return FAILURE;


    // Enumerate all of the values
    if (!(pReg->dwSwitches & SWITCH_FIND_KEY_ONLY)) {

        // Allocate memory for lpValueName
        if (CHECKRETURN(pReg->lpValueName = (LPWSTR)calloc(dwMaxValueNameSize++, sizeof(WCHAR)))) {

            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FAILURE;
        }


        for (DWORD dwIndex = 0; dwIndex < nValues; dwIndex++) {

            // Reset at maximum memory size
            dwNeededValueNameSize = dwMaxValueNameSize;

            // Continue even if an error occurred
            if ((dwResult = RegEnumValueW(hKey, dwIndex, pReg->lpValueName, &dwNeededValueNameSize, NULL, &dwType, NULL, NULL)) == ERROR_SUCCESS) {

                if (pReg->dwSwitches & SWITCH_SPECIFY_DATA_TYPE && dwType != pReg->dwSpecifyDataType)
                    continue;

                if (!(pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) && WildCardMatched(pReg->lpValueName, pReg->lpFindPattern)) {

                    dwMatches++;

                    if (CHECKRETURN(QueryRegistryValue(pReg, hKey, nValues, dwIndex)))
                        SetLastError(dwResult);
                }
                else if (pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) {

                    if (StrStrIW(pReg->lpValueName, pReg->lpFindPattern)) {

                        dwMatches++;

                        if (CHECKRETURN(QueryRegistryValue(pReg, hKey, nValues, dwIndex)))
                            SetLastError(dwResult);

                    }
                    else if (pReg->dwSwitches & SWITCH_CASE_SENSITIVE && CHECKRETURN(StrStrW(pReg->lpValueName, pReg->lpFindPattern))) {

                        dwMatches++;

                        if (CHECKRETURN(QueryRegistryValue(pReg, hKey, nValues, dwIndex)))
                            SetLastError(dwResult);

                    }
                }
            }
            else SetLastError(dwResult);
        }

        // Display search result
        if (pReg->dwSwitches & SWITCH_FIND_DATA_ONLY)
            wprintf(L"End of search: %d match(es) found.\n", dwMatches);

        // If the return code is ERROR_NO_MORE_ITEMS, it is not an error.
        if (dwResult == ERROR_NO_MORE_ITEMS) dwResult = ERROR_SUCCESS;

        if (dwResult != ERROR_SUCCESS) return FAILURE;
    }

    LPWSTR lpKeyName = NULL;

    // Enumerate all of the keys
    if (!(pReg->dwSwitches & SWITCH_FIND_DATA_ONLY)) {

        wprintf(L"\n");

        // Allocate memory for lpKeyName
        if ((lpKeyName = (LPWSTR)calloc(dwMaxKeyNameSize++, sizeof(WCHAR))) == NULL) {

            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FAILURE;
        }

        DWORD dwKeyNameSize = 0;

        for (DWORD dwIndex = 0; dwIndex < nKeys; dwIndex++) {

            // Reset at maximum memory size
            dwKeyNameSize = dwMaxKeyNameSize;

            if (dwResult = RegEnumKeyExW(hKey, dwIndex, lpKeyName, &dwKeyNameSize, NULL, NULL, NULL, NULL)) {
                SetLastError(dwResult);
                break;
            }

            if (!(pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) && WildCardMatched(lpKeyName, pReg->lpFindPattern)) {

                dwMatches++;
                wprintf(L"%s", pReg->lpRootKeyName);
                if(lpSubRoot != NULL) wprintf(L"\\%s", lpSubRoot);
                wprintf(L"\\%s\n", lpKeyName);
            }
            else if (pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN) {

                if (StrStrIW(lpKeyName, pReg->lpFindPattern)) {

                    dwMatches++;
                    wprintf(L"%s", pReg->lpRootKeyName);
                    if (lpSubRoot != NULL) wprintf(L"\\%s", lpSubRoot);
                    wprintf(L"%s\n", lpKeyName);
                }
                else if (pReg->dwSwitches & SWITCH_CASE_SENSITIVE && StrStrW(pReg->lpFullKey, pReg->lpFindPattern)) {

                    dwMatches++;
                    wprintf(L"%s", pReg->lpRootKeyName);
                    if (lpSubRoot != NULL) wprintf(L"\\%s", lpSubRoot);
                    wprintf(L"%s\n", lpKeyName);
                }
                else continue;
            }
            else continue;

            if (pReg->dwSwitches & SWITCH_RECURSE) {

                WCHAR szRecurseKey[256] = L"";

                if (CHECKRETURN(StrCmpW(pReg->lpSubKey, L""))) {

                    StrCpyW(szRecurseKey, lpKeyName);
                }
                else {

                    StrCpyW(szRecurseKey, pReg->lpSubKey);
                    StrCatW(szRecurseKey, L"\\");
                    StrCatW(szRecurseKey, lpKeyName);
                }

                // Open new key
                HKEY hSubKey = OpenRegKey(pReg, szRecurseKey, KEY_READ);

                // Recurse
                EnumRegistryKeysAndValues(pReg, hSubKey, szRecurseKey);
            }
        }

        // Display search result
        if (pReg->dwSwitches & SWITCH_FIND_KEY_ONLY)
            wprintf(L"End of search: %d match(es) found.\n", dwMatches);

        // If the return code is ERROR_NO_MORE_ITEMS, it is not an error.
        if (dwResult == ERROR_NO_MORE_ITEMS) dwResult = ERROR_SUCCESS;

        if (dwResult != ERROR_SUCCESS) return FAILURE;
    }

    // Display search result
    if (pReg->dwSwitches & SWITCH_SPECIFY_FIND_PATTERN && !(pReg->dwSwitches & SWITCH_FIND_DATA_ONLY) && !(pReg->dwSwitches & SWITCH_FIND_KEY_ONLY))
        wprintf(L"End of search: %d match(es) found.\n", dwMatches);

    return SUCCESS;
}


BOOL QueryRegistryValue(PREG pReg, HKEY hKey, DWORD nValues, DWORD dwIndex) {

    DWORD dwResult = ERROR_SUCCESS;
    WCHAR szTypeStr[32] = L"";
    DWORD dwDataType = 0;
    DWORD dwDataSize = 1;
    PBYTE pData = NULL;

    // Get data size
    if ((dwResult = RegQueryValueExW(hKey, pReg->lpValueName, 0, &dwDataType, NULL, &dwDataSize)) != ERROR_SUCCESS) {

        SetLastError(dwResult);
        return FAILURE;
    }

    // Allocate memory
    if ((pData = (PBYTE)calloc(dwDataSize += (dwDataSize % 2UL), sizeof(BYTE))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FAILURE;
    }

    // Get registry data with needed data size
    if ((dwResult = RegQueryValueExW(hKey, pReg->lpValueName, 0, &dwDataType, (PBYTE)pData, &dwDataSize)) != ERROR_SUCCESS) {

        if (pData) free(pData);
        SetLastError(dwResult);
        return FAILURE;
    }

    if (CHECKRETURN(GetDataTypeString(&szTypeStr, dwDataType))) {

        if (pData) free(pData);
        return FAILURE; // Unexpected error
    }

    // If there is only one value and there is no data, this function returns successfully
    if (nValues == 1 && CHECKRETURN(StrCmpW((LPWSTR)pData, L""))) {

        if (pData) free(pData);
        SetLastError(ERROR_NO_MORE_ITEMS);
        return SUCCESS;
    }

    // Display the key name as the title header the first time
    if (dwIndex == 0) wprintf(L"\n%s\n", pReg->lpFullKey);

    // Display value name and value type
    wprintf(L"    %s    %s", pReg->lpValueName, szTypeStr);

    // Specify display data type detail
    if(pReg->dwSwitches &SWITCH_SPECIFY_NUMERIC_EQUAL)
        wprintf(L" (%d)", dwDataType);

    // Display value data
    switch (dwDataType) {

    case REG_BINARY:

        wprintf(L"    ");
        for (DWORD i = 0; i < dwDataSize; i++)
            wprintf(L"%02X", pData[i]);
        break;

    case REG_SZ:
    case REG_EXPAND_SZ:

        wprintf(L"    %s", (LPWSTR)pData);
        break;

    case REG_DWORD:
    case REG_DWORD_BIG_ENDIAN:

        wprintf(L"    0x%x", *(LPDWORD)pData);
        break;

    case REG_MULTI_SZ: {

        wprintf(L"    ");

        LPWSTR pBuffer = (LPWSTR)pData;

        // Replace '\0' with "\0" for REG_MULTI_SZ
        while ((PBYTE)pBuffer < pData + dwDataSize) {

            if ((pReg->dwSwitches & SWITCH_SPECIFY_SEPATATOR)
                ? (*pBuffer == '\0') : (StrStrW(pBuffer, pReg->lpSeparator) == pBuffer)) {

                wprintf(L"\\0");
                pBuffer++;
            }
            else {

                wprintf(L"%s", pBuffer);
                pBuffer += wcslen(pBuffer);
            }
        }
        break;
    }
    }

    wprintf(L"\n");

    if (pData) free(pData);
    return SUCCESS;
}


BOOL GetRegEmptyValue(PREG pReg, HKEY hKey) {

    DWORD dwResult = ERROR_SUCCESS;
    DWORD dwDataSize = 0;

    // Get data
    if ((dwResult = RegQueryValueExW(hKey, pReg->lpValueName, 0, NULL, NULL, &dwDataSize)) == ERROR_SUCCESS) {

        if (dwResult == ERROR_FILE_NOT_FOUND) {

            // Display the key name as the title header
            wprintf(L"\n%s\n", pReg->lpFullKey);

            // No value set
            wprintf(L"    (Default)    REG_SZ    (value not set)\n");
        }

        SetLastError(dwResult);
        return FAILURE;
    }
    else {

        // Allocate memory
        PBYTE pData = NULL;
        if ((pData = (PBYTE)calloc((size_t)(dwDataSize += (dwDataSize % 2UL)) + 2, sizeof(BYTE))) == NULL) {

            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FAILURE;
        }

        // Get registry data with needed data size
        if ((dwResult = RegQueryValueExW(hKey, pReg->lpValueName, 0, NULL, (LPBYTE)pData, &dwDataSize)) != ERROR_SUCCESS) {

            if (pData) free(pData);
            SetLastError(dwResult);
            return FAILURE;
        }

        // Display the key name as the title header
        wprintf(L"\n%s\n", pReg->lpFullKey);

        // Value name
        wprintf(L"    (Default)    REG_SZ    %s\n", (LPWSTR)pData);
    }

    return SUCCESS;
}


BOOL WildCardMatched(LPWSTR lpTarget, LPWSTR lpWildCard) {

    LPWSTR lpTarget2 = lpTarget;
    LPWSTR lpWildCard2 = lpWildCard;

    while (TRUE) {

        if (*lpTarget2 == 0) {

            while (*lpWildCard2 == L'*') lpWildCard2++;
            return *lpWildCard2 == 0;
        }
        else if (*lpWildCard2 == 0) return 0;
        else if (*lpWildCard2 == L'*') {

            return *(lpWildCard2 + 1) == 0 || WildCardMatched(lpWildCard2, lpTarget2 + 1)
                || WildCardMatched(lpWildCard2 + 1, lpTarget2);
        }
        else if (*lpWildCard2 == L'?' || (*lpWildCard2 == *lpTarget2)) {

            lpWildCard2++; lpTarget2++;
            continue;
        }
        else return 0;
    }
}
