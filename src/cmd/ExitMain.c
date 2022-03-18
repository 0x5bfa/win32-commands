// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"


int ExitMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered ExitMain() function\n");

    if (argc == 1) {

        CmdExit(0);
        return SUCCESS;
    }
    else {

        if (argv[1][0] == L'/') {

            if (argv[1][1] == L'?') {

                DisplayTextMessage(MSG_HELP_EXIT, NO_ARGS);
                return SUCCESS;
            }
            else if (argv[1][1] == L'b' || argv[1][1] == L'B') {

                // Not implement
            }
            else {

                DisplayTextMessage(MSG_BAD_SYNTAX, NO_ARGS);
                return FAILURE;
            }
        }
        else {

            CmdExit(strtol(argv[1], NULL, 10));
            return SUCCESS;
        }
    }

    return SUCCESS;
}


VOID CmdExit(DWORD dwExitCode) {

    exit(dwExitCode);
}