@echo off

rem 编译Debug/Release版本
rem msdev server.dsp /MAKE "prj_win32 - Win32 Release" /REBUILD /NORECURSE /OUT .\version\CompileInfo\ospserver_R.txt

echo server.exe build begin

@msdev server.dsp /MAKE "prj_win32 - Win32 Debug" /REBUILD /NORECURSE /OUT .\version\CompileInfo\ospserver_D.txt
@msdev server.dsp /MAKE "prj_win32 - Win32 Release" /REBUILD /NORECURSE /OUT .\version\CompileInfo\ospserver_R.txt

echo server.exe build over

copy /Y .\prj_win32\Debug\server.exe .\version\debug\
copy /Y .\prj_win32\Release\server.exe .\version\release\

copy /Y ..\lib\ospdll.dll .\version\debug\
copy /Y ..\lib\ospdll.dll .\version\release\

rem del  /f /s /q .\Debug
rem del  /f /s /q .\Release
del .\*.aps
del .\*.pdb
del .\*.ncb
del .\*.opt
del .\*.ncb
del .\*.plg
del .\*.positions
del .\*.dsw
del .\*.dep
del .\*.mak

pause

echo on
