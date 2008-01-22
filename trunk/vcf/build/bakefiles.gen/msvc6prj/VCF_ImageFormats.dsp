# Microsoft Developer Studio Project File - Name="VCF_ImageFormats" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ImageFormats - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ImageFormats.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_ImageFormats.mak" CFG="ImageFormats - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageFormats - Win32 vc90 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc90 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImageFormats - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageFormats - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageFormats - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc90_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc90_sd.lib LibPNG_vc90_sd.lib LibJPEG_vc90_sd.lib AGG_vc90_sd.lib FoundationKit_vc90_d.lib GraphicsKit_vc90_d.lib ApplicationKit_vc90_d.lib ..\..\..\lib\AGG_vc90_sd.lib ..\..\..\lib\ZLib_vc90_sd.lib ..\..\..\lib\LibJPEG_vc90_sd.lib ..\..\..\lib\LibPNG_vc90_sd.lib ..\..\..\lib\LibTIFF_vc90_sd.lib ..\..\..\lib\paintlib_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc90_d.lib" /debug
# ADD LINK32 ZLib_vc90_sd.lib LibPNG_vc90_sd.lib LibJPEG_vc90_sd.lib AGG_vc90_sd.lib FoundationKit_vc90_d.lib GraphicsKit_vc90_d.lib ApplicationKit_vc90_d.lib ..\..\..\lib\AGG_vc90_sd.lib ..\..\..\lib\ZLib_vc90_sd.lib ..\..\..\lib\LibJPEG_vc90_sd.lib ..\..\..\lib\LibPNG_vc90_sd.lib ..\..\..\lib\LibTIFF_vc90_sd.lib ..\..\..\lib\paintlib_vc90_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc90_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc90.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc90_s.lib LibPNG_vc90_s.lib LibJPEG_vc90_s.lib AGG_vc90_s.lib FoundationKit_vc90.lib GraphicsKit_vc90.lib ApplicationKit_vc90.lib ..\..\..\lib\AGG_vc90_s.lib ..\..\..\lib\ZLib_vc90_s.lib ..\..\..\lib\LibJPEG_vc90_s.lib ..\..\..\lib\LibPNG_vc90_s.lib ..\..\..\lib\LibTIFF_vc90_s.lib ..\..\..\lib\paintlib_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc90.lib"
# ADD LINK32 ZLib_vc90_s.lib LibPNG_vc90_s.lib LibJPEG_vc90_s.lib AGG_vc90_s.lib FoundationKit_vc90.lib GraphicsKit_vc90.lib ApplicationKit_vc90.lib ..\..\..\lib\AGG_vc90_s.lib ..\..\..\lib\ZLib_vc90_s.lib ..\..\..\lib\LibJPEG_vc90_s.lib ..\..\..\lib\LibPNG_vc90_s.lib ..\..\..\lib\LibTIFF_vc90_s.lib ..\..\..\lib\paintlib_vc90_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc90.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc90_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc90_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc90_s.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc80_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc80_sd.lib LibPNG_vc80_sd.lib LibJPEG_vc80_sd.lib AGG_vc80_sd.lib FoundationKit_vc80_d.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib ..\..\..\lib\AGG_vc80_sd.lib ..\..\..\lib\ZLib_vc80_sd.lib ..\..\..\lib\LibJPEG_vc80_sd.lib ..\..\..\lib\LibPNG_vc80_sd.lib ..\..\..\lib\LibTIFF_vc80_sd.lib ..\..\..\lib\paintlib_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc80_d.lib" /debug
# ADD LINK32 ZLib_vc80_sd.lib LibPNG_vc80_sd.lib LibJPEG_vc80_sd.lib AGG_vc80_sd.lib FoundationKit_vc80_d.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib ..\..\..\lib\AGG_vc80_sd.lib ..\..\..\lib\ZLib_vc80_sd.lib ..\..\..\lib\LibJPEG_vc80_sd.lib ..\..\..\lib\LibPNG_vc80_sd.lib ..\..\..\lib\LibTIFF_vc80_sd.lib ..\..\..\lib\paintlib_vc80_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc80.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc80_s.lib LibPNG_vc80_s.lib LibJPEG_vc80_s.lib AGG_vc80_s.lib FoundationKit_vc80.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib ..\..\..\lib\AGG_vc80_s.lib ..\..\..\lib\ZLib_vc80_s.lib ..\..\..\lib\LibJPEG_vc80_s.lib ..\..\..\lib\LibPNG_vc80_s.lib ..\..\..\lib\LibTIFF_vc80_s.lib ..\..\..\lib\paintlib_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc80.lib"
# ADD LINK32 ZLib_vc80_s.lib LibPNG_vc80_s.lib LibJPEG_vc80_s.lib AGG_vc80_s.lib FoundationKit_vc80.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib ..\..\..\lib\AGG_vc80_s.lib ..\..\..\lib\ZLib_vc80_s.lib ..\..\..\lib\LibJPEG_vc80_s.lib ..\..\..\lib\LibPNG_vc80_s.lib ..\..\..\lib\LibTIFF_vc80_s.lib ..\..\..\lib\paintlib_vc80_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc80.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc80_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc80_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc80_s.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc71_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc71_sd.lib LibPNG_vc71_sd.lib LibJPEG_vc71_sd.lib AGG_vc71_sd.lib FoundationKit_vc71_d.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib ..\..\..\lib\AGG_vc71_sd.lib ..\..\..\lib\ZLib_vc71_sd.lib ..\..\..\lib\LibJPEG_vc71_sd.lib ..\..\..\lib\LibPNG_vc71_sd.lib ..\..\..\lib\LibTIFF_vc71_sd.lib ..\..\..\lib\paintlib_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc71_d.lib" /debug
# ADD LINK32 ZLib_vc71_sd.lib LibPNG_vc71_sd.lib LibJPEG_vc71_sd.lib AGG_vc71_sd.lib FoundationKit_vc71_d.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib ..\..\..\lib\AGG_vc71_sd.lib ..\..\..\lib\ZLib_vc71_sd.lib ..\..\..\lib\LibJPEG_vc71_sd.lib ..\..\..\lib\LibPNG_vc71_sd.lib ..\..\..\lib\LibTIFF_vc71_sd.lib ..\..\..\lib\paintlib_vc71_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc71.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc71_s.lib LibPNG_vc71_s.lib LibJPEG_vc71_s.lib AGG_vc71_s.lib FoundationKit_vc71.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib ..\..\..\lib\AGG_vc71_s.lib ..\..\..\lib\ZLib_vc71_s.lib ..\..\..\lib\LibJPEG_vc71_s.lib ..\..\..\lib\LibPNG_vc71_s.lib ..\..\..\lib\LibTIFF_vc71_s.lib ..\..\..\lib\paintlib_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc71.lib"
# ADD LINK32 ZLib_vc71_s.lib LibPNG_vc71_s.lib LibJPEG_vc71_s.lib AGG_vc71_s.lib FoundationKit_vc71.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib ..\..\..\lib\AGG_vc71_s.lib ..\..\..\lib\ZLib_vc71_s.lib ..\..\..\lib\LibJPEG_vc71_s.lib ..\..\..\lib\LibPNG_vc71_s.lib ..\..\..\lib\LibTIFF_vc71_s.lib ..\..\..\lib\paintlib_vc71_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc71.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc71_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc71_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc71_s.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc70_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc70_sd.lib LibPNG_vc70_sd.lib LibJPEG_vc70_sd.lib AGG_vc70_sd.lib FoundationKit_vc70_d.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib ..\..\..\lib\AGG_vc70_sd.lib ..\..\..\lib\ZLib_vc70_sd.lib ..\..\..\lib\LibJPEG_vc70_sd.lib ..\..\..\lib\LibPNG_vc70_sd.lib ..\..\..\lib\LibTIFF_vc70_sd.lib ..\..\..\lib\paintlib_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc70_d.lib" /debug
# ADD LINK32 ZLib_vc70_sd.lib LibPNG_vc70_sd.lib LibJPEG_vc70_sd.lib AGG_vc70_sd.lib FoundationKit_vc70_d.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib ..\..\..\lib\AGG_vc70_sd.lib ..\..\..\lib\ZLib_vc70_sd.lib ..\..\..\lib\LibJPEG_vc70_sd.lib ..\..\..\lib\LibPNG_vc70_sd.lib ..\..\..\lib\LibTIFF_vc70_sd.lib ..\..\..\lib\paintlib_vc70_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc70.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc70_s.lib LibPNG_vc70_s.lib LibJPEG_vc70_s.lib AGG_vc70_s.lib FoundationKit_vc70.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib ..\..\..\lib\AGG_vc70_s.lib ..\..\..\lib\ZLib_vc70_s.lib ..\..\..\lib\LibJPEG_vc70_s.lib ..\..\..\lib\LibPNG_vc70_s.lib ..\..\..\lib\LibTIFF_vc70_s.lib ..\..\..\lib\paintlib_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc70.lib"
# ADD LINK32 ZLib_vc70_s.lib LibPNG_vc70_s.lib LibJPEG_vc70_s.lib AGG_vc70_s.lib FoundationKit_vc70.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib ..\..\..\lib\AGG_vc70_s.lib ..\..\..\lib\ZLib_vc70_s.lib ..\..\..\lib\LibJPEG_vc70_s.lib ..\..\..\lib\LibPNG_vc70_s.lib ..\..\..\lib\LibTIFF_vc70_s.lib ..\..\..\lib\paintlib_vc70_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc70.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc70_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc70_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc70_s.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_vc6_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib ..\..\..\lib\AGG_vc6_sd.lib ..\..\..\lib\ZLib_vc6_sd.lib ..\..\..\lib\LibJPEG_vc6_sd.lib ..\..\..\lib\LibPNG_vc6_sd.lib ..\..\..\lib\LibTIFF_vc6_sd.lib ..\..\..\lib\paintlib_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc6_d.lib" /debug
# ADD LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib ..\..\..\lib\AGG_vc6_sd.lib ..\..\..\lib\ZLib_vc6_sd.lib ..\..\..\lib\LibJPEG_vc6_sd.lib ..\..\..\lib\LibPNG_vc6_sd.lib ..\..\..\lib\LibTIFF_vc6_sd.lib ..\..\..\lib\paintlib_vc6_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats_vc6.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib ..\..\..\lib\AGG_vc6_s.lib ..\..\..\lib\ZLib_vc6_s.lib ..\..\..\lib\LibJPEG_vc6_s.lib ..\..\..\lib\LibPNG_vc6_s.lib ..\..\..\lib\LibTIFF_vc6_s.lib ..\..\..\lib\paintlib_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc6.lib"
# ADD LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib ..\..\..\lib\AGG_vc6_s.lib ..\..\..\lib\ZLib_vc6_s.lib ..\..\..\lib\LibJPEG_vc6_s.lib ..\..\..\lib\LibPNG_vc6_s.lib ..\..\..\lib\LibTIFF_vc6_s.lib ..\..\..\lib\paintlib_vc6_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_vc6.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_vc6_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_vc6_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_vc6_s.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\ImageFormats_d.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib ..\..\..\lib\AGG_sd.lib ..\..\..\lib\ZLib_sd.lib ..\..\..\lib\LibJPEG_sd.lib ..\..\..\lib\LibPNG_sd.lib ..\..\..\lib\LibTIFF_sd.lib ..\..\..\lib\paintlib_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_d.lib" /debug
# ADD LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib ..\..\..\lib\AGG_sd.lib ..\..\..\lib\ZLib_sd.lib ..\..\..\lib\LibJPEG_sd.lib ..\..\..\lib\LibPNG_sd.lib ..\..\..\lib\LibTIFF_sd.lib ..\..\..\lib\paintlib_sd.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats_d.lib" /debug

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\ImageFormats.pdb /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "IMAGEFORMATS_DLL" /D "IMAGEFORMATS_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "IMAGEFORMATS_DLL" /d IMAGEFORMATS_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib ..\..\..\lib\AGG_s.lib ..\..\..\lib\ZLib_s.lib ..\..\..\lib\LibJPEG_s.lib ..\..\..\lib\LibPNG_s.lib ..\..\..\lib\LibTIFF_s.lib ..\..\..\lib\paintlib_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats.lib"
# ADD LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib ..\..\..\lib\AGG_s.lib ..\..\..\lib\ZLib_s.lib ..\..\..\lib\LibJPEG_s.lib ..\..\..\lib\LibPNG_s.lib ..\..\..\lib\LibTIFF_s.lib ..\..\..\lib\paintlib_s.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\ImageFormats.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\ImageFormats.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\ImageFormats_sd.pdb /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_sd.lib"

