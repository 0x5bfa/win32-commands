// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#define DIR_SWITCH_SPECIFIES_ATTRIBUTES             0x0001  // /A
#define DIR_SWITCH_USES_BARE_FORMAT                 0x0002  // /B
#define DIR_SWITCH_THOUSAND_SEPARATOR               0x0004  // /C
#define DIR_SWITCH_WIDE_BY_COLUMN                   0x0008  // /D
#define DIR_SWITCH_USES_LOWERCASE                   0x0010  // /L
#define DIR_SWITCH_FILE_LIST_FORMAT                 0x0020  // /N
#define DIR_SWITCH_SPECIFIES_SORTORDER              0x0040  // /O
#define DIR_SWITCH_PAUSES_SCREEN                    0x0080  // /P
#define DIR_SWITCH_DISPLAY_FILE_OWNER               0x0100  // /Q
#define DIR_SWITCH_DISPLAY_ALTERNATE                0x0200  // /R
#define DIR_SWITCH_RECURSES_ALL_SUBS                0x0400  // /S
#define DIR_SWITCH_SPECIFIES_TIMEFIELD              0x0800  // /T
#define DIR_SWITCH_USES_WIDE_LIST_FORMAT            0x1000  // /W
#define DIR_SWITCH_DISPLAY_SHORT_NAME               0x2000  // /X
#define DIR_SWITCH_FOUR_DIGIT_YEARS                 0x4000  // /4

#define DIR_ATTRIBUTE_ADD_DIRECTORIES               0x00001  // +D
#define DIR_ATTRIBUTE_DELETE_DIRECTORIES            0x00002  // -D
#define DIR_ATTRIBUTE_ADD_READONLY                  0x00004  // +R
#define DIR_ATTRIBUTE_DELETE_READONLY               0x00008  // -R
#define DIR_ATTRIBUTE_ADD_HIDDEN                    0x00010  // +H
#define DIR_ATTRIBUTE_DELETE_HIDDEN                 0x00020  // -H
#define DIR_ATTRIBUTE_ADD_ARCHIVE                   0x00040  // +A
#define DIR_ATTRIBUTE_DELETE_ARCHIVE                0x00080  // -A
#define DIR_ATTRIBUTE_ADD_SYSTEM                    0x00100  // +S
#define DIR_ATTRIBUTE_DELETE_SYSTEM                 0x00200  // -S
#define DIR_ATTRIBUTE_ADD_NOT_CONTENT_INDEXED       0x00400  // +I
#define DIR_ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED    0x00800  // -I
#define DIR_ATTRIBUTE_ADD_REPARSE_POINTS            0x01000  // +L
#define DIR_ATTRIBUTE_DELETE_REPARSE_POINTS         0x02000  // -L
#define DIR_ATTRIBUTE_ADD_OFFLINE                   0x04000  // +O
#define DIR_ATTRIBUTE_DELETE_OFFLINE                0x08000  // -O

#define DIR_SORTORDER_BY_ALPHA_NAME                 0x0001  // N
#define DIR_SORTORDER_BY_SMALLEST_SIZE              0x0002  // S
#define DIR_SORTORDER_BY_ALPHA_EXT                  0x0004  // E
#define DIR_SORTORDER_BY_OLDEST_TIME                0x0008  // D
#define DIR_SORTORDER_BY_GROUP_DIR_FIRST            0x0010  // G
#define DIR_SORTORDER_BY_REVERSE_ORDER              0x0020  // -

#define DIR_TIMEFIELD_CREATION                      0x0001  // C
#define DIR_TIMEFIELD_LAST_ACCESS                   0x0002  // A
#define DIR_TIMEFIELD_LAST_WRITTEN                  0x0003  // W


typedef struct _DIR {

    DWORD dwSwitches;

    DWORD dwSpecifiedAttributes;
    DWORD dwSortOrder;
    DWORD dwTimeField;

    DWORD dwTotalNumOfFiles;
    DWORD dwTotalNumOfBitesOfFiles;
    DWORD dwTotalNumOfDirs;

}DIR, * PDIR;


BOOL EnumFilesOrDirectoryies(PDIR pDir, LPWSTR lpDirectoryName);
BOOL DisplayFileTime(PDIR pDir, PWIN32_FIND_DATA pFindData);
BOOL DisplayFileSize(PDIR pDir, PWIN32_FIND_DATA pFindData);
BOOL DisplayFileOwner(PDIR pDir, LPWSTR lpFullDirPath);
BOOL InsertThousandCommaSeparator(PDIR pDir, LPWSTR lpFileSize);
BOOL DisplayHeader(LPWSTR lpFullDirPath);
BOOL DisplayFooter(PDIR pDir, LPWSTR lpFullDirPath);

BOOL ParseDirSwitch(PDIR pDir, int argc, LPWSTR argv[]);
BOOL ParseAttributeSwitch(PDIR pDir, LPWSTR lpAttributesSwitch);
BOOL ParseSortOrderSwitch(PDIR pDir, LPWSTR lpSortOrderSwitch);
BOOL ParseTimeFieldSwitch(PDIR pDir, LPWSTR lpTimeFieldSwitch);
