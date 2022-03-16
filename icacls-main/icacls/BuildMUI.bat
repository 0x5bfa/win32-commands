if not exist en-US\IcaclsMessage.res (
 cd en-US
 mc IcaclsMessage.mc
 move /y IcaclsMessage.h ..\IcaclsMessage.h
 cd ..
)
if not exist CommonRes.res (
 rc /fo CommonRes.res /fm en-US\IcaclsMessage.res /q IcaclsMessage.rcconfig en-US\IcaclsMessage.rc
)
if not exist ..\Debug\en-US\icacls.exe.mui (
 mkdir ..\Debug\en-US
 link /out:"..\Debug\en-US\icacls.exe.mui" /nodefaultlib /noentry /dynamicbase /nxcompat /dll en-US\IcaclsMessage.res
)
