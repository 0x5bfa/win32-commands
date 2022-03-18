// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "RegMain.h"


DWORD ParseRegCmdLine(PREG pReg, int argc, LPWSTR argv[]);
BOOL InitializeReg(PREG pReg);


int wmain(int argc, LPWSTR argv[]) {

    _wsetlocale(LC_ALL, L"");

    BOOL bResult = SUCCESS;
    REG Reg = { 0 };
    InitializeReg(&Reg);

    Reg.dwOperation = ParseRegCmdLine(&Reg, argc, argv);
    argc--; argv++;

    // Pass to each command
    switch (Reg.dwOperation) {

    case OPERATION_QUERY:

        bResult = RegQueryMain(&Reg, argc, argv);
        break;

    case OPERATION_ADD:

        bResult = RegAddMain(&Reg, argc, argv);
        break;

    case OPERATION_DELETE:

        bResult = RegDeleteMain(&Reg, argc, argv);
        break;

    case OPERATION_COPY:

        break;

    case OPERATION_SAVE:

        bResult = RegSaveMain(&Reg, argc, argv);
        break;

    case OPERATION_LOAD:

        bResult = RegLoadMain(&Reg, argc, argv);
        break;

    case OPERATION_UNLOAD:

        bResult = RegUnLoadMain(&Reg, argc, argv);
        break;

    case OPERATION_RESTORE:

        bResult = RegRestoreMain(&Reg, argc, argv);
        break;

    case OPERATION_COMPARE:

        break;

    case OPERATION_EXPORT:

        bResult = RegExportMain(&Reg, argc, argv);
        break;

    case OPERATION_IMPORT:

        break;

    case OPERATION_FLAGS:

        break;
    }

    // Clean up return status
    if (bResult != ERROR_SUCCESS) {

        switch (GetMsgCode()) {

        case MSG_DISPLAYED_MESSAGE:
            return 1;

        }
    }

    return 0;
}


DWORD ParseRegCmdLine(PREG pReg, int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_INVALID_SYNTAX_REG_OP, NO_ARGS);
        return FAILURE;
    }
    else if (CHECKRETURN(StrCmpIW(argv[1], L"/?")) || CHECKRETURN(StrCmpIW(argv[1], L"-?")) ||
        CHECKRETURN(StrCmpIW(argv[1], L"/h")) || CHECKRETURN(StrCmpIW(argv[1], L"-h"))) {

        DisplayTextMessage(MSG_HELP_REG, NO_ARGS);
        return SUCCESS;
    }
    else if (CHECKRETURN(StrCmpIW(argv[1], L"query")))   return OPERATION_QUERY;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"add")))     return OPERATION_ADD;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"delete")))  return OPERATION_DELETE;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"copy")))    return OPERATION_COPY;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"save")))    return OPERATION_SAVE;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"restore"))) return OPERATION_RESTORE;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"load")))    return OPERATION_LOAD;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"unload")))  return OPERATION_UNLOAD;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"compare"))) return OPERATION_COMPARE;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"export")))  return OPERATION_EXPORT;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"import")))  return OPERATION_IMPORT;
    else if (CHECKRETURN(StrCmpIW(argv[1], L"flags")))   return OPERATION_FLAGS;
    else {

        DisplayTextMessage(MSG_INVALID_PARAMS_GET_USAGE, ONE_ARG, argv[1]);
        return FAILURE;
    }

    return SUCCESS;
}


BOOL InitializeReg(PREG pReg) {

    pReg->nHKey = 0;
    pReg->dwSwitches = 0;
    pReg->dwOperation = 0;

    pReg->lpMachineName = NULL;
    pReg->lpFullKey = NULL;
    pReg->lpSubKey = NULL;
    pReg->lpValueName = NULL;
    pReg->lpSeparator = NULL;
    pReg->lpFindPattern = L"*";
    pReg->dwSpecifyDataType = 0;

    return SUCCESS;
}


HKEY OpenRegKey(PREG pReg, LPWSTR lpSubRoot, REGSAM samDesired) {

    HKEY hKey = NULL;
    DWORD dwResult = ERROR_SUCCESS;

    // Remote or local
    if (pReg->dwSwitches & SWITCH_SPECIFY_MACHINE) {

        if ((dwResult = RegConnectRegistryExW(lpSubRoot, pReg->nHKey,
            samDesired | ((pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) ? KEY_WOW64_32KEY : KEY_WOW64_64KEY), &hKey)) != ERROR_SUCCESS) {

            // Because the calling function may create the specified key
            if (!(pReg->dwOperation == OPERATION_ADD || pReg->dwOperation == OPERATION_DELETE))
                DisplayTextMessage(dwResult, NO_ARGS);

            SetLastError(dwResult);
            return FAILURE;
        }
    }
    else {

        if ((dwResult = RegOpenKeyExW(pReg->nHKey, lpSubRoot, 0,
            samDesired | ((pReg->dwSwitches & SWITCH_SPECIFY_USE_32ARCH_REG) ? KEY_WOW64_32KEY : KEY_WOW64_64KEY), &hKey)) != ERROR_SUCCESS) {

            // Because the calling function may create the specified key
            if (!(pReg->dwOperation == OPERATION_ADD || pReg->dwOperation == OPERATION_DELETE))
                DisplayTextMessage(dwResult, NO_ARGS);

            SetLastError(dwResult);
            return FAILURE;
        }
    }

    SetLastError(ERROR_SUCCESS);
    return hKey;
}


BOOL EnableTokenPrivileges(LPWSTR lpMachineName, LPWSTR lpPrivilegeName, DWORD dwAttributes) {

    HANDLE hToken = NULL;
    TOKEN_PRIVILEGES TokenPrivileges = { 0 };

    if (CHECKRETURN(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)))
        return FAILURE;

    if (CHECKRETURN(LookupPrivilegeValueW(lpMachineName, lpPrivilegeName, &TokenPrivileges.Privileges[0].Luid)))
        return FAILURE;

    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Attributes = dwAttributes;

    if (CHECKRETURN(AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, (PTOKEN_PRIVILEGES)NULL, NULL)))
        return FAILURE;

    return SUCCESS;
}
