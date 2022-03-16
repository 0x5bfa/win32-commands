// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#pragma once
#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include "RegMessage.h"
#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")

#define CHECKRETURN(x) ((x) == 0)

#define SUCCESS    0x0001
#define FAILURE    0x0000

#define MSG_DISPLAYED_MESSAGE               ((DWORD)0x00000001L)

#define NO_ARGS  0
#define ONE_ARG  1
#define TWO_ARGS 2


typedef struct _REG {

    // Detail
    HKEY nHKey;
    DWORD dwSwitches;
    DWORD dwOperation;

    // Specify
    LPWSTR lpMachineName;
    WCHAR lpRootKeyName[16];
    LPWSTR lpKeyName;
    LPWSTR lpFullKey;
    LPWSTR lpSubKey;
    LPWSTR lpValueName;
    LPWSTR lpSeparator;
    LPWSTR lpFindPattern;
    DWORD dwSpecifyDataType;
    LPWSTR lpSpecifyData;

    // for save and restore command
    LPWSTR lpFileName;

}REG, *PREG;


// Operations

#define OPERATION_QUERY          2
#define OPERATION_ADD            3
#define OPERATION_DELETE         4
#define OPERATION_COPY           5
#define OPERATION_SAVE           6
#define OPERATION_LOAD           7
#define OPERATION_UNLOAD         8
#define OPERATION_RESTORE        9
#define OPERATION_COMPARE        10
#define OPERATION_EXPORT         11
#define OPERATION_IMPORT         12
#define OPERATION_FLAGS          13

// Switches

#define SWITCH_SPECIFY_VALUE           0x0001
#define SWITCH_SPECIFY_EMPTY           0x0002
#define SWITCH_RECURSE                 0x0004
#define SWITCH_SPECIFY_SEPATATOR       0x0008
#define SWITCH_NO_CONFIRM              0x0010
#define SWITCH_SPECIFY_FIND_PATTERN    0x0020
#define SWITCH_FIND_KEY_ONLY           0x0040
#define SWITCH_FIND_DATA_ONLY          0x0080
#define SWITCH_CASE_SENSITIVE          0x0100
#define SWITCH_EXACT_MATCHES_ONLY      0x0200
#define SWITCH_SPECIFY_DATA_TYPE       0x0400
#define SWITCH_SPECIFY_NUMERIC_EQUAL   0x0800
#define SWITCH_SPECIFY_USE_32ARCH_REG  0x1000
#define SWITCH_SPECIFY_MACHINE         0x2000
#define SWITCH_SPECIFY_DATA            0x4000
#define SWITCH_DELETE_ALL_VALUES        0x8000


// RegMessage.c

BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...);
DWORD GetMsgCode(VOID);
VOID SetMsgCode(DWORD dwErrorCode);

// RegParse.c

BOOL ParseRegistryKeyName(PREG pReg, LPWSTR lpKeyName);
BOOL GetRootKey(PREG pReg, LPWSTR lpHKey);
BOOL GetRootKeyString(PREG pReg);
DWORD GetRegDataType(LPWSTR lpRegDataType);
BOOL GetDataTypeString(OUT LPWSTR lpDataType, IN DWORD dwDataType);

// RegMain.c

HKEY OpenRegKey(PREG pReg, LPWSTR lpSubRoot, REGSAM samDesired);
BOOL EnableTokenPrivileges(LPWSTR lpMachineName, LPWSTR lpPrivilegeName, DWORD nAttribute);

// RegExport.c

BOOL ExportRegFile(PREG pReg, HANDLE hFile, HKEY hKey, LPWSTR lpKeyName);

// Sub commands' main function

BOOL RegQueryMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegAddMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegSaveMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegRestoreMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegExportMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegLoadMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegUnLoadMain(PREG pReg, int argc, LPWSTR argv[]);
BOOL RegDeleteMain(PREG pReg, int argc, LPWSTR argv[]);
