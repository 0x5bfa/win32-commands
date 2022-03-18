if not exist %3\%1Message.res (
 cd %3
 mc %1Message.mc
 move /y %1Message.h ..\%1Message.h
 cd ..
)
if not exist CommonRes.res (
 rc /fo CommonRes.res /fm %3\%1Message.res /q %1Message.rcconfig %3\%1Message.rc
)
if not exist ..\Debug\%3\%2.exe.mui (
 mkdir ..\Debug\%3
 link /out:"..\Debug\%3\%2.exe.mui" /nodefaultlib /noentry /dynamicbase /nxcompat /dll %3\%1Message.res
)
