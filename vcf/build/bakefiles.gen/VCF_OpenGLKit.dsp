# Microsoft Developer Studio Project File - Name="VCF_OpenGLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenGLKit - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_OpenGLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_OpenGLKit.mak" CFG="OpenGLKit - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenGLKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc80 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc80 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc71 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc71 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc70 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc70 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 vc6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 vc6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 icl7 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 icl7 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 icl7 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 icl7 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 icl6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 icl6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 icl6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 icl6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenGLKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "OpenGLKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenGLKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc80_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_d\OpenGLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc80_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_d\OpenGLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib libAGG_vc80_sd.lib ZLib_vc80_sd.lib LibJPEG_vc80_sd.lib LibPNG_vc80_sd.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc80_d.lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib libAGG_vc80_sd.lib ZLib_vc80_sd.lib LibJPEG_vc80_sd.lib LibPNG_vc80_sd.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc80.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80\OpenGLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc80.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80\OpenGLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib libAGG_vc80_s.lib ZLib_vc80_s.lib LibJPEG_vc80_s.lib LibPNG_vc80_s.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc80.lib"
# ADD LINK32 FoundationKit_vc80.lib libAGG_vc80_s.lib ZLib_vc80_s.lib LibJPEG_vc80_s.lib LibPNG_vc80_s.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc80.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc80_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_sd\OpenGLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc80_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_sd\OpenGLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc80 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc80_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_s\OpenGLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc80_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc80_s\OpenGLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc71_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_d\OpenGLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc71_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_d\OpenGLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib libAGG_vc71_sd.lib ZLib_vc71_sd.lib LibJPEG_vc71_sd.lib LibPNG_vc71_sd.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc71_d.lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib libAGG_vc71_sd.lib ZLib_vc71_sd.lib LibJPEG_vc71_sd.lib LibPNG_vc71_sd.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc71.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71\OpenGLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc71.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71\OpenGLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib libAGG_vc71_s.lib ZLib_vc71_s.lib LibJPEG_vc71_s.lib LibPNG_vc71_s.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc71.lib"
# ADD LINK32 FoundationKit_vc71.lib libAGG_vc71_s.lib ZLib_vc71_s.lib LibJPEG_vc71_s.lib LibPNG_vc71_s.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc71.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc71_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_sd\OpenGLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc71_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_sd\OpenGLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc71 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc71_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_s\OpenGLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc71_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc71_s\OpenGLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc70_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_d\OpenGLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc70_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_d\OpenGLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib libAGG_vc70_sd.lib ZLib_vc70_sd.lib LibJPEG_vc70_sd.lib LibPNG_vc70_sd.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc70_d.lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib libAGG_vc70_sd.lib ZLib_vc70_sd.lib LibJPEG_vc70_sd.lib LibPNG_vc70_sd.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc70.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70\OpenGLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc70.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70\OpenGLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib libAGG_vc70_s.lib ZLib_vc70_s.lib LibJPEG_vc70_s.lib LibPNG_vc70_s.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc70.lib"
# ADD LINK32 FoundationKit_vc70.lib libAGG_vc70_s.lib ZLib_vc70_s.lib LibJPEG_vc70_s.lib LibPNG_vc70_s.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc70.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc70_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_sd\OpenGLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc70_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_sd\OpenGLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc70 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc70_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_s\OpenGLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc70_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc70_s\OpenGLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_vc6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_d\OpenGLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib libAGG_vc6_sd.lib ZLib_vc6_sd.lib LibJPEG_vc6_sd.lib LibPNG_vc6_sd.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc6_d.lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib libAGG_vc6_sd.lib ZLib_vc6_sd.lib LibJPEG_vc6_sd.lib LibPNG_vc6_sd.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6\OpenGLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_vc6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6\OpenGLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib libAGG_vc6_s.lib ZLib_vc6_s.lib LibJPEG_vc6_s.lib LibPNG_vc6_s.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc6.lib"
# ADD LINK32 FoundationKit_vc6.lib libAGG_vc6_s.lib ZLib_vc6_s.lib LibJPEG_vc6_s.lib LibPNG_vc6_s.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_vc6.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_vc6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_sd\OpenGLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 vc6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_s\OpenGLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_vc6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_vc6_s\OpenGLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_icl7_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_d\OpenGLKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_icl7_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_d\OpenGLKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7_d.lib libAGG_icl7_sd.lib ZLib_icl7_sd.lib LibJPEG_icl7_sd.lib LibPNG_icl7_sd.lib GraphicsKit_icl7_d.lib ApplicationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl7_d.lib" /debug
# ADD LINK32 FoundationKit_icl7_d.lib libAGG_icl7_sd.lib ZLib_icl7_sd.lib LibJPEG_icl7_sd.lib LibPNG_icl7_sd.lib GraphicsKit_icl7_d.lib ApplicationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl7_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_icl7.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7\OpenGLKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_icl7.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7\OpenGLKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7.lib libAGG_icl7_s.lib ZLib_icl7_s.lib LibJPEG_icl7_s.lib LibPNG_icl7_s.lib GraphicsKit_icl7.lib ApplicationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl7.lib"
# ADD LINK32 FoundationKit_icl7.lib libAGG_icl7_s.lib ZLib_icl7_s.lib LibJPEG_icl7_s.lib LibPNG_icl7_s.lib GraphicsKit_icl7.lib ApplicationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl7.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl7 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_icl7_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_sd\OpenGLKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_icl7_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_sd\OpenGLKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl7 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_icl7_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_s\OpenGLKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_icl7_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl7_s\OpenGLKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl7_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_icl6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_d\OpenGLKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_icl6_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_d\OpenGLKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6_d.lib libAGG_icl6_sd.lib ZLib_icl6_sd.lib LibJPEG_icl6_sd.lib LibPNG_icl6_sd.lib GraphicsKit_icl6_d.lib ApplicationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl6_d.lib" /debug
# ADD LINK32 FoundationKit_icl6_d.lib libAGG_icl6_sd.lib ZLib_icl6_sd.lib LibJPEG_icl6_sd.lib LibPNG_icl6_sd.lib GraphicsKit_icl6_d.lib ApplicationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl6_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_icl6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6\OpenGLKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit_icl6.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6\OpenGLKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6.lib libAGG_icl6_s.lib ZLib_icl6_s.lib LibJPEG_icl6_s.lib LibPNG_icl6_s.lib GraphicsKit_icl6.lib ApplicationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl6.lib"
# ADD LINK32 FoundationKit_icl6.lib libAGG_icl6_s.lib ZLib_icl6_s.lib LibJPEG_icl6_s.lib LibPNG_icl6_s.lib GraphicsKit_icl6.lib ApplicationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_icl6.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_icl6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_sd\OpenGLKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_icl6_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_sd\OpenGLKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 icl6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_icl6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_s\OpenGLKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_icl6_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_icl6_s\OpenGLKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_icl6_s.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_d\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_d\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\OpenGLKit_d.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_d\OpenGLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib libAGG_sd.lib ZLib_sd.lib LibJPEG_sd.lib LibPNG_sd.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_d.lib" /debug
# ADD LINK32 FoundationKit_d.lib libAGG_sd.lib ZLib_sd.lib LibJPEG_sd.lib LibPNG_sd.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj\OpenGLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\OpenGLKit.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj\OpenGLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "OPENGLKIT_DLL" /D "OPENGLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
# ADD RSC /l 0x409 /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "OPENGLKIT_DLL" /d OPENGLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib libAGG_s.lib ZLib_s.lib LibJPEG_s.lib LibPNG_s.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit.lib"
# ADD LINK32 FoundationKit.lib libAGG_s.lib ZLib_s.lib LibJPEG_s.lib LibPNG_s.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\OpenGLKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\OpenGLKit.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_sd\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_sd\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\OpenGLKit_sd.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_sd\OpenGLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_sd.lib"

