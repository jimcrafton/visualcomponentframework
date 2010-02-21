# Microsoft Developer Studio Project File - Name="VCFExamples_MFCIntegration1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MFCIntegration1 - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_MFCIntegration1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_MFCIntegration1.mak" CFG="MFCIntegration1 - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MFCIntegration1 - Win32 vc6 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 vc6 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 vc6 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 vc6 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "MFCIntegration1 - Win32 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MFCIntegration1 - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_sd.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_vc6_s.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_d.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /debug /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_sd.pdb"

!ELSEIF  "$(CFG)" == "MFCIntegration1 - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\MFCIntegration1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\MFCIntegration1"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\MFCIntegration1"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_AFXDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d _AFXDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /pdb:"..\..\..\..\examples\MFCIntegration1\MFCIntegration1_s.pdb"

!ENDIF

# Begin Target

# Name "MFCIntegration1 - Win32 vc6 DLL Debug"
# Name "MFCIntegration1 - Win32 vc6 DLL Release"
# Name "MFCIntegration1 - Win32 vc6 LIB Debug"
# Name "MFCIntegration1 - Win32 vc6 LIB Release"
# Name "MFCIntegration1 - Win32 DLL Debug"
# Name "MFCIntegration1 - Win32 DLL Release"
# Name "MFCIntegration1 - Win32 LIB Debug"
# Name "MFCIntegration1 - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\MFCIntegration1.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\MFCIntegration1.rc
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\MFCIntegration1.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\..\..\..\..\examples\MFCIntegration1\resource.h
# End Source File
# End Group
# End Target
# End Project

