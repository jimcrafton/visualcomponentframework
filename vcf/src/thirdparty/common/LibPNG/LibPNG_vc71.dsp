# Microsoft Developer Studio Project File - Name="LibPNG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibPNG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LibPNG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibPNG.mak" CFG="LibPNG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibPNG - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibPNG - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibPNG - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "vc71\Release\"
# PROP Intermediate_Dir "vc71\Release\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "$(VCF_INCLUDE)" /I "../zlib" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX /FR
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../../lib/LibPNG_vc71_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../lib/LibPNG_vc71_s.lib"

!ELSEIF  "$(CFG)" == "LibPNG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "vc71\Debug\"
# PROP Intermediate_Dir "vc71\Debug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(VCF_INCLUDE)" /I "../zlib" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fd"..\..\..\..\lib\LibPNG_vc71_sd.pdb" /FD /GZ /c
# SUBTRACT CPP /YX /FR
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../../lib/LibPNG_vc71_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../../lib/LibPNG_vc71_sd.lib"

!ENDIF 

# Begin Target

# Name "LibPNG - Win32 Release"
# Name "LibPNG - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=png.c
# End Source File
# Begin Source File

SOURCE=pngerror.c
# End Source File
# Begin Source File

SOURCE=pnggccrd.c
# End Source File
# Begin Source File

SOURCE=pngget.c
# End Source File
# Begin Source File

SOURCE=pngmem.c
# End Source File
# Begin Source File

SOURCE=pngpread.c
# End Source File
# Begin Source File

SOURCE=pngread.c
# End Source File
# Begin Source File

SOURCE=pngrio.c
# End Source File
# Begin Source File

SOURCE=pngrtran.c
# End Source File
# Begin Source File

SOURCE=pngrutil.c
# End Source File
# Begin Source File

SOURCE=pngset.c
# End Source File
# Begin Source File

SOURCE=pngtest.c
# End Source File
# Begin Source File

SOURCE=pngtrans.c
# End Source File
# Begin Source File

SOURCE=pngvcrd.c
# End Source File
# Begin Source File

SOURCE=pngwio.c
# End Source File
# Begin Source File

SOURCE=pngwrite.c
# End Source File
# Begin Source File

SOURCE=pngwtran.c
# End Source File
# Begin Source File

SOURCE=pngwutil.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=png.h
# End Source File
# Begin Source File

SOURCE=pngconf.h
# End Source File
# End Group
# End Target
# End Project
