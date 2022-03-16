// Copyright (c) 2021 WindowsCommands
// Licensed under the MIT License.

#include "Cmd.h"
#include "Dir.h"


BOOL ParseDirSwitch(PDIR pDir, int argc, LPWSTR argv[]) {

    BOOL bToggleMinus = FALSE;

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == L'/') {

            argv[i]++;

            switch ((int)CharUpperW(argv[i][0])) {

            case L'?': {

                DisplayTextMessage(MSG_HELP_DIR, NO_ARGS);
                return SUCCESS;
            }
            case L'A': {

                argv[i]++;

                // Initialize attributes specifying switch
                pDir->dwSpecifiedAttributes = 0;

                if (CHECKRETURN(ParseAttributeSwitch(pDir, argv[i]))) {

                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_SPECIFIES_ATTRIBUTES) : (pDir->dwSwitches &= ~DIR_SWITCH_SPECIFIES_ATTRIBUTES);

                break;
            }
            case L'B': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_USES_BARE_FORMAT) : (pDir->dwSwitches &= ~DIR_SWITCH_USES_BARE_FORMAT);

                break;
            }
            case L'C': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_THOUSAND_SEPARATOR) : (pDir->dwSwitches &= ~DIR_SWITCH_THOUSAND_SEPARATOR);

                break;
            }
            case L'D': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_WIDE_BY_COLUMN) : (pDir->dwSwitches &= ~DIR_SWITCH_WIDE_BY_COLUMN);

                break;
            }
            case L'L': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_USES_LOWERCASE) : (pDir->dwSwitches &= ~DIR_SWITCH_USES_LOWERCASE);

                break;
            }
            case L'N': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_FILE_LIST_FORMAT) : (pDir->dwSwitches &= ~DIR_SWITCH_FILE_LIST_FORMAT);

                break;
            }
            case L'O': {

                argv[i]++;

                // Initialize sort order specifying switch
                pDir->dwSortOrder = 0;

                if (CHECKRETURN(ParseSortOrderSwitch(pDir, argv[i]))) {

                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_SPECIFIES_SORTORDER) : (pDir->dwSwitches &= ~DIR_SWITCH_SPECIFIES_SORTORDER);

                break;
            }
            case L'P': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_PAUSES_SCREEN) : (pDir->dwSwitches &= ~DIR_SWITCH_PAUSES_SCREEN);

                break;
            }
            case L'Q': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_DISPLAY_FILE_OWNER) : (pDir->dwSwitches &= ~DIR_SWITCH_DISPLAY_FILE_OWNER);

                break;
            }
            case L'R': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_DISPLAY_ALTERNATE) : (pDir->dwSwitches &= ~DIR_SWITCH_DISPLAY_ALTERNATE);

                break;
            }
            case L'S': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_RECURSES_ALL_SUBS) : (pDir->dwSwitches &= ~DIR_SWITCH_RECURSES_ALL_SUBS);

                break;
            }
            case L'T': {

                argv[i]++;

                // Initialize time field specifying switch
                pDir->dwTimeField = 0;

                if (CHECKRETURN(ParseTimeFieldSwitch(pDir, argv[i]))) {

                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_SPECIFIES_TIMEFIELD) : (pDir->dwSwitches &= ~DIR_SWITCH_SPECIFIES_TIMEFIELD);

                break;
            }
            case L'W': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_USES_WIDE_LIST_FORMAT) : (pDir->dwSwitches &= ~DIR_SWITCH_USES_WIDE_LIST_FORMAT);

                break;
            }
            case L'X': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_DISPLAY_SHORT_NAME) : (pDir->dwSwitches &= ~DIR_SWITCH_DISPLAY_SHORT_NAME);

                break;
            }
            case L'4': {

                if (argv[i][1] != NULL) {

                    DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                    return FAILURE;
                }

                (bToggleMinus == FALSE) ? (pDir->dwSwitches |= DIR_SWITCH_FOUR_DIGIT_YEARS) : (pDir->dwSwitches &= ~DIR_SWITCH_FOUR_DIGIT_YEARS);

                break;
            }
            case L'-': {

                bToggleMinus = TRUE;
                break;
            }
            default: {

                DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, argv[i]);
                return FAILURE;
            }
            }
        }
    }

    return SUCCESS;
}


