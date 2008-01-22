# Microsoft Developer Studio Project File - Name="VCF_paintlib_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=paintlib_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_paintlib_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_paintlib_lib.mak" CFG="paintlib_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "paintlib_lib - Win32 vc90 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc90 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "paintlib_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "paintlib_lib - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc90_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc80_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc71_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc70_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_vc6_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_s.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\paintlib_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_sd.lib"

!ELSEIF  "$(CFG)" == "paintlib_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\paintlib_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\paintlib_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\paintlib\common\Filter" /I "..\..\..\src\thirdparty\common\paintlib\common" /I "..\..\..\src\thirdparty\common\paintlib\win\paintlib" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\LibTIFF" /I "..\..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\paintlib_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\paintlib_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\paintlib_s.lib"

!ENDIF

# Begin Target

# Name "paintlib_lib - Win32 vc90 DLL Debug"
# Name "paintlib_lib - Win32 vc90 DLL Release"
# Name "paintlib_lib - Win32 vc90 LIB Debug"
# Name "paintlib_lib - Win32 vc90 LIB Release"
# Name "paintlib_lib - Win32 vc80 DLL Debug"
# Name "paintlib_lib - Win32 vc80 DLL Release"
# Name "paintlib_lib - Win32 vc80 LIB Debug"
# Name "paintlib_lib - Win32 vc80 LIB Release"
# Name "paintlib_lib - Win32 vc71 DLL Debug"
# Name "paintlib_lib - Win32 vc71 DLL Release"
# Name "paintlib_lib - Win32 vc71 LIB Debug"
# Name "paintlib_lib - Win32 vc71 LIB Release"
# Name "paintlib_lib - Win32 vc70 DLL Debug"
# Name "paintlib_lib - Win32 vc70 DLL Release"
# Name "paintlib_lib - Win32 vc70 LIB Debug"
# Name "paintlib_lib - Win32 vc70 LIB Release"
# Name "paintlib_lib - Win32 vc6 DLL Debug"
# Name "paintlib_lib - Win32 vc6 DLL Release"
# Name "paintlib_lib - Win32 vc6 LIB Debug"
# Name "paintlib_lib - Win32 vc6 LIB Release"
# Name "paintlib_lib - Win32 DLL Debug"
# Name "paintlib_lib - Win32 DLL Release"
# Name "paintlib_lib - Win32 LIB Debug"
# Name "paintlib_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\jmemdest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\jmemsrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plStreamSink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\planybmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\planydec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpenc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldatasink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldatasrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\pldibsect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plexcept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plexif.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plfilesink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plfilesrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercolorize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercontrast.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercrop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterflip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterfliprgb.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltergetalpha.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltergrayscale.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterintensity.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterlightness.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltermirror.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterquantize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizebilinear.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizebox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizegaussian.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizehamming.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterrotate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterthreshold.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltervideoinvert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plhsvconvert.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pliff85dec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plinplacefilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pljpegdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pljpegenc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plmemsink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plmemsrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plobject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpcxdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpgmdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpicdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpicenc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpictdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixelformat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpngdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpngenc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plppmdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpsddec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plressrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plsgidec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plsubbmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltgadec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffenc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffencex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plwemfdec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plwinbmp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\tif_msrc.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\PaintLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\PaintLibSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\jmemdest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\jmemsrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\pl2passscale.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plStreamSink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\planybmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\planydec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbitmap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpbase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plbmpinfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plcontribdefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plcountedpointer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldatasink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldatasrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldebug.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pldecoderfactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\pldibsect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plexcept.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plexif.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plfilesink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plfilesrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercolorize.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercontrast.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltercrop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterfill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterfillrect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterflip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterfliprgb.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltergetalpha.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltergrayscale.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterintensity.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterlightness.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltermirror.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterpixel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterquantize.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresize.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizebilinear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizebox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizegaussian.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterresizehamming.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterrotate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfilterthreshold.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plfiltervideoinvert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plgifdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plhsvconvert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pliff85.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pliff85dec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\Filter\plinplacefilter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pljpegdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pljpegenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plmemsink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plmemsrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plobject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\ploptable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpaintlibdefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpcx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpcxdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpgm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpgmdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpicdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpicenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpictdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixel16.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixel24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixel32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixel8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixeldefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpixelformat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpngdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpngenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plppm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plppmdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plprognot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plpsddec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plrect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plressrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plsgidec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plsubbmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltga.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltgadec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffenc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\pltiffencex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plurlsrc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plwemfdec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\win\paintlib\plwinbmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\plwindefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\qdraw.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\paintlib\common\tif_msrc.h
# End Source File
# End Group
# End Target
# End Project

