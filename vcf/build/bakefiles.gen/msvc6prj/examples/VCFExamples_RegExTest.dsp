# Microsoft Developer Studio Project File - Name="VCFExamples_RegExTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=RegExTest - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_RegExTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_RegExTest.mak" CFG="RegExTest - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegExTest - Win32 vc6 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 vc6 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 vc6 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 vc6 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "RegExTest - Win32 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RegExTest - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_sd.lib FoundationKit_vc6_d.lib RegExKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_sd.lib FoundationKit_vc6_d.lib RegExKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_s.lib FoundationKit_vc6.lib RegExKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_s.lib FoundationKit_vc6.lib RegExKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_sd.lib FoundationKit_vc6_sd.lib RegExKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_sd.lib FoundationKit_vc6_sd.lib RegExKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_s.lib FoundationKit_vc6_s.lib RegExKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_vc6_s.lib FoundationKit_vc6_s.lib RegExKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_sd.lib FoundationKit_d.lib RegExKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_sd.lib FoundationKit_d.lib RegExKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /D "FOUNDATIONKIT_DLL" /D "REGEXKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern /d "FOUNDATIONKIT_DLL" /d REGEXKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_s.lib FoundationKit.lib RegExKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_s.lib FoundationKit.lib RegExKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_sd.lib FoundationKit_sd.lib RegExKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_sd.lib FoundationKit_sd.lib RegExKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ELSEIF  "$(CFG)" == "RegExTest - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\RegExTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\RegExTest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\RegExTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\RegExTest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\RegExTest\RegExTest.pdb /I "..\..\..\..\src\thirdparty\common\oniguruma" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D ONIG_EXTERN=extern /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\thirdparty\common\oniguruma" /d ONIG_EXTERN=extern
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_s.lib FoundationKit_s.lib RegExKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib oniguruma_s.lib FoundationKit_s.lib RegExKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\RegExTest\RegExTest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\RegExTest\RegExTest.pdb"

!ENDIF

# Begin Target

# Name "RegExTest - Win32 vc6 DLL Debug"
# Name "RegExTest - Win32 vc6 DLL Release"
# Name "RegExTest - Win32 vc6 LIB Debug"
# Name "RegExTest - Win32 vc6 LIB Release"
# Name "RegExTest - Win32 DLL Debug"
# Name "RegExTest - Win32 DLL Release"
# Name "RegExTest - Win32 LIB Debug"
# Name "RegExTest - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\RegExTest\RegExTest.cpp
# End Source File
# End Group
# End Target
# End Project

