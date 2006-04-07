# Microsoft Developer Studio Project File - Name="VCF_FreeImage_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FreeImage_lib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_FreeImage_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_FreeImage_lib.mak" CFG="FreeImage_lib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FreeImage_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc80 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc80 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc71 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc71 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc70 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc70 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 vc6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl7 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl7 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl7 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl7 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 icl6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "FreeImage_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FreeImage_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc80 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc80 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc80_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc71 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc71 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc71_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc70 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc70 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc70_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 vc6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_vc6_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl7 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl7 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl7_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 icl6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_icl6_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_d\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_d\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_s.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_sd\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_sd\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\FreeImage_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_sd.lib"

!ELSEIF  "$(CFG)" == "FreeImage_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_s\FreeImage_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_s\FreeImage_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\FreeImage_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\FreeImage_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\FreeImage_s.lib"

!ENDIF

# Begin Target

# Name "FreeImage_lib - Win32 vc80 DLL Debug"
# Name "FreeImage_lib - Win32 vc80 DLL Release"
# Name "FreeImage_lib - Win32 vc80 Debug"
# Name "FreeImage_lib - Win32 vc80 Release"
# Name "FreeImage_lib - Win32 vc71 DLL Debug"
# Name "FreeImage_lib - Win32 vc71 DLL Release"
# Name "FreeImage_lib - Win32 vc71 Debug"
# Name "FreeImage_lib - Win32 vc71 Release"
# Name "FreeImage_lib - Win32 vc70 DLL Debug"
# Name "FreeImage_lib - Win32 vc70 DLL Release"
# Name "FreeImage_lib - Win32 vc70 Debug"
# Name "FreeImage_lib - Win32 vc70 Release"
# Name "FreeImage_lib - Win32 vc6 DLL Debug"
# Name "FreeImage_lib - Win32 vc6 DLL Release"
# Name "FreeImage_lib - Win32 vc6 Debug"
# Name "FreeImage_lib - Win32 vc6 Release"
# Name "FreeImage_lib - Win32 icl7 DLL Debug"
# Name "FreeImage_lib - Win32 icl7 DLL Release"
# Name "FreeImage_lib - Win32 icl7 Debug"
# Name "FreeImage_lib - Win32 icl7 Release"
# Name "FreeImage_lib - Win32 icl6 DLL Debug"
# Name "FreeImage_lib - Win32 icl6 DLL Release"
# Name "FreeImage_lib - Win32 icl6 Debug"
# Name "FreeImage_lib - Win32 icl6 Release"
# Name "FreeImage_lib - Win32 DLL Debug"
# Name "FreeImage_lib - Win32 DLL Release"
# Name "FreeImage_lib - Win32 Debug"
# Name "FreeImage_lib - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\BitmapAccess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion16_555.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion16_565.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion24.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Conversion8.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\FreeImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\FreeImageIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\GetType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\LoadFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\NNQuantizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\Plugin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginBMP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginICO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginIFF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginKOALA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginMNG.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginPCD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginPCX.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginPNM.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginPSD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginRAS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginTARGA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginTIFF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\PluginWBMP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage\WuQuantizer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImageIO.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\FreeImageSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\Plugin.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\Quantizers.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\FreeImage\Source\Utilities.h
# End Source File
# End Group
# End Target
# End Project

