# Microsoft Developer Studio Project File - Name="VCF_js_dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=js_dll - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_js_dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_js_dll.mak" CFG="js_dll - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "js_dll - Win32 vc90 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc90 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc90 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc90 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc80 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc80 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc71 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc71 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc70 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc70 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc6 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 vc6 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "js_dll - Win32 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "js_dll - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc90.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc80.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc71.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc70.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_vc6.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js.lib"

!ELSEIF  "$(CFG)" == "js_dll - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\js_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_d.lib" /debug
# ADD LINK32 ..\..\..\lib\fdlibm_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js_d.lib" /debug

!ELSEIF  "$(CFG)" == "js_dll - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\js_dll"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\js_dll"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\js.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "XP_WIN" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "EXPORT_JS_API" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "XP_WIN" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ..\..\..\lib\fdlibm_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js.lib"
# ADD LINK32 ..\..\..\lib\fdlibm_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\js.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\js.lib"

!ENDIF

# Begin Target

# Name "js_dll - Win32 vc90 DLL Debug"
# Name "js_dll - Win32 vc90 DLL Release"
# Name "js_dll - Win32 vc90 LIB Debug"
# Name "js_dll - Win32 vc90 LIB Release"
# Name "js_dll - Win32 vc80 DLL Debug"
# Name "js_dll - Win32 vc80 DLL Release"
# Name "js_dll - Win32 vc80 LIB Debug"
# Name "js_dll - Win32 vc80 LIB Release"
# Name "js_dll - Win32 vc71 DLL Debug"
# Name "js_dll - Win32 vc71 DLL Release"
# Name "js_dll - Win32 vc71 LIB Debug"
# Name "js_dll - Win32 vc71 LIB Release"
# Name "js_dll - Win32 vc70 DLL Debug"
# Name "js_dll - Win32 vc70 DLL Release"
# Name "js_dll - Win32 vc70 LIB Debug"
# Name "js_dll - Win32 vc70 LIB Release"
# Name "js_dll - Win32 vc6 DLL Debug"
# Name "js_dll - Win32 vc6 DLL Release"
# Name "js_dll - Win32 vc6 LIB Debug"
# Name "js_dll - Win32 vc6 LIB Release"
# Name "js_dll - Win32 DLL Debug"
# Name "js_dll - Win32 DLL Release"
# Name "js_dll - Win32 LIB Debug"
# Name "js_dll - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\js.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarena.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarray.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsatom.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbool.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscntxt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdbgapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdhash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdtoa.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsemit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsexn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfun.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsgc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jshash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsinterp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsiter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslog2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslong.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsmath.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsnum.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsobj.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsparse.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprf.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsregexp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscope.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscript.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsutil.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxdrapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxml.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\prmjtime.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarena.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsarray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsatom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsautokw.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsbool.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsclist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscntxt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscompat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jscpucfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdbgapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdhash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsdtoa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsemit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsexn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsfun.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsgc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jshash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsiter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslibmath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jslong.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsmath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsnum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsobj.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsopcode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsosdep.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsotypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsparse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsprvtd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jspubtd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsregexp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscan.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscope.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsscript.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstddef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsstr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jstypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsutil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxdrapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\jsxml.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\prmjtime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\JavaScriptKit\js-impl\resource.h
# End Source File
# End Group
# End Target
# End Project

