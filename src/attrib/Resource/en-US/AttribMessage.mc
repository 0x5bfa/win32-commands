;// Copyright (c) 2021 WindowsCommands
;// Licensed under the MIT License.

MessageIdTypedef = DWORD

SeverityNames = (
    Success =       0x0: STATUS_SEVERITY_SUCCESS
    Informational = 0x1: STATUS_SEVERITY_INFORMATIONAL
    Warning =       0x2: STATUS_SEVERITY_WARNING
    Error =         0x3: STATUS_SEVERITY_ERROR
)

FacilityNames = (
    System =  0x0: FACILITY_SYSTEM
    Runtime = 0x2: FACILITY_RUNTIME
    Stubs =   0x3: FACILITY_STUBS
    Io =      0x4: FACILITY_IO_ERROR_CODE
)

LanguageNames = (English = 0x409:  MSG00409)
LanguageNames = (Japanese = 0x411: MSG00411)


;//
;// Define the severity codes
;//