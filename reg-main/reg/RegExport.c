// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"

BOOL ParseExportSwitches(PREG pReg, int argc, LPWSTR argv[]);
BOOL WriteRegistryTree(PREG pReg, HANDLE hFile, HKEY hKey, LPWSTR lpKeyName);
BOOL WriteValueData(HANDLE hFile, DWORD dwDataType, LPBYTE pData, DWORD dwDataSize);
BOOL WriteString(HANDLE hFile, LPWSTR lpString);


BOOL RegExportMain(PREG pReg, int argc, LPWSTR argv[]) {

    DWORD dwResult = 0;
    HKEY hKey = NULL;
    HANDLE hFile;

    // Parse command line
    if (CHECKRETURN(ParseExportSwitches(pReg, argc, argv)))
        return FAILURE;

    // Open registry handle
    if (CHECKRETURN(hKey = OpenRegKey(pReg, pReg->lpSubKey, KEY_WRITE | KEY_READ))) {

        return FAILURE;
    }

    // Confirm overwriting of the file
    if ((hFile = CreateFileW(pReg->lpFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_ARCHIVE, NULL)) == INVALID_HANDLE_VALUE) {

        if (GetLastError() == ERROR_FILE_EXISTS) { // Overwrite

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

                RegCloseKey(hKey);
                return FAILURE;
            }

            // Retry
            if ((hFile = CreateFileW(pReg->lpFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_ARCHIVE, NULL)) == INVALID_HANDLE_VALUE) {

                DisplayTextMessage(dwResult, NO_ARGS);
                RegCloseKey(hKey);
                return FAILURE;
            }
        }
    }

    if (CHECKRETURN(ExportRegFile(pReg, hFile, hKey, pReg->lpSubKey))) {

        CloseHandle(hFile);
        RegCloseKey(hKey);
        return FAILURE;
    }

    CloseHandle(hFile);
    RegCloseKey(hKey);
    return SUCCESS;
}


BOOL ParseExportSwitches(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"EXPORT");
        return FAILURE;
    }
    else {

        // argv[1] = help or key name
        if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?"))
            || CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

            DisplayTextMessage(MSG_HELP_REG_EXPORT, NO_ARGS);
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

                    DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"EXPORT");
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

                DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, ONE_ARG, L"EXPORT");
                return FAILURE;
            }
        }
    }

    return SUCCESS;
}


BOOL ExportRegFile(PREG pReg, HANDLE hFile, HKEY hKey, LPWSTR lpKeyName) {

    // Write reg file version header
    WCHAR szRegFileVersion[] = L"Windows Registry Editor Version 5.00\n";
    wprintf(L"%s", szRegFileVersion);
    WriteString(hFile, szRegFileVersion);

    // Write registry tree
    WriteRegistryTree(pReg, hFile, hKey, lpKeyName);

    return SUCCESS;
}


