// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

BOOL bDisableUNCCheck = FALSE;
BOOL bEnableExtensions = FALSE;
BOOL bDelayedExpansion = FALSE;
WORD wDefaultColor = 0;
WCHAR cCompletionCtrl = 0;
WCHAR cPathCompletionCtrl = 0;

BOOL GetCmdRegistryValue(LPWSTR lpAutorunCmds[]);
BOOL ParseCmdSwitch(PCMD pCmd, int argc, LPWSTR argv[]);


BOOL InitializeCmdPrompt(PCMD pCmd) {

    WCHAR szAutoRun[2][1024] = { L"", L"" };

    // Get command prompt policy
    if (GetCmdPromptPolicy() == FALSE) {

        DisplayTextMessage(MSG_DISABLED_BY_POLICY, NO_ARGS);
        return FAILURE;
    }

    // Get registry values for windows command prompt
    if (CHECKRETURN(GetCmdRegistryValue(&szAutoRun))) {

        return FAILURE;
    }

    // Set color
    if (wDefaultColor != 0 && CHECKRETURN(SetColor(wDefaultColor))) {

        return FAILURE;
    }

    CMD CmdUserAutorun = { 0 };
    CMD CmdMachineAutorun = { 0 };

    // Parse autorun command(s)
    if (!(pCmd->dwSwitch & SWITCH_DISABLE_AUTORUN)) {

        int iUserArgc = 0;
        int iMachineArgc = 0;

        LPWSTR lpUserArgv = CommandLineToArgvW(szAutoRun[0], &iUserArgc);
        LPWSTR lpMachineArgv = CommandLineToArgvW(szAutoRun[1], &iMachineArgc);

        ParseCmdSwitch(&CmdUserAutorun, iUserArgc, lpUserArgv);
        ParseCmdSwitch(&CmdMachineAutorun, iMachineArgc, lpMachineArgv);
    }

    return SUCCESS;
}


BOOL GetCmdRegistryValue(LPWSTR lpAutorunCmds[]) {

    DWORD dwResult = ERROR_SUCCESS;
    HKEY PredefinedKeys[2] = { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER };
    HKEY hKeyResult = NULL;
    DWORD cbData = 0;
    DWORD dwDataType = REG_NONE;
    DWORD dwBuffer[1024] = { 0 };
    LPBYTE pData = (PBYTE)dwBuffer;
    LPWSTR lpAutorunBuffer = NULL;
    WCHAR szExpandedBuffer[1024] = L"";

    // (i == 1): HKEY_CURRENT_USER
    // (i == 2): HKEY_LOCEL_MACHINE
    for (int i = 0; i < 2; i++) {

        dwDataType = REG_NONE;
        szExpandedBuffer[0] = L'\0';

        if ((dwResult = RegOpenKeyW(PredefinedKeys[i], L"Software\\Microsoft\\Command Processor", &hKeyResult)) != ERROR_SUCCESS) {

            continue;
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"AutoRun", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS) {

            lpAutorunBuffer = (LPWSTR)pData;

            if (dwDataType == REG_EXPAND_SZ) {

                if (CHECKRETURN(ExpandEnvironmentStringsW(lpAutorunBuffer, &szExpandedBuffer, sizeof(szExpandedBuffer) / sizeof(WCHAR))))
                    szExpandedBuffer[0] = L'\0';
            }

            if (szExpandedBuffer[0] != L'\0') wcscpy(lpAutorunCmds[i], szExpandedBuffer);
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"EnableExtensions", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS) {

            if (dwDataType == REG_DWORD) {

                bEnableExtensions = (*(LPDWORD)pData != FALSE);
            }
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"DelayedExpansion", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS) {

            if (dwDataType == REG_DWORD) {

                bDelayedExpansion = (*(LPDWORD)pData != FALSE);
            }
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"DisableUNCCheck", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS) {

            if (dwDataType == REG_DWORD) {

                bDisableUNCCheck = (*(LPDWORD)pData != FALSE);
            }
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"DefaultColor", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS){

            if (dwDataType == REG_DWORD) {

                wDefaultColor = (WORD)*(LPDWORD)pData;
            }
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"CompletionChar", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS){

            if (dwDataType == REG_DWORD) {

                cCompletionCtrl = (WCHAR)(*(LPDWORD)pData);
            }
        }

        cbData = sizeof(dwBuffer);
        if ((dwResult = RegQueryValueExW(hKeyResult, L"PathCompletionChar", NULL, &dwDataType, pData, &cbData)) == ERROR_SUCCESS) {

            if (dwDataType == REG_DWORD) {

                cPathCompletionCtrl = (WCHAR)(*(LPDWORD)pData);
            }

        }

        RegCloseKey(hKeyResult);
    }

    return SUCCESS;
}


BOOL GetCmdPromptPolicy(void) {

    DWORD dwResult = ERROR_SUCCESS;
    HKEY hKey = NULL;
    DWORD dwSize = sizeof(INT);
    DWORD dwDataType = 0;
    BOOL bAccessible = FALSE;

    if ((dwResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\System", 0, KEY_READ | KEY_WOW64_64KEY, &hKey)) == ERROR_SUCCESS) {

        if ((dwResult = RegQueryValueExW(hKey, L"DisableCMD", NULL, &dwDataType, (PBYTE)bAccessible, &dwSize)) != ERROR_SUCCESS) {

            RegCloseKey(hKey);
            return ((bAccessible == 2) ? TRUE : FALSE);
        }
        else {

            RegCloseKey(hKey);

            return TRUE;
        }
    }

    return TRUE;
}
