// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Tree.h"

// For /A switch
WCHAR lpcStructureChars[10] = L"";

int wmain(int argc, LPWSTR argv[]) {

    setlocale(LC_ALL, "");

    WCHAR szCurrentDirectory[MAX_PATH] = L".";
    WCHAR szHierarchicalShape[MAX_PATH] = L"";

    if (argc == 1) {

        if (CHECKRETURN(WalkDirectoryTree(0, szCurrentDirectory, 0, szHierarchicalShape, 0))) {

            return FAILURE;
        }

        return SUCCESS;
    }
    else {

        DWORD dwSwitches = 0;
        LPWSTR lpFilePath = NULL;

        for (int i = 1; i < argc; i++) {

            if (argv[i][0] == L'/') {

                argv[i]++;

                switch ((int)CharLowerW(argv[i][0])) {

                case L'?':

                    DisplayTextMessage(MSG_HELP_MESSAGE, NO_ARGS);
                    return SUCCESS;

                case L'f':

                    dwSwitches |= TREE_SWITCH_DISPLAY_FILES;
                    break;

                case L'a':

                    dwSwitches |= TREE_SWITCH_USES_ASCII;
                    break;

                default:

                    DisplayTextMessage(MSG_INVALID_SWITCH, ONE_ARG, argv[i]);
                    return SUCCESS;
                }
            }
            else {

                if (lpFilePath == NULL) {

                    lpFilePath = argv[i];
                }
                else break;
            }
        }

        // There is no specified path, the search path is current dir
        if (lpFilePath == NULL) {

            lpFilePath = szCurrentDirectory;
        }

        if (CHECKRETURN(WalkDirectoryTree(dwSwitches, lpFilePath, 0, szHierarchicalShape, 0))) {

            return FAILURE;
        }

        return SUCCESS;
    }

    return SUCCESS;
}