!ELSEIF  "$(CFG)" == "OpenGLKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_s\OpenGLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_s\OpenGLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_s\OpenGLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\OpenGLKit_s.pdb /Yu"vcf\OpenGLKit\OpenGLKit.h" /Fp"msvc6prj_s\OpenGLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\OpenGLKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\OpenGLKit_s.lib"

!ENDIF

# Begin Target

# Name "OpenGLKit - Win32 vc80 DLL Debug"
# Name "OpenGLKit - Win32 vc80 DLL Release"
# Name "OpenGLKit - Win32 vc80 Debug"
# Name "OpenGLKit - Win32 vc80 Release"
# Name "OpenGLKit - Win32 vc71 DLL Debug"
# Name "OpenGLKit - Win32 vc71 DLL Release"
# Name "OpenGLKit - Win32 vc71 Debug"
# Name "OpenGLKit - Win32 vc71 Release"
# Name "OpenGLKit - Win32 vc70 DLL Debug"
# Name "OpenGLKit - Win32 vc70 DLL Release"
# Name "OpenGLKit - Win32 vc70 Debug"
# Name "OpenGLKit - Win32 vc70 Release"
# Name "OpenGLKit - Win32 vc6 DLL Debug"
# Name "OpenGLKit - Win32 vc6 DLL Release"
# Name "OpenGLKit - Win32 vc6 Debug"
# Name "OpenGLKit - Win32 vc6 Release"
# Name "OpenGLKit - Win32 icl7 DLL Debug"
# Name "OpenGLKit - Win32 icl7 DLL Release"
# Name "OpenGLKit - Win32 icl7 Debug"
# Name "OpenGLKit - Win32 icl7 Release"
# Name "OpenGLKit - Win32 icl6 DLL Debug"
# Name "OpenGLKit - Win32 icl6 DLL Release"
# Name "OpenGLKit - Win32 icl6 Debug"
# Name "OpenGLKit - Win32 icl6 Release"
# Name "OpenGLKit - Win32 DLL Debug"
# Name "OpenGLKit - Win32 DLL Release"
# Name "OpenGLKit - Win32 Debug"
# Name "OpenGLKit - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLToolkit.cpp
# ADD BASE CPP /Yc"vcf\OpenGLKit\OpenGLKit.h"
# ADD CPP /Yc"vcf\OpenGLKit\OpenGLKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\Win32OpenGLPeer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLControl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLKit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\OpenGLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\VCFOpenGL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\OpenGLKit\Win32OpenGLPeer.h
# End Source File
# End Group
# End Target
# End Project

