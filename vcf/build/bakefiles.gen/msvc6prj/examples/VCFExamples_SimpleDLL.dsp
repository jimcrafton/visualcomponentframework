# Microsoft Developer Studio Project File - Name="VCFExamples_SimpleDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SimpleDLL - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_SimpleDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_SimpleDLL.mak" CFG="SimpleDLL - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleDLL - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 vc6 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 vc6 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 LIB Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SimpleDLL - Win32 LIB Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimpleDLL - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /Zi /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /debug /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ELSEIF  "$(CFG)" == "SimpleDLL - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\SimpleDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\SharedLibraries"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\SimpleDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /Fd..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d _USRDLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\..\examples\SharedLibraries\SimpleDLL.so" /implib:"..\..\..\..\examples\SharedLibraries\SimpleDLL.lib" /pdb:"..\..\..\..\examples\SharedLibraries\SimpleDLL.pdb"

!ENDIF

# Begin Target

# Name "SimpleDLL - Win32 vc6 DLL Debug"
# Name "SimpleDLL - Win32 vc6 DLL Release"
# Name "SimpleDLL - Win32 vc6 LIB Debug"
# Name "SimpleDLL - Win32 vc6 LIB Release"
# Name "SimpleDLL - Win32 DLL Debug"
# Name "SimpleDLL - Win32 DLL Release"
# Name "SimpleDLL - Win32 LIB Debug"
# Name "SimpleDLL - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\SharedLibraries\SimpleDLL.cpp
# End Source File
# End Group
# End Target
# End Project

