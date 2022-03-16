// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"


int PauseMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered PauseMain() function\n");

    if (argc != 1) {

        if (CHECKRETURN(StrCmpW(argv[1], L"/?"))) {

            DisplayTextMessage(MSG_HELP_PAUSE, NO_ARGS);
            return SUCCESS;
        }
    }

    PauseScreen();

    return SUCCESS;
}


BOOL PauseScreen(void) {

    DisplayTextMessage(MSG_STRIKE_ANY_KEY, NO_ARGS);

    getc(stdin);

    return SUCCESS;
}
