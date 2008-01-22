# Microsoft Developer Studio Project File - Name="VCF_XMLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=XMLKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_XMLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_XMLKit.mak" CFG="XMLKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLKit - Win32 vc90 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc90 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XMLKit - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc90_d.lib ..\..\..\lib\libxml_vc90_sd.lib ..\..\..\lib\libxslt_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc90_d.lib" /debug
# ADD LINK32 FoundationKit_vc90_d.lib ..\..\..\lib\libxml_vc90_sd.lib ..\..\..\lib\libxslt_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc90_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc90.lib ..\..\..\lib\libxml_vc90_s.lib ..\..\..\lib\libxslt_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc90.lib"
# ADD LINK32 FoundationKit_vc90.lib ..\..\..\lib\libxml_vc90_s.lib ..\..\..\lib\libxslt_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc90.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc90_s.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib ..\..\..\lib\libxml_vc80_sd.lib ..\..\..\lib\libxslt_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc80_d.lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib ..\..\..\lib\libxml_vc80_sd.lib ..\..\..\lib\libxslt_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib ..\..\..\lib\libxml_vc80_s.lib ..\..\..\lib\libxslt_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc80.lib"
# ADD LINK32 FoundationKit_vc80.lib ..\..\..\lib\libxml_vc80_s.lib ..\..\..\lib\libxslt_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc80.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib ..\..\..\lib\libxml_vc71_sd.lib ..\..\..\lib\libxslt_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc71_d.lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib ..\..\..\lib\libxml_vc71_sd.lib ..\..\..\lib\libxslt_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib ..\..\..\lib\libxml_vc71_s.lib ..\..\..\lib\libxslt_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc71.lib"
# ADD LINK32 FoundationKit_vc71.lib ..\..\..\lib\libxml_vc71_s.lib ..\..\..\lib\libxslt_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc71.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib ..\..\..\lib\libxml_vc70_sd.lib ..\..\..\lib\libxslt_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc70_d.lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib ..\..\..\lib\libxml_vc70_sd.lib ..\..\..\lib\libxslt_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib ..\..\..\lib\libxml_vc70_s.lib ..\..\..\lib\libxslt_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc70.lib"
# ADD LINK32 FoundationKit_vc70.lib ..\..\..\lib\libxml_vc70_s.lib ..\..\..\lib\libxslt_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc70.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib ..\..\..\lib\libxml_vc6_sd.lib ..\..\..\lib\libxslt_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc6_d.lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib ..\..\..\lib\libxml_vc6_sd.lib ..\..\..\lib\libxslt_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib ..\..\..\lib\libxml_vc6_s.lib ..\..\..\lib\libxslt_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc6.lib"
# ADD LINK32 FoundationKit_vc6.lib ..\..\..\lib\libxml_vc6_s.lib ..\..\..\lib\libxslt_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_vc6.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\XMLKit_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib ..\..\..\lib\libxml_sd.lib ..\..\..\lib\libxslt_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_d.lib" /debug
# ADD LINK32 FoundationKit_d.lib ..\..\..\lib\libxml_sd.lib ..\..\..\lib\libxslt_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "XMLKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\XMLKit.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\..\src\thirdparty\common\libxml\include" /i "..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "XMLKIT_DLL" /d XMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib ..\..\..\lib\libxml_s.lib ..\..\..\lib\libxslt_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit.lib"
# ADD LINK32 FoundationKit.lib ..\..\..\lib\libxml_s.lib ..\..\..\lib\libxslt_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\XMLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\XMLKit.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\XMLKit_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_sd.lib"

!ELSEIF  "$(CFG)" == "XMLKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\XMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\XMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\XMLKit_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\XMLKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_s.lib"

!ENDIF

# Begin Target

# Name "XMLKit - Win32 vc90 DLL Debug"
# Name "XMLKit - Win32 vc90 DLL Release"
# Name "XMLKit - Win32 vc90 LIB Debug"
# Name "XMLKit - Win32 vc90 LIB Release"
# Name "XMLKit - Win32 vc80 DLL Debug"
# Name "XMLKit - Win32 vc80 DLL Release"
# Name "XMLKit - Win32 vc80 LIB Debug"
# Name "XMLKit - Win32 vc80 LIB Release"
# Name "XMLKit - Win32 vc71 DLL Debug"
# Name "XMLKit - Win32 vc71 DLL Release"
# Name "XMLKit - Win32 vc71 LIB Debug"
# Name "XMLKit - Win32 vc71 LIB Release"
# Name "XMLKit - Win32 vc70 DLL Debug"
# Name "XMLKit - Win32 vc70 DLL Release"
# Name "XMLKit - Win32 vc70 LIB Debug"
# Name "XMLKit - Win32 vc70 LIB Release"
# Name "XMLKit - Win32 vc6 DLL Debug"
# Name "XMLKit - Win32 vc6 DLL Release"
# Name "XMLKit - Win32 vc6 LIB Debug"
# Name "XMLKit - Win32 vc6 LIB Release"
# Name "XMLKit - Win32 DLL Debug"
# Name "XMLKit - Win32 DLL Release"
# Name "XMLKit - Win32 LIB Debug"
# Name "XMLKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.h
# End Source File
# End Group
# End Target
# End Project

