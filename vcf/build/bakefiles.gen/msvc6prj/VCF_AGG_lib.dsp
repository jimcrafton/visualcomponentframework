# Microsoft Developer Studio Project File - Name="VCF_AGG_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AGG_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_AGG_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_AGG_lib.mak" CFG="AGG_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AGG_lib - Win32 vc90 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc90 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "AGG_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AGG_lib - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc90_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc80_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc71_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc70_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_vc6_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_s.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\AGG_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_sd.lib"

!ELSEIF  "$(CFG)" == "AGG_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\AGG_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\AGG_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\AGG_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\AGG_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\AGG_s.lib"

!ENDIF

# Begin Target

# Name "AGG_lib - Win32 vc90 DLL Debug"
# Name "AGG_lib - Win32 vc90 DLL Release"
# Name "AGG_lib - Win32 vc90 LIB Debug"
# Name "AGG_lib - Win32 vc90 LIB Release"
# Name "AGG_lib - Win32 vc80 DLL Debug"
# Name "AGG_lib - Win32 vc80 DLL Release"
# Name "AGG_lib - Win32 vc80 LIB Debug"
# Name "AGG_lib - Win32 vc80 LIB Release"
# Name "AGG_lib - Win32 vc71 DLL Debug"
# Name "AGG_lib - Win32 vc71 DLL Release"
# Name "AGG_lib - Win32 vc71 LIB Debug"
# Name "AGG_lib - Win32 vc71 LIB Release"
# Name "AGG_lib - Win32 vc70 DLL Debug"
# Name "AGG_lib - Win32 vc70 DLL Release"
# Name "AGG_lib - Win32 vc70 LIB Debug"
# Name "AGG_lib - Win32 vc70 LIB Release"
# Name "AGG_lib - Win32 vc6 DLL Debug"
# Name "AGG_lib - Win32 vc6 DLL Release"
# Name "AGG_lib - Win32 vc6 LIB Debug"
# Name "AGG_lib - Win32 vc6 LIB Release"
# Name "AGG_lib - Win32 DLL Debug"
# Name "AGG_lib - Win32 DLL Release"
# Name "AGG_lib - Win32 LIB Debug"
# Name "AGG_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_arc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_arrowhead.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bezier_arc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bspline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_curves.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_embedded_raster_fonts.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_gsv_text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_image_filters.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_line_aa_basics.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_line_profile_aa.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rounded_rect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_sqrt_tables.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_affine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_double_path.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_single_path.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_warp_magnifier.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_bspline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_contour.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_dash.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_markers_term.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_smooth_poly1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_stroke.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vpgen_clip_polygon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vpgen_segmentator.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_alpha_mask_u8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_arc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_arrowhead.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_basics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bezier_arc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bitset_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bounding_rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_clip_liang_barsky.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_color_rgba.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_color_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_color_rgba8_pre.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_adaptor_vcgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_adaptor_vpgen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_clip_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_close_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_concat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_contour.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_curve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_dash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_gpc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_marker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_marker_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_segmentator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_shorten_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_smooth_poly1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_transform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_conv_unclose_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_curves.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_dda_line.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_ellipse_bresenham.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_embedded_raster_fonts.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_font_cache_manager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_gamma_functions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_gamma_lut.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_glyph_raster_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_gsv_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_image_accessors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_image_filters.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_line_aa_basics.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_math.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_path_length.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_path_storage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_path_storage_integer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pattern_filters_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_amask_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgb24_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgb24_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgb555.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgb565.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgba32_plain.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_pixfmt_rgba32_pre.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_cells_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_compound_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_outline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_outline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_scanline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rasterizer_sl_clip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_markers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_mclip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_outline_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_outline_image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_primitives.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_raster_text.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_renderer_scanline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rendering_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_rounded_rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_boolean_algebra.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_p.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_storage_aa.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_storage_bin.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_scanline_u.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_shorten_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_simul_eq.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_converter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_generator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_gouraud.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_gouraud_gray8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_gouraud_rgba8.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_gouraud_rgba8_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_gradient.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_image_filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_image_filter_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_image_filter_rgb24_gamma.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_image_filter_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_interpolator_adaptor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_interpolator_linear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_interpolator_trans.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_pattern_gray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_pattern_rgb24.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_pattern_rgba32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_span_solid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_affine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_bilinear.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_double_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_perspective.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_single_path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_viewport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_trans_warp_magnifier.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_bspline.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_contour.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_dash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_markers_term.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_smooth_poly1.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vcgen_vertex_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vertex_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vertex_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vpgen_clip_polygon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\agg\src\agg_vpgen_segmentator.h
# End Source File
# End Group
# End Target
# End Project

