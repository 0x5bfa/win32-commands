// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#pragma once
#include <stdio.h>
#include <Windows.h>
#include "CmdMessage.h"
#include <shlwapi.h>
#include <locale.h>
#pragma comment (lib, "Shlwapi.lib")
#pragma warning (disable: 4996)

#define CHECKRETURN(x) ((x) == 0)

#define FAILURE 0
#define SUCCESS 1

#define NO_ARGS  0x0
#define ONE_ARG  0x1
#define TWO_ARGS 0x2

#define SWITCH_EXECUTE_CMD_AND_EXIT      0x0001
#define SWITCH_EXECUTE_CMD_AND_CONTINUE  0x0002
#define SWITCH_CHANGE_STRING_TREATMENT   0x0004
#define SWITCH_ECHO_OFF                  0x0008
#define SWITCH_DISABLE_AUTORUN           0x0010
#define SWITCH_OUTPUT_AS_ANSI            0x0020
#define SWITCH_OUTPUT_AS_UNICODE         0x0040
#define SWITCH_SET_BACK_FORE_COLOR       0x0080
#define SWITCH_ENABLE_EXTENSION          0x0100
#define SWITCH_DISABLE_EXTENSION         0x0200
#define SWITCH_ENABLE_COMPLETION         0x0400
#define SWITCH_DISABLE_COMPLETION        0x0800
#define SWITCH_ENABLE_DELAYED_EXPANSION  0x1000
#define SWITCH_DISABLE_DELAYED_EXPANSION 0x2000

#define CMD_ASSOC        0x001
#define CMD_BREAK        0x002
#define CMD_CALL         0x003
#define CMD_CD           0x004
#define CMD_CHCP         0x005
#define CMD_CHDIR        0x006
#define CMD_CLS          0x007
#define CMD_COLOR        0x008
#define CMD_DATE         0x009
#define CMD_DEL          0x010
#define CMD_DIR          0x011
#define CMD_ECHO         0x012
#define CMD_ENDLOCAL     0x013
#define CMD_ERASE        0x014
#define CMD_EXIT         0x015
#define CMD_FOR          0x016
#define CMD_FTYPE        0x017
#define CMD_GOTO         0x018
#define CMD_IF           0x019
#define CMD_MD           0x020
#define CMD_MKDIR        0x021
#define CMD_MOVE         0x022
#define CMD_PAUSE        0x023
#define CMD_POPD         0x024
#define CMD_PROMPT       0x025
#define CMD_PUSHD        0x026
#define CMD_RD           0x027
#define CMD_REM          0x028
#define CMD_REN          0x029
#define CMD_RENAME       0x030
#define CMD_RMDIR        0x031
#define CMD_SET          0x032
#define CMD_SETLOCAL     0x033
#define CMD_SC           0x034
#define CMD_SHIFT        0x035
#define CMD_TITLE        0x036
#define CMD_TREE         0x037
#define CMD_TYPE         0x038
#define CMD_VER          0x039
#define CMD_VERIFY       0x040
#define CMD_VOL          0x041


typedef struct _CMD {

    DWORD dwSwitch;

}CMD, *PCMD;


extern BOOL bCommandEchoing;
extern WCHAR szDisplayPrompt[256];


// Functions

BOOL InitializeCmdPrompt(PCMD pCmd);
BOOL DbgPrint(LPWSTR lpMessage, ...);
BOOL GetCmdPromptPolicy(void);
BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...);
BOOL GetWindowsVersion(void);
VOID CmdExit(DWORD dwExitCode);
BOOL SetColor(WORD wColorAttribute);
BOOL DisplayVolInfo(LPWSTR lpDrivePath);
BOOL ClearScreen(void);
LPWSTR GetTextMessage(DWORD dwErrCode, DWORD nArgs, ...);
BOOL CmdSetConsoleTitle(LPWSTR lpConsoleTitle);
BOOL PauseScreen(void);

// Internal main function
int AssocMain(int argc, LPWSTR argv[]);
int ChDirMain(int argc, LPWSTR argv[]);
int VerMain(int argc, LPWSTR argv[]);
int VolMain(int argc, LPWSTR argv[]);
int ClsMain(int argc, LPWSTR argv[]);
int ColorMain(int argc, LPWSTR argv[]);
int ExitMain(int argc, LPWSTR argv[]);
int DirMain(int argc, LPWSTR argv[]);
int ChCpMain(int argc, LPWSTR argv[]);
int DateMain(int argc, LPWSTR argv[]);
int TitleMain(int argc, LPWSTR argv[]);
int MkDirMain(int argc, LPWSTR argv[]);
int PauseMain(int argc, LPWSTR argv[]);
int EchoMain(int argc, LPWSTR argv[]);
int PromptMain(int argc, LPWSTR argv[]);
int FTypeMain(int argc, LPWSTR argv[]);
