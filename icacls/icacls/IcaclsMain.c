// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Icacls.h"


int wmain(int argc, LPWSTR argv[]) {

    if (argc == 1) {

        DisplayTextMessage(MSG_HELP_ICACLS, NO_ARGS);
        return SUCCESS;
    }
    else {

        LPWSTR lpPathName = NULL;
        ICACLS Icacls = { 0 };

        if (argv[1][0] == L'/') {

            if (CHECKRETURN(StrCmpW(argv[1], L"/?"))) {

                DisplayTextMessage(MSG_HELP_ICACLS, NO_ARGS);
                return SUCCESS;
            }
            else {

                // First parameter is filename or help only
                DisplayTextMessage(MSG_FIRST_PARM_MUST_BE, NO_ARGS);
                DisplayTextMessage(MSG_HELP_ICACLS, NO_ARGS);
                return SUCCESS;
            }
            return SUCCESS;
        }
        else {

            // Filename
            lpPathName = argv[1];
        }

        if (argc > 5 && argv[4] != NULL) {

            ParseSwitches(&Icacls, argc - 4, argv + 4);
        }

        Icacls.lpBuffer = argv[3];

        // Parsing second parameter
        if (argc >= 3 && argv[2][0] == L'/') {

            if (CHECKRETURN(StrCmpIW(argv[2], L"/save"))) {

                if (argc >= 4 && argv[3] != NULL) {

                    Icacls.dwOperation = OPERATION_SAVE;
                    FindFile(&Icacls, lpPathName);
                }
                else {

                    DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[2], L"/restore"))) {

                if (argc >= 4 && argv[3] != NULL) {

                    Icacls.dwOperation = OPERATION_RESTORE;

                    // lpPathName must be directory only.
                    HandleProcessingBranch(&Icacls, lpPathName);
                }
                else {

                    DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[2], L"/setowner"))) {

                if (argc >= 4 && argv[3] != NULL) {

                    Icacls.dwOperation = OPERATION_SETOWNER;
                    FindFile(&Icacls, lpPathName);
                }
                else {

                    DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[2], L"/findsid"))) {

                if (argc >= 4 && argv[3] != NULL) {

                    Icacls.dwOperation = OPERATION_FINDSID;
                    FindFile(&Icacls, lpPathName);
                }
                else {

                    DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                    return FAILURE;
                }
            }
            else if (CHECKRETURN(StrCmpIW(argv[2], L"/verify"))) {

                if (argc >= 4 && argv[3] != NULL) {

                    Icacls.dwOperation = OPERATION_VERIFY;
                    FindFile(&Icacls, lpPathName, NULL);
                }
                else {

                    DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                    return FAILURE;
                }
            }
            else {

                // filename and switches
                ParseSwitches(&Icacls, argc - 2, argv + 2);
                FindFile(&Icacls, lpPathName, NULL);
            }
        }
        else {

            // Display
            FindFile(&Icacls, lpPathName, NULL);
        }
    }

    return SUCCESS;
}


BOOL ParseSwitches(PICACLS pIcacls, int argc, LPWSTR argv[]) {

    pIcacls->dwSwitches = 0;

    for (int i = 0; i < argc; i++) {

        if (argv[i][0] == L'/') {

            switch ((int)CharUpperW(argv[i][1])) {

            case L'T':

                pIcacls->dwSwitches |= SWITCH_RECURSE_ALL_MATCHING_FILE;
                break;

            case L'C':

                pIcacls->dwSwitches |= SWITCH_CONTINUE_FILE_PROCESSING;
                break;

            case L'L':

                pIcacls->dwSwitches |= SWITCH_PROCESSING_SYMBOLIC_ITSELF;
                break;

            case L'Q':

                pIcacls->dwSwitches |= SWITCH_REPRESS_SUCCESS_MESSAGE;
                break;

            default:

                DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
                return FAILURE;
            }
        }
        else {

            DisplayTextMessage(MSG_BAD_PARM, ONE_ARG, argv[2]);
            return FAILURE;
        }
    }

    return SUCCESS;
}
