# Microsoft Developer Studio Project File - Name="VCF_RemoteObjectKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RemoteObjectKit - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RemoteObjectKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_RemoteObjectKit.mak" CFG="RemoteObjectKit - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RemoteObjectKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc80 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc80 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc71 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc71 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc70 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc70 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 vc6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 icl7 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 icl7 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 icl7 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 icl7 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 icl6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 icl6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 icl6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 icl6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RemoteObjectKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "RemoteObjectKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RemoteObjectKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc80_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_d\RemoteObjectKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc80_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_d\RemoteObjectKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib FoundationKit_vc80_d.lib NetworkKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc80_d.lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib FoundationKit_vc80_d.lib NetworkKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc80.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80\RemoteObjectKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc80.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80\RemoteObjectKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib FoundationKit_vc80.lib NetworkKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc80.lib"
# ADD LINK32 FoundationKit_vc80.lib FoundationKit_vc80.lib NetworkKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc80.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc80 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc80_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_sd\RemoteObjectKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc80_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_sd\RemoteObjectKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc80 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc80_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_s\RemoteObjectKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc80_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc80_s\RemoteObjectKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc71_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_d\RemoteObjectKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc71_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_d\RemoteObjectKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib FoundationKit_vc71_d.lib NetworkKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc71_d.lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib FoundationKit_vc71_d.lib NetworkKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc71.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71\RemoteObjectKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc71.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71\RemoteObjectKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib FoundationKit_vc71.lib NetworkKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc71.lib"
# ADD LINK32 FoundationKit_vc71.lib FoundationKit_vc71.lib NetworkKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc71.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc71 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc71_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_sd\RemoteObjectKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc71_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_sd\RemoteObjectKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc71 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc71_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_s\RemoteObjectKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc71_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc71_s\RemoteObjectKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc70_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_d\RemoteObjectKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc70_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_d\RemoteObjectKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib FoundationKit_vc70_d.lib NetworkKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc70_d.lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib FoundationKit_vc70_d.lib NetworkKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc70.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70\RemoteObjectKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc70.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70\RemoteObjectKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib FoundationKit_vc70.lib NetworkKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc70.lib"
# ADD LINK32 FoundationKit_vc70.lib FoundationKit_vc70.lib NetworkKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc70.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc70 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc70_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_sd\RemoteObjectKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc70_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_sd\RemoteObjectKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc70 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc70_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_s\RemoteObjectKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc70_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc70_s\RemoteObjectKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_d\RemoteObjectKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_vc6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_d\RemoteObjectKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib FoundationKit_vc6_d.lib NetworkKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc6_d.lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib FoundationKit_vc6_d.lib NetworkKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6\RemoteObjectKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_vc6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6\RemoteObjectKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib FoundationKit_vc6.lib NetworkKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc6.lib"
# ADD LINK32 FoundationKit_vc6.lib FoundationKit_vc6.lib NetworkKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_vc6.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_sd\RemoteObjectKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_vc6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_sd\RemoteObjectKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 vc6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_s\RemoteObjectKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_vc6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_vc6_s\RemoteObjectKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_icl7_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_d\RemoteObjectKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_icl7_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_d\RemoteObjectKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7_d.lib FoundationKit_icl7_d.lib NetworkKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl7_d.lib" /debug
# ADD LINK32 FoundationKit_icl7_d.lib FoundationKit_icl7_d.lib NetworkKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl7_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_icl7.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7\RemoteObjectKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_icl7.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7\RemoteObjectKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7.lib FoundationKit_icl7.lib NetworkKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl7.lib"
# ADD LINK32 FoundationKit_icl7.lib FoundationKit_icl7.lib NetworkKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl7.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl7 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_icl7_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_sd\RemoteObjectKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_icl7_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_sd\RemoteObjectKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl7 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_icl7_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_s\RemoteObjectKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_icl7_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl7_s\RemoteObjectKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl7_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_icl6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_d\RemoteObjectKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_icl6_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_d\RemoteObjectKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6_d.lib FoundationKit_icl6_d.lib NetworkKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl6_d.lib" /debug
# ADD LINK32 FoundationKit_icl6_d.lib FoundationKit_icl6_d.lib NetworkKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl6_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_icl6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6\RemoteObjectKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit_icl6.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6\RemoteObjectKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6.lib FoundationKit_icl6.lib NetworkKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl6.lib"
# ADD LINK32 FoundationKit_icl6.lib FoundationKit_icl6.lib NetworkKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_icl6.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_icl6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_sd\RemoteObjectKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_icl6_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_sd\RemoteObjectKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 icl6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_icl6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_s\RemoteObjectKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_icl6_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_icl6_s\RemoteObjectKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_icl6_s.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_d\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_d\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_d\RemoteObjectKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\RemoteObjectKit_d.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_d\RemoteObjectKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib FoundationKit_d.lib NetworkKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_d.lib" /debug
# ADD LINK32 FoundationKit_d.lib FoundationKit_d.lib NetworkKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj\RemoteObjectKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\RemoteObjectKit.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj\RemoteObjectKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "NETWORKKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "REMOTEKIT_DLL" /D "REMOTEKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /d "FOUNDATIONKIT_DLL" /d "NETWORKKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "REMOTEKIT_DLL" /d REMOTEKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib FoundationKit.lib NetworkKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit.lib"
# ADD LINK32 FoundationKit.lib FoundationKit.lib NetworkKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\RemoteObjectKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\RemoteObjectKit.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_sd\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_sd\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_sd\RemoteObjectKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\RemoteObjectKit_sd.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_sd\RemoteObjectKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_sd.lib"

