# Microsoft Developer Studio Project File - Name="JavaScriptKit_jstest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=jstest - Win32 DLL Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_jstest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_jstest.mak" CFG="jstest - Win32 DLL Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "jstest - Win32 vc80 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc80 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc71 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc71 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc70 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc70 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc6 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc6 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 icl7 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 icl7 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 icl6 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 icl6 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "jstest - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc80_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc80_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc80_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc80_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc80_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc80\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc80\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc80.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc80.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc80.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc80.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc71_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc71_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc71_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc71_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc71_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc71\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc71\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc71.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc71.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc71.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc71.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc70_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc70_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc70_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc70_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc70_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc70\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc70\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc70.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc70.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc70.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc70.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc6_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc6_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_vc6_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc6_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc6_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_vc6\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_vc6\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc6.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_vc6.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc6.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_vc6.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl7_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_icl7_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_icl7_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl7_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl7_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl7\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl7\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_icl7.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_icl7.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl7.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl7.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl6_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_icl6_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_icl6_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl6_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl6_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_icl6\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_icl6\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_icl6.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest_icl6.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl6.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_icl6.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MDd /I "..\js-impl" /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Zi /Gm /GZ /Fd.\jstest_d.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console
# ADD LINK32 FoundationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest_d.exe" /libpath:"$(VCF_ROOT)\lib" /debug /subsystem:console

!ELSEIF  "$(CFG)" == "jstest - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "."
# PROP BASE Intermediate_Dir "msvc6prj\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "msvc6prj\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD CPP /nologo /FD /MD /I "..\js-impl" /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /Fd.\jstest.pdb /I ".." /D "WIN32" /D "XP_WIN" /D "FOUNDATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_CONSOLE" /c
# ADD BASE RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
# ADD RSC /l 0x409 /i "..\js-impl" /d "XP_WIN" /d "FOUNDATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WIN32" /d "WIN32" /i "$(VCF_ROOT)\src" /d "_CONSOLE" /i ..
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console
# ADD LINK32 FoundationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib .\JavaScriptKit_dll.lib /nologo /machine:i386 /out:".\jstest.exe" /libpath:"$(VCF_ROOT)\lib" /subsystem:console

!ENDIF

# Begin Target

# Name "jstest - Win32 vc80 DLL Debug"
# Name "jstest - Win32 vc80 DLL Release"
# Name "jstest - Win32 vc71 DLL Debug"
# Name "jstest - Win32 vc71 DLL Release"
# Name "jstest - Win32 vc70 DLL Debug"
# Name "jstest - Win32 vc70 DLL Release"
# Name "jstest - Win32 vc6 DLL Debug"
# Name "jstest - Win32 vc6 DLL Release"
# Name "jstest - Win32 icl7 DLL Debug"
# Name "jstest - Win32 icl7 DLL Release"
# Name "jstest - Win32 icl6 DLL Debug"
# Name "jstest - Win32 icl6 DLL Release"
# Name "jstest - Win32 DLL Debug"
# Name "jstest - Win32 DLL Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\jstest.cpp
# End Source File
# End Group
# End Target
# End Project
