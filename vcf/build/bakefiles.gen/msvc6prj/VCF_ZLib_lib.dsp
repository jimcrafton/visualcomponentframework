# Microsoft Developer Studio Project File - Name="VCF_ZLib_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ZLib_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ZLib_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ZLib_lib.mak" CFG="ZLib_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ZLib_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ZLib_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ZLib_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_s.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_vc6_s.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_sd.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_s.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\ZLib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_sd.lib"

!ELSEIF  "$(CFG)" == "ZLib_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\ZLib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\ZLib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ZLib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ZLib_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ZLib_s.lib"

!ENDIF

# Begin Target

# Name "ZLib_lib - Win32 vc6 DLL Debug"
# Name "ZLib_lib - Win32 vc6 DLL Release"
# Name "ZLib_lib - Win32 vc6 LIB Debug"
# Name "ZLib_lib - Win32 vc6 LIB Release"
# Name "ZLib_lib - Win32 DLL Debug"
# Name "ZLib_lib - Win32 DLL Release"
# Name "ZLib_lib - Win32 LIB Debug"
# Name "ZLib_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\adler32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\compress.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\crc32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\deflate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\gzio.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\infback.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inffast.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inflate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inftrees.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\trees.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\uncompr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\zutil.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\crc32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\deflate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inffast.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inffixed.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inflate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\inftrees.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\trees.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\zconf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\zlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\ZLib\zutil.h
# End Source File
# End Group
# End Target
# End Project

