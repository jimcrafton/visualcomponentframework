# Microsoft Developer Studio Project File - Name="VCF_RegExKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RegExKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RegExKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RegExKit.mak" CFG="RegExKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RegExKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RegExKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RegExKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RegExKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_d\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_d\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib ..\..\lib\oniguruma_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc80_d.lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib ..\..\lib\oniguruma_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib ..\..\lib\oniguruma_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc80.lib"
# ADD LINK32 FoundationKit_vc80.lib ..\..\lib\oniguruma_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc80.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_sd\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_sd\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc80_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc80_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_s\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_s\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc80_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc80_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_d\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_d\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib ..\..\lib\oniguruma_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc71_d.lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib ..\..\lib\oniguruma_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib ..\..\lib\oniguruma_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc71.lib"
# ADD LINK32 FoundationKit_vc71.lib ..\..\lib\oniguruma_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc71.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_sd\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_sd\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc71_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc71_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_s\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_s\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc71_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc71_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_d\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_d\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib ..\..\lib\oniguruma_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc70_d.lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib ..\..\lib\oniguruma_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib ..\..\lib\oniguruma_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc70.lib"
# ADD LINK32 FoundationKit_vc70.lib ..\..\lib\oniguruma_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc70.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_sd\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_sd\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc70_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc70_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_s\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_s\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc70_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc70_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_d\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_d\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib ..\..\lib\oniguruma_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc6_d.lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib ..\..\lib\oniguruma_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib ..\..\lib\oniguruma_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc6.lib"
# ADD LINK32 FoundationKit_vc6.lib ..\..\lib\oniguruma_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_vc6.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_sd\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_sd\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_s\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_s\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_d\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_d\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RegExKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib ..\..\lib\oniguruma_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_d.lib" /debug
# ADD LINK32 FoundationKit_d.lib ..\..\lib\oniguruma_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "RegExKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RegExKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REGEXKIT_DLL" /D "REGEXKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d ONIG_EXTERN=extern /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\src" /d "REGEXKIT_DLL" /d REGEXKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib ..\..\lib\oniguruma_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit.lib"
# ADD LINK32 FoundationKit.lib ..\..\lib\oniguruma_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RegExKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RegExKit.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_sd\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_sd\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RegExKit_sd.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_sd.lib"

!ELSEIF  "$(CFG)" == "RegExKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_s\RegExKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_s\RegExKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RegExKit_s.pdb /D "WIN32" /D "_LIB" /D ONIG_EXTERN=extern /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RegExKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RegExKit_s.lib"

!ENDIF

# Begin Target

# Name "RegExKit - Win32 vc80 DLL Debug"
# Name "RegExKit - Win32 vc80 DLL Release"
# Name "RegExKit - Win32 vc80 LIB Debug"
# Name "RegExKit - Win32 vc80 LIB Release"
# Name "RegExKit - Win32 vc71 DLL Debug"
# Name "RegExKit - Win32 vc71 DLL Release"
# Name "RegExKit - Win32 vc71 LIB Debug"
# Name "RegExKit - Win32 vc71 LIB Release"
# Name "RegExKit - Win32 vc70 DLL Debug"
# Name "RegExKit - Win32 vc70 DLL Release"
# Name "RegExKit - Win32 vc70 LIB Debug"
# Name "RegExKit - Win32 vc70 LIB Release"
# Name "RegExKit - Win32 vc6 DLL Debug"
# Name "RegExKit - Win32 vc6 DLL Release"
# Name "RegExKit - Win32 vc6 LIB Debug"
# Name "RegExKit - Win32 vc6 LIB Release"
# Name "RegExKit - Win32 DLL Debug"
# Name "RegExKit - Win32 DLL Release"
# Name "RegExKit - Win32 LIB Debug"
# Name "RegExKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\RegExKit\RegExKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\RegExKit\RegExKit.h
# End Source File
# End Group
# End Target
# End Project

