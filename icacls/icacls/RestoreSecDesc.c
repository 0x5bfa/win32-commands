// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


BOOL RestoreSecDesc(LPCWSTR lpRootDir, LPCWSTR lpRestoreFile) {

    FILE* fp = NULL;
    WCHAR szLine[1024] = L"";
    BOOL bResult = SUCCESS;

    // Read file
    if (_wfopen_s(&fp, lpRestoreFile, L"r, ccs=UTF-16LE") != 0 || fp == NULL)
        return FAILURE;

    WCHAR szFullPath[MAX_PATH] = L"";

    // Get one line at a time
    for (int i = 1; fgetws(szLine, sizeof(szLine) / sizeof(WCHAR), fp) != NULL; i++) {

        // Remove line feed
        szLine[wcslen(szLine) - 1] = L'\0';

        // Get fullpath
        if (i % 2 != 0) {

            // Copy dir
            wcscpy_s(szFullPath, MAX_PATH, lpRootDir);

            // Add backslash
            PathAddBackslashW(szFullPath);
            wcscat_s(szFullPath, MAX_PATH, szLine);
        }
        // Set security descriptor
        else {

            // Start protected statement
            __try {

                PSECURITY_DESCRIPTOR pSD = NULL;

                // Convert string to security descriptor
                if (CHECKRETURN(ConvertStringSecurityDescriptorToSecurityDescriptorW(szLine, SDDL_REVISION_1, &pSD, NULL))) {

                    bResult = FAILURE;
                    __leave;
                }

                // Set security to file
                if (CHECKRETURN(SetFileSecurityW(szFullPath, DACL_SECURITY_INFORMATION, pSD))) {

                    bResult = FAILURE;
                    __leave;
                }
            }
            __finally {

                // Cleanup
                fclose(fp);
                return bResult;
            }
        }
    }

    // Cleanup
    fclose(fp);
    return bResult;
}
