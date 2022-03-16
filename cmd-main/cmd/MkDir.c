// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"


int MkDirMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered MkDirMain() function\n");

    if (argc == 1) {

        DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
        return FAILURE;
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_MKDIR, NO_ARGS);
                DisplayTextMessage(MSG_HELP_MKDIR_X, NO_ARGS);
                return SUCCESS;
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

        }

    }

    return SUCCESS;
}


