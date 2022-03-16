// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

BOOL EnumFileTypes(void);
BOOL GetFileTypeCommand(LPWSTR lpFileTypeName);
BOOL SetFileTypeCommand(LPWSTR lpFileTypeName, LPWSTR lpCommnadLine);
BOOL DeleteFileTypeCommand(LPWSTR lpFileTypeName);


int FTypeMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered FTypeMain() function\n");

    if (argc == 1) {

        return EnumFileTypes();
    }
    else {

        if (CHECKRETURN(StrCmpW(argv[1], L"/?"))) {

            DisplayTextMessage(MSG_HELP_FTYPE, NO_ARGS);
            return SUCCESS;
        }
        else {

            LPWSTR lpCommandLine = NULL;

            if ((lpCommandLine = StrStrW(argv[1], L"=")) != NULL) {

                if (lpCommandLine[1] == L'\0') {

                    lpCommandLine[0] = L'\0';
                    return DeleteFileTypeCommand(lpCommandLine);
                }
                else {

                    lpCommandLine[0] = L'\0';
                    lpCommandLine++;
                    return SetFileTypeCommand(argv[1], lpCommandLine);
                }
            }
            else {

                return GetFileTypeCommand(argv[1]);
            }
        }
    }

    return SUCCESS;
}


BOOL EnumFileTypes(void) {

    HKEY hkResult = NULL;
    DWORD dwResult = ERROR_SUCCESS;

    if ((dwResult = RegOpenKeyExW(HKEY_CLASSES_ROOT, L"", 0, KEY_READ, &hkResult)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    DWORD nValues = 0;

    if ((dwResult = RegQueryInfoKeyW(hkResult, NULL, 0, NULL, &nValues, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) != ERROR_SUCCESS) {

        DisplayTextMessage(dwResult, NO_ARGS);
        return FAILURE;
    }

    WCHAR szValueName[MAX_PATH] = L"";
    WCHAR szCommandPath[MAX_PATH] = L"";
    WCHAR szCommandLine[1024] = L"";
    DWORD cchCommandLine = 1024;

    for (DWORD dwIndex = 0; dwIndex < nValues; dwIndex++) {

        if ((dwResult = RegEnumKeyW(hkResult, dwIndex, szValueName, MAX_PATH)) != ERROR_SUCCESS) {

            DisplayTextMessage(dwResult, NO_ARGS);
            return FAILURE;
        }

        if (szValueName[0] == L'.') continue;

        StrCpyW(szCommandPath, szValueName);
        StrCatW(szCommandPath, L"\\SHELL\\OPEN\\COMMAND");

        if (RegQueryValueW(HKEY_CLASSES_ROOT, szCommandPath, szCommandLine, &cchCommandLine) != ERROR_SUCCESS || szCommandLine[0] == L'\0') {

            continue;
        }

        wprintf(L"%s=%s\n", szValueName, szCommandLine);
    }

    return SUCCESS;
}


BOOL GetFileTypeCommand(LPWSTR lpFileTypeName) {

    DWORD dwResult = ERROR_SUCCESS;
    WCHAR szCommandPath[MAX_PATH] = L"";
    WCHAR szCommandLine[1024] = L"";
    DWORD cchCommandLine = 1024;

    StrCpyW(szCommandPath, lpFileTypeName);
    StrCatW(szCommandPath, L"\\SHELL\\OPEN\\COMMAND");

    if ((dwResult = RegQueryValueW(HKEY_CLASSES_ROOT, szCommandPath, szCommandLine, &cchCommandLine)) != ERROR_SUCCESS || szCommandLine[0] == L'\0') {

        DisplayTextMessage(MSG_FTYPE_NOT_FOUND, ONE_ARG, lpFileTypeName);
        return FAILURE;
    }

    wprintf(L"%s=%s\n", lpFileTypeName, szCommandLine);

    return SUCCESS;
}


BOOL SetFileTypeCommand(LPWSTR lpFileTypeName, LPWSTR lpCommnadLine) {

    HKEY hkResult = NULL;

    if (RegCreateKeyW(HKEY_CLASSES_ROOT, lpFileTypeName, &hkResult) != ERROR_SUCCESS) {

        DisplayTextMessage(MSG_FTYPE_NOT_FOUND, ONE_ARG, lpFileTypeName);
        return FAILURE;
    }

    if (RegSetValueW(hkResult, L"SHELL\\OPEN\\COMMAND", REG_SZ, (PBYTE)lpCommnadLine, sizeof(lpCommnadLine)) != ERROR_SUCCESS) {

        DisplayTextMessage(MSG_FTYPE_NOT_FOUND, ONE_ARG, lpFileTypeName);
        return FAILURE;
    }
    else {

        wprintf(L"%s=%s\n", lpFileTypeName, lpCommnadLine);
    }

    RegCloseKey(hkResult);
    return SUCCESS;
}


BOOL DeleteFileTypeCommand(LPWSTR lpFileTypeName) {

    HKEY hkResult = NULL;

    if (RegOpenKeyExW(HKEY_CLASSES_ROOT, L"", 0, KEY_READ, &hkResult) != ERROR_SUCCESS) {

        DisplayTextMessage(MSG_FTYPE_NOT_FOUND, ONE_ARG, lpFileTypeName);
        return FAILURE;
    }

    if (RegDeleteKeyW(hkResult, lpFileTypeName) != ERROR_SUCCESS) {

        DisplayTextMessage(MSG_FTYPE_NOT_FOUND, ONE_ARG, lpFileTypeName);
        return FAILURE;
    }

    RegCloseKey(hkResult);

    return SUCCESS;
}
