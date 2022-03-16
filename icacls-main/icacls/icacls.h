// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#pragma once
#include <stdio.h>
#include <Windows.h>
#include <sddl.h>
#include <locale.h>
#include <AccCtrl.h>
#include <Shlwapi.h>
#include <aclapi.h>
#include "IcaclsMessage.h"
#pragma comment (lib, "Shlwapi.lib")

// Return error defines
#define FAILURE 0
#define SUCCESS 1

#define CHECKRETURN(x) ((x) == FAILURE)

#define NO_ARGS  0
#define ONE_ARG  1
#define TWO_ARGS 2

#define CHECK_LEAVE(a) {     \
    if (a != 0) { __leave; } \
}

#define SWITCH_RECURSE_ALL_MATCHING_FILE    0x0001 // /T
#define SWITCH_CONTINUE_FILE_PROCESSING     0x0002 // /C
#define SWITCH_PROCESSING_SYMBOLIC_ITSELF   0x0004 // /L
#define SWITCH_REPRESS_SUCCESS_MESSAGE      0x0008 // /Q

#define OPERATION_SAVE                      0x0001 // /save
#define OPERATION_RESTORE                   0x0002 // /restore
#define OPERATION_SETOWNER                  0x0004 // /setowner
#define OPERATION_FINDSID                   0x0008 // /findsid
#define OPERATION_VERIFY                    0x0010 // /verify
#define OPERATION_RESET                     0x0020 // /reset
#define OPERATION_GRANT                     0x0040 // /grant
#define OPERATION_DENY                      0x0080 // /deny
#define OPERATION_REMOVE                    0x0100 // /remove
#define OPERATION_SETINTEGRITYLEVEL         0x0200 // /setintegritylevel
#define OPERATION_INHERITANCE               0x0400 // /inheritance


typedef struct _ICACLS {

    DWORD dwSwitches;
    DWORD dwOperation;

    DWORD dwTotalSuccess;
    DWORD dwTotalFailure;

    LPWSTR lpBuffer;

} ICACLS, *PICACLS;


// Functions

// IcalcsMain.c
DWORD ParseSwitches(PICACLS pIcacls, int argc, LPWSTR argv[]);

// FindFile.c
BOOL HandleProcessingBranch(PICACLS pIcacls, LPWSTR lpFileName);
BOOL FindFile(PICACLS pIcacls, LPWSTR lpRoot);

// DisplaySecInfo.c
BOOL DislpaySecInfo(LPCWSTR lpFileName);

// SaveSecDesc.c
BOOL BackupSecDesc(LPCWSTR lpFileName, LPCWSTR lpWriteFile);
BOOL InitializeBuckupFile(LPCWSTR lpFileName);

// RestoreSecDesc.c
BOOL RestoreSecDesc(LPCWSTR lpRootDir, LPCWSTR lpRestoreFile);

// FindAccount.c
BOOL GetAccountSid(LPCWSTR lpUserName, PSID* ppSid, LPWSTR* lplpDomainName);
BOOL GetAccountName(const PSID pSid, LPWSTR* lplpUserName, LPWSTR* lplpDomainName);

// SetFileOwner.c
BOOL SetFileOwner(LPCWSTR lpFileName, LPCWSTR lpUserName);

// FindSid.c
BOOL FindSid(LPCWSTR lpFileName, LPCWSTR lpStringSid);

// IcaclsMessage.c
BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...);
BOOL DbgPrint(LPWSTR lpMessage, ...);
