# Microsoft Developer Studio Project File - Name="VCF_OpenGLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenGLKit - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_OpenGLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_OpenGLKit.mak" CFG="OpenGLKit - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGLKit - Win32 vc90 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc90 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc90 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc90 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc80 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc80 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc71 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc71 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc70 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc70 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc6 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc6 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 LIB Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 LIB Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenGLKit - Win32 vc90 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc90_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_d\OpenGLKit_vc90_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc90_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_d\OpenGLKit_vc90_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc90_sd.lib LibPNG_vc90_sd.lib LibJPEG_vc90_sd.lib AGG_vc90_sd.lib FoundationKit_vc90_d.lib GraphicsKit_vc90_d.lib ApplicationKit_vc90_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc90_d.lib" /debug
# ADD LINK32 ZLib_vc90_sd.lib LibPNG_vc90_sd.lib LibJPEG_vc90_sd.lib AGG_vc90_sd.lib FoundationKit_vc90_d.lib GraphicsKit_vc90_d.lib ApplicationKit_vc90_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc90_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc90_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc90 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc90.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90\OpenGLKit_vc90.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc90.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90\OpenGLKit_vc90.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc90_s.lib LibPNG_vc90_s.lib LibJPEG_vc90_s.lib AGG_vc90_s.lib FoundationKit_vc90.lib GraphicsKit_vc90.lib ApplicationKit_vc90.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc90.lib"
# ADD LINK32 ZLib_vc90_s.lib LibPNG_vc90_s.lib LibJPEG_vc90_s.lib AGG_vc90_s.lib FoundationKit_vc90.lib GraphicsKit_vc90.lib ApplicationKit_vc90.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc90.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc90.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc90 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc90_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_sd\OpenGLKit_vc90_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc90_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_sd\OpenGLKit_vc90_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc90_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc90_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc90 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc90_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc90_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_s\OpenGLKit_vc90_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc90_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc90_s\OpenGLKit_vc90_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc90_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc90_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc80_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_d\OpenGLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc80_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_d\OpenGLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc80_sd.lib LibPNG_vc80_sd.lib LibJPEG_vc80_sd.lib AGG_vc80_sd.lib FoundationKit_vc80_d.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc80_d.lib" /debug
# ADD LINK32 ZLib_vc80_sd.lib LibPNG_vc80_sd.lib LibJPEG_vc80_sd.lib AGG_vc80_sd.lib FoundationKit_vc80_d.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc80_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc80.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80\OpenGLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc80.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80\OpenGLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc80_s.lib LibPNG_vc80_s.lib LibJPEG_vc80_s.lib AGG_vc80_s.lib FoundationKit_vc80.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc80.lib"
# ADD LINK32 ZLib_vc80_s.lib LibPNG_vc80_s.lib LibJPEG_vc80_s.lib AGG_vc80_s.lib FoundationKit_vc80.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc80.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc80.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc80_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_sd\OpenGLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc80_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_sd\OpenGLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc80_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc80_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_s\OpenGLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc80_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc80_s\OpenGLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc71_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_d\OpenGLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc71_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_d\OpenGLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc71_sd.lib LibPNG_vc71_sd.lib LibJPEG_vc71_sd.lib AGG_vc71_sd.lib FoundationKit_vc71_d.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc71_d.lib" /debug
# ADD LINK32 ZLib_vc71_sd.lib LibPNG_vc71_sd.lib LibJPEG_vc71_sd.lib AGG_vc71_sd.lib FoundationKit_vc71_d.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc71_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc71.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71\OpenGLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc71.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71\OpenGLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc71_s.lib LibPNG_vc71_s.lib LibJPEG_vc71_s.lib AGG_vc71_s.lib FoundationKit_vc71.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc71.lib"
# ADD LINK32 ZLib_vc71_s.lib LibPNG_vc71_s.lib LibJPEG_vc71_s.lib AGG_vc71_s.lib FoundationKit_vc71.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc71.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc71.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc71_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_sd\OpenGLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc71_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_sd\OpenGLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc71_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc71_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_s\OpenGLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc71_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc71_s\OpenGLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc70_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_d\OpenGLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc70_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_d\OpenGLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc70_sd.lib LibPNG_vc70_sd.lib LibJPEG_vc70_sd.lib AGG_vc70_sd.lib FoundationKit_vc70_d.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc70_d.lib" /debug
# ADD LINK32 ZLib_vc70_sd.lib LibPNG_vc70_sd.lib LibJPEG_vc70_sd.lib AGG_vc70_sd.lib FoundationKit_vc70_d.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc70_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc70.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70\OpenGLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc70.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70\OpenGLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc70_s.lib LibPNG_vc70_s.lib LibJPEG_vc70_s.lib AGG_vc70_s.lib FoundationKit_vc70.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc70.lib"
# ADD LINK32 ZLib_vc70_s.lib LibPNG_vc70_s.lib LibJPEG_vc70_s.lib AGG_vc70_s.lib FoundationKit_vc70.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc70.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc70.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc70_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_sd\OpenGLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc70_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_sd\OpenGLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc70_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc70_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_s\OpenGLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc70_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc70_s\OpenGLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6_d.lib" /debug
# ADD LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\OpenGLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit_vc6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6\OpenGLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6.lib"
# ADD LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_vc6_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\OpenGLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_vc6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_s\OpenGLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_d.lib" /debug
# ADD LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj\OpenGLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\..\bin\OpenGLKit.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj\OpenGLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit.lib"
# ADD LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /GR /EHsc /W1 /I "..\..\..\src" /Zi /Gm /GZ /Fd..\..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\lib"
# PROP BASE Intermediate_Dir "..\..\..\lib\msvc6prj_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "..\..\..\lib\msvc6prj_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_s\OpenGLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MD /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /O2 /GR /EHsc /W1 /I "..\..\..\src" /Fd..\..\..\lib\OpenGLKit_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_s\OpenGLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\..\lib\OpenGLKit_s.lib"

