# Microsoft Developer Studio Project File - Name="ImageKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ImageKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImageKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImageKit.mak" CFG="ImageKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ImageKit___Win32_Release"
# PROP BASE Intermediate_Dir "ImageKit___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/vcf/ImageKit/glew/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /D "USE_OPENGLKIT_LIB" /D "GLEW_STATIC" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /fo"..\..\..\lib\ImageKit.res" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "ImageKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ImageKit___Win32_Debug"
# PROP BASE Intermediate_Dir "ImageKit___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/vcf/ImageKit/glew/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "USE_APPLICATIONKIT_LIB" /D "USE_OPENGLKIT_LIB" /D "GLEW_STATIC" /YX /FD /I /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"..\..\..\lib\ImageKit_d.res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/ImageKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "ImageKit - Win32 Release"
# Name "ImageKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\glew\src\glew.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\ImageKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\ImageKit.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\ImageKit\ImageKit.h
# End Source File
# End Group
# Begin Group "Shaders"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
