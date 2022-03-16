// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


BOOL DislpaySecInfo(LPCWSTR lpFileName) {

    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD nLengthNeeded = 0;
    PACL pDacl = { 0 };
    ACL_SIZE_INFORMATION aclSize = { 0 };
    PACCESS_ALLOWED_ACE pAce = { 0 };
    LPWSTR lpAccountName = NULL;
    LPWSTR lpDomainName = NULL;
    SID_NAME_USE snu = { 0 };
    BOOL bDaclDefault = FALSE;
    BOOL bDaclPresent = FALSE;

    if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, NULL, 0, &nLengthNeeded))) {

        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {

            if ((pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, nLengthNeeded)) == NULL)
                return FAILURE;

            __try {

                if (CHECKRETURN(GetFileSecurityW(lpFileName, DACL_SECURITY_INFORMATION, pSD, nLengthNeeded, &nLengthNeeded)))
                    __leave;

                if (CHECKRETURN(GetSecurityDescriptorDacl(pSD, &bDaclPresent, &pDacl, &bDaclDefault)))
                    __leave;

                if (CHECKRETURN(GetAclInformation(pDacl, &aclSize, sizeof(aclSize), AclSizeInformation)))
                    __leave;

                for (DWORD i = 0; i < aclSize.AceCount; i++) {

                    if (CHECKRETURN(GetAce(pDacl, i, (LPVOID*)&pAce)))
                        __leave;

                    if(CHECKRETURN(GetAccountName(&pAce->SidStart, &lpAccountName, &lpDomainName)))
                        __leave;

                    // Display filename
                    if (i == 0) {

                        wprintf(L"%s", lpFileName);
                    }
                    else {

                        for (int i = 0; i < (int)wcslen(lpFileName); i++) {

                            wprintf(L" ");
                        }
                    }

                    // Display principal
                    if (CHECKRETURN(StrCmpW(lpDomainName, L""))) {

                        wprintf(L" %s:", lpAccountName);
                    }
                    else {

                        wprintf(L" %s\\%s:", lpDomainName, lpAccountName);
                    }

                    // if denied access, display "(Deny)"
                    if (pAce->Header.AceType & ACCESS_DENIED_ACE_TYPE)
                        DisplayTextMessage(MSG_DENY_ACCESS, NO_ARGS);

                    // Display inheritance
                    if (pAce->Header.AceFlags & INHERITED_ACE)
                        wprintf(L"(I)");

                    if (pAce->Header.AceFlags & OBJECT_INHERIT_ACE)
                        DisplayTextMessage(MSG_OI_INHERITANCE, NO_ARGS);

                    if (pAce->Header.AceFlags & CONTAINER_INHERIT_ACE)
                        DisplayTextMessage(MSG_CI_INHERITANCE, NO_ARGS);

                    if (pAce->Header.AceFlags & INHERIT_ONLY_ACE)
                        DisplayTextMessage(MSG_IO_INHERITANCE, NO_ARGS);

                    if (pAce->Header.AceFlags & NO_PROPAGATE_INHERIT_ACE)
                        DisplayTextMessage(MSG_NP_INHERITANCE, NO_ARGS);

                    WCHAR szAccMask[256] = L"";

                    if ((pAce->Mask & FILE_ALL_ACCESS) == FILE_ALL_ACCESS) {

                        wcscpy_s(szAccMask, 256, L"F");
                    }
                    else {

                        if ((pAce->Mask & FILE_GENERIC_READ) == FILE_GENERIC_READ &&
                            (pAce->Mask & FILE_GENERIC_WRITE) == FILE_GENERIC_WRITE &&
                            (pAce->Mask & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE &&
                            (pAce->Mask & DELETE) == DELETE) {

                            wcscat_s(szAccMask, 256, L"M,");
                        }
                        else {

                            if ((pAce->Mask & FILE_GENERIC_READ) == FILE_GENERIC_READ &&
                                (pAce->Mask & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE) {

                                wcscat_s(szAccMask, 256, L"RX,");
                            }
                            else {

                                if ((pAce->Mask & FILE_GENERIC_READ) == FILE_GENERIC_READ) {

                                    wcscat_s(szAccMask, 256, L"R,");
                                }
                                else {

                                    if ((pAce->Mask & FILE_READ_DATA) == FILE_READ_DATA)
                                        wcscat_s(szAccMask, 256, L"RD,");
                                    if ((pAce->Mask & FILE_READ_ATTRIBUTES) == FILE_READ_ATTRIBUTES)
                                        wcscat_s(szAccMask, 256, L"RA,");
                                    if ((pAce->Mask & FILE_READ_EA) == FILE_READ_EA)
                                        wcscat_s(szAccMask, 256, L"REA,");
                                    if ((pAce->Mask & SYNCHRONIZE) == SYNCHRONIZE)
                                        wcscat_s(szAccMask, 256, L"S,");
                                }
                                if ((pAce->Mask & FILE_EXECUTE) == FILE_EXECUTE) {

                                    wcscat_s(szAccMask, 256, L"X,");
                                }
                            }
                            if ((pAce->Mask & FILE_GENERIC_WRITE) == FILE_GENERIC_WRITE) {

                                wcscat_s(szAccMask, 256, L"GW,");
                            }
                            else {

                                if ((pAce->Mask & FILE_WRITE_DATA) == FILE_WRITE_DATA)
                                    wcscat_s(szAccMask, 256, L"WD,");

                                if ((pAce->Mask & FILE_APPEND_DATA) == FILE_APPEND_DATA)
                                    wcscat_s(szAccMask, 256, L"AD,");

                                if ((pAce->Mask & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES)
                                    wcscat_s(szAccMask, 256, L"WA,");

                                if ((pAce->Mask & FILE_WRITE_EA) == FILE_WRITE_EA)
                                    wcscat_s(szAccMask, 256, L"WEA,");
                            }
                            if ((pAce->Mask & DELETE) == DELETE) {

                                wcscat_s(szAccMask, 256, L"D,");
                            }
                        }
                        if ((pAce->Mask & WRITE_DAC) == WRITE_DAC) {

                            wcscat_s(szAccMask, 256, L"WDAC,");
                        }
                        if ((pAce->Mask & WRITE_OWNER) == WRITE_OWNER) {

                            wcscat_s(szAccMask, 256, L"WO,");
                        }
                    }

                    // Display access mask
                    if (pAce->Mask != 0) {

                        if (wcslen(szAccMask) > 0 && szAccMask[wcslen(szAccMask) - 1] == L',') {

                            szAccMask[wcslen(szAccMask) - 1] = L'\0';
                        }

                        wprintf(L"(%s)", szAccMask);
                    }

                    wprintf(L"\n");
                }
            }
            __finally {

                wprintf(L"\n");
                if (pSD) LocalFree(pSD);
            }
        }
        else return FAILURE;
    }
    else return FAILURE;

    return SUCCESS;
}
