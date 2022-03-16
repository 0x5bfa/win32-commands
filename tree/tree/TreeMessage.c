// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Tree.h"


BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...) {

    setlocale(LC_ALL, "");

    // Create arguments list
    va_list vl = NULL;
    va_start(vl, nArgs);

    LPVOID lpMessage = NULL;

    if (CHECKRETURN(FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | ((dwErrCode >= 9000) ? FORMAT_MESSAGE_FROM_HMODULE : FORMAT_MESSAGE_FROM_SYSTEM),
        NULL, dwErrCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMessage, 0, &vl))) {

        return FAILURE;
    }

    wprintf(L"%s", (LPWSTR)lpMessage);

    LocalFree(lpMessage);
    va_end(vl);

    return SUCCESS;
}
