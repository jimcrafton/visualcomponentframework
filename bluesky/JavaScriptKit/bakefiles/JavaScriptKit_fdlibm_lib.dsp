# Microsoft Developer Studio Project File - Name="JavaScriptKit_fdlibm_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=fdlibm_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_fdlibm_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JavaScriptKit_fdlibm_lib.mak" CFG="fdlibm_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fdlibm_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl7 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl7 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl7 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl7 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 icl6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "fdlibm_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fdlibm_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc80_d"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc80_d"
# PROP Intermediate_Dir "msvc6prj_vc80_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc80_d\fdlibm_vc80_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc80_d\fdlibm_vc80_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc80_d\fdlibm_vc80_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc80_d\fdlibm_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc80"
# PROP BASE Intermediate_Dir "msvc6prj_vc80\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc80"
# PROP Intermediate_Dir "msvc6prj_vc80\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc80\fdlibm_vc80_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc80\fdlibm_vc80_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc80\fdlibm_vc80_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc80\fdlibm_vc80_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc80_sd"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc80_sd"
# PROP Intermediate_Dir "msvc6prj_vc80_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc80_sd\fdlibm_vc80_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc80_sd\fdlibm_vc80_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc80_sd\fdlibm_vc80_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc80_sd\fdlibm_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc80_s"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc80_s"
# PROP Intermediate_Dir "msvc6prj_vc80_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc80_s\fdlibm_vc80_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc80_s\fdlibm_vc80_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc80_s\fdlibm_vc80_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc80_s\fdlibm_vc80_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc71_d"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc71_d"
# PROP Intermediate_Dir "msvc6prj_vc71_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc71_d\fdlibm_vc71_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc71_d\fdlibm_vc71_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc71_d\fdlibm_vc71_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc71_d\fdlibm_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc71"
# PROP BASE Intermediate_Dir "msvc6prj_vc71\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc71"
# PROP Intermediate_Dir "msvc6prj_vc71\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc71\fdlibm_vc71_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc71\fdlibm_vc71_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc71\fdlibm_vc71_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc71\fdlibm_vc71_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc71_sd"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc71_sd"
# PROP Intermediate_Dir "msvc6prj_vc71_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc71_sd\fdlibm_vc71_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc71_sd\fdlibm_vc71_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc71_sd\fdlibm_vc71_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc71_sd\fdlibm_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc71_s"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc71_s"
# PROP Intermediate_Dir "msvc6prj_vc71_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc71_s\fdlibm_vc71_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc71_s\fdlibm_vc71_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc71_s\fdlibm_vc71_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc71_s\fdlibm_vc71_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc70_d"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc70_d"
# PROP Intermediate_Dir "msvc6prj_vc70_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc70_d\fdlibm_vc70_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc70_d\fdlibm_vc70_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc70_d\fdlibm_vc70_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc70_d\fdlibm_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc70"
# PROP BASE Intermediate_Dir "msvc6prj_vc70\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc70"
# PROP Intermediate_Dir "msvc6prj_vc70\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc70\fdlibm_vc70_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc70\fdlibm_vc70_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc70\fdlibm_vc70_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc70\fdlibm_vc70_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc70_sd"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc70_sd"
# PROP Intermediate_Dir "msvc6prj_vc70_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc70_sd\fdlibm_vc70_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc70_sd\fdlibm_vc70_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc70_sd\fdlibm_vc70_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc70_sd\fdlibm_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc70_s"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc70_s"
# PROP Intermediate_Dir "msvc6prj_vc70_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc70_s\fdlibm_vc70_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc70_s\fdlibm_vc70_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc70_s\fdlibm_vc70_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc70_s\fdlibm_vc70_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc6_d"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc6_d"
# PROP Intermediate_Dir "msvc6prj_vc6_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc6_d\fdlibm_vc6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc6_d\fdlibm_vc6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc6_d\fdlibm_vc6_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc6_d\fdlibm_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc6"
# PROP BASE Intermediate_Dir "msvc6prj_vc6\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc6"
# PROP Intermediate_Dir "msvc6prj_vc6\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc6\fdlibm_vc6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc6\fdlibm_vc6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc6\fdlibm_vc6_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc6\fdlibm_vc6_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_vc6_sd"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_vc6_sd"
# PROP Intermediate_Dir "msvc6prj_vc6_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc6_sd\fdlibm_vc6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_vc6_sd\fdlibm_vc6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc6_sd\fdlibm_vc6_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc6_sd\fdlibm_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_vc6_s"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_vc6_s"
# PROP Intermediate_Dir "msvc6prj_vc6_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_vc6_s\fdlibm_vc6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_vc6_s\fdlibm_vc6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_vc6_s\fdlibm_vc6_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_vc6_s\fdlibm_vc6_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_icl7_d"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_icl7_d"
# PROP Intermediate_Dir "msvc6prj_icl7_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl7_d\fdlibm_icl7_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl7_d\fdlibm_icl7_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl7_d\fdlibm_icl7_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl7_d\fdlibm_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_icl7"
# PROP BASE Intermediate_Dir "msvc6prj_icl7\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_icl7"
# PROP Intermediate_Dir "msvc6prj_icl7\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_icl7\fdlibm_icl7_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_icl7\fdlibm_icl7_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl7\fdlibm_icl7_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl7\fdlibm_icl7_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl7 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_icl7_sd"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_icl7_sd"
# PROP Intermediate_Dir "msvc6prj_icl7_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl7_sd\fdlibm_icl7_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl7_sd\fdlibm_icl7_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl7_sd\fdlibm_icl7_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl7_sd\fdlibm_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl7 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_icl7_s"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_icl7_s"
# PROP Intermediate_Dir "msvc6prj_icl7_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_icl7_s\fdlibm_icl7_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_icl7_s\fdlibm_icl7_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl7_s\fdlibm_icl7_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl7_s\fdlibm_icl7_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_icl6_d"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_icl6_d"
# PROP Intermediate_Dir "msvc6prj_icl6_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl6_d\fdlibm_icl6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl6_d\fdlibm_icl6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl6_d\fdlibm_icl6_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl6_d\fdlibm_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_icl6"
# PROP BASE Intermediate_Dir "msvc6prj_icl6\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_icl6"
# PROP Intermediate_Dir "msvc6prj_icl6\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_icl6\fdlibm_icl6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_icl6\fdlibm_icl6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl6\fdlibm_icl6_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl6\fdlibm_icl6_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_icl6_sd"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_icl6_sd"
# PROP Intermediate_Dir "msvc6prj_icl6_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl6_sd\fdlibm_icl6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_icl6_sd\fdlibm_icl6_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl6_sd\fdlibm_icl6_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl6_sd\fdlibm_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 icl6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_icl6_s"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_icl6_s"
# PROP Intermediate_Dir "msvc6prj_icl6_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_icl6_s\fdlibm_icl6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_icl6_s\fdlibm_icl6_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_icl6_s\fdlibm_icl6_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_icl6_s\fdlibm_icl6_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_d"
# PROP BASE Intermediate_Dir "msvc6prj_d\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_d"
# PROP Intermediate_Dir "msvc6prj_d\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_d\fdlibm_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_d\fdlibm_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_d\fdlibm_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_d\fdlibm_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj"
# PROP BASE Intermediate_Dir "msvc6prj\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj"
# PROP Intermediate_Dir "msvc6prj\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj\fdlibm_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj\fdlibm_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj\fdlibm_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj\fdlibm_s.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "msvc6prj_sd"
# PROP BASE Intermediate_Dir "msvc6prj_sd\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "msvc6prj_sd"
# PROP Intermediate_Dir "msvc6prj_sd\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_sd\fdlibm_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MDd /Zi /Gm /GZ /Fdmsvc6prj_sd\fdlibm_sd.pdb /Od /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_sd\fdlibm_sd.lib"
# ADD LIB32 /nologo /out:"msvc6prj_sd\fdlibm_sd.lib"

