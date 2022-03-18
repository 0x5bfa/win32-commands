if not exist en-US\CmdMessage.res (
 cd en-US
 mc CmdMessage.mc
 move /y CmdMessage.h ..\CmdMessage.h
 cd ..
)
if not exist CommonRes.res (
 rc /fo CommonRes.res /fm en-US\CmdMessage.res /q CmdMessage.rcconfig en-US\CmdMessage.rc
)
if not exist ..\Debug\en-US\cmd.exe.mui (
 mkdir ..\Debug\en-US
 link /out:"..\Debug\en-US\cmd.exe.mui" /nodefaultlib /noentry /dynamicbase /nxcompat /dll en-US\CmdMessage.res
)