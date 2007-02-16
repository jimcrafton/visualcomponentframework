# Microsoft Developer Studio Project File - Name="DatabaseKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DatabaseKitDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DatabaseKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DatabaseKitDLL.mak" CFG="DatabaseKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DatabaseKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DatabaseKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DatabaseKitDLL - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DATABASEKITDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DATABASEKITDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "DatabaseKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../vcf/bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DATABASEKITDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/win32" /I "./" /I "./DBProviders/sqlite" /I "./DBProviders/ms-ado" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DATABASEKIT_EXPORTS" /D "DATABASEKIT_DLL" /D "USE_FOUNDATIONKIT_DLL" /D "NO_TCL" /D "OS_WIN" /D "SQLITE_ENABLE_COLUMN_METADATA" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../vcf/bin/DatabaseKit_vc6_d.dll" /implib:"../../vcf/lib/DatabaseKit_vc6_d.lib" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DatabaseKitDLL - Win32 Release"
# Name "DatabaseKitDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\SQLiteDataSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StringList.cpp
# End Source File
# Begin Source File

SOURCE=.\Transaction.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=.\SQLiteDataSet.h
# End Source File
# Begin Source File

SOURCE=.\StringList.h
# End Source File
# Begin Source File

SOURCE=.\Transaction.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "DB Providers"

# PROP Default_Filter ""
# Begin Group "SQLite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\DBProviders\sqlite\alter.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\analyze.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\attach.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\auth.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\btree.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\build.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\callback.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\complete.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\date.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\delete.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\expr.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\func.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\hash.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\insert.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\legacy.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\main.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\opcodes.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\os.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\os_win.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\pager.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\parse.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\pragma.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\prepare.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\printf.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\random.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\select.c"
# End Source File
# Begin Source File

SOURCE=.\SQLiteDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLiteDatabase.h
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\table.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\tclsqlite.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\tokenize.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\trigger.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\update.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\utf.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\util.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vacuum.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vdbe.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vdbeapi.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vdbeaux.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vdbefifo.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\vdbemem.c"
# End Source File
# Begin Source File

SOURCE=".\DBProviders\sqlite\where.c"
# End Source File
# End Group
# End Group
# End Target
# End Project
