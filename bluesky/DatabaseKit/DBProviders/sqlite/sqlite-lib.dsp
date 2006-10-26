# Microsoft Developer Studio Project File - Name="sqlite" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sqlite - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sqlite-lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sqlite-lib.mak" CFG="sqlite - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sqlite - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sqlite - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sqlite - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_TCL" /D "OS_WIN" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\sqlite-3.3.6_s.lib"

!ELSEIF  "$(CFG)" == "sqlite - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_TCL" /D "OS_WIN" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\sqlite-3.3.6_sd.lib"

!ENDIF 

# Begin Target

# Name "sqlite - Win32 Release"
# Name "sqlite - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alter.c
# End Source File
# Begin Source File

SOURCE=.\analyze.c
# End Source File
# Begin Source File

SOURCE=.\attach.c
# End Source File
# Begin Source File

SOURCE=.\auth.c
# End Source File
# Begin Source File

SOURCE=.\btree.c
# End Source File
# Begin Source File

SOURCE=.\build.c
# End Source File
# Begin Source File

SOURCE=.\callback.c
# End Source File
# Begin Source File

SOURCE=.\complete.c
# End Source File
# Begin Source File

SOURCE=.\date.c
# End Source File
# Begin Source File

SOURCE=.\delete.c
# End Source File
# Begin Source File

SOURCE=.\expr.c
# End Source File
# Begin Source File

SOURCE=.\func.c
# End Source File
# Begin Source File

SOURCE=.\hash.c
# End Source File
# Begin Source File

SOURCE=.\insert.c
# End Source File
# Begin Source File

SOURCE=.\legacy.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\opcodes.c
# End Source File
# Begin Source File

SOURCE=.\os.c

!IF  "$(CFG)" == "sqlite - Win32 Release"

!ELSEIF  "$(CFG)" == "sqlite - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\os_win.c
# End Source File
# Begin Source File

SOURCE=.\pager.c
# End Source File
# Begin Source File

SOURCE=.\parse.c
# End Source File
# Begin Source File

SOURCE=.\pragma.c
# End Source File
# Begin Source File

SOURCE=.\prepare.c
# End Source File
# Begin Source File

SOURCE=.\printf.c
# End Source File
# Begin Source File

SOURCE=.\random.c
# End Source File
# Begin Source File

SOURCE=.\select.c
# End Source File
# Begin Source File

SOURCE=.\shell.c
# End Source File
# Begin Source File

SOURCE=.\table.c
# End Source File
# Begin Source File

SOURCE=.\tclsqlite.c
# End Source File
# Begin Source File

SOURCE=.\tokenize.c
# End Source File
# Begin Source File

SOURCE=.\trigger.c
# End Source File
# Begin Source File

SOURCE=.\update.c
# End Source File
# Begin Source File

SOURCE=.\utf.c
# End Source File
# Begin Source File

SOURCE=.\util.c
# End Source File
# Begin Source File

SOURCE=.\vacuum.c
# End Source File
# Begin Source File

SOURCE=.\vdbe.c
# End Source File
# Begin Source File

SOURCE=.\vdbeapi.c
# End Source File
# Begin Source File

SOURCE=.\vdbeaux.c
# End Source File
# Begin Source File

SOURCE=.\vdbefifo.c
# End Source File
# Begin Source File

SOURCE=.\vdbemem.c
# End Source File
# Begin Source File

SOURCE=.\where.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\btree.h
# End Source File
# Begin Source File

SOURCE=.\hash.h
# End Source File
# Begin Source File

SOURCE=.\keywordhash.h
# End Source File
# Begin Source File

SOURCE=.\opcodes.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# Begin Source File

SOURCE=.\os_common.h
# End Source File
# Begin Source File

SOURCE=.\os_win.h
# End Source File
# Begin Source File

SOURCE=.\pager.h
# End Source File
# Begin Source File

SOURCE=.\parse.h
# End Source File
# Begin Source File

SOURCE=.\sqlite3.h
# End Source File
# Begin Source File

SOURCE=.\sqliteInt.h
# End Source File
# Begin Source File

SOURCE=.\vdbe.h
# End Source File
# Begin Source File

SOURCE=.\vdbeInt.h
# End Source File
# End Group
# End Target
# End Project
