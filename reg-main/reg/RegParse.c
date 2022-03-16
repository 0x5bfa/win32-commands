// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "RegMain.h"


BOOL ParseRegistryKeyName(PREG pReg, LPWSTR lpKeyName) {

    DWORD dwMachineNameSize = 0;
    DWORD dwRootKeyNameSize = 0;
    LPWSTR lpRootKeyName = NULL;


    // Parse machine name
    if (lpKeyName[0] == L'\\' && lpKeyName[1] == L'\\') {

        // Get machine name size
        for (; lpKeyName[dwMachineNameSize] != L'\0'; dwMachineNameSize++) {

            if (dwMachineNameSize >= 2 && lpKeyName[dwMachineNameSize] == L'\\')
                break;
        }

        dwMachineNameSize++;

        if (lpKeyName[2] == L'.') lpKeyName += 3;
        else if (lpKeyName[2] == L'\\' || lpKeyName[2] == L'\0') return FAILURE;
        else {

            // Allocate memory
            if ((pReg->lpMachineName = (LPWSTR)calloc(dwMachineNameSize, sizeof(WCHAR))) == NULL) {

                SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                return FAILURE;
            }

            StrCpyNW(pReg->lpMachineName, lpKeyName, dwMachineNameSize);

            lpKeyName += dwMachineNameSize;

            pReg->dwSwitches |= SWITCH_SPECIFY_MACHINE;
        }
    }

    BOOL bSubKey = FALSE;

    // Parse root key
    for (; lpKeyName[dwRootKeyNameSize] != L'\0'; dwRootKeyNameSize++) {

        if (lpKeyName[dwRootKeyNameSize] == L'\\') {

            bSubKey = TRUE;
            break;
        }
    }

    dwRootKeyNameSize++;

    if ((lpRootKeyName = (LPWSTR)calloc(dwRootKeyNameSize, sizeof(WCHAR))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FAILURE;
    }

    StrCpyNW(lpRootKeyName, lpKeyName, dwRootKeyNameSize);

    GetRootKey(pReg, lpRootKeyName);

    // There is subkey
    if (bSubKey == TRUE) lpKeyName += dwRootKeyNameSize;
    else lpKeyName += (dwRootKeyNameSize - 1UL);

    // Parse sub key
    pReg->lpSubKey = lpKeyName;

    // Full key
    if ((pReg->lpFullKey = (LPWSTR)calloc(wcslen(lpKeyName) + 32, sizeof(WCHAR))) == NULL) {

        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return FAILURE;
    }

    // Get root key
    GetRootKeyString(pReg);

    if (StrCmpW(pReg->lpSubKey, L"") != 0) {

        StrCatW(pReg->lpFullKey, L"\\");
        StrCatW(pReg->lpFullKey, pReg->lpSubKey);
    }

    return SUCCESS;
}


BOOL GetRootKey(PREG pReg, LPWSTR lpHKey) {

    if (CHECKRETURN(StrCmpIW(lpHKey, L"HKEY_LOCAL_MACHINE")) || CHECKRETURN(StrCmpIW(lpHKey, L"HKLM"))) {

        pReg->nHKey = HKEY_LOCAL_MACHINE;
    }
    else if (CHECKRETURN(StrCmpIW(lpHKey, L"HKEY_CURRENT_USER")) || CHECKRETURN(StrCmpIW(lpHKey, L"HKCU"))) {

        pReg->nHKey = HKEY_CURRENT_USER;
    }
    else if (CHECKRETURN(StrCmpIW(lpHKey, L"HKEY_CLASSES_ROOT")) || CHECKRETURN(StrCmpIW(lpHKey, L"HKCR"))) {

        pReg->nHKey = HKEY_CLASSES_ROOT;
    }
    else if (CHECKRETURN(StrCmpIW(lpHKey, L"HKEY_USERS")) || CHECKRETURN(StrCmpIW(lpHKey, L"HKU"))) {

        pReg->nHKey = HKEY_USERS;
    }
    else if (CHECKRETURN(StrCmpIW(lpHKey, L"HKEY_CURRENT_CONFIG")) || CHECKRETURN(StrCmpIW(lpHKey, L"HKCC"))) {

        pReg->nHKey = HKEY_CURRENT_CONFIG;
    }
    else return FAILURE;

    return SUCCESS;
}


BOOL GetRootKeyString(PREG pReg) {

    if (pReg->nHKey == HKEY_CLASSES_ROOT) {

        StrCpyW(pReg->lpFullKey, L"HKEY_CLASSES_ROOT");
        StrCpyW(pReg->lpRootKeyName, L"HKEY_CLASSES_ROOT");
    }
    else if (pReg->nHKey == HKEY_CURRENT_CONFIG) {

        StrCpyW(pReg->lpFullKey, L"HKEY_CURRENT_CONFIG");
        StrCpyW(pReg->lpRootKeyName, L"HKEY_CURRENT_CONFIG");
    }
    else if (pReg->nHKey == HKEY_CURRENT_USER) {

        StrCpyW(pReg->lpFullKey, L"HKEY_CURRENT_USER");
        StrCpyW(pReg->lpRootKeyName, L"HKEY_CURRENT_USER");
    }
    else if (pReg->nHKey == HKEY_LOCAL_MACHINE) {


        StrCpyW(pReg->lpFullKey, L"HKEY_LOCAL_MACHINE");
        StrCpyW(pReg->lpRootKeyName, L"HKEY_LOCAL_MACHINE");
    }
    else if (pReg->nHKey == HKEY_USERS) {

        StrCpyW(pReg->lpFullKey, L"HKEY_USERS");
        StrCpyW(pReg->lpRootKeyName, L"HKEY_USERS");
    }
    else return FAILURE;

    return SUCCESS;
}


DWORD GetRegDataType(LPWSTR lpRegDataType) {

    if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_BINARY"))) {

        return REG_BINARY;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_DWORD"))) {

        return REG_DWORD;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_DWORD_LITTLE_ENDIAN"))) {

        return REG_DWORD_LITTLE_ENDIAN;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_DWORD_BIG_ENDIAN"))) {

        return REG_DWORD_BIG_ENDIAN;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_EXPAND_SZ"))) {

        return REG_EXPAND_SZ;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_LINK"))) {

        return REG_LINK;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_MULTI_SZ"))) {

        return REG_MULTI_SZ;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_NONE"))) {

        return REG_NONE;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_QWORD"))) {

        return REG_QWORD;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_QWORD_LITTLE_ENDIAN"))) {

        return REG_QWORD_LITTLE_ENDIAN;
    }
    else if (CHECKRETURN(StrCmpIW(lpRegDataType, L"REG_SZ"))) {

        return REG_SZ;
    }

    return SUCCESS;
}


BOOL GetDataTypeString(OUT LPWSTR lpDataType, IN DWORD dwDataType) {

    if (lpDataType == NULL) return FAILURE;

    switch (dwDataType) {

    case REG_BINARY:
        StrCpyW(lpDataType, L"REG_BINARY");
        break;

    case REG_DWORD:
        StrCpyW(lpDataType, L"REG_DWORD");
        break;

    case REG_DWORD_BIG_ENDIAN:
        StrCpyW(lpDataType, L"REG_DWORD_BIG_ENDIAN");
        break;

    case REG_EXPAND_SZ:
        StrCpyW(lpDataType, L"REG_EXPAND_SZ");
        break;

    case REG_LINK:
        StrCpyW(lpDataType, L"REG_LINK");
        break;

    case REG_MULTI_SZ:
        StrCpyW(lpDataType, L"REG_MULTI_SZ");
        break;

    case REG_QWORD:
        StrCpyW(lpDataType, L"REG_QWORD");
        break;

    case REG_SZ:
        StrCpyW(lpDataType, L"REG_SZ");
        break;

    default:
        StrCpyW(lpDataType, L"REG_NONE");
        break;
    }

    return SUCCESS;
}