!ENDIF

# Begin Target

# Name "OpenGLKit - Win32 vc90 DLL Debug"
# Name "OpenGLKit - Win32 vc90 DLL Release"
# Name "OpenGLKit - Win32 vc90 LIB Debug"
# Name "OpenGLKit - Win32 vc90 LIB Release"
# Name "OpenGLKit - Win32 vc80 DLL Debug"
# Name "OpenGLKit - Win32 vc80 DLL Release"
# Name "OpenGLKit - Win32 vc80 LIB Debug"
# Name "OpenGLKit - Win32 vc80 LIB Release"
# Name "OpenGLKit - Win32 vc71 DLL Debug"
# Name "OpenGLKit - Win32 vc71 DLL Release"
# Name "OpenGLKit - Win32 vc71 LIB Debug"
# Name "OpenGLKit - Win32 vc71 LIB Release"
# Name "OpenGLKit - Win32 vc70 DLL Debug"
# Name "OpenGLKit - Win32 vc70 DLL Release"
# Name "OpenGLKit - Win32 vc70 LIB Debug"
# Name "OpenGLKit - Win32 vc70 LIB Release"
# Name "OpenGLKit - Win32 vc6 DLL Debug"
# Name "OpenGLKit - Win32 vc6 DLL Release"
# Name "OpenGLKit - Win32 vc6 LIB Debug"
# Name "OpenGLKit - Win32 vc6 LIB Release"
# Name "OpenGLKit - Win32 DLL Debug"
# Name "OpenGLKit - Win32 DLL Release"
# Name "OpenGLKit - Win32 LIB Debug"
# Name "OpenGLKit - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLToolkit.cpp
# ADD BASE CPP /Yc"vcf\OpenGLKit\OpenGLKit.h"
# ADD CPP /Yc"vcf\OpenGLKit\OpenGLKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\Win32OpenGLPeer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\VCFOpenGL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\Win32OpenGLPeer.h
# End Source File
# End Group
# End Target
# End Project

