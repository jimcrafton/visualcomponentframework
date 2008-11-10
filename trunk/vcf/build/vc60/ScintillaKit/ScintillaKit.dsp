# Microsoft Developer Studio Project File - Name="ScintillaKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ScintillaKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ScintillaKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ScintillaKit.mak" CFG="ScintillaKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ScintillaKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ScintillaKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ScintillaKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/include" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /D "STATIC_BUILD" /D "SCI_LEXER" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ScintillaKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/include" /I "$(VCF_ROOT)/src/thirdparty/common/scintilla/src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /D "STATIC_BUILD" /D "SCI_LEXER" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/ScintillaKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "ScintillaKit - Win32 Release"
# Name "ScintillaKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
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
# End Target
# End Project
