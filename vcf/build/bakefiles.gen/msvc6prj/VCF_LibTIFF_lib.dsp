# Microsoft Developer Studio Project File - Name="VCF_LibTIFF_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=LibTIFF_lib - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_LibTIFF_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_LibTIFF_lib.mak" CFG="LibTIFF_lib - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibTIFF_lib - Win32 vc6 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 vc6 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "LibTIFF_lib - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibTIFF_lib - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_vc6_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_vc6_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_s.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_vc6_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_vc6_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_vc6_s.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_sd.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_s.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\LibTIFF_sd.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_sd.lib"

!ELSEIF  "$(CFG)" == "LibTIFF_lib - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\LibTIFF_lib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\LibTIFF_lib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\LibTIFF_s.pdb /D "WIN32" /D "_LIB" /D "USE_WIN32_FILEIO" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\LibTIFF_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\LibTIFF_s.lib"

!ENDIF

# Begin Target

# Name "LibTIFF_lib - Win32 vc6 DLL Debug"
# Name "LibTIFF_lib - Win32 vc6 DLL Release"
# Name "LibTIFF_lib - Win32 vc6 LIB Debug"
# Name "LibTIFF_lib - Win32 vc6 LIB Release"
# Name "LibTIFF_lib - Win32 DLL Debug"
# Name "LibTIFF_lib - Win32 DLL Release"
# Name "LibTIFF_lib - Win32 LIB Debug"
# Name "LibTIFF_lib - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_aux.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_close.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_codec.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_color.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_compress.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dir.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dirinfo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dirread.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dirwrite.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dumpmode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_error.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_extension.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_fax3.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_fax3sm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_flush.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_getimage.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_jpeg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_luv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_lzw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_next.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_ojpeg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_open.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_packbits.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_pixarlog.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_predict.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_print.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_read.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_stream.cxx
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_strip.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_swab.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_thunder.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_tile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_version.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_warning.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_win32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_write.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_zip.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\t4.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_dir.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_fax3.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tif_predict.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tiff.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tiffconf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tiffio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\tiffiop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\thirdparty\common\LibTIFF\uvcode.h
# End Source File
# End Group
# End Target
# End Project

