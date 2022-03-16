#include "Icacls.h"


BOOL FindSid(LPCWSTR lpFileName, LPCWSTR lpStringSid) {

    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD nLengthNeeded = 0;
    PACL pDacl = { 0 };
    ACL_SIZE_INFORMATION aclSize = { 0 };
    PACCESS_ALLOWED_ACE pAce = { 0 };
    SID_NAME_USE snu = { 0 };
    BOOL bDaclDefault = FALSE;
    BOOL bDaclPresent = FALSE;
    PSID pSid = NULL;

    // Get account sid from string
    if (CHECKRETURN(ConvertSid(lpStringSid, &pSid)))
        return FAILURE;

    // Get security descriptor
    if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, NULL, 0, &nLengthNeeded))) {

        // Buffer shortage
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            // Allocate
            if ((pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, nLengthNeeded)) == NULL)
                return FAILURE;

            // Start protected statement
            __try {

                // Get security descriptor with size needed
                if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, pSD, nLengthNeeded, &nLengthNeeded)))
                    __leave;

                // Get dacl from security descriptor
                if (CHECKRETURN(GetSecurityDescriptorDacl(pSD, &bDaclPresent, &pDacl, &bDaclDefault)))
                    __leave;

                // get acl information from dacl
                if (CHECKRETURN(GetAclInformation(pDacl, &aclSize, sizeof(aclSize), AclSizeInformation)))
                    __leave;

                for (DWORD i = 0; i < aclSize.AceCount; i++) {

                    // Get ace from acl
                    if (CHECKRETURN(GetAce(pDacl, i, (LPVOID*)&pAce)))
                        __leave;

                    // Is equal sid
                    if (pSid != NULL && EqualSid(&pAce->SidStart, pSid)) {

                        wprintf(L"SID Found: %s\n", lpFileName);
                        __leave;
                    }
                }
            }
            __finally {

                // Cleanup
                if (pSD) LocalFree(pSD);
                return SUCCESS;
            }
        }
    }

    return FAILURE;
}


BOOL ConvertSid(LPWSTR lpStringSid, PSID* ppSid) {

    // Is numeric format
    if (lpStringSid[0] == L'*') {

        lpStringSid++;

        if (CHECKRETURN(ConvertStringSidToSidW(lpStringSid, &*ppSid)))
            return FAILURE;
    }
    // Is friendly name format
    else {

        GetAccountSid(lpStringSid, &ppSid, NULL);
    }

    return SUCCESS;
}