BOOL WalkDirectoryTree(DWORD dwSwitches, LPWSTR lpSpecifiedPath, DWORD dwRecursiveDepth, LPWSTR lpStructureString, BOOL bThereAreMoreDirsBefore) {

    if ((++dwRecursiveDepth) == 1) {

        if (dwSwitches & TREE_SWITCH_USES_ASCII) {

            StrCpyW(lpcStructureChars, L"|+\\-");
        }
        else {

            StrCpyW(lpcStructureChars, L"„ „¥„¤„Ÿ");
        }
    }

    WCHAR szDirPathAddedWildcard[MAX_PATH] = L"";
    WCHAR szNextPathAddedWildcard[MAX_PATH] = L"";
    DWORD nMaxDirs = 0;
    DWORD dwCurrentDirPosition = 0;
    WCHAR szStructureString[MAX_PATH] = L"";
    BOOL bDisplayedFilesInThisDirAlready = FALSE;
    WCHAR szTempStructString[260] = L"";
    HANDLE hFindDir = NULL;
    WIN32_FIND_DATAW FindDirData = { 0 };

    // Add wildcard
    StrCpyW(szDirPathAddedWildcard, lpSpecifiedPath);
    PathAddBackslashW(szDirPathAddedWildcard);
    StrCatW(szDirPathAddedWildcard, L"*");

    // Find files
    if ((hFindDir = FindFirstFileW(szDirPathAddedWildcard, &FindDirData)) == INVALID_HANDLE_VALUE) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    // Get number of directories in the specified dir
    if (dwRecursiveDepth == 1) {

        // Display volume infomation
        if (CHECKRETURN(DisplayTreeHeader(lpSpecifiedPath))) {

            return FAILURE;
        }
    }

    // Get number of dirs
    if (CHECKRETURN(GetNumOfDirs(szDirPathAddedWildcard, &nMaxDirs))) {

        return FAILURE;
    }

    do {

        StrCpyW(szStructureString, lpStructureString);

        if (dwRecursiveDepth != 1) {

            if (bThereAreMoreDirsBefore == 0) {

                StrCatW(szStructureString, L"   ");
            }
            else {

                swprintf(szTempStructString, 260, L"%c  ", lpcStructureChars[0]);
                StrCatW(szStructureString, szTempStructString);
            }
        }

        if (CHECKRETURN(StrCmpW(FindDirData.cFileName, L"..")) || CHECKRETURN(StrCmpW(FindDirData.cFileName, L"."))) {

            // Do nothing
        }
        else if (!(FindDirData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !(FindDirData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)) {

            if (!(FindDirData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && dwSwitches & TREE_SWITCH_DISPLAY_FILES && bDisplayedFilesInThisDirAlready == FALSE) {

                HANDLE hFindFile = NULL;
                WIN32_FIND_DATA FindFileData = { 0 };

                if ((hFindFile = FindFirstFileW(szDirPathAddedWildcard, &FindFileData)) == INVALID_HANDLE_VALUE) {

                    DisplayTextMessage(GetLastError(), NO_ARGS);
                    return FAILURE;
                }

                do {

                    if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                        wprintf(L"%s", szStructureString);

                        if (nMaxDirs == dwCurrentDirPosition) {

                            wprintf(L"   ");
                        }
                        else {

                            wprintf(L"%c  ", lpcStructureChars[0]);
                        }

                        wprintf(L"%s\n", FindFileData.cFileName);
                    }

                } while (FindNextFileW(hFindFile, &FindFileData));

                // Line feed

                wprintf(L"%s", szStructureString);

                if (nMaxDirs == dwCurrentDirPosition) {

                    wprintf(L"   ");
                }
                else {

                    wprintf(L"%c  ", lpcStructureChars[0]);
                }

                wprintf(L"\n");

                FindClose(hFindFile);

                bDisplayedFilesInThisDirAlready = TRUE;
            }

            if (FindDirData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

                dwCurrentDirPosition++;

                // For recursive all directories
                StrCpyW(szNextPathAddedWildcard, lpSpecifiedPath);
                PathAddBackslashW(szNextPathAddedWildcard);
                StrCatW(szNextPathAddedWildcard, FindDirData.cFileName);

                wprintf(L"%s", szStructureString);

                if (nMaxDirs == dwCurrentDirPosition) {

                    wprintf(L"%c", lpcStructureChars[2]);
                }
                else {

                    wprintf(L"%c", lpcStructureChars[1]);
                }

                wprintf(L"%c%s\n", lpcStructureChars[3], FindDirData.cFileName);

                // Recurse
                WalkDirectoryTree(dwSwitches, szNextPathAddedWildcard, dwRecursiveDepth, szStructureString, nMaxDirs - dwCurrentDirPosition);
            }
        }
        else continue;

    } while (FindNextFileW(hFindDir, &FindDirData));

    FindClose(hFindDir);

    return SUCCESS;
}


BOOL DisplayTreeHeader(LPWSTR lpDirPath) {

    WCHAR szFullPath[MAX_PATH] = L"";
    GetFullPathNameW(lpDirPath, MAX_PATH, szFullPath, NULL);

    WCHAR szRootPath[4] = L"";
    WCHAR szVolumeLabel[MAX_PATH] = L"";
    DWORD dwSerialNo = 0;
    WCHAR szHighPartSerialNo[10] = L"";
    WCHAR szLowPartSerialNo[10] = L"";

    szRootPath[0] = szFullPath[0];
    szRootPath[1] = szFullPath[1];
    szRootPath[2] = szFullPath[2];

    // Get volume info
    if (CHECKRETURN(GetVolumeInformationW(szRootPath, szVolumeLabel, MAX_PATH, &dwSerialNo, NULL, NULL, NULL, NULL))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    DisplayTextMessage(MSG_DIR_LISTING_WITH_VOLUME_NAME, ONE_ARG, szVolumeLabel);

    swprintf(szHighPartSerialNo, 10, L"%04X", HIWORD(dwSerialNo));
    swprintf(szLowPartSerialNo, 10, L"%04X", LOWORD(dwSerialNo));

    DisplayTextMessage(MSG_32_BIT_SERIAL_NUMBER, ONE_ARG, szHighPartSerialNo, szLowPartSerialNo);

    // There is no specified path
    if (CHECKRETURN(StrCmpW(lpDirPath, L"."))) {

        wprintf(L"%c:.\n", szRootPath[0]);
    }
    else {

        wprintf(L"%s\n", CharUpperW(lpDirPath));
    }

    return SUCCESS;
}


BOOL GetNumOfDirs(LPWSTR lpDirPathAddedWildcard, LPDWORD nMaxDirs) {

    HANDLE hFindDir = NULL;
    WIN32_FIND_DATAW FindDirData = { 0 };
    DWORD nDirs = 0;

    if ((hFindDir = FindFirstFileW(lpDirPathAddedWildcard, &FindDirData)) == INVALID_HANDLE_VALUE) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    do {

        if (CHECKRETURN(StrCmpW(FindDirData.cFileName, L"..")) || CHECKRETURN(StrCmpW(FindDirData.cFileName, L"."))) {}
        else if (FindDirData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && !(FindDirData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) && !(FindDirData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)) {

            nDirs++; // Count only dirs
        }
        else continue;

    } while (FindNextFileW(hFindDir, &FindDirData));

    FindClose(hFindDir);

    *nMaxDirs = nDirs;

    return SUCCESS;
}
