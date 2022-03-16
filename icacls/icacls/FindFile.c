// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


BOOL FindFile(PICACLS pIcacls, LPWSTR lpRoot) {

    WCHAR szPath[MAX_PATH] = L"";
    WCHAR szPart[MAX_PATH] = L"";
    LPWSTR lpFilePart = NULL;

    // Parse file part
    if (CHECKRETURN(GetFullPathNameW(lpRoot, MAX_PATH, szPath, &lpFilePart)))
        return FAILURE;

    if (CHECKRETURN(StrCmpW(lpFilePart, L""))) {

        if (pIcacls->dwSwitches & SWITCH_RECURSE_ALL_MATCHING_FILE) {

            wcscpy_s(szPart, MAX_PATH, L"*");
        }
    }
    else wcscpy_s(szPart, MAX_PATH, lpFilePart);

    wcscpy_s(szPath, MAX_PATH, lpRoot);
    szPath[wcslen(szPath) - wcslen(szPart)] = L'\0';

    WIN32_FIND_DATAW FindData = { 0 };
    HANDLE hFind = FindFirstFileW(lpRoot, &FindData);
    if (hFind == INVALID_HANDLE_VALUE) return 1;

    WCHAR szFilePath[MAX_PATH] = L"";

    // File only
    do {

        // Do nothing
        if (CHECKRETURN(StrCmpW(FindData.cFileName, L"..")) || CHECKRETURN(StrCmpW(FindData.cFileName, L"."))) {}
        // Directory
        else if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(pIcacls->dwSwitches & SWITCH_RECURSE_ALL_MATCHING_FILE)) {

            wcscpy_s(szFilePath, MAX_PATH, szPath);
            wcscat_s(szFilePath, MAX_PATH, FindData.cFileName);

            HandleProcessingBranch(pIcacls, szFilePath);
        }
        // File
        else {

            wcscpy_s(szFilePath, MAX_PATH, szPath);
            wcscat_s(szFilePath, MAX_PATH, FindData.cFileName);

            HandleProcessingBranch(pIcacls, szFilePath);
        }
    } while (FindNextFileW(hFind, &FindData));

    if ((hFind = FindFirstFileW(lpRoot, &FindData)) == INVALID_HANDLE_VALUE)
        return FAILURE;

    // For recuring
    if (pIcacls->dwSwitches & SWITCH_RECURSE_ALL_MATCHING_FILE) {

        do {

            if (CHECKRETURN(StrCmpW(FindData.cFileName, L"..")) || CHECKRETURN(StrCmpW(FindData.cFileName, L"."))) {}
            // Directory
            else if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                // Recurse directory
                wcscpy_s(szFilePath, MAX_PATH, szPath);
                wcscat_s(szFilePath, MAX_PATH, FindData.cFileName);
                wcscat_s(szFilePath, MAX_PATH, L"\\");
                wcscat_s(szFilePath, MAX_PATH, szPart);
                
                FindFile(pIcacls, szFilePath);

            }
        } while (FindNextFileW(hFind, &FindData));
    }

    return SUCCESS;
}


BOOL HandleProcessingBranch(PICACLS pIcacls, LPWSTR lpFileName) {

    // Display
    switch (pIcacls->dwOperation) {

    case 0:

        DislpaySecInfo(pIcacls, lpFileName);
        break;

    case OPERATION_SAVE:

        InitializeBuckupFile(pIcacls->lpBuffer);
        BackupSecDesc(lpFileName, pIcacls->lpBuffer);
        break;

    case OPERATION_RESTORE:

        RestoreSecDesc(lpFileName, pIcacls->lpBuffer);
        break;

    case OPERATION_SETOWNER:

        SetFileOwner(lpFileName, pIcacls->lpBuffer);
        break;

    case OPERATION_FINDSID:

        FindSid(lpFileName, pIcacls->lpBuffer);
        break;

    case OPERATION_VERIFY:

        FindSid(lpFileName, pIcacls->lpBuffer);
        break;
    }

    return SUCCESS;
}
