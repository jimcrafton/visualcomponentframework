# Microsoft Developer Studio Project File - Name="Onig_sample_dll_sql" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=sample_dll_sql - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Onig_sample_dll_sql.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Onig_sample_dll_sql.mak" CFG="sample_dll_sql - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sample_dll_sql - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "sample_dll_sql - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sample_dll_sql - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_d"
# PROP BASE Intermediate_Dir "msvc6prj_d\sample_dll_sql"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_d"
# PROP Intermediate_Dir "msvc6prj_d\sample_dll_sql"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_d\sample_dll_sql.pdb /Od /GR /EHsc /W1 /I "." /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_d\sample_dll_sql.pdb /Od /GR /EHsc /W1 /I "." /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d "_CONSOLE" /i .
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d "_CONSOLE" /i .
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_d\Onig_dll.lib /nologo /machine:i386 /out:"msvc6prj_d\sample_dll_sql.exe" /debug /subsystem:console
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_d\Onig_dll.lib /nologo /machine:i386 /out:"msvc6prj_d\sample_dll_sql.exe" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "sample_dll_sql - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj"
# PROP BASE Intermediate_Dir "msvc6prj\sample_dll_sql"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj"
# PROP Intermediate_Dir "msvc6prj\sample_dll_sql"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj\sample_dll_sql.pdb /O2 /GR /EHsc /W1 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj\sample_dll_sql.pdb /O2 /GR /EHsc /W1 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d "_CONSOLE" /i .
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /d "_CONSOLE" /i .
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj\Onig_dll.lib /nologo /machine:i386 /out:"msvc6prj\sample_dll_sql.exe" /subsystem:console
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj\Onig_dll.lib /nologo /machine:i386 /out:"msvc6prj\sample_dll_sql.exe" /subsystem:console

!ENDIF

# Begin Target

# Name "sample_dll_sql - Win32 Debug"
# Name "sample_dll_sql - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sample\sql.c
# End Source File
# End Group
# End Target
# End Project

