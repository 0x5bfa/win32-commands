// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Attrib.h"


BOOL wmain(int argc, LPWSTR argv[]) {

    ATTRIB Attrib = { 0 };

    if (argc == 1) {

        // [CurrentFullDirectry]\*
        WCHAR szCurrentDir[MAX_PATH] = L"";
        GetCurrentDirectoryW(MAX_PATH, (LPWSTR)&szCurrentDir);
        PathAddBackslashW(szCurrentDir);
        StrCatW(szCurrentDir, L"*");

        // Find matching files
        return FindFile(&Attrib, szCurrentDir);

    }
    else {

        LPWSTR lpRootPath = NULL;

        for (int i = 1; i < argc; i++) {

            if (argv[i][0] == L'/' && argv[i][2] == L'\0') {

                switch (argv[i][1]) {
                case L'?':

                    wprintf(L"Displays or changes file attributes.\r\n\r\nATTRIB [+R | -R] [+A | -A] [+S | -S] [+H | -H] [+O | -O] [+I | -I] [+X | -X] [+P | -P] [+U | -U]\r\n       [drive:][path][filename] [/S [/D]] [/L]\r\n\r\n  +   Sets an attribute.\r\n  -   Clears an attribute.\r\n  R   Read-only file attribute.\r\n  A   Archive file attribute.\r\n  S   System file attribute.\r\n  H   Hidden file attribute.\r\n  O   Offline attribute.\r\n  I   Not content indexed file attribute.\r\n  X   No scrub file attribute.\r\n  V   Integrity attribute.\r\n  P   Pinned attribute.\r\n  U   Unpinned attribute.\r\n  B   SMR Blob attribute.\r\n  [drive:][path][filename]\r\n      Specifies a file or files for attrib to process.\r\n  /S  Processes matching files in the current folder\r\n      and all subfolders.\r\n  /D  Processes folders as well.\r\n  /L  Work on the attributes of the Symbolic Link versus\r\n      the target of the Symbolic Link\r\n\r\n");
                    break;

                case L'S':

                    Attrib.dwSwitches |= SWITCH_RECURSE_ALL_DIRECTORY;
                    Attrib.dwSwitches |= SWITCH_PROCESS_FOLDER_AS_WELL;
                    break;

                case L'D':

                    Attrib.dwSwitches |= SWITCH_PROCESS_FOLDER_AS_WELL;
                    break;

                case L'L':

                    Attrib.dwSwitches |= SWITCH_SYMBOLIC_LINK_TARGET;
                    break;

                default:

                    wprintf(L"Invalid switch - %s", argv[i]);
                    return FAILURE;
                }
            }
            else {

                // Parse on/off attributes
                if (argv[i][0] == L'-' || argv[i][0] == L'+') {

                    if (CHECKRETURN(ParseSetAttributesParam(&Attrib, argv[i])))
                        return FAILURE;

                    argv++; i++;
                }
                else {

                    if (lpRootPath) {

                        wprintf(L"Parameter format not correct - %s", argv[i]);
                        return FAILURE;
                    }

                    lpRootPath = argv[i];
                }
            }
        }

        return FindFile(&Attrib, lpRootPath);
    }

    return SUCCESS;
}


BOOL ParseSetAttributesParam(PATTRIB pAttrib, LPWSTR lpAttribSwitch) {

    BOOL bToggleMinus = FALSE;

    if (lpAttribSwitch[0] == L'-') bToggleMinus = TRUE;
    else bToggleMinus = FALSE;

    switch (toupper(lpAttribSwitch[1])) {

    case L'R':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_READONLY) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_READONLY);
        break;

    case L'A':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_ARCHIVE) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_ARCHIVE);
        break;

    case L'S':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_SYSTEM) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_SYSTEM);
        break;

    case L'H':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_HIDDEN) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_HIDDEN);
        break;

    case L'O':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_OFFLINE) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_OFFLINE);
        break;

    case L'I':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_NOT_CONTENT_INDEXED) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED);
        break;

    case L'X':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_NO_SCRUB_DATA) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_NO_SCRUB_DATA);
        break;

    case L'P':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_PINNED) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_PINNED);
        break;

    case L'U':

        (bToggleMinus == FALSE) ? (pAttrib->dwChangedAttributes |= ATTRIBUTE_ADD_UNPINNED) :
            (pAttrib->dwChangedAttributes |= ATTRIBUTE_DELETE_UNPINNED);
        break;

    default:

        wprintf(L"Invalid switch - %s", lpAttribSwitch);
        return FAILURE;
    }

    return SUCCESS;
}


