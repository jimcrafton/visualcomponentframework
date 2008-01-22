# Microsoft Developer Studio Project File - Name="VCF_libxslt_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libxslt_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_libxslt_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_libxslt_lib.mak" CFG="libxslt_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libxslt_lib - Win32 vc90 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc90 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxslt_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libxslt_lib - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc90_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc90_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc80_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc71_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc70_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_vc6_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_s.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxslt_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_sd.lib"

!ELSEIF  "$(CFG)" == "libxslt_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\libxslt_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\libxslt_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\src\thirdparty\common\libxslt" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxslt_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxslt_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxslt_s.lib"

!ENDIF

# Begin Target

# Name "libxslt_lib - Win32 vc90 DLL Debug"
# Name "libxslt_lib - Win32 vc90 DLL Release"
# Name "libxslt_lib - Win32 vc90 LIB Debug"
# Name "libxslt_lib - Win32 vc90 LIB Release"
# Name "libxslt_lib - Win32 vc80 DLL Debug"
# Name "libxslt_lib - Win32 vc80 DLL Release"
# Name "libxslt_lib - Win32 vc80 LIB Debug"
# Name "libxslt_lib - Win32 vc80 LIB Release"
# Name "libxslt_lib - Win32 vc71 DLL Debug"
# Name "libxslt_lib - Win32 vc71 DLL Release"
# Name "libxslt_lib - Win32 vc71 LIB Debug"
# Name "libxslt_lib - Win32 vc71 LIB Release"
# Name "libxslt_lib - Win32 vc70 DLL Debug"
# Name "libxslt_lib - Win32 vc70 DLL Release"
# Name "libxslt_lib - Win32 vc70 LIB Debug"
# Name "libxslt_lib - Win32 vc70 LIB Release"
# Name "libxslt_lib - Win32 vc6 DLL Debug"
# Name "libxslt_lib - Win32 vc6 DLL Release"
# Name "libxslt_lib - Win32 vc6 LIB Debug"
# Name "libxslt_lib - Win32 vc6 LIB Release"
# Name "libxslt_lib - Win32 DLL Debug"
# Name "libxslt_lib - Win32 DLL Release"
# Name "libxslt_lib - Win32 LIB Debug"
# Name "libxslt_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attributes.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attrvt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\documents.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extensions.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extra.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\functions.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\imports.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\keys.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\namespaces.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\numbers.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\pattern.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\preproc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\security.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\templates.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\transform.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\variables.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xslt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltutils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\attributes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\documents.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extensions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\extra.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\functions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\imports.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\keys.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\libxslt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\namespaces.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\numbersInternals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\preproc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\security.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\templates.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\transform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\trio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\triodef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\variables.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\win32config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xslt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltInternals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltexports.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltutils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxslt\libxslt\xsltwin32config.h
# End Source File
# End Group
# End Target
# End Project

