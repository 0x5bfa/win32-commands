// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "RegMain.h"

static DWORD dwMessageCode = ERROR_SUCCESS;

BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...) {

    return FAILURE; // don't use yet

    // Create arguments list
    va_list vl;
    va_start(vl, nArgs);

    LPVOID lpMessage = NULL;

    if (!FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, dwErrCode, 0, (LPWSTR)&lpMessage, 0, NULL)) {

        return FAILURE;
    }

    wprintf(L"%s\n", (LPWSTR)lpMessage);

    // Don't display message at main
    SetMsgCode(MSG_DISPLAYED_MESSAGE);

    va_end(vl);
    return SUCCESS;
}

DWORD GetMsgCode(VOID) {

    return dwMessageCode;
}

VOID SetMsgCode(DWORD dwErrorCode) {

    dwMessageCode = dwErrorCode;
}
