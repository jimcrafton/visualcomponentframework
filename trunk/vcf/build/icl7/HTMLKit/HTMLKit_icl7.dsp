# Microsoft Developer Studio Project File - Name="HTMLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=HTMLKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HTMLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HTMLKit.mak" CFG="HTMLKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HTMLKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HTMLKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\"
# PROP Intermediate_Dir "Release\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /I "$(VCF_INCLUDE)/thirdparty/win32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /Yu"vcf/HTMLKit/HTMLKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/HTMLKit_icl7_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "HTMLKit___Win32_Debug"
# PROP BASE Intermediate_Dir "HTMLKit___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "HTMLKit___Win32_Debug\"
# PROP Intermediate_Dir "HTMLKit___Win32_Debug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /I "$(VCF_INCLUDE)/thirdparty/win32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /Fd"..\..\..\lib\HTMLKit_icl7_sd.pdb" /Yu"vcf/HTMLKit/HTMLKit.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/HTMLKit_icl7_sd.lib"

!ENDIF 

# Begin Target

# Name "HTMLKit - Win32 Release"
# Name "HTMLKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLBrowserControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLKit.cpp
# ADD CPP /Yc"vcf/HTMLKit/HTMLKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLBrowser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLDOMElements.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLToolkit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLBrowserControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLBrowserPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLDOMElements.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\HTMLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLBrowser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLDOMElements.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\HTMLKit\Win32HTMLToolkit.h
# End Source File
# End Group
# End Target
# End Project
