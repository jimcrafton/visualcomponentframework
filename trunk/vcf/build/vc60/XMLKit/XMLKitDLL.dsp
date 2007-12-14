# Microsoft Developer Studio Project File - Name="XMLKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=XMLKitDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XMLKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMLKitDLL.mak" CFG="XMLKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "ReleaseDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLKITDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/libxml" /I "$(VCF_ROOT)/src/thirdparty/common/libxml/include" /I "$(VCF_ROOT)/src/thirdparty/common/libxslt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\..\bin\XMLKit_vc6.dll" /libpath:"..\..\..\lib"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "DebugDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XMLKITDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/libxml" /I "$(VCF_ROOT)/src/thirdparty/common/libxml/include" /I "$(VCF_ROOT)/src/thirdparty/common/libxslt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "XMLKIT_DLL" /D "XMLKIT_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\bin\XMLKit_vc6_d.dll" /pdbtype:sept /libpath:"..\..\..\lib"

!ENDIF 

# Begin Target

# Name "XMLKitDLL - Win32 Release"
# Name "XMLKitDLL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "libxslt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attributes.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attrvt.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\documents.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extensions.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extra.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\functions.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\imports.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\keys.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\namespaces.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\numbers.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\pattern.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\preproc.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\security.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\templates.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\transform.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\variables.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xslt.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltutils.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxslt"

!ENDIF 

# End Source File
# End Group
# Begin Group "libxml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\c14n.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\catalog.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\chvalid.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\debugXML.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\dict.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\DOCBparser.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\encoding.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\entities.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\error.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\globals.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\hash.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLparser.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLtree.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\legacy.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\list.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanoftp.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanohttp.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parser.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parserInternals.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\pattern.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\relaxng.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX2.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\schematron.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\threads.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\tree.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\uri.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\valid.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xinclude.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xlink.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlIO.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmemory.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmodule.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlreader.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlregexp.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlsave.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemas.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemastypes.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlstring.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlunicode.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlwriter.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpath.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpointer.c

!IF  "$(CFG)" == "XMLKitDLL - Win32 Release"

# PROP Intermediate_Dir "ReleaseDLL\libxml"

!ELSEIF  "$(CFG)" == "XMLKitDLL - Win32 Debug"

# PROP Intermediate_Dir "DebugDLL\libxml"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
