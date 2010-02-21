# Microsoft Developer Studio Project File - Name="VCFExamples_InetKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=InetKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_InetKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_InetKit.mak" CFG="InetKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "InetKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "InetKit - Win32 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "InetKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_vc6_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib InternetKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_d.lib InternetKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_vc6.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib InternetKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6.lib InternetKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_vc6_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib InternetKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_sd.lib InternetKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_sd.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_vc6_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib InternetKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_vc6_s.lib InternetKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_vc6_s.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_d.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib InternetKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_d.lib InternetKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_d.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib InternetKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit.lib InternetKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\InetKit\InetKit_sd.pdb /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib InternetKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_sd.lib InternetKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\InetKit\InetKit_sd.pdb"

!ELSEIF  "$(CFG)" == "InetKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\InetKit"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\InetKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\InetKit"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\InetKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\InetKit\InetKit_s.pdb /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d _WINDOWS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib InternetKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib FoundationKit_s.lib InternetKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\InetKit\InetKit_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\InetKit\InetKit_s.pdb"

!ENDIF

# Begin Target

# Name "InetKit - Win32 vc6 DLL Debug"
# Name "InetKit - Win32 vc6 DLL Release"
# Name "InetKit - Win32 vc6 LIB Debug"
# Name "InetKit - Win32 vc6 LIB Release"
# Name "InetKit - Win32 DLL Debug"
# Name "InetKit - Win32 DLL Release"
# Name "InetKit - Win32 LIB Debug"
# Name "InetKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\InetKit\InetKit.cpp
# End Source File
# End Group
# End Target
# End Project

