# Microsoft Developer Studio Project File - Name="JavaScriptKit_JavaScriptKit_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=JavaScriptKit_dll - Win32 DLL Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_JavaScriptKit_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_JavaScriptKit_dll.mak" CFG="JavaScriptKit_dll - Win32 DLL Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JavaScriptKit_dll - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 icl7 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 icl7 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 icl6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 icl6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JavaScriptKit_dll - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc80_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc80_d\fdlibm_vc80_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc80_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc80_d\fdlibm_vc80_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc80_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc80\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc80\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc80\fdlibm_vc80_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc80.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc80\fdlibm_vc80_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc80.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc71_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc71_d\fdlibm_vc71_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc71_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc71_d\fdlibm_vc71_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc71_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc71\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc71\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc71\fdlibm_vc71_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc71.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc71\fdlibm_vc71_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc71.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc70_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc70_d\fdlibm_vc70_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc70_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc70_d\fdlibm_vc70_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc70_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc70\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc70\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc70\fdlibm_vc70_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc70.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc70\fdlibm_vc70_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc70.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc6_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc6_d\fdlibm_vc6_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc6_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc6_d\fdlibm_vc6_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc6_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc6\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc6\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc6\fdlibm_vc6_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc6.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_vc6\fdlibm_vc6_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_vc6.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl7_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_icl7_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_icl7_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl7_d\fdlibm_icl7_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl7_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl7_d\fdlibm_icl7_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl7_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl7\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl7\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_icl7.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_icl7.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl7\fdlibm_icl7_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl7.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl7\fdlibm_icl7_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl7.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl6_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_icl6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_icl6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl6_d\fdlibm_icl6_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl6_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl6_d\fdlibm_icl6_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl6_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl6\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl6\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_icl6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit_icl6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl6\fdlibm_icl6_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl6.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_icl6\fdlibm_icl6_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_icl6.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_d\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_d\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\JavaScriptKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_d\fdlibm_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug
# ADD LINK32 FoundationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj_d\fdlibm_sd.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit_d.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib" /debug

!ELSEIF  "$(CFG)" == "JavaScriptKit_dll - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj\JavaScriptKit_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj\JavaScriptKit_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\JavaScriptKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "JAVASCRIPTKIT_DLL" /D "JAVASCRIPTKIT_EXPORTS" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "JAVASCRIPTKIT_DLL" /d "JAVASCRIPTKIT_EXPORTS" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj\fdlibm_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"
# ADD LINK32 FoundationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib msvc6prj\fdlibm_s.lib /nologo /dll /machine:i386 /out:".\JavaScriptKit.dll" /implib:".\JavaScriptKit_dll.lib" /libpath:"$(VCF_ROOT)\lib"

!ENDIF

# Begin Target

# Name "JavaScriptKit_dll - Win32 vc80 DLL Debug"
# Name "JavaScriptKit_dll - Win32 vc80 DLL Release"
# Name "JavaScriptKit_dll - Win32 vc71 DLL Debug"
# Name "JavaScriptKit_dll - Win32 vc71 DLL Release"
# Name "JavaScriptKit_dll - Win32 vc70 DLL Debug"
# Name "JavaScriptKit_dll - Win32 vc70 DLL Release"
# Name "JavaScriptKit_dll - Win32 vc6 DLL Debug"
# Name "JavaScriptKit_dll - Win32 vc6 DLL Release"
# Name "JavaScriptKit_dll - Win32 icl7 DLL Debug"
# Name "JavaScriptKit_dll - Win32 icl7 DLL Release"
# Name "JavaScriptKit_dll - Win32 icl6 DLL Debug"
# Name "JavaScriptKit_dll - Win32 icl6 DLL Release"
# Name "JavaScriptKit_dll - Win32 DLL Debug"
# Name "JavaScriptKit_dll - Win32 DLL Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\JavaScriptKit.cpp
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\js.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsapi.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsarena.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsarray.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsatom.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsbool.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jscntxt.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdate.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdbgapi.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdhash.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdtoa.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsemit.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsexn.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsfile.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsfun.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsgc.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jshash.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsinterp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsiter.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslock.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslog2.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslong.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsmath.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsnum.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsobj.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsopcode.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsparse.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsprf.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsregexp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscan.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscope.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscript.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsstr.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsutil.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsxdrapi.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsxml.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\prmjtime.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\JavaScriptKit.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsapi.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsarena.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsarray.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsatom.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsautokw.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsbit.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsbool.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsclist.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jscntxt.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jscompat.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsconfig.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jscpucfg.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdate.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdbgapi.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdhash.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsdtoa.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsemit.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsexn.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsfile.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsfun.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsgc.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jshash.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsinterp.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsiter.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslibmath.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslock.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jslong.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsmath.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsnum.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsobj.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsopcode.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsosdep.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsotypes.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsparse.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsprf.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsprvtd.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jspubtd.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsregexp.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscan.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscope.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsscript.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsstddef.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsstr.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jstypes.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsutil.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsxdrapi.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\jsxml.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\prmjtime.h
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\resource.h
# End Source File
# End Group
# End Target
# End Project

