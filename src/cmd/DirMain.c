// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"
#include "Dir.h"


int DirMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered DirMain() function\n");

    // Initialize
    DIR Dir = { 0 };
    Dir.dwSwitches |= DIR_SWITCH_THOUSAND_SEPARATOR;
    Dir.dwSwitches |= DIR_SWITCH_FOUR_DIGIT_YEARS;
    Dir.dwSwitches |= DIR_SWITCH_FILE_LIST_FORMAT;
    Dir.dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_HIDDEN;
    Dir.dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_SYSTEM;

    if (argc == 1) {

        if (CHECKRETURN(EnumFilesOrDirectoryies(&Dir, NULL))) {

            return FAILURE;
        }
    }
    else {

        if (CHECKRETURN(ParseDirSwitch(&Dir, argc, argv))) {

            return FAILURE;
        }

        if (CHECKRETURN(EnumFilesOrDirectoryies(&Dir, NULL))) {

            return FAILURE;
        }
    }

    return SUCCESS;
}


BOOL EnumFilesOrDirectoryies(PDIR pDir, LPWSTR lpDirectoryName) {

    WCHAR szFullDirPath[MAX_PATH + 2] = L"";
    WCHAR szFullPath[MAX_PATH] = L"";
    WCHAR szFullDirPathWithWildCard[MAX_PATH + 2] = L"";
    LPWSTR lpWildCard = NULL;
    HANDLE hFind = NULL;
    WIN32_FIND_DATAW FindData = { 0 };

    if (lpDirectoryName == NULL) {

        GetCurrentDirectoryW(MAX_PATH, szFullDirPath);
        lpDirectoryName = szFullDirPath;
    }

    GetFullPathNameW(lpDirectoryName, MAX_PATH, szFullDirPathWithWildCard, &lpWildCard);

    // Add back slash and wild card
    if (lpWildCard == NULL || StrStrW(lpWildCard, L"*") == NULL) {

        PathAddBackslashW(szFullDirPathWithWildCard);
        lpWildCard = szFullDirPathWithWildCard;
        lpWildCard += wcslen(szFullDirPathWithWildCard);
        StrCatW(szFullDirPathWithWildCard, L"*");
    }

    if ((hFind = FindFirstFileW(szFullDirPathWithWildCard, &FindData)) == INVALID_HANDLE_VALUE) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return  FAILURE;
    }

    // Display header
    if (!(pDir->dwSwitches & DIR_SWITCH_USES_BARE_FORMAT)) {

        StrCpyW(szFullDirPath, szFullDirPathWithWildCard);
        LPWSTR lpFilePart = NULL;
        GetFullPathNameW(szFullDirPathWithWildCard, MAX_PATH + 2, szFullDirPath, &lpFilePart);
        *lpFilePart = L'\0'; // Delete file part
        DisplayHeader(szFullDirPath);
    }

    do {

        wcscpy(szFullPath, szFullDirPath);
        wcscat(szFullPath, L"\\");
        wcscat(szFullPath, FindData.cFileName);

        if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

            if (!(pDir->dwSwitches & DIR_SWITCH_USES_BARE_FORMAT) && !(pDir->dwSwitches & DIR_SWITCH_WIDE_BY_COLUMN) &&!(pDir->dwSwitches & DIR_SWITCH_USES_WIDE_LIST_FORMAT)) {

                DisplayFileTime(pDir, &FindData);

                DisplayTextMessage(MSG_DIR, NO_ARGS);

                pDir->dwTotalNumOfDirs++;

                wprintf(L"   ");

                if (pDir->dwSwitches & DIR_SWITCH_DISPLAY_FILE_OWNER)
                    DisplayFileOwner(pDir, szFullPath);
            }

            DisplayFileName(pDir, &FindData);
        }
        else {

            if (!(pDir->dwSwitches & DIR_SWITCH_USES_BARE_FORMAT) && !(pDir->dwSwitches & DIR_SWITCH_WIDE_BY_COLUMN) && !(pDir->dwSwitches & DIR_SWITCH_USES_WIDE_LIST_FORMAT)) {

                DisplayFileTime(pDir, &FindData);

                DisplayFileSize(pDir, &FindData);

                if (pDir->dwSwitches & DIR_SWITCH_DISPLAY_FILE_OWNER)
                    DisplayFileOwner(pDir, szFullPath);
            }

            DisplayFileName(pDir, &FindData);
        }
    } while (FindNextFileW(hFind, &FindData));

    FindClose(hFind);

    // Display footer
    if (!(pDir->dwSwitches & DIR_SWITCH_USES_BARE_FORMAT)) {

        DisplayFooter(pDir, szFullDirPath);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!(pDir->dwSwitches & DIR_SWITCH_RECURSES_ALL_SUBS)) {

        return SUCCESS;
    }

    hFind = NULL;

    if ((hFind = FindFirstFileW(szFullDirPathWithWildCard, &FindData)) == INVALID_HANDLE_VALUE) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return  FAILURE;
    }

    // Recurse all sub directories
    do {

        if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

            wcscpy(szFullPath, szFullDirPath);
            wcscat(szFullPath, L"\\");
            wcscat(szFullPath, FindData.cFileName);
            wcscat(szFullPath, L"\\");
            wcscat(szFullPath, lpWildCard);

            EnumFilesOrDirectoryies(pDir, szFullPath);
        }

    } while (FindNextFileW(hFind, &FindData));

    return SUCCESS;
}


