// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Icacls.h"


BOOL VerifySecDesc(LPWSTR lpFileName) {

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

                if (CHECKRETURN(IsValidSecurityDescriptor(pSD))) {

                    // temporary display message
                    wprintf(L"AAA\n");
                }
            }
            __finally {

                // Cleanup
                if (pSD != NULL) LocalFree(pSD);

                return SUCCESS;
            }
        }
    }
}