!ELSEIF  "$(CFG)" == "ImageFormats - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\ImageFormats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\ImageFormats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\ImageFormats_s.pdb /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\ImageFormats_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\ImageFormats_s.lib"

!ENDIF

# Begin Target

# Name "ImageFormats - Win32 vc90 DLL Debug"
# Name "ImageFormats - Win32 vc90 DLL Release"
# Name "ImageFormats - Win32 vc90 LIB Debug"
# Name "ImageFormats - Win32 vc90 LIB Release"
# Name "ImageFormats - Win32 vc80 DLL Debug"
# Name "ImageFormats - Win32 vc80 DLL Release"
# Name "ImageFormats - Win32 vc80 LIB Debug"
# Name "ImageFormats - Win32 vc80 LIB Release"
# Name "ImageFormats - Win32 vc71 DLL Debug"
# Name "ImageFormats - Win32 vc71 DLL Release"
# Name "ImageFormats - Win32 vc71 LIB Debug"
# Name "ImageFormats - Win32 vc71 LIB Release"
# Name "ImageFormats - Win32 vc70 DLL Debug"
# Name "ImageFormats - Win32 vc70 DLL Release"
# Name "ImageFormats - Win32 vc70 LIB Debug"
# Name "ImageFormats - Win32 vc70 LIB Release"
# Name "ImageFormats - Win32 vc6 DLL Debug"
# Name "ImageFormats - Win32 vc6 DLL Release"
# Name "ImageFormats - Win32 vc6 LIB Debug"
# Name "ImageFormats - Win32 vc6 LIB Release"
# Name "ImageFormats - Win32 DLL Debug"
# Name "ImageFormats - Win32 DLL Release"
# Name "ImageFormats - Win32 LIB Debug"
# Name "ImageFormats - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\ImageFormats\ImageFormats.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\ImageFormats\ImageFormats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImageFormats\ImageFormatsSelectLib.h
# End Source File
# End Group
# End Target
# End Project