BOOL FindFile(PATTRIB pAttrib, LPWSTR lpRoot) {

    // Get find file data
    WIN32_FIND_DATA FindData = { 0 };
    HANDLE hFind = NULL;
    WCHAR szFilePath[MAX_PATH] = L"";
    WCHAR szFilePart[MAX_PATH] = L"";
    LPWSTR lpFilePart = NULL;
    WCHAR szFullPath[MAX_PATH] = L"";

    if ((hFind = FindFirstFileW(lpRoot, &FindData)) == INVALID_HANDLE_VALUE) {

        wprintf(L"File not found - %s", lpRoot);
        return FAILURE;
    }

    GetFullPathNameW(lpRoot, MAX_PATH, &szFilePath, &lpFilePart);
    StrCpyW(szFilePart, lpFilePart);

    // Remove the part of file name from full path
    szFilePath[wcslen(szFilePath) - wcslen(szFilePart)] = L'\0';

    // 1 = directories, 2 = files
    for (int i = 1; i <= 2; i++) {

        hFind = FindFirstFileW(lpRoot, &FindData);

        do {

            // Initialize
            StrCpyW(szFullPath, szFilePath);
            PathAddBackslashW(szFilePath);

            if (i == 1) {

                // Directories except parent directory and current directory
                if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
                    && StrCmpW(FindData.cFileName, L".") && StrCmpW(FindData.cFileName, L"..")) {

                    if (pAttrib->dwSwitches & SWITCH_PROCESS_FOLDER_AS_WELL) {

                        StrCatW(szFullPath, FindData.cFileName);

                        if (pAttrib->dwChangedAttributes == ATTRIBUTE_NO_CHANGES) {

                            // No change
                            if(CHECKRETURN(DisplayFileAttributes(szFullPath)))
                                return FAILURE;
                        }
                        else {

                            // Set attributes to directory
                            if(CHECKRETURN(SetFileAttributesFromParams(szFullPath, pAttrib->dwChangedAttributes)))
                                return FAILURE;
                        }

                        if (pAttrib->dwSwitches & SWITCH_RECURSE_ALL_DIRECTORY) {

                            // Recurse (default: szFilePart = L"*")
                            StrCatW(szFullPath, L"\\");
                            StrCatW(szFullPath, szFilePart);

                            if (CHECKRETURN(FindFile(pAttrib, szFullPath)))
                                return FAILURE;
                        }
                    }
                }
            }
            else {

                // Files
                if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                    StrCatW(szFullPath, FindData.cFileName);

                    if (pAttrib->dwChangedAttributes == ATTRIBUTE_NO_CHANGES) {

                        // No change
                        if (CHECKRETURN(DisplayFileAttributes(szFullPath)))
                            return FAILURE;
                    }
                    else {

                        // Set attributes to directory
                        if (CHECKRETURN(SetFileAttributesFromParams(szFullPath, pAttrib->dwChangedAttributes)))
                            return FAILURE;
                    }
                }
            }

        } while (FindNextFileW(hFind, &FindData));
    }

    return SUCCESS;
}


BOOL SetFileAttributesFromParams(LPWSTR lpFullFilePath, DWORD dwRequiredParamAttrib) {

    DWORD dwAttributes = GetFileAttributesW(lpFullFilePath);

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_READONLY)
        dwAttributes |= FILE_ATTRIBUTE_READONLY;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_READONLY)
        dwAttributes &= ~FILE_ATTRIBUTE_READONLY;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_ARCHIVE)
        dwAttributes |= FILE_ATTRIBUTE_ARCHIVE;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_ARCHIVE)
        dwAttributes &= ~FILE_ATTRIBUTE_ARCHIVE;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_SYSTEM)
        dwAttributes |= FILE_ATTRIBUTE_SYSTEM;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_SYSTEM)
        dwAttributes &= ~FILE_ATTRIBUTE_SYSTEM;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_HIDDEN)
        dwAttributes |= FILE_ATTRIBUTE_HIDDEN;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_HIDDEN)
        dwAttributes &= ~FILE_ATTRIBUTE_HIDDEN;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_OFFLINE)
        dwAttributes |= FILE_ATTRIBUTE_OFFLINE;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_OFFLINE)
        dwAttributes &= ~FILE_ATTRIBUTE_OFFLINE;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_NOT_CONTENT_INDEXED)
        dwAttributes |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED)
        dwAttributes &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_NO_SCRUB_DATA)
        dwAttributes |= FILE_ATTRIBUTE_NO_SCRUB_DATA;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_NO_SCRUB_DATA)
        dwAttributes &= ~FILE_ATTRIBUTE_NO_SCRUB_DATA;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_PINNED)
        dwAttributes |= FILE_ATTRIBUTE_PINNED;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_PINNED)
        dwAttributes &= ~FILE_ATTRIBUTE_PINNED;

    if (dwRequiredParamAttrib & ATTRIBUTE_ADD_UNPINNED)
        dwAttributes |= FILE_ATTRIBUTE_UNPINNED;

    if (dwRequiredParamAttrib & ATTRIBUTE_DELETE_UNPINNED)
        dwAttributes &= ~FILE_ATTRIBUTE_UNPINNED;

    return SetFileAttributesW(lpFullFilePath, dwAttributes);
}
