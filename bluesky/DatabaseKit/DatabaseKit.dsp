# Microsoft Developer Studio Project File - Name="DatabaseKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=DatabaseKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DatabaseKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DatabaseKit.mak" CFG="DatabaseKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DatabaseKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "DatabaseKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DatabaseKit - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/win32" /I "./" /I "./DBProviders/sqlite" /I "./DBProviders/ms-ado" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "DATABASEKIT_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "NO_TCL" /D "OS_WIN" /D "SQLITE_ENABLE_COLUMN_METADATA" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../vcf/lib/DatabaseKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "DatabaseKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DatabaseKit___Win32_Debug"
# PROP BASE Intermediate_Dir "DatabaseKit___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DatabaseKit___Win32_Debug"
# PROP Intermediate_Dir "DatabaseKit___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/win32" /I "./" /I "./DBProviders/sqlite" /I "./DBProviders/ms-ado" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "DATABASEKIT_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "NO_TCL" /D "OS_WIN" /D "SQLITE_ENABLE_COLUMN_METADATA" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../vcf/lib/DatabaseKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "DatabaseKit - Win32 Release"
# Name "DatabaseKit - Win32 Debug"
# Begin Group "DB Providers"

# PROP Default_Filter ""
# Begin Group "SQLite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DBProviders\sqlite\alter.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\analyze.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\attach.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\auth.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\btree.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\build.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\callback.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\complete.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\date.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\delete.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\expr.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\func.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\hash.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\insert.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\legacy.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\loadext.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\main.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\opcodes.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\os.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\os_win.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\pager.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\parse.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\pragma.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\prepare.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\printf.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\random.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\select.c
# End Source File
# Begin Source File

SOURCE=.\SQLiteDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLiteDatabase.h
# End Source File
# Begin Source File

SOURCE=.\SQLiteDataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLiteDataSet.h
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\table.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\tclsqlite.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\tokenize.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\trigger.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\update.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\utf.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\util.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vacuum.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vdbe.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vdbeapi.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vdbeaux.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vdbefifo.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vdbemem.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\vtab.c
# End Source File
# Begin Source File

SOURCE=.\DBProviders\sqlite\where.c
# End Source File
# End Group
# Begin Group "MS-ADO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ADODataSet.cpp
# End Source File
# Begin Source File

SOURCE=".\DBProviders\ms-ado\ADODB.h"
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Database.h
# End Source File
# Begin Source File

SOURCE=.\DatabaseError.h
# End Source File
# Begin Source File

SOURCE=.\DatabaseKit.h
# End Source File
# Begin Source File

SOURCE=.\DatabaseToolkit.h
# End Source File
# Begin Source File

SOURCE=.\DataField.h
# End Source File
# Begin Source File

SOURCE=.\DataLink.h
# End Source File
# Begin Source File

SOURCE=.\DataSet.h
# End Source File
# Begin Source File

SOURCE=.\DataSource.h
# End Source File
# Begin Source File

SOURCE=.\FieldDefinitions.h
# End Source File
# Begin Source File

SOURCE=.\StringList.h
# End Source File
# Begin Source File

SOURCE=.\Transaction.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Database.cpp
# End Source File
# Begin Source File

SOURCE=.\DatabaseKit.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=.\DatabaseToolkit.cpp
# End Source File
# Begin Source File

SOURCE=.\DataField.cpp
# End Source File
# Begin Source File

SOURCE=.\DataLink.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldDefinitions.cpp
# End Source File
# Begin Source File

SOURCE=.\StringList.cpp
# End Source File
# Begin Source File

SOURCE=.\Transaction.cpp
# End Source File
# End Group
# End Target
# End Project
