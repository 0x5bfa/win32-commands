// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Attrib.h"

BOOL DisplayFileAttributes(LPWSTR lpFullPathName) {

    WCHAR szAttributes[256] = L"";

    DWORD dwAttributes = GetFileAttributesW(lpFullPathName);
    if (dwAttributes == INVALID_FILE_ATTRIBUTES) return FAILURE;

    swprintf(szAttributes, 256, L"%lc  %lc%lc%lc %lc%lc  %lc %lc%lc     ",
        dwAttributes & FILE_ATTRIBUTE_ARCHIVE ?  L'A' : L' ',

        dwAttributes & FILE_ATTRIBUTE_SYSTEM ?   L'S' : L' ',
        dwAttributes & FILE_ATTRIBUTE_HIDDEN ?   L'H' : L' ',
        dwAttributes & FILE_ATTRIBUTE_READONLY ? L'R' : L' ',

        dwAttributes & FILE_ATTRIBUTE_OFFLINE ?  L'O' : L' ',
        dwAttributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED ? L'I' : L' ',

        dwAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA ? L'X' : L' ',
        dwAttributes & FILE_ATTRIBUTE_PINNED ?   L'P' : L' ',
        dwAttributes & FILE_ATTRIBUTE_UNPINNED ? L'U' : L' '
    );

    wprintf(L"%s %s\n", szAttributes, lpFullPathName);

    return SUCCESS;
}


BOOL DisplayFormattedMessage(DWORD dwMsgId, DWORD nArgs, ...) {

    va_list args = NULL;
    va_start(args, nArgs);

    LPWSTR lpMessage = NULL;

    if (!FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwMsgId, 0, (LPTSTR)&lpMessage, 10, &args))
        return FAILURE;

    va_end(args);

    return SUCCESS;

}