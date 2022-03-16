// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"


int ClsMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered ClsMain() function\n");

    if (argc == 1) {

        return ClearScreen();
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_CLS, NO_ARGS);
                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            return ClearScreen();
        }

    }

    return SUCCESS;
}


BOOL ClearScreen(void) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO ConsoleScreenBuffInfo = { 0 };
    SMALL_RECT ScrollRect = { 0 };
    COORD ScrollTarget = { 0 };
    CHAR_INFO FillInfo = { 0 };

    // Get the number of character cells in the current buffer.
    if (CHECKRETURN(GetConsoleScreenBufferInfo(hConsole, &ConsoleScreenBuffInfo))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    // Scroll the rectangle of the entire buffer.
    ScrollRect.Left = 0;
    ScrollRect.Top = 0;
    ScrollRect.Right = ConsoleScreenBuffInfo.dwSize.X;
    ScrollRect.Bottom = ConsoleScreenBuffInfo.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    ScrollTarget.X = 0;
    ScrollTarget.Y = (SHORT)(0 - ConsoleScreenBuffInfo.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    FillInfo.Char.UnicodeChar = L' ';
    FillInfo.Attributes = ConsoleScreenBuffInfo.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &ScrollRect, NULL, ScrollTarget, &FillInfo);

    // Move the cursor to the top left corner too.
    ConsoleScreenBuffInfo.dwCursorPosition.X = 0;
    ConsoleScreenBuffInfo.dwCursorPosition.Y = 0;

    if (CHECKRETURN(SetConsoleCursorPosition(hConsole, ConsoleScreenBuffInfo.dwCursorPosition))) {

        DisplayTextMessage(GetLastError(), NO_ARGS);
        return FAILURE;
    }

    return SUCCESS;
}