!ELSEIF  "$(CFG)" == "RemoteObjectKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_s\RemoteObjectKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_s\RemoteObjectKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_s\RemoteObjectKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\RemoteObjectKit_s.pdb /Yu"vcf\RemoteObjectKit\RemoteObjectKit.h" /Fp"msvc6prj_s\RemoteObjectKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\RemoteObjectKit_s.lib"

!ENDIF

# Begin Target

# Name "RemoteObjectKit - Win32 vc80 DLL Debug"
# Name "RemoteObjectKit - Win32 vc80 DLL Release"
# Name "RemoteObjectKit - Win32 vc80 Debug"
# Name "RemoteObjectKit - Win32 vc80 Release"
# Name "RemoteObjectKit - Win32 vc71 DLL Debug"
# Name "RemoteObjectKit - Win32 vc71 DLL Release"
# Name "RemoteObjectKit - Win32 vc71 Debug"
# Name "RemoteObjectKit - Win32 vc71 Release"
# Name "RemoteObjectKit - Win32 vc70 DLL Debug"
# Name "RemoteObjectKit - Win32 vc70 DLL Release"
# Name "RemoteObjectKit - Win32 vc70 Debug"
# Name "RemoteObjectKit - Win32 vc70 Release"
# Name "RemoteObjectKit - Win32 vc6 DLL Debug"
# Name "RemoteObjectKit - Win32 vc6 DLL Release"
# Name "RemoteObjectKit - Win32 vc6 Debug"
# Name "RemoteObjectKit - Win32 vc6 Release"
# Name "RemoteObjectKit - Win32 icl7 DLL Debug"
# Name "RemoteObjectKit - Win32 icl7 DLL Release"
# Name "RemoteObjectKit - Win32 icl7 Debug"
# Name "RemoteObjectKit - Win32 icl7 Release"
# Name "RemoteObjectKit - Win32 icl6 DLL Debug"
# Name "RemoteObjectKit - Win32 icl6 DLL Release"
# Name "RemoteObjectKit - Win32 icl6 Debug"
# Name "RemoteObjectKit - Win32 icl6 Release"
# Name "RemoteObjectKit - Win32 DLL Debug"
# Name "RemoteObjectKit - Win32 DLL Release"
# Name "RemoteObjectKit - Win32 Debug"
# Name "RemoteObjectKit - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\ClassServerInstance.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\DistributedException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\InstanceID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\Proxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.cpp
# ADD BASE CPP /Yc"vcf\RemoteObjectKit\RemoteObjectKit.h"
# ADD CPP /Yc"vcf\RemoteObjectKit\RemoteObjectKit.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\AbstractDistributedApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\ClassRegistryEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\ClassServerInstance.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\DistributedClassRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\DistributedException.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\InstanceID.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\Proxy.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\RemoteCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\RemoteConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\RemoteObjectKit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\RemoteObjectKit\RemoteObjectKitSelectLib.h
# End Source File
# End Group
# End Target
# End Project