BOOL DisplayFileTime(PDIR pDir, PWIN32_FIND_DATA pFindData) {

    SYSTEMTIME SystemTime = { 0 };
    FILETIME FileTime = { 0 };

    // NOTE: File time is constant time display format

    if (pDir->dwSpecifiedAttributes & DIR_SWITCH_SPECIFIES_TIMEFIELD) {

        switch (pDir->dwTimeField) {

        case DIR_TIMEFIELD_CREATION:

            FileTimeToLocalFileTime(&pFindData->ftCreationTime, &FileTime);
            FileTimeToSystemTime(&FileTime, &SystemTime);
            wprintf(L"%04d/%02d/%02d  %02d:%02d    ", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute);
            break;

        case DIR_TIMEFIELD_LAST_ACCESS:

            FileTimeToLocalFileTime(&pFindData->ftLastAccessTime, &FileTime);
            FileTimeToSystemTime(&FileTime, &SystemTime);
            wprintf(L"%04d/%02d/%02d  %02d:%02d    ", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute);
            break;
        }

        return SUCCESS;
    }

    // DIR_TIMEFIELD_LAST_WRITTEN
    FileTimeToLocalFileTime(&pFindData->ftLastWriteTime, &FileTime);
    FileTimeToSystemTime(&FileTime, &SystemTime);
    wprintf(L"%04d/%02d/%02d  %02d:%02d    ", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute);

    return SUCCESS;
}


BOOL DisplayFileSize(PDIR pDir, PWIN32_FIND_DATA pFindData) {

    WCHAR szFileSize[64] = L"";

    if (pFindData->nFileSizeHigh) {

        swprintf(szFileSize, 64, L"%d%d", pFindData->nFileSizeHigh, pFindData->nFileSizeLow);
    }
    else {

        swprintf(szFileSize, 64, L"%d", pFindData->nFileSizeLow);
    }

    InsertThousandCommaSeparator(pDir, szFileSize);
    wprintf(L"%14s ", szFileSize);

    pDir->dwTotalNumOfBitesOfFiles += pFindData->nFileSizeLow;
    pDir->dwTotalNumOfFiles++;

    return SUCCESS;
}


BOOL DisplayFileOwner(PDIR pDir, LPWSTR lpFullDirPath) {

    PACL pResultAcl = NULL;
    PSECURITY_DESCRIPTOR pSecurityDescriptor = NULL;
    DWORD dwSecurityDescriptorSize = 0;
    PSID pOwnerSid = NULL;
    BOOL bOwnerDefaulted = FALSE;
    TCHAR szAccountName[1024] = L"";
    TCHAR szDomainName[256] = L"";
    DWORD dwAccountNameSize = 1024;
    DWORD dwDomainNameSize = 256;
    WCHAR szFullAccountName[1024 + 256] = L"";
    SID_NAME_USE nSidNameUse = { 0 };

    if (CHECKRETURN(GetFileSecurityW(lpFullDirPath, OWNER_SECURITY_INFORMATION, NULL, 0, &dwSecurityDescriptorSize))) {

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {

            DisplayTextMessage(GetLastError(), NO_ARGS);
            return FAILURE;
        }
    }

    if ((pSecurityDescriptor = (PSECURITY_DESCRIPTOR)calloc(1, dwSecurityDescriptorSize + 1000)) == NULL) {

        DisplayTextMessage(ERROR_NOT_ENOUGH_MEMORY, NO_ARGS);
        return FAILURE;
    }

    if (CHECKRETURN(GetFileSecurityW(lpFullDirPath, OWNER_SECURITY_INFORMATION, pSecurityDescriptor, dwSecurityDescriptorSize, &dwSecurityDescriptorSize))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);

        if (pSecurityDescriptor) free(pSecurityDescriptor);

        return FAILURE;
    }

    if (CHECKRETURN(GetSecurityDescriptorOwner(pSecurityDescriptor, &pOwnerSid, &bOwnerDefaulted))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);

        if (pSecurityDescriptor) free(pSecurityDescriptor);

        return FAILURE;
    }

    if (CHECKRETURN(LookupAccountSidW(NULL, pOwnerSid, szAccountName, &dwAccountNameSize, szDomainName, &dwDomainNameSize, &nSidNameUse))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);

        if (pSecurityDescriptor) free(pSecurityDescriptor);

        return FAILURE;
    }

    wcscpy(szFullAccountName, szDomainName);
    wcscat(szFullAccountName, L"\\");
    wcscat(szFullAccountName, szAccountName);

    wprintf(L"%-22s ", szFullAccountName);

    return SUCCESS;
}


