// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"

WORD wDefaultScreenColor = 0;


int ColorMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered ColorMain() function\n");

    if (argc == 1) {

        return SetColor(wDefaultScreenColor);
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_COLOR, NO_ARGS);
                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            WORD dwSetColor = (WORD)wcstol(argv[1], NULL, 16);
            return SetColor(dwSetColor);
        }
    }

    return SUCCESS;
}


BOOL SetColor(WORD wColorAttribute) {

    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBuffInfo = { 0 };
    HANDLE hStdOut = NULL;
    COORD Coordinate = { 0 };
    DWORD dwWritten = 0;

    // Fail if foreground and background color the same
    if (wColorAttribute != 0 && (wColorAttribute & 0xF) == ((wColorAttribute >> 4) & 0xF)) {

        return SUCCESS;
    }

    // Get the handle
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the console info
    if (GetConsoleScreenBufferInfo(hStdOut, &ConsoleScreenBuffInfo)) {

        if (wDefaultScreenColor == 0) {

            DbgPrint(L" default color is %X\n", ConsoleScreenBuffInfo.wAttributes);
            wDefaultScreenColor = ConsoleScreenBuffInfo.wAttributes;
        }

        Coordinate.Y = 0; Coordinate.X = 0;
        FillConsoleOutputAttribute(hStdOut, wColorAttribute, ConsoleScreenBuffInfo.dwSize.Y * ConsoleScreenBuffInfo.dwSize.X, Coordinate, &dwWritten);

        SetConsoleTextAttribute(hStdOut, wColorAttribute);
        return SUCCESS;
    }
    else return FAILURE;

    return SUCCESS;
}
