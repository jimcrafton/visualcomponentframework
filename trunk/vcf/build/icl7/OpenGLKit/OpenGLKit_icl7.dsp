# Microsoft Developer Studio Project File - Name="OpenGLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=OpenGLKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenGLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenGLKit.mak" CFG="OpenGLKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGLKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenGLKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "icl7\ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_APPLICATIONKIT_LIB" /FD /c
# SUBTRACT CPP /YX /Yc /Yu /FR
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\lib\OpenGLKit_icl7_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_icl7_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "icl7\DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_APPLICATIONKIT_LIB" /Fd"..\..\..\lib\OpenGLKit_icl7_sd.pdb" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu /FR
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\lib\OpenGLKit_icl7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_icl7_sd.lib"

!ENDIF 

# Begin Target

# Name "OpenGLKit - Win32 Release"
# Name "OpenGLKit - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\Win32OpenGLPeer.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\VCFOpenGL.h
# End Source File
# End Group
# End Target
# End Project
