# Microsoft Developer Studio Project File - Name="VCFExamples_WorkingWithEnumerators" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=WorkingWithEnumerators - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_WorkingWithEnumerators.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_WorkingWithEnumerators.mak" CFG="WorkingWithEnumerators - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WorkingWithEnumerators - Win32 vc6 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 vc6 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 vc6 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 vc6 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "WorkingWithEnumerators - Win32 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WorkingWithEnumerators - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_sd.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_vc6_s.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_d.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "FOUNDATIONKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /d FOUNDATIONKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_sd.pdb"

!ELSEIF  "$(CFG)" == "WorkingWithEnumerators - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\WorkingWithEnumerators"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\WorkingWithEnumerators"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\WorkingWithEnumerators"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _CONSOLE
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators_s.pdb"

!ENDIF

# Begin Target

# Name "WorkingWithEnumerators - Win32 vc6 DLL Debug"
# Name "WorkingWithEnumerators - Win32 vc6 DLL Release"
# Name "WorkingWithEnumerators - Win32 vc6 LIB Debug"
# Name "WorkingWithEnumerators - Win32 vc6 LIB Release"
# Name "WorkingWithEnumerators - Win32 DLL Debug"
# Name "WorkingWithEnumerators - Win32 DLL Release"
# Name "WorkingWithEnumerators - Win32 LIB Debug"
# Name "WorkingWithEnumerators - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\WorkingWithEnumerators\WorkingWithEnumerators.cpp
# End Source File
# End Group
# End Target
# End Project