BOOL ParseAttributeSwitch(PDIR pDir, LPWSTR lpAttributesSwitch) {

    if (lpAttributesSwitch[0] == L':') lpAttributesSwitch++;

    BOOL bToggleMinus = FALSE;

    while (lpAttributesSwitch[0] != NULL) {

        switch ((int)CharUpperW(lpAttributesSwitch[0])) {

        case L'D': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_DIRECTORIES) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_DIRECTORIES);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_DIRECTORIES) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_DIRECTORIES);

            break;
        }
        case L'R': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_READONLY) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_READONLY);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_READONLY) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_READONLY);

            break;
        }
        case L'H': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_HIDDEN) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_HIDDEN);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_HIDDEN) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_HIDDEN);

            break;
        }
        case L'A': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_ARCHIVE) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_ARCHIVE);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_ARCHIVE) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_ARCHIVE);

            break;
        }
        case L'S': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_SYSTEM) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_SYSTEM);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_SYSTEM) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_SYSTEM);

            break;
        }
        case L'I': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_NOT_CONTENT_INDEXED) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_NOT_CONTENT_INDEXED) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_NOT_CONTENT_INDEXED);

            break;
        }
        case L'L': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_REPARSE_POINTS) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_REPARSE_POINTS);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_REPARSE_POINTS) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_REPARSE_POINTS);

            break;
        }
        case L'O': {

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_ADD_OFFLINE) : (pDir->dwSpecifiedAttributes |= DIR_ATTRIBUTE_DELETE_OFFLINE);

            (bToggleMinus == FALSE) ? (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_DELETE_OFFLINE) : (pDir->dwSpecifiedAttributes &= ~DIR_ATTRIBUTE_ADD_OFFLINE);

            break;
        }
        case L'-': {

            bToggleMinus = TRUE;
            break;
        }
        default: {

            DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpAttributesSwitch);
            return FAILURE;
        }
        }

        lpAttributesSwitch++;
    }

    return SUCCESS;
}


BOOL ParseSortOrderSwitch(PDIR pDir, LPWSTR lpSortOrderSwitch) {

    if (lpSortOrderSwitch[0] == L':') lpSortOrderSwitch++;

    BOOL bToggleMinus = FALSE;

    if (lpSortOrderSwitch[1] != L'-' && lpSortOrderSwitch[1] != NULL) {

        lpSortOrderSwitch++;
        DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpSortOrderSwitch);
        return FAILURE;
    }

    if (lpSortOrderSwitch[1] == L'-' && lpSortOrderSwitch[2] == NULL) bToggleMinus = TRUE;
    else {

        DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpSortOrderSwitch);
        return FAILURE;
    }

    switch ((int)CharUpperW(lpSortOrderSwitch[0])) {

    case L'N': {

        pDir->dwSortOrder = DIR_SORTORDER_BY_ALPHA_NAME;

        if (bToggleMinus == TRUE) {

            pDir->dwSortOrder |= DIR_SORTORDER_BY_REVERSE_ORDER;
        }

        break;
    }
    case L'S': {

        pDir->dwSortOrder = DIR_SORTORDER_BY_SMALLEST_SIZE;

        if (bToggleMinus == TRUE) {

            pDir->dwSortOrder |= DIR_SORTORDER_BY_REVERSE_ORDER;
        }

        break;
    }
    case L'E': {

        pDir->dwSortOrder = DIR_SORTORDER_BY_ALPHA_EXT;

        if (bToggleMinus == TRUE) {

            pDir->dwSortOrder |= DIR_SORTORDER_BY_REVERSE_ORDER;
        }

        break;
    }
    case L'D': {

        pDir->dwSortOrder = DIR_SORTORDER_BY_OLDEST_TIME;

        if (bToggleMinus == TRUE) {

            pDir->dwSortOrder |= DIR_SORTORDER_BY_REVERSE_ORDER;
        }

        break;
    }
    case L'G': {

        pDir->dwSortOrder = DIR_SORTORDER_BY_GROUP_DIR_FIRST;

        if (bToggleMinus == TRUE) {

            pDir->dwSortOrder |= DIR_SORTORDER_BY_REVERSE_ORDER;
        }

        break;
    }
    default: {

        DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpSortOrderSwitch);
        return FAILURE;
    }
    }

    return SUCCESS;
}


BOOL ParseTimeFieldSwitch(PDIR pDir, LPWSTR lpTimeFieldSwitch) {

    if (lpTimeFieldSwitch[0] == L':') lpTimeFieldSwitch++;

    if (lpTimeFieldSwitch[1] != NULL) {

        lpTimeFieldSwitch++;
        DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpTimeFieldSwitch);
        return FAILURE;
    }

    switch ((int)CharUpperW(lpTimeFieldSwitch[0])) {

    case L'C': {

        pDir->dwTimeField = DIR_TIMEFIELD_CREATION;
        break;
    }
    case L'A': {

        pDir->dwTimeField = DIR_TIMEFIELD_LAST_ACCESS;
        break;
    }
    case L'W': {

        pDir->dwTimeField = DIR_TIMEFIELD_LAST_WRITTEN;
        break;
    }
    default: {

        DisplayTextMessage(MSG_PARAMETER_FORMAT_NOT_CORRECT, NO_ARGS, lpTimeFieldSwitch);
        return FAILURE;
    }
    }

    return SUCCESS;
}
