// Copyright (c) 2021 onein528
// Licensed under the MIT License.

#include "Cmd.h"

BOOL bCommandEchoing = FALSE;


int EchoMain(int argc, LPWSTR argv[]) {

    DbgPrint(L"Entered EchoMain() function\n");

    if (argc == 1) {

        (bCommandEchoing == FALSE) ? 
            DisplayTextMessage(MSG_ECHO_OFF, NO_ARGS) : DisplayTextMessage(MSG_ECHO_ON, NO_ARGS);

        return SUCCESS;
    }
    else {

        for (int i = 1; i < argc; i++) {

            if (CHECKRETURN(StrCmpW(argv[i], L"/?"))) {

                DisplayTextMessage(MSG_HELP_ECHO, NO_ARGS);
                return SUCCESS;
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"ON")) && !(i < argc - 1)) {

                bCommandEchoing = TRUE;
            }
            else if (CHECKRETURN(StrCmpIW(argv[i], L"OFF")) && !(i < argc - 1)) {

                bCommandEchoing = FALSE;
            }
            else {

                wprintf(L"%s ", argv[i]);

                if (i == argc - 1) {

                    wprintf(L"\n");
                }
            }
        }
    }

    return SUCCESS;
}
