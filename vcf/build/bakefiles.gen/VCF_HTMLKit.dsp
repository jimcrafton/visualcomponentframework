# Microsoft Developer Studio Project File - Name="VCF_HTMLKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=HTMLKit - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCF_HTMLKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCF_HTMLKit.mak" CFG="HTMLKit - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HTMLKit - Win32 vc80 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc80 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc80 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc80 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc71 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc71 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc71 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc71 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc70 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc70 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc70 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc70 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 vc6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 vc6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 icl7 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 icl7 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 icl7 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 icl7 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 icl6 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 icl6 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 icl6 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 icl6 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 DLL Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 DLL Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HTMLKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "HTMLKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HTMLKit - Win32 vc80 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc80_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_d\HTMLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc80_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_d\HTMLKit_vc80_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80_d.lib libAGG_vc80_sd.lib ZLib_vc80_sd.lib LibJPEG_vc80_sd.lib LibPNG_vc80_sd.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc80_d.lib" /debug
# ADD LINK32 FoundationKit_vc80_d.lib libAGG_vc80_sd.lib ZLib_vc80_sd.lib LibJPEG_vc80_sd.lib LibPNG_vc80_sd.lib GraphicsKit_vc80_d.lib ApplicationKit_vc80_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc80_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc80_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc80 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc80.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80\HTMLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc80.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80\HTMLKit_vc80.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc80.lib libAGG_vc80_s.lib ZLib_vc80_s.lib LibJPEG_vc80_s.lib LibPNG_vc80_s.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc80.lib"
# ADD LINK32 FoundationKit_vc80.lib libAGG_vc80_s.lib ZLib_vc80_s.lib LibJPEG_vc80_s.lib LibPNG_vc80_s.lib GraphicsKit_vc80.lib ApplicationKit_vc80.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc80.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc80.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc80 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc80_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_sd\HTMLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc80_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_sd\HTMLKit_vc80_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc80_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc80_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc80 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc80_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc80_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc80_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_s\HTMLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc80_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc80_s\HTMLKit_vc80_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc80_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc80_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc71 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc71_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_d\HTMLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc71_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_d\HTMLKit_vc71_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71_d.lib libAGG_vc71_sd.lib ZLib_vc71_sd.lib LibJPEG_vc71_sd.lib LibPNG_vc71_sd.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc71_d.lib" /debug
# ADD LINK32 FoundationKit_vc71_d.lib libAGG_vc71_sd.lib ZLib_vc71_sd.lib LibJPEG_vc71_sd.lib LibPNG_vc71_sd.lib GraphicsKit_vc71_d.lib ApplicationKit_vc71_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc71_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc71_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc71 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc71.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71\HTMLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc71.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71\HTMLKit_vc71.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc71.lib libAGG_vc71_s.lib ZLib_vc71_s.lib LibJPEG_vc71_s.lib LibPNG_vc71_s.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc71.lib"
# ADD LINK32 FoundationKit_vc71.lib libAGG_vc71_s.lib ZLib_vc71_s.lib LibJPEG_vc71_s.lib LibPNG_vc71_s.lib GraphicsKit_vc71.lib ApplicationKit_vc71.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc71.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc71.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc71 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc71_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_sd\HTMLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc71_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_sd\HTMLKit_vc71_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc71_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc71_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc71 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc71_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc71_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc71_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_s\HTMLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc71_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc71_s\HTMLKit_vc71_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc71_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc71_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc70 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc70_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_d\HTMLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc70_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_d\HTMLKit_vc70_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70_d.lib libAGG_vc70_sd.lib ZLib_vc70_sd.lib LibJPEG_vc70_sd.lib LibPNG_vc70_sd.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc70_d.lib" /debug
# ADD LINK32 FoundationKit_vc70_d.lib libAGG_vc70_sd.lib ZLib_vc70_sd.lib LibJPEG_vc70_sd.lib LibPNG_vc70_sd.lib GraphicsKit_vc70_d.lib ApplicationKit_vc70_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc70_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc70_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc70 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc70.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70\HTMLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc70.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70\HTMLKit_vc70.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc70.lib libAGG_vc70_s.lib ZLib_vc70_s.lib LibJPEG_vc70_s.lib LibPNG_vc70_s.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc70.lib"
# ADD LINK32 FoundationKit_vc70.lib libAGG_vc70_s.lib ZLib_vc70_s.lib LibJPEG_vc70_s.lib LibPNG_vc70_s.lib GraphicsKit_vc70.lib ApplicationKit_vc70.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc70.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc70.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc70 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc70_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_sd\HTMLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc70_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_sd\HTMLKit_vc70_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc70_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc70_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc70 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc70_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc70_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc70_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_s\HTMLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc70_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc70_s\HTMLKit_vc70_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc70_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc70_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc6_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_d\HTMLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_vc6_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_d\HTMLKit_vc6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6_d.lib libAGG_vc6_sd.lib ZLib_vc6_sd.lib LibJPEG_vc6_sd.lib LibPNG_vc6_sd.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc6_d.lib" /debug
# ADD LINK32 FoundationKit_vc6_d.lib libAGG_vc6_sd.lib ZLib_vc6_sd.lib LibJPEG_vc6_sd.lib LibPNG_vc6_sd.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc6_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc6.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6\HTMLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_vc6.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6\HTMLKit_vc6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_vc6.lib libAGG_vc6_s.lib ZLib_vc6_s.lib LibJPEG_vc6_s.lib LibPNG_vc6_s.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc6.lib"
# ADD LINK32 FoundationKit_vc6.lib libAGG_vc6_s.lib ZLib_vc6_s.lib LibJPEG_vc6_s.lib LibPNG_vc6_s.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_vc6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_vc6.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc6_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_sd\HTMLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_vc6_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_sd\HTMLKit_vc6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc6_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 vc6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_vc6_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_vc6_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc6_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_s\HTMLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_vc6_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_vc6_s\HTMLKit_vc6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_vc6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl7 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_icl7_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_d\HTMLKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_icl7_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_d\HTMLKit_icl7_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7_d.lib libAGG_icl7_sd.lib ZLib_icl7_sd.lib LibJPEG_icl7_sd.lib LibPNG_icl7_sd.lib GraphicsKit_icl7_d.lib ApplicationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl7_d.lib" /debug
# ADD LINK32 FoundationKit_icl7_d.lib libAGG_icl7_sd.lib ZLib_icl7_sd.lib LibJPEG_icl7_sd.lib LibPNG_icl7_sd.lib GraphicsKit_icl7_d.lib ApplicationKit_icl7_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl7_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl7_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl7 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_icl7.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7\HTMLKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_icl7.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7\HTMLKit_icl7.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl7.lib libAGG_icl7_s.lib ZLib_icl7_s.lib LibJPEG_icl7_s.lib LibPNG_icl7_s.lib GraphicsKit_icl7.lib ApplicationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl7.lib"
# ADD LINK32 FoundationKit_icl7.lib libAGG_icl7_s.lib ZLib_icl7_s.lib LibJPEG_icl7_s.lib LibPNG_icl7_s.lib GraphicsKit_icl7.lib ApplicationKit_icl7.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl7.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl7.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl7 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_icl7_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_sd\HTMLKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_icl7_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_sd\HTMLKit_icl7_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_icl7_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_icl7_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl7 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl7_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl7_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_icl7_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_s\HTMLKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_icl7_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl7_s\HTMLKit_icl7_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_icl7_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_icl7_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_icl6_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_d\HTMLKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_icl6_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_d\HTMLKit_icl6_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6_d.lib libAGG_icl6_sd.lib ZLib_icl6_sd.lib LibJPEG_icl6_sd.lib LibPNG_icl6_sd.lib GraphicsKit_icl6_d.lib ApplicationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl6_d.lib" /debug
# ADD LINK32 FoundationKit_icl6_d.lib libAGG_icl6_sd.lib ZLib_icl6_sd.lib LibJPEG_icl6_sd.lib LibPNG_icl6_sd.lib GraphicsKit_icl6_d.lib ApplicationKit_icl6_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl6_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl6_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_icl6.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6\HTMLKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit_icl6.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6\HTMLKit_icl6.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_icl6.lib libAGG_icl6_s.lib ZLib_icl6_s.lib LibJPEG_icl6_s.lib LibPNG_icl6_s.lib GraphicsKit_icl6.lib ApplicationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl6.lib"
# ADD LINK32 FoundationKit_icl6.lib libAGG_icl6_s.lib ZLib_icl6_s.lib LibJPEG_icl6_s.lib LibPNG_icl6_s.lib GraphicsKit_icl6.lib ApplicationKit_icl6.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_icl6.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_icl6.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl6 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_icl6_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_sd\HTMLKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_icl6_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_sd\HTMLKit_icl6_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_icl6_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_icl6_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 icl6 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_icl6_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_icl6_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_icl6_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_s\HTMLKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_icl6_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_icl6_s\HTMLKit_icl6_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_icl6_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_icl6_s.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_d\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_d\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_d\HTMLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\..\bin\HTMLKit_d.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_d\HTMLKit_d.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "_DEBUG" /d "_DEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit_d.lib libAGG_sd.lib ZLib_sd.lib LibJPEG_sd.lib LibPNG_sd.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_d.lib" /debug
# ADD LINK32 FoundationKit_d.lib libAGG_sd.lib ZLib_sd.lib LibJPEG_sd.lib LibPNG_sd.lib GraphicsKit_d.lib ApplicationKit_d.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit_d.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit_d.lib" /debug

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj\HTMLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\..\bin\HTMLKit.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj\HTMLKit.pch" /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_USRDLL" /D "DLL_EXPORTS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_USRDLL" /D "HTMLKIT_DLL" /D "HTMLKIT_EXPORTS" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
# ADD RSC /l 0x409 /i "..\..\src\thirdparty\win32" /d "FOUNDATIONKIT_DLL" /i "..\..\src\thirdparty\common\agg\include" /i "..\..\src\thirdparty\common\ZLib" /i "..\..\src\thirdparty\common\LibJPEG" /i "..\..\src\thirdparty\common\LibPNG" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "NDEBUG" /d "VCF_DISABLE_PRAGMA_LINKING" /d "_WINDOWS" /d "_WIN32" /d "WIN32" /d "_CRT_SECURE_NO_DEPRECATE" /d "_SCL_SECURE_NO_DEPRECATE" /d "_CRT_NON_CONFORMING_SWPRINTFS" /i "..\..\src" /d "_USRDLL" /d "HTMLKIT_DLL" /d HTMLKIT_EXPORTS
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 FoundationKit.lib libAGG_s.lib ZLib_s.lib LibJPEG_s.lib LibPNG_s.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit.lib"
# ADD LINK32 FoundationKit.lib libAGG_s.lib ZLib_s.lib LibJPEG_s.lib LibPNG_s.lib GraphicsKit.lib ApplicationKit.lib rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib oleacc.lib urlmon.lib /nologo /dll /machine:i386 /out:"..\..\lib\..\bin\HTMLKit.dll" /libpath:"..\..\lib" /implib:"..\..\lib\HTMLKit.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_sd\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_sd\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_sd\HTMLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MDd /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /Od /GR /EHsc /W1 /I "..\..\src" /Zi /Gm /GZ /Fd..\..\lib\HTMLKit_sd.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_sd\HTMLKit_sd.pch" /D "WIN32" /D "_LIB" /D "_DEBUG" /D "_DEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_sd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_sd.lib"

