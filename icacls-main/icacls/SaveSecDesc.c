// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


BOOL BackupSecDesc(LPCWSTR lpFileName, LPCWSTR lpWriteFile) {

    DWORD nSDSize = 0;
    PSECURITY_DESCRIPTOR pSD = NULL;
    LPWSTR lpWritingBuffer = NULL;

    // Get security descriptor
    if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, NULL, nSDSize, &nSDSize))) {

        // Buffer shortage
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // Start protected statement
            __try {

                // Allocate
                if ((pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, nSDSize)) == NULL)
                    __leave;

                // Get security descriptor with allocated buffer
                if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, pSD, nSDSize, &nSDSize)))
                    __leave;

                // Convert pSD into string
                LPWSTR lpSDString;
                ConvertSecurityDescriptorToStringSecurityDescriptorW(pSD, SDDL_REVISION_1, DACL_SECURITY_INFORMATION, &lpSDString, NULL);

                // Open written file
                HANDLE hFile = CreateFileW(lpWriteFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile == INVALID_HANDLE_VALUE) __leave;

                // Set pointer to end of the file
                SetFilePointer(hFile, 0, NULL, FILE_END);

                // Write filename
                DWORD dwWritten = 0;
                WriteFile(hFile, lpFileName, wcslen(lpFileName) * sizeof(WCHAR), &dwWritten, NULL);

                // Write linefeed
                WCHAR szLineFeed[] = { '\r', '\n' };
                WriteFile(hFile, szLineFeed, wcslen(szLineFeed) * sizeof(WCHAR), &dwWritten, NULL);

                // Write string SD
                WriteFile(hFile, lpSDString, wcslen(lpSDString) * sizeof(WCHAR), &dwWritten, NULL);

                // Write linefeed
                WriteFile(hFile, szLineFeed, wcslen(szLineFeed) * sizeof(WCHAR), &dwWritten, NULL);
            }
            __finally {

                // Cleanup
                if (pSD != NULL) LocalFree(pSD);
                return FALSE;
            }
        }
    }
}


BOOL InitializeBuckupFile(LPCWSTR lpFileName) {

    // Create file always
    HANDLE hFile = CreateFileW(lpFileName, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Write u16le byte order mark
    CHAR szBom[] = { '\xFF', '\xFE' };
    DWORD dwWritten = 0;
    WriteFile(hFile, szBom, 2 * sizeof(CHAR), &dwWritten, NULL);

    return SUCCESS;
}