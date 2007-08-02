# Microsoft Developer Studio Project File - Name="VCF_LibJPEG_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibJPEG_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_LibJPEG_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_LibJPEG_lib.mak" CFG="LibJPEG_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibJPEG_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibJPEG_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibJPEG_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc80_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc71_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc70_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_vc6_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_s.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\LibJPEG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_sd.lib"

!ELSEIF  "$(CFG)" == "LibJPEG_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\LibJPEG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\LibJPEG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibJPEG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibJPEG_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibJPEG_s.lib"

!ENDIF

# Begin Target

# Name "LibJPEG_lib - Win32 vc80 DLL Debug"
# Name "LibJPEG_lib - Win32 vc80 DLL Release"
# Name "LibJPEG_lib - Win32 vc80 LIB Debug"
# Name "LibJPEG_lib - Win32 vc80 LIB Release"
# Name "LibJPEG_lib - Win32 vc71 DLL Debug"
# Name "LibJPEG_lib - Win32 vc71 DLL Release"
# Name "LibJPEG_lib - Win32 vc71 LIB Debug"
# Name "LibJPEG_lib - Win32 vc71 LIB Release"
# Name "LibJPEG_lib - Win32 vc70 DLL Debug"
# Name "LibJPEG_lib - Win32 vc70 DLL Release"
# Name "LibJPEG_lib - Win32 vc70 LIB Debug"
# Name "LibJPEG_lib - Win32 vc70 LIB Release"
# Name "LibJPEG_lib - Win32 vc6 DLL Debug"
# Name "LibJPEG_lib - Win32 vc6 DLL Release"
# Name "LibJPEG_lib - Win32 vc6 LIB Debug"
# Name "LibJPEG_lib - Win32 vc6 LIB Release"
# Name "LibJPEG_lib - Win32 DLL Debug"
# Name "LibJPEG_lib - Win32 DLL Release"
# Name "LibJPEG_lib - Win32 LIB Debug"
# Name "LibJPEG_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcapimin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcapistd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jccoefct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jccolor.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcdctmgr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jchuff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcinit.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcmainct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcmarker.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcmaster.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcomapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcparam.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcphuff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcprepct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jcsample.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jctrans.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdapimin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdapistd.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdatadst.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdatasrc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdcoefct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdcolor.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jddctmgr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdhuff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdinput.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdmainct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdmarker.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdmaster.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdmerge.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdphuff.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdpostct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdsample.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdtrans.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jerror.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jfdctflt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jfdctint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jidctflt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jidctfst.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jidctint.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jidctred.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jmemmgr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jmemnobs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jquant1.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jquant2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jutils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jchuff.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdct.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jdhuff.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jerror.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jinclude.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jmemsys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jmorecfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jpegint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jpeglib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibJPEG\jversion.h
# End Source File
# End Group
# End Target
# End Project