!ELSEIF  "$(CFG)" == "HTMLKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\lib"
# PROP BASE Intermediate_Dir "msvc6prj_s\HTMLKit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\lib"
# PROP Intermediate_Dir "msvc6prj_s\HTMLKit"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_s\HTMLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD CPP /nologo /FD /MD /I "..\..\src\thirdparty\win32" /I "..\..\src\thirdparty\common\agg\include" /I "..\..\src\thirdparty\common\ZLib" /I "..\..\src\thirdparty\common\LibJPEG" /I "..\..\src\thirdparty\common\LibPNG" /O2 /GR /EHsc /W1 /I "..\..\src" /Fd..\..\lib\HTMLKit_s.pdb /Yu"vcf\HTMLKit\HTMLKit.h" /Fp"msvc6prj_s\HTMLKit_s.pch" /D "WIN32" /D "_LIB" /D "NDEBUG" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "_WIN32" /D "WIN32" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_CRT_NON_CONFORMING_SWPRINTFS" /D "_LIB" /D "_MBCS" /D "NO_MFC" /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\HTMLKit_s.lib"
# ADD LIB32 /nologo /out:"..\..\lib\HTMLKit_s.lib"

!ENDIF

# Begin Target

# Name "HTMLKit - Win32 vc80 DLL Debug"
# Name "HTMLKit - Win32 vc80 DLL Release"
# Name "HTMLKit - Win32 vc80 Debug"
# Name "HTMLKit - Win32 vc80 Release"
# Name "HTMLKit - Win32 vc71 DLL Debug"
# Name "HTMLKit - Win32 vc71 DLL Release"
# Name "HTMLKit - Win32 vc71 Debug"
# Name "HTMLKit - Win32 vc71 Release"
# Name "HTMLKit - Win32 vc70 DLL Debug"
# Name "HTMLKit - Win32 vc70 DLL Release"
# Name "HTMLKit - Win32 vc70 Debug"
# Name "HTMLKit - Win32 vc70 Release"
# Name "HTMLKit - Win32 vc6 DLL Debug"
# Name "HTMLKit - Win32 vc6 DLL Release"
# Name "HTMLKit - Win32 vc6 Debug"
# Name "HTMLKit - Win32 vc6 Release"
# Name "HTMLKit - Win32 icl7 DLL Debug"
# Name "HTMLKit - Win32 icl7 DLL Release"
# Name "HTMLKit - Win32 icl7 Debug"
# Name "HTMLKit - Win32 icl7 Release"
# Name "HTMLKit - Win32 icl6 DLL Debug"
# Name "HTMLKit - Win32 icl6 DLL Release"
# Name "HTMLKit - Win32 icl6 Debug"
# Name "HTMLKit - Win32 icl6 Release"
# Name "HTMLKit - Win32 DLL Debug"
# Name "HTMLKit - Win32 DLL Release"
# Name "HTMLKit - Win32 Debug"
# Name "HTMLKit - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLBrowserControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLToolkit.cpp
# ADD BASE CPP /Yc"vcf\HTMLKit\HTMLKit.h"
# ADD CPP /Yc"vcf\HTMLKit\HTMLKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLBrowser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLDOMElements.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLToolkit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLBrowserControl.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLBrowserPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLDOMElements.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLKit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\HTMLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLBrowser.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLDOMElements.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32HTMLToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vcf\HTMLKit\Win32WebBrowserHost.h
# End Source File
# End Group
# End Target
# End Project

