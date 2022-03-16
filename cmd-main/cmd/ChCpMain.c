// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"

BOOL GetCodePage(void);
BOOL SetCodePage(DWORD dwCodePage);


int ChCpMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered ChCpMain() function\n");

    if (argc == 1) {

        return GetCodePage();
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                wprintf(L"Displays or sets the active code page number.\r\n\r\nCHCP [nnn]\r\n\r\n  nnn   Specifies a code page number.\r\n\r\nType CHCP without a parameter to display the active code page number.\r\n");
                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            return SetCodePage(StrToIntW(argv[1]));
        }

    }

    return SUCCESS;
}


BOOL GetCodePage(void) {

    DWORD dwCodePage = GetConsoleOutputCP();

    wprintf(L"Active code page: %d\n", dwCodePage);

    return SUCCESS;
}


BOOL SetCodePage(DWORD dwCodePage) {

    // Set code page
    SetConsoleOutputCP(dwCodePage);

    // Clear screen
    ClearScreen();

    // Get and display code page
    GetCodePage();

    return SUCCESS;
}
