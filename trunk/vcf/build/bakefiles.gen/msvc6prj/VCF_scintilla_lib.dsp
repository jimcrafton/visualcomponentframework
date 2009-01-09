# Microsoft Developer Studio Project File - Name="VCF_scintilla_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=scintilla_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_scintilla_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_scintilla_lib.mak" CFG="scintilla_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scintilla_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "scintilla_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scintilla_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_vc6_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_vc6_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_s.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_vc6_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_vc6_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_vc6_s.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_sd.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_s.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\scintilla_sd.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_sd.lib"

!ELSEIF  "$(CFG)" == "scintilla_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\scintilla_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\scintilla_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\scintilla\include" /I "..\..\..\src\thirdparty\common\scintilla\src" /I "..\..\..\src\thirdparty\common\scintilla\win32" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\scintilla_s.pdb /D "WIN32" /D "_LIB" /D "STATIC_BUILD" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\scintilla_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\scintilla_s.lib"

!ENDIF

# Begin Target

# Name "scintilla_lib - Win32 vc6 DLL Debug"
# Name "scintilla_lib - Win32 vc6 DLL Release"
# Name "scintilla_lib - Win32 vc6 LIB Debug"
# Name "scintilla_lib - Win32 vc6 LIB Release"
# Name "scintilla_lib - Win32 DLL Debug"
# Name "scintilla_lib - Win32 DLL Release"
# Name "scintilla_lib - Win32 LIB Debug"
# Name "scintilla_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\AutoComplete.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CallTip.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CellBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ContractionState.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Document.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\DocumentAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Editor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ExternalLexer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Indicator.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyMap.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyWords.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAVE.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAda.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAsm.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexBaan.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexBullant.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCPP.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCSS.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexConf.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCrontab.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexEiffel.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexFortran.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexHTML.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexLisp.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexLua.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexMatlab.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexOthers.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexPascal.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexPerl.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexPython.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexRuby.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexSQL.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexVB.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LineMarker.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\PlatWin.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\PropSet.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\RESearch.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ScintillaBase.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ScintillaWin.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Style.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\StyleContext.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\UniConversion.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ViewStyle.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\WindowAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\XPM.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\Accessor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\AutoComplete.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CallTip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CellBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ContractionState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Document.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\DocumentAccessor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Editor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ExternalLexer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Indicator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\KeyWords.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LineMarker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\Platform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\PlatformRes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\PropSet.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\RESearch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\SString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\SVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\SciLexer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\Scintilla.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ScintillaBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\ScintillaWidget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Style.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\StyleContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\UniConversion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ViewStyle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\WinDefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\include\WindowAccessor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\XPM.h
# End Source File
# End Group
# End Target
# End Project

