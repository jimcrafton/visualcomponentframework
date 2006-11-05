# Microsoft Developer Studio Project File - Name="VCF_oniguruma_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=oniguruma_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_oniguruma_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_oniguruma_lib.mak" CFG="oniguruma_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oniguruma_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl7 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl7 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl7 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl7 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 icl6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "oniguruma_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oniguruma_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc80_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc80_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc80_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc71_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc71_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc71_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc70_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc70_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc70_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_vc6_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_vc6_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_vc6_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl7_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl7_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl7\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl7\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl7 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl7_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl7_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl7_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl7 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl7_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl7_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl7_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl7_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl6_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl6_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl6\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl6\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl6_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl6_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_icl6_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 icl6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_icl6_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_icl6_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_icl6_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_icl6_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_d\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_d\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_s.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_sd\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_sd\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\oniguruma" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\oniguruma_sd.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_sd.lib"

!ELSEIF  "$(CFG)" == "oniguruma_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "..\..\lib\msvc6prj_s\oniguruma_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "..\..\lib\msvc6prj_s\oniguruma_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\oniguruma" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\oniguruma_s.pdb /D "WIN32" /D "_LIB" /D "NOT_RUBY" /D ONIG_EXTERN=extern /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WIN32" /D "WIN32" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\oniguruma_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\oniguruma_s.lib"

!ENDIF

# Begin Target

# Name "oniguruma_lib - Win32 vc80 DLL Debug"
# Name "oniguruma_lib - Win32 vc80 DLL Release"
# Name "oniguruma_lib - Win32 vc80 LIB Debug"
# Name "oniguruma_lib - Win32 vc80 LIB Release"
# Name "oniguruma_lib - Win32 vc71 DLL Debug"
# Name "oniguruma_lib - Win32 vc71 DLL Release"
# Name "oniguruma_lib - Win32 vc71 LIB Debug"
# Name "oniguruma_lib - Win32 vc71 LIB Release"
# Name "oniguruma_lib - Win32 vc70 DLL Debug"
# Name "oniguruma_lib - Win32 vc70 DLL Release"
# Name "oniguruma_lib - Win32 vc70 LIB Debug"
# Name "oniguruma_lib - Win32 vc70 LIB Release"
# Name "oniguruma_lib - Win32 vc6 DLL Debug"
# Name "oniguruma_lib - Win32 vc6 DLL Release"
# Name "oniguruma_lib - Win32 vc6 LIB Debug"
# Name "oniguruma_lib - Win32 vc6 LIB Release"
# Name "oniguruma_lib - Win32 icl7 DLL Debug"
# Name "oniguruma_lib - Win32 icl7 DLL Release"
# Name "oniguruma_lib - Win32 icl7 LIB Debug"
# Name "oniguruma_lib - Win32 icl7 LIB Release"
# Name "oniguruma_lib - Win32 icl6 DLL Debug"
# Name "oniguruma_lib - Win32 icl6 DLL Release"
# Name "oniguruma_lib - Win32 icl6 LIB Debug"
# Name "oniguruma_lib - Win32 icl6 LIB Release"
# Name "oniguruma_lib - Win32 DLL Debug"
# Name "oniguruma_lib - Win32 DLL Release"
# Name "oniguruma_lib - Win32 LIB Debug"
# Name "oniguruma_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\ascii.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\big5.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\euc_jp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\euc_kr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\euc_tw.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\gb18030.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_1.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_10.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_11.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_13.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_14.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_15.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_16.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_3.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_4.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_5.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_6.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_7.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_8.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\iso8859_9.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\koi8.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\koi8_r.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regcomp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regenc.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regerror.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regexec.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regext.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\reggnu.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regparse.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regposerr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regposix.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regsyntax.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regtrav.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regversion.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\sjis.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\st.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\unicode.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\utf16_be.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\utf16_le.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\utf32_be.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\utf32_le.c
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\enc\utf8.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\oniggnu.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\onigposix.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\oniguruma.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regenc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regint.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\regparse.h
# End Source File
# Begin Source File

SOURCE=..\..\src\thirdparty\common\oniguruma\st.h
# End Source File
# End Group
# End Target
# End Project

