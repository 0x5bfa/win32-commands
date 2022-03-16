// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "icacls.h"


BOOL GetAccountSid(LPCWSTR lpUserName, PSID* ppSid, LPWSTR* lplpDomainName) {

    LPWSTR lpDomainName = NULL;
    DWORD nDomainSize = 0;
    PSID pSid = NULL;
    DWORD nSidSize = 0;
    SID_NAME_USE snu = { 0 };

    // Get account sid size needed
    if (CHECKRETURN(LookupAccountNameW(NULL, lpUserName, NULL, &nSidSize, NULL, &nDomainSize, &snu))) {

        // Buffer shortage
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // Allocate memory
            if ((pSid = (PSID)LocalAlloc(LPTR, nSidSize)) == NULL)
                return FAILURE;

            // Allocate memory
            if ((lpDomainName = (LPWSTR)LocalAlloc(LPTR, nDomainSize)) == NULL) {
                if (pSid) LocalFree(pSid);
                return FAILURE;
            }

            // Get account sid
            if (CHECKRETURN(LookupAccountNameW(NULL, lpUserName, pSid, &nSidSize, lpDomainName, &nDomainSize, &snu))) {

                if (pSid) LocalFree(pSid);
                if (lpDomainName) LocalFree(lpDomainName);
                return FAILURE;
            }
        }
        else return FAILURE;
    }
    else return FAILURE;

    *ppSid = pSid;

    if (lplpDomainName == NULL && lpDomainName) LocalFree(lpDomainName);
    else *lplpDomainName = lpDomainName;

    return SUCCESS;
}


BOOL GetAccountName(const PSID pSid, LPWSTR* lplpUserName, LPWSTR* lplpDomainName) {

    LPWSTR lpDomainName = NULL;
    DWORD dwDomainSize = 0;
    LPWSTR lpUserName = NULL;
    DWORD dwUserNameSize = 0;
    SID_NAME_USE snu;

    // Get account name size needed
    if (CHECKRETURN(LookupAccountSidW(NULL, pSid, NULL, &dwUserNameSize, NULL, &dwDomainSize, &snu))) {

        // Buffer shortage
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // Allocate memory
            if ((lpUserName = (LPWSTR)LocalAlloc(LPTR, dwUserNameSize)) == NULL || (lpDomainName = (LPWSTR)LocalAlloc(LPTR, dwDomainSize)) == NULL)
                return FAILURE;

            // Get account name
            if (CHECKRETURN(LookupAccountSidW(NULL, pSid, lpUserName, &dwUserNameSize, lpDomainName, &dwDomainSize, &snu))) {
                if (lpUserName) LocalFree(lpUserName);
                return FAILURE;
            }
        }
        else return FAILURE;
    }
    else return FAILURE;

    *lplpUserName = lpUserName;

    if (lplpDomainName == NULL && lpDomainName) LocalFree(lpDomainName);
    else *lplpDomainName = lpDomainName;

    return SUCCESS;
}
