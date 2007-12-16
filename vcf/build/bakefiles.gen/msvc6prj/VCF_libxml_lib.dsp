# Microsoft Developer Studio Project File - Name="VCF_libxml_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libxml_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_libxml_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_libxml_lib.mak" CFG="libxml_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libxml_lib - Win32 vc80 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc80 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc71 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc71 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc70 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc70 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libxml_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libxml_lib - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc80_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc80_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc71_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc71_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc70_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc70_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_vc6_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_vc6_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_s.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\libxml\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\libxml_sd.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_sd.lib"

!ELSEIF  "$(CFG)" == "libxml_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\libxml_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\libxml_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\libxml\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\libxml_s.pdb /D "WIN32" /D "_LIB" /D "LIBXML_STATIC" /D "HAVE_WIN32_THREADS" /D "HAVE_COMPILER_TLS" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\libxml_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\libxml_s.lib"

!ENDIF

# Begin Target

# Name "libxml_lib - Win32 vc80 DLL Debug"
# Name "libxml_lib - Win32 vc80 DLL Release"
# Name "libxml_lib - Win32 vc80 LIB Debug"
# Name "libxml_lib - Win32 vc80 LIB Release"
# Name "libxml_lib - Win32 vc71 DLL Debug"
# Name "libxml_lib - Win32 vc71 DLL Release"
# Name "libxml_lib - Win32 vc71 LIB Debug"
# Name "libxml_lib - Win32 vc71 LIB Release"
# Name "libxml_lib - Win32 vc70 DLL Debug"
# Name "libxml_lib - Win32 vc70 DLL Release"
# Name "libxml_lib - Win32 vc70 LIB Debug"
# Name "libxml_lib - Win32 vc70 LIB Release"
# Name "libxml_lib - Win32 vc6 DLL Debug"
# Name "libxml_lib - Win32 vc6 DLL Release"
# Name "libxml_lib - Win32 vc6 LIB Debug"
# Name "libxml_lib - Win32 vc6 LIB Release"
# Name "libxml_lib - Win32 DLL Debug"
# Name "libxml_lib - Win32 DLL Release"
# Name "libxml_lib - Win32 LIB Debug"
# Name "libxml_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\DOCBparser.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLparser.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\HTMLtree.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\SAX2.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\c14n.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\catalog.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\chvalid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\debugXML.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\dict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\encoding.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\entities.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\error.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\globals.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\hash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\legacy.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\list.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanoftp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\nanohttp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parser.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\parserInternals.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\pattern.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\relaxng.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\schematron.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\threads.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\tree.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\trio.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\trionan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\triostr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\uri.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\valid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xinclude.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xlink.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlIO.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmemory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlmodule.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlreader.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlregexp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlsave.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemas.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlschemastypes.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlstring.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlunicode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xmlwriter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpath.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\xpointer.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\DOCBparser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\HTMLparser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\HTMLtree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\SAX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\SAX2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\c14n.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\catalog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\chvalid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\debugXML.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\dict.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\elfgcchack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\encoding.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\entities.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\globals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\hash.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\libxml.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\list.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\nanoftp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\nanohttp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\parserInternals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\pattern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\relaxng.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\schemasInternals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\schematron.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\threads.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\tree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\trio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\triodef.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\trionan.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\triop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\triostr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\uri.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\valid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\win32config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\wsockcompat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xinclude.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xlink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlautomata.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlerror.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlexports.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlmemory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlmodule.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlreader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlregexp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlsave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlschemas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlschemastypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlstring.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlunicode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlversion.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xmlwriter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xpath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xpathInternals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\libxml\include\libxml\xpointer.h
# End Source File
# End Group
# End Target
# End Project

