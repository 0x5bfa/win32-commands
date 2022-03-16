// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#pragma once
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include "TreeMessage.h"
#include <shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")
#pragma warning (disable: 4996)

#define FAILURE 0
#define SUCCESS 1

#define CHECKRETURN(x) ((x) == FAILURE)

#define NO_ARGS  0x0
#define ONE_ARG  0x1
#define TWO_ARGS 0x2

#define TREE_SWITCH_DISPLAY_FILES    0x0001
#define TREE_SWITCH_USES_ASCII       0x0002

// Functions
BOOL DisplayTextMessage(DWORD dwErrCode, DWORD nArgs, ...);
