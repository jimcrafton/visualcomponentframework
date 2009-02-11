# Microsoft Developer Studio Project File - Name="ScintillaKitDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ScintillaKitDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScintillaKitDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScintillaKitDll.mak" CFG="ScintillaKitDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScintillaKitDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ScintillaKitDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScintillaKitDll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ScintillaKitDll___Win32_Release"
# PROP BASE Intermediate_Dir "ScintillaKitDll___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ScintillaKitDll___Win32_Release"
# PROP Intermediate_Dir "ScintillaKitDll___Win32_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCINTILLAKITDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCINTILLAKITDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "ScintillaKitDll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ScintillaKitDll___Win32_Debug"
# PROP BASE Intermediate_Dir "ScintillaKitDll___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCINTILLAKITDLL_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/include" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_APPLICATIONKIT_DLL" /D "STATIC_BUILD" /D "SCI_LEXER" /D "SCINTILLAKIT_EXPORTS" /D "SCINTILLAKIT_DLL" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../../bin/ScintillaKit_vc6_d.dll" /implib:"../../../lib/ScintillaKit_vc6_d.lib" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ScintillaKitDll - Win32 Release"
# Name "ScintillaKitDll - Win32 Debug"
# Begin Group "scintilla"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\AutoComplete.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\AutoComplete.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CallTip.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CallTip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CellBuffer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\CellBuffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ContractionState.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ContractionState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Document.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Document.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\DocumentAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\DocumentAccessor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Editor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Editor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ExternalLexer.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Indicator.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Indicator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyMap.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyMap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\KeyWords.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAda.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAsm.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexAVE.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexBaan.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexBullant.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexConf.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCPP.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCrontab.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LexCSS.cxx
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

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\LineMarker.h
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

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\RESearch.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ScintillaBase.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ScintillaBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ScintillaWin.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\win32\ScintRes.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Style.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\Style.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\StyleContext.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\StyleContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\SVector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\UniConversion.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\UniConversion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ViewStyle.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\ViewStyle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\WindowAccessor.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\XPM.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\scintilla\src\XPM.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\ScintillaKit\ScintillaKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ScintillaKit\ScintillaKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ScintillaKit\ScintillaPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ScintillaKit\ScintillaPeer.h
# End Source File
# End Group
# End Target
# End Project