BOOL DisplayFileName(PDIR pDir, PWIN32_FIND_DATA pFindData) {

    if (pDir->dwSwitches & DIR_SWITCH_USES_LOWERCASE) {

        CharLowerBuffW(pFindData->cFileName, MAX_PATH);
        CharLowerBuffW(pFindData->cAlternateFileName, 14);
    }

    if (pDir->dwSwitches & DIR_SWITCH_DISPLAY_SHORT_NAME) {

        wprintf(L"%-12s ", pFindData->cAlternateFileName);
    }

    if (pDir->dwSwitches & DIR_SWITCH_USES_WIDE_LIST_FORMAT) {

        return SUCCESS;
    }

    if (pDir->dwSwitches & DIR_SWITCH_WIDE_BY_COLUMN) {

        return SUCCESS;
    }

    wprintf(L"%s\n", pFindData->cFileName);

    return SUCCESS;
}


BOOL InsertThousandCommaSeparator(PDIR pDir, LPWSTR lpFileSize) {

    if (!(pDir->dwSwitches & DIR_SWITCH_THOUSAND_SEPARATOR)) {

        return SUCCESS;
    }

    DWORD dwFileSizeLen = wcslen(lpFileSize);
    DWORD dwLoop = (dwFileSizeLen - (dwFileSizeLen % 2)) / 2;
    WCHAR cTemporary = L'\0';

    // Replace charcters (1234 to 4321)
    for (int i = 0, j = dwFileSizeLen - 1; (DWORD)i < dwLoop; i++, j--) {

        cTemporary = lpFileSize[i];
        lpFileSize[i] = lpFileSize[j];
        lpFileSize[j] = cTemporary;
    }

    // Insert thousand comma separators (4321 to 432,1)
    for (int i = 0; lpFileSize[i] != L'\0'; i++) {

        if ((i + 1) % 4 == 0) {

            for (int j = dwFileSizeLen; j > i; j--) {

                lpFileSize[j] = lpFileSize[j - 1];
            }

            lpFileSize[i] = L',';
            dwFileSizeLen++;
        }
    }

    dwFileSizeLen = wcslen(lpFileSize);
    dwLoop = (dwFileSizeLen - (dwFileSizeLen % 2)) / 2;

    // Replace chracters (432,1 to 1,234)
    for (int i = 0, j = dwFileSizeLen - 1; (DWORD)i < dwLoop; i++, j--) {

        cTemporary = lpFileSize[i];
        lpFileSize[i] = lpFileSize[j];
        lpFileSize[j] = cTemporary;
    }

    return SUCCESS;
}


BOOL DisplayHeader(LPWSTR lpFullDirPath) {

    WCHAR szDrivePath[3] = L"";
    szDrivePath[0] = lpFullDirPath[0];
    szDrivePath[1] = lpFullDirPath[1];

    DisplayVolInfo(szDrivePath);

    wprintf(L"\n");
    DisplayTextMessage(MSG_DIR_OF, ONE_ARG, lpFullDirPath);

    return SUCCESS;
}


BOOL DisplayFooter(PDIR pDir, LPWSTR lpFullDirPath) {

    // High size part is not available
    // so use LARGE_INTEGER structure or use long long type?

    WCHAR szTemporary[32] = L"";

    WCHAR szTotalNumOfFiles[32] = L"";
    WCHAR szTotalNumOfBitesOfFiles[32] = L"";
    WCHAR szTotalNumOfDirs[32] = L"";
    WCHAR szTotalNumOfBitesOfFree[32] = L"";

    swprintf(szTemporary, 32, L"%d", pDir->dwTotalNumOfFiles);
    InsertThousandCommaSeparator(pDir, szTemporary);
    swprintf(szTotalNumOfFiles, 32, L"%11s", szTemporary);

    swprintf(szTemporary, 32, L"%d", pDir->dwTotalNumOfBitesOfFiles);
    InsertThousandCommaSeparator(pDir, szTemporary);
    swprintf(szTotalNumOfBitesOfFiles, 32, L"%14s", szTemporary);

    swprintf(szTemporary, 32, L"%d", pDir->dwTotalNumOfDirs);
    InsertThousandCommaSeparator(pDir, szTemporary);
    swprintf(szTotalNumOfDirs, 32, L"%11s", szTemporary);

    long long dwSectorsPerCluster = 0;
    long long dwBytesPerSector = 0;
    long long dwNumberOfFreeClusters = 0;

    if (CHECKRETURN(GetDiskFreeSpaceW(lpFullDirPath, &(DWORD)dwSectorsPerCluster, &(DWORD)dwBytesPerSector, &(DWORD)dwNumberOfFreeClusters, NULL))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    long long dwFreeSpaceSize = dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters;

    swprintf(szTemporary, 32, L"%lld", dwFreeSpaceSize);
    InsertThousandCommaSeparator(pDir, szTemporary);
    swprintf(szTotalNumOfBitesOfFree, 32, L"%14s", szTemporary);

    DisplayTextMessage(MSG_FILES_COUNT_FREE, TWO_ARGS, szTotalNumOfFiles, szTotalNumOfBitesOfFiles);

    DisplayTextMessage(MSG_FILES_TOTAL_FREE, TWO_ARGS, szTotalNumOfDirs, szTotalNumOfBitesOfFree);

    return SUCCESS;
}
