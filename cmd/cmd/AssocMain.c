// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"

BOOL ParseAssocCmdLine(int argc, LPWSTR argv[]);
BOOL EnumFileAssociation(void);
BOOL GetFileAssociation(LPWSTR lpExtensionName);
BOOL SetFileAssociation(LPWSTR lpExtensionName, LPWSTR lpFileType);
BOOL DeleteFileAssociation(LPWSTR lpExtensionName);


int AssocMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered AssocMain() function\n");

    if (argc == 1) {

        return EnumFileAssociation();
    }
    else {

        return ParseAssocCmdLine(argc, argv);
    }

    return SUCCESS;
}


BOOL ParseAssocCmdLine(int argc, LPWSTR argv[]) {

    // Parse only first command switch
    if (CHECKRETURN(StrCmpIW(argv[1], L"/?"))) {

        DisplayTextMessage(MSG_HELP_ASSOC, NO_ARGS);
        return SUCCESS;
    }
    else {

        LPWSTR lpFileType = StrStrW(argv[1], L"=");

        // There is no L"=" in cmd line
        if (lpFileType == NULL) {

            // Query file association
             return GetFileAssociation(argv[1]);
        }
        // L"=" only
        else if (wcslen(lpFileType) == 1) {

            // Delete file association
            lpFileType[0] = L'\0';
            return DeleteFileAssociation(argv[1]);
        }
        else {

            // Set file association
            lpFileType[0] = L'\0';
            return SetFileAssociation(argv[1], ++lpFileType);
        }
    }

    return SUCCESS;
}


BOOL EnumFileAssociation(void) {

    HKEY hkResult = NULL;
    DWORD dwResult = ERROR_SUCCESS;
    WCHAR szExtensionName[256] = L"";
    DWORD dwExtensionNameSize = 256;

    if ((RegOpenKeyExW(HKEY_CLASSES_ROOT, L"", 0, KEY_READ, &hkResult)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    for (DWORD dwIndex = 0; dwResult != ERROR_NO_MORE_ITEMS; dwIndex++) {

        dwExtensionNameSize = 256;

        if ((dwResult = RegEnumKeyExW(hkResult, dwIndex, szExtensionName, &dwExtensionNameSize, NULL, NULL, NULL, NULL)) == ERROR_SUCCESS) {

            // For example ".txt"
            if (szExtensionName[0] == L'.') {

                GetFileAssociation(szExtensionName);
            }
            else continue;
        }
    }

    RegCloseKey(hkResult);
    return SUCCESS;
}


BOOL GetFileAssociation(LPWSTR lpExtensionName) {

    HKEY hkResult = NULL;
    DWORD dwResult = ERROR_SUCCESS;
    DWORD dwDataType = 0;
    BYTE byData[1024] = { 0 }; // This is faster than malloc()
    DWORD dwDataSize = sizeof(byData);

    if ((dwResult = RegOpenKeyExW(HKEY_CLASSES_ROOT, lpExtensionName, 0, KEY_READ, &hkResult)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        return FAILURE;
    }

    if ((dwResult = RegQueryValueExW(hkResult, L"", NULL, &dwDataType, byData, &dwDataSize)) != ERROR_SUCCESS) {

        //DisplayTextMessage(dwResult, NO_ARGS);
        //DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        //return FAILURE;
    }

    if (dwDataType == REG_SZ) {

        switch (dwDataType) {

        case REG_SZ:
            wprintf(L"%s=%s\n", lpExtensionName, (LPWSTR)byData);
            break;

        default: break;
        }
    }

    RegCloseKey(hkResult);
    return SUCCESS;
}


BOOL SetFileAssociation(LPWSTR lpExtensionName, LPWSTR lpFileType) {

    HKEY hkResult = NULL;
    DWORD dwResult = ERROR_SUCCESS;

    if ((dwResult = RegCreateKeyW(HKEY_CLASSES_ROOT, lpExtensionName, &hkResult)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        return FAILURE;
    }

    if ((dwResult = RegSetValueExW(hkResult, L"", 0, REG_SZ, (PBYTE)lpFileType, sizeof(lpFileType))) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        return FAILURE;
    }
    else {

        wprintf(L"%s=%s\n", lpExtensionName, lpFileType);
    }

    RegCloseKey(hkResult);
    return SUCCESS;
}


BOOL DeleteFileAssociation(LPWSTR lpExtensionName) {

    HKEY hkResult = NULL;
    DWORD dwResult = ERROR_SUCCESS;

    if ((dwResult = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"", 0, KEY_READ, &hkResult)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        return FAILURE;
    }

    if ((dwResult = RegDeleteKeyW(hkResult, lpExtensionName))) {

        DisplayTextMessage(dwResult, NO_ARGS);
        DisplayTextMessage(MSG_ERR_PROC_ARG, ONE_ARG, lpExtensionName);
        return FAILURE;
    }

    RegCloseKey(hkResult);

    return SUCCESS;
}
