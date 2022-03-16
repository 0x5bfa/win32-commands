// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


BOOL SetFileOwner(LPCWSTR lpFileName, LPCWSTR lpOwnerName) {

    PSID pSid = NULL;
    SECURITY_INFORMATION SecInfo  = OWNER_SECURITY_INFORMATION;

    GetAccountSid(lpOwnerName, &pSid, NULL);

    // Start protected statement
    __try {

        // Set new owner/group in the object's security descriptor
        if (CHECKRETURN(SetNamedSecurityInfoW(lpFileName, SE_FILE_OBJECT, SecInfo, pSid, NULL, NULL, NULL)))
            __leave;
    }
    __finally {

        // Cleanup
        if (pSid) LocalFree(pSid);
        return SUCCESS;
    }
}
