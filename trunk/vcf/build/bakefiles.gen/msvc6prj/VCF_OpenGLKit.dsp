# Microsoft Developer Studio Project File - Name="VCF_OpenGLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102
# TARGTYPE "Win32 (x86) Static Library" 0x0104

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

!IF  "$(CFG)" == "OpenGLKit - Win32 vc6 DLL Debug"

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
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb"
# ADD LINK32 ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6_d.lib" /debug /pdb:"..\..\..\lib\..\bin\OpenGLKit_vc6_d.pdb"

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
# ADD BASE LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\OpenGLKit_vc6.pdb"
# ADD LINK32 ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_vc6.lib" /pdb:"..\..\..\lib\..\bin\OpenGLKit_vc6.pdb"

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
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
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
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_USRDLL" /D "VCF_DISABLE_PRAGMA_LINKING" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "_USRDLL" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\src" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\OpenGLKit_d.pdb"
# ADD LINK32 ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit_d.lib" /debug /pdb:"..\..\..\lib\..\bin\OpenGLKit_d.pdb"

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
# ADD BASE LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit.lib" /pdb:"..\..\..\lib\..\bin\OpenGLKit.pdb"
# ADD LINK32 ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\..\lib" /implib:"..\..\..\lib\OpenGLKit.lib" /pdb:"..\..\..\lib\..\bin\OpenGLKit.pdb"

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
# ADD BASE CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
# ADD CPP /nologo /FD /MDd /I "..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\src\thirdparty\common\agg\include" /Od /Gm /GR /EHsc /W1 /I "..\..\..\src" /Zi /Fd..\..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"..\..\..\lib\msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "_LIB" /D "VCF_DISABLE_PRAGMA_LINKING" /c
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

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.cpp
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

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\OpenGLKit\OpenGLControl.h
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