BOOL WriteRegistryTree(PREG pReg, HANDLE hFile, HKEY hKey, LPWSTR lpKeyName) {

    DWORD dwResult = 0;
    DWORD nKeys = 0;
    DWORD nValues = 0;
    DWORD dwMaxKeyNameSize = 0;
    DWORD dwMaxValueNameSize = 0;
    DWORD dwMaxDataSize = 0;
    DWORD dwDataType = 0;
    DWORD dwNeededValueNameSize = 0;
    DWORD dwNeededDataSize = 0;
    DWORD dwNeededKeyNameSize = 0;
    WCHAR szFormattedValueName[256 + 3] = L"";

    // Write key name
    WCHAR szKeyNameHeader[256] = L"";
    swprintf(szKeyNameHeader, 256, L"\n[%s\\%s]\n", pReg->lpRootKeyName, lpKeyName);
    wprintf(L"%s", szKeyNameHeader);
    WriteString(hFile, szKeyNameHeader);

    // Get maximum size of registry key names, value names and value datas
    dwResult = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, &nKeys, &dwMaxKeyNameSize, NULL, &nValues, &dwMaxValueNameSize, &dwMaxDataSize, NULL, NULL);
    if (dwResult != ERROR_SUCCESS) return FAILURE;

    // Allocate maximum value name size in bytes
    LPWSTR lpValueName = NULL;
    if ((lpValueName = (LPWSTR)calloc(dwMaxValueNameSize++, sizeof(WCHAR))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FAILURE;
    }

    // Allocate maximum data size in bytes
    LPBYTE pData = NULL;
    if ((pData = (LPBYTE)calloc(dwMaxDataSize++, sizeof(WCHAR))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        if (lpValueName) free(lpValueName);
        return FAILURE;
    }

    // Write value names in the specified key name
    for (DWORD dwIndex = 0; dwIndex < nValues; dwIndex++) {

        dwNeededValueNameSize = dwMaxValueNameSize;
        dwNeededDataSize = dwMaxDataSize;

        if((dwResult = RegEnumValueW(hKey, dwIndex, lpValueName, &dwNeededValueNameSize, NULL, &dwDataType, pData, &dwNeededDataSize)) != ERROR_SUCCESS) {

            SetLastError(dwResult);
            if (lpValueName) free(lpValueName);
            if (pData) free(pData);
            return FAILURE;
        }

        if (wcslen(lpValueName) == 0) swprintf(szFormattedValueName, 256 + 3, L"@=");
        else swprintf(szFormattedValueName, 256 + 3, L"\"%s\"=", lpValueName);
        wprintf(L"%s", szFormattedValueName);
        WriteString(hFile, szFormattedValueName);

        // Write value data
        WriteValueData(hFile, dwDataType, pData, dwNeededDataSize);
    }

    // Allocate maximum key name size in bytes
    LPWSTR lpSubKey = NULL;
    if ((lpSubKey = (LPWSTR)calloc(dwMaxKeyNameSize, sizeof(WCHAR))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        if (lpValueName) free(lpValueName);
        if (pData) free(pData);
        return FAILURE;
    }

    WCHAR szFullSubKey[256] = L"";
    HKEY hSubKey = NULL;

    // Call recursively with sub key name
    for (DWORD dwIndex = 0; dwIndex < nKeys; dwIndex++) {

        dwNeededKeyNameSize = dwMaxKeyNameSize;

        if ((dwResult = RegEnumKeyW(hKey, dwIndex, lpSubKey, &dwNeededKeyNameSize)) != ERROR_SUCCESS) {

            if (lpValueName) free(lpValueName);
            if (pData) free(pData);
            if (lpSubKey) free(lpSubKey);
            return FAILURE;
        }

        StrCpyW(szFullSubKey, lpKeyName);
        StrCatW(szFullSubKey, L"\\");
        StrCatW(szFullSubKey, lpSubKey);

        if ((hSubKey = OpenRegKey(pReg, szFullSubKey, KEY_READ)))
            return FAILURE;

        WriteRegistryTree(pReg, hFile, hSubKey, szFullSubKey);
    }

    return SUCCESS;
}


BOOL WriteValueData(HANDLE hFile, DWORD dwDataType, LPBYTE pData, DWORD dwDataSize) {

    WCHAR szFormattedData[1024] = L"";
    WCHAR szTwoDigitBinary[4] = L"";

    switch (dwDataType) {

    default:
    case REG_BINARY:

        StrCpyW(szFormattedData, L"hex");

        if (dwDataType == REG_BINARY) StrCatW(szFormattedData, L":");
        else {

            swprintf(szTwoDigitBinary, 4, L"(%d)", dwDataType);
            StrCatW(szFormattedData, szTwoDigitBinary);
            StrCatW(szFormattedData, L":");
        }

        if (dwDataSize == 0) {
            StrCatW(szFormattedData, L"\n");
            break;
        }

        for (DWORD dwBinaryDataIndex = 0; dwBinaryDataIndex < dwDataSize; dwBinaryDataIndex++) {

            swprintf(szTwoDigitBinary, 4, L"%02X", pData[dwBinaryDataIndex]);
            StrCatW(szFormattedData, szTwoDigitBinary);

            if ((dwBinaryDataIndex + 1) != dwDataSize) StrCatW(szFormattedData, L",");
            else StrCatW(szFormattedData, L"\n");

            if ((dwBinaryDataIndex < 18) && ((dwBinaryDataIndex + 1) % 18 == 0) && ((dwBinaryDataIndex + 1) != dwDataSize))
                StrCatW(szFormattedData, L"\\\n  ");

            if ((dwBinaryDataIndex > 18) && ((dwBinaryDataIndex + 1) % 25 == 0) && ((dwBinaryDataIndex + 1) != dwDataSize))
                StrCatW(szFormattedData, L"\\\n  ");
        }
        break;

    case REG_DWORD_BIG_ENDIAN:
    case REG_DWORD:

        swprintf(szFormattedData, 1024, L"dword:%08x\n", *(LPDWORD)pData);
        break;

    case REG_EXPAND_SZ:
    case REG_SZ:

        swprintf(szFormattedData, 1024, L"\"%s\"\n", (LPWSTR)pData);
        break;
    }

    wprintf(L"%s", szFormattedData);
    WriteString(hFile, szFormattedData);

    return SUCCESS;
}


BOOL WriteString(HANDLE hFile, LPWSTR lpString) {

    DWORD nBytesWritten = 0;

    return WriteFile(hFile, lpString, wcslen(lpString) * sizeof(WCHAR), &nBytesWritten, NULL);
}