!ELSEIF  "$(CFG)" == "fdlibm_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "msvc6prj_s"
# PROP BASE Intermediate_Dir "msvc6prj_s\fdlibm_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "msvc6prj_s"
# PROP Intermediate_Dir "msvc6prj_s\fdlibm_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /Fdmsvc6prj_s\fdlibm_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD CPP /nologo /FD /MD /Fdmsvc6prj_s\fdlibm_s.pdb /O2 /GR /EHsc /W1 /I "$(VCF_ROOT)\src" /D "WIN32" /D "_LIB" /D "_IEEE_LIBM" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"msvc6prj_s\fdlibm_s.lib"
# ADD LIB32 /nologo /out:"msvc6prj_s\fdlibm_s.lib"

!ENDIF

# Begin Target

# Name "fdlibm_lib - Win32 vc80 DLL Debug"
# Name "fdlibm_lib - Win32 vc80 DLL Release"
# Name "fdlibm_lib - Win32 vc80 LIB Debug"
# Name "fdlibm_lib - Win32 vc80 LIB Release"
# Name "fdlibm_lib - Win32 vc71 DLL Debug"
# Name "fdlibm_lib - Win32 vc71 DLL Release"
# Name "fdlibm_lib - Win32 vc71 LIB Debug"
# Name "fdlibm_lib - Win32 vc71 LIB Release"
# Name "fdlibm_lib - Win32 vc70 DLL Debug"
# Name "fdlibm_lib - Win32 vc70 DLL Release"
# Name "fdlibm_lib - Win32 vc70 LIB Debug"
# Name "fdlibm_lib - Win32 vc70 LIB Release"
# Name "fdlibm_lib - Win32 vc6 DLL Debug"
# Name "fdlibm_lib - Win32 vc6 DLL Release"
# Name "fdlibm_lib - Win32 vc6 LIB Debug"
# Name "fdlibm_lib - Win32 vc6 LIB Release"
# Name "fdlibm_lib - Win32 icl7 DLL Debug"
# Name "fdlibm_lib - Win32 icl7 DLL Release"
# Name "fdlibm_lib - Win32 icl7 LIB Debug"
# Name "fdlibm_lib - Win32 icl7 LIB Release"
# Name "fdlibm_lib - Win32 icl6 DLL Debug"
# Name "fdlibm_lib - Win32 icl6 DLL Release"
# Name "fdlibm_lib - Win32 icl6 LIB Debug"
# Name "fdlibm_lib - Win32 icl6 LIB Release"
# Name "fdlibm_lib - Win32 DLL Debug"
# Name "fdlibm_lib - Win32 DLL Release"
# Name "fdlibm_lib - Win32 LIB Debug"
# Name "fdlibm_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_acos.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_acosh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_asin.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_atan2.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_atanh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_cosh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_exp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_fmod.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_gamma.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_gamma_r.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_hypot.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_j0.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_j1.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_jn.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_lgamma.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_lgamma_r.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_log.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_log10.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_pow.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_rem_pio2.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_remainder.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_scalb.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_sinh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\e_sqrt.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\k_cos.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\k_rem_pio2.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\k_sin.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\k_standard.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\k_tan.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_asinh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_atan.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_cbrt.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_ceil.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_copysign.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_cos.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_erf.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_expm1.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_fabs.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_finite.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_floor.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_frexp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_ilogb.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_isnan.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_ldexp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_lib_version.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_log1p.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_logb.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_matherr.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_modf.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_nextafter.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_rint.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_scalbn.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_signgam.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_significand.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_sin.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_tan.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\s_tanh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_acos.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_acosh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_asin.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_atan2.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_atanh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_cosh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_exp.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_fmod.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_gamma.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_gamma_r.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_hypot.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_j0.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_j1.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_jn.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_lgamma.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_lgamma_r.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_log.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_log10.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_pow.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_remainder.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_scalb.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_sinh.c
# End Source File
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\w_sqrt.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\js-impl\fdlibm\fdlibm.h
# End Source File
# End Group
# End Target
# End Project
