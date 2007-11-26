# Microsoft Developer Studio Project File - Name="XMLKitLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=XMLKitLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XMLKitLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMLKitLib.mak" CFG="XMLKitLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLKitLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XMLKitLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "ReleaseLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/libxml" /I "$(VCF_ROOT)/src/thirdparty/common/libxml/include" /I "$(VCF_ROOT)/src/thirdparty/common/libxslt" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "XMLKIT_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "XMLKitLib___Win32_Debug"
# PROP BASE Intermediate_Dir "XMLKitLib___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "DebugLib\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/common/libxml" /I "$(VCF_ROOT)/src/thirdparty/common/libxml/include" /I "$(VCF_ROOT)/src/thirdparty/common/libxslt" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_FOUNDATIONKIT_LIB" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "XMLKIT_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\XMLKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "XMLKitLib - Win32 Release"
# Name "XMLKitLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\DOM3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\XMLKit\XMLKit.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "libxml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\c14n.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\catalog.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\chvalid.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\debugXML.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\dict.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\DOCBparser.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\encoding.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\entities.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\error.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\globals.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\hash.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLparser.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLtree.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\legacy.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\list.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanoftp.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanohttp.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parser.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parserInternals.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\pattern.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\relaxng.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX2.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\schematron.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\threads.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\tree.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\uri.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\valid.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xinclude.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xlink.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlIO.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmemory.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmodule.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlreader.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlregexp.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlsave.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemas.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemastypes.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlstring.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlunicode.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlwriter.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpath.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpointer.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxml"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxml"

!ENDIF 

# End Source File
# End Group
# Begin Group "libxslt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attributes.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attrvt.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\documents.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extensions.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extra.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\functions.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\imports.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\keys.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\namespaces.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\numbers.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\pattern.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\preproc.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\security.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\templates.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\transform.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\variables.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xslt.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltutils.c

!IF  "$(CFG)" == "XMLKitLib - Win32 Release"

# PROP Intermediate_Dir "ReleaseLib\libxslt"

!ELSEIF  "$(CFG)" == "XMLKitLib - Win32 Debug"

# PROP Intermediate_Dir "DebugLib\libxslt"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
