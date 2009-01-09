# Microsoft Developer Studio Project File - Name="VCF_RemoteObjectKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RemoteObjectKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RemoteObjectKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RemoteObjectKit.mak" CFG="RemoteObjectKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RemoteObjectKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\RemoteObjectKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\RemoteObjectKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib FoundationKit_vc6_d.lib NetworkKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb"
# ADD LINK32 FoundationKit_vc6_d.lib FoundationKit_vc6_d.lib NetworkKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\RemoteObjectKit_vc6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\RemoteObjectKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\RemoteObjectKit_vc6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\RemoteObjectKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib FoundationKit_vc6.lib NetworkKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_vc6.pdb"
# ADD LINK32 FoundationKit_vc6.lib FoundationKit_vc6.lib NetworkKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_vc6.pdb"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\RemoteObjectKit_vc6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\RemoteObjectKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\RemoteObjectKit_vc6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\RemoteObjectKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\RemoteObjectKit_vc6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\RemoteObjectKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\RemoteObjectKit_vc6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\RemoteObjectKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\RemoteObjectKit_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_d\RemoteObjectKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\RemoteObjectKit_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_d\RemoteObjectKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib FoundationKit_d.lib NetworkKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_d.pdb"
# ADD LINK32 FoundationKit_d.lib FoundationKit_d.lib NetworkKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\RemoteObjectKit_d.pdb"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\RemoteObjectKit.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj\RemoteObjectKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\RemoteObjectKit.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj\RemoteObjectKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib FoundationKit.lib NetworkKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit.lib" /pdb:"..\..\..\lib\..\bin\RemoteObjectKit.pdb"
# ADD LINK32 FoundationKit.lib FoundationKit.lib NetworkKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\RemoteObjectKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\RemoteObjectKit.lib" /pdb:"..\..\..\lib\..\bin\RemoteObjectKit.pdb"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\RemoteObjectKit_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_sd\RemoteObjectKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\RemoteObjectKit_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_sd\RemoteObjectKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\RemoteObjectKit_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_s\RemoteObjectKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\RemoteObjectKit_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"..\..\..\lib\msvc6prj_s\RemoteObjectKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\RemoteObjectKit_s.lib"

!ENDIF

# Begin Target

# Name "RemoteObjectKit - Win32 vc6 DLL Debug"
# Name "RemoteObjectKit - Win32 vc6 DLL Release"
# Name "RemoteObjectKit - Win32 vc6 LIB Debug"
# Name "RemoteObjectKit - Win32 vc6 LIB Release"
# Name "RemoteObjectKit - Win32 DLL Debug"
# Name "RemoteObjectKit - Win32 DLL Release"
# Name "RemoteObjectKit - Win32 LIB Debug"
# Name "RemoteObjectKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassServerInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\InstanceID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\Proxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.cpp
# ADD BASE CPP /Yc"vcf\RemoteObjectKit\RemoteObjectKit.h"
# ADD CPP /Yc"vcf\RemoteObjectKit\RemoteObjectKit.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\ClassServerInstance.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\DistributedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\InstanceID.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\Proxy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\RemoteObjectKit\RemoteObjectKitSelectLib.h
# End Source File
# End Group
# End Target
# End Project

