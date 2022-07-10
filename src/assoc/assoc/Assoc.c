// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Assoc.h"

int wmain(int argc, LPWSTR argv[]) {

    if (argc == 1) {
        EnumFileAssocRegValue();
    }
    else {
        argment(argv[1]);
    }

    return 0;
}

int argment(TCHAR* arg) {

    if (arg[0] == '/' && arg[1] == '?' && arg[2] == '\0') {
        DisplayHelp();
    }
    else {
        DigitValue(arg);
    }
    return 0;
}

int DisplayHelp(void) {
    printf("ファイル拡張子の関連付けを表示または変更します。\n\nASSOC [.拡張子[=[ファイル タイプ]]]\n\n");
    printf("  .拡張子          ファイル タイプに関連付ける拡張子を指定します。\n  ファイル タイプ  拡張子に関連付けるファイル タイプを指定します。\n\n");
    printf("パラメーターを指定しないで「ASSOC」と入力すると、現在のファイルの関連付け\nを表示します。ファイル拡張子を指定して ASSOC を実行すると、そのファイル\n");
    printf("拡張子の現在のファイルの関連付けを表示します。ファイル タイプやコマンド\nを指定しないと、そのファイル拡張子の関連付けを削除します。\n");
    return 0;
}

int DigitValue(TCHAR* ext) {

    TCHAR** words = malloc(sizeof(TCHAR*) * 100);
    int tokCount = 0;
    TCHAR* contxt;
    TCHAR equal[] = L"=";
    BOOL attachEqual = FALSE;

    if (wcsstr(ext, equal) != NULL) {
        attachEqual = TRUE;
    }

    words[0] = wcstok(ext, L"=", &contxt);
    for (int i = 1;; i++) {
        words[i] = wcstok(NULL, L"=", &contxt);
        if (words[i] == NULL) {
            break;
        }
        tokCount++;
    }
    wprintf(L"%s", ext);

    if (attachEqual == TRUE && tokCount == 0) {
        DeleteAssoc(ext);
    }
    else if (attachEqual == TRUE && tokCount == 1) {
        SetAssoc(words[0], words[1]);
    }
    else if (attachEqual == FALSE && tokCount == 0) {
        GetAssoc(ext);
    }
    else {
        printf("コマンドの構文が間違っています\n");
    }

    free(words);
    return 0;
}

int EnumFileAssocRegValue(void) {

    HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
    TCHAR szFullKeyPath[1024] = L"SOFTWARE\\Classes\\";
    HKEY hKey = NULL;
    DWORD dwResult = 0;
    DWORD dwIndex = 0;
    TCHAR szExtensionName[1024] = L"";
    DWORD nFullKeyPathSize = wcslen(szFullKeyPath);

    if (!RegOpenKeyExW(hKeyRoot, szFullKeyPath, 0, KEY_READ, &hKey))
        return 0;


    for (dwIndex = 0; dwResult != ERROR_NO_MORE_ITEMS; dwIndex++) {

        DWORD szSubKeyNameSize = 1024;
        if (!RegEnumKeyExW(hKey, dwIndex, szExtensionName, &szSubKeyNameSize, NULL, NULL, NULL, NULL)) {

            if (szExtensionName[0] == '.') {

                GetAssoc(szExtensionName);
            }

            szFullKeyPath[nFullKeyPathSize] = L'\0';
        }
    }

    RegCloseKey(hKey);
    return 0;
}

int GetAssoc(TCHAR* ext) {

    HKEY hKey = NULL;
    DWORD dwResult = 0;
    TCHAR findKey[1024] = L"SOFTWARE\\Classes\\";
    TCHAR entry[1024] = L"";

    wcscat(findKey, ext);

    if (!RegOpenKeyExW(HKEY_LOCAL_MACHINE, findKey, 0, KEY_READ, &hKey)) {
        wprintf(L"レジストリのキーが開けませんでした。");
        return 0;
    }

    DWORD type = 0;
    BYTE data[1024] = { 0 };
    DWORD cbData = sizeof(data);

    if (!RegQueryValueExW(hKey, entry, NULL, &type, data, &cbData)) {

        switch (type) {

        case REG_SZ:
            wprintf(L"%s=%s\n", ext, (TCHAR*)data); break;
        default:
            break;
        }
    }

    RegCloseKey(hKey);
    return 0;
}

int SetAssoc(TCHAR* ext, TCHAR* data) {

    HKEY hKey;
    TCHAR newData[1024];
    wcscpy(newData, data);
    TCHAR subKey[1024] = L"SOFTWARE\\Classes\\";
    wcscat(subKey, ext);

    LONG lRet = RegCreateKeyW(HKEY_LOCAL_MACHINE, subKey, &hKey);
    lRet = RegSetValueExW(hKey, L"", 0, REG_SZ, (const BYTE*)newData, sizeof(newData));

    if (lRet == ERROR_SUCCESS) {
        wprintf(L"%s=%s", ext, data);
    }
    else {
        if (lRet == 5L) {
            printf("アクセスが拒否されました。\n");
        }
    }

    RegCloseKey(hKey);
    return 0;
}

int DeleteAssoc(TCHAR* ext) {

    HKEY hKey;
    LONG lRet;
    setlocale(LC_ALL, setlocale(LC_CTYPE, ""));

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Classes\\"), 0, KEY_READ, &hKey);
    if (lRet != ERROR_SUCCESS) return 0;

    lRet = RegDeleteKeyW(hKey, ext);
    if (lRet != ERROR_SUCCESS) {
        TCHAR szMsg[256];        DWORD dwRet;
        dwRet = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, lRet, 0, szMsg, sizeof(szMsg) / sizeof(szMsg[0]), NULL);
        if (dwRet > 0) {
            _tprintf(TEXT("%s\n"), szMsg);
        }
        else {
        }
    }
    RegCloseKey(hKey);
    return 0;
}