// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#pragma once

#include <stdio.h>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi.lib")



// Status defines

#define SUCCESS    0x0001
#define FAILURE    0x0000

#define CHECKRETURN(x) ((x) == 0)

#define SWITCH_RECURSE_ALL_DIRECTORY  0x0001 // /s
#define SWITCH_PROCESS_FOLDER_AS_WELL 0x0002 // /d
#define SWITCH_SYMBOLIC_LINK_TARGET   0x0004 // /l

#define ATTRIBUTE_NO_CHANGES                 0x00000
#define ATTRIBUTE_ADD_READONLY               0x00001
#define ATTRIBUTE_DELETE_READONLY            0x00002
#define ATTRIBUTE_ADD_ARCHIVE                0x00004
#define ATTRIBUTE_DELETE_ARCHIVE             0x00008
#define ATTRIBUTE_ADD_SYSTEM                 0x00010
#define ATTRIBUTE_DELETE_SYSTEM              0x00020
#define ATTRIBUTE_ADD_HIDDEN                 0x00040
#define ATTRIBUTE_DELETE_HIDDEN              0x00080
#define ATTRIBUTE_ADD_OFFLINE                0x00100
#define ATTRIBUTE_DELETE_OFFLINE             0x00200
#define ATTRIBUTE_ADD_NOT_CONTENT_INDEXED    0x00400
#define ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED 0x00800
#define ATTRIBUTE_ADD_NO_SCRUB_DATA          0x01000
#define ATTRIBUTE_DELETE_NO_SCRUB_DATA       0x02000
#define ATTRIBUTE_ADD_PINNED                 0x04000
#define ATTRIBUTE_DELETE_PINNED              0x08000
#define ATTRIBUTE_ADD_UNPINNED               0x10000
#define ATTRIBUTE_DELETE_UNPINNED            0x20000


typedef struct _ATTRIB {

    DWORD dwSwitches;

    DWORD dwChangedAttributes;

}ATTRIB, *PATTRIB;


// AttribMain.c

BOOL ParseSetAttributesParam(PATTRIB pAttrib, LPWSTR lpAttribSwitch);
BOOL FindFile(PATTRIB pAttrib, LPWSTR lpRoot);

// AttribDislapy.c

BOOL DisplayFileAttributes(LPWSTR lpFullPathName);
BOOL DisplayFormattedMessage(DWORD dwMsgId, DWORD nArgs, ...);
