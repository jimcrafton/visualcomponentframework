# Microsoft Developer Studio Project File - Name="VCFExamples_jstest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=jstest - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_jstest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_jstest.mak" CFG="jstest - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "jstest - Win32 vc6 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc6 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc6 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 vc6 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 DLL Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 DLL Release" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 LIB Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "jstest - Win32 LIB Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "jstest - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_sd.lib js_vc6_d.lib FoundationKit_vc6_d.lib JavaScriptKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_sd.lib js_vc6_d.lib FoundationKit_vc6_d.lib JavaScriptKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_s.lib js_vc6.lib FoundationKit_vc6.lib JavaScriptKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_s.lib js_vc6.lib FoundationKit_vc6.lib JavaScriptKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_sd.lib js_vc6_d.lib FoundationKit_vc6_sd.lib JavaScriptKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_sd.lib js_vc6_d.lib FoundationKit_vc6_sd.lib JavaScriptKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_s.lib js_vc6.lib FoundationKit_vc6_s.lib JavaScriptKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_vc6_s.lib js_vc6.lib FoundationKit_vc6_s.lib JavaScriptKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_sd.lib js_d.lib FoundationKit_d.lib JavaScriptKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_sd.lib js_d.lib FoundationKit_d.lib JavaScriptKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /D "FOUNDATIONKIT_DLL" /D "JAVASCRIPTKIT_DLL" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d "EXPORT_JS_API" /d "FOUNDATIONKIT_DLL" /d JAVASCRIPTKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_s.lib js.lib FoundationKit.lib JavaScriptKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_s.lib js.lib FoundationKit.lib JavaScriptKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_sd.lib js_d.lib FoundationKit_sd.lib JavaScriptKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_sd.lib js_d.lib FoundationKit_sd.lib JavaScriptKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /debug /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ELSEIF  "$(CFG)" == "jstest - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\jstest"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\JavaScriptTest"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\jstest"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\JavaScriptTest\jstest.pdb /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /I "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_CONSOLE" /D "EXPORT_JS_API" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_CONSOLE" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl" /i "..\..\..\..\src\vcf\JavaScriptKit\js-impl\fdlibm" /d EXPORT_JS_API
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_s.lib js.lib FoundationKit_s.lib JavaScriptKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib fdlibm_s.lib js.lib FoundationKit_s.lib JavaScriptKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\JavaScriptTest\jstest.exe" /libpath:"..\..\..\..\lib" /subsystem:console /pdb:"..\..\..\..\examples\JavaScriptTest\jstest.pdb"

!ENDIF

# Begin Target

# Name "jstest - Win32 vc6 DLL Debug"
# Name "jstest - Win32 vc6 DLL Release"
# Name "jstest - Win32 vc6 LIB Debug"
# Name "jstest - Win32 vc6 LIB Release"
# Name "jstest - Win32 DLL Debug"
# Name "jstest - Win32 DLL Release"
# Name "jstest - Win32 LIB Debug"
# Name "jstest - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\JavaScriptTest\jstest.cpp
# End Source File
# End Group
# End Target
# End Project

