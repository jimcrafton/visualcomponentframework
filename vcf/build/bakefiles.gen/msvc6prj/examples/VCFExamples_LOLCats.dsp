# Microsoft Developer Studio Project File - Name="VCFExamples_LOLCats" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=LOLCats - Win32 LIB Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_LOLCats.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VCFExamples_LOLCats.mak" CFG="LOLCats - Win32 LIB Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LOLCats - Win32 vc6 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 vc6 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 vc6 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 vc6 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 DLL Debug" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 DLL Release" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 LIB Debug" (based on "Win32 (x86) Application")
!MESSAGE "LOLCats - Win32 LIB Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LOLCats - Win32 vc6 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_d\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_d.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_d.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib HTMLKit_vc6_d.lib libxml_vc6_sd.lib libxslt_vc6_sd.lib FoundationKit_vc6_d.lib XMLKit_vc6_d.lib FoundationKit_vc6_d.lib InternetKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_d.lib GraphicsKit_vc6_d.lib ApplicationKit_vc6_d.lib HTMLKit_vc6_d.lib libxml_vc6_sd.lib libxslt_vc6_sd.lib FoundationKit_vc6_d.lib XMLKit_vc6_d.lib FoundationKit_vc6_d.lib InternetKit_vc6_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_d.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 vc6 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib HTMLKit_vc6.lib libxml_vc6_s.lib libxslt_vc6_s.lib FoundationKit_vc6.lib XMLKit_vc6.lib FoundationKit_vc6.lib InternetKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6.lib GraphicsKit_vc6.lib ApplicationKit_vc6.lib HTMLKit_vc6.lib libxml_vc6_s.lib libxslt_vc6_s.lib FoundationKit_vc6.lib XMLKit_vc6.lib FoundationKit_vc6.lib InternetKit_vc6.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 vc6 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_sd\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib HTMLKit_vc6_sd.lib libxml_vc6_sd.lib libxslt_vc6_sd.lib FoundationKit_vc6_sd.lib XMLKit_vc6_sd.lib FoundationKit_vc6_sd.lib InternetKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib ZLib_vc6_sd.lib LibPNG_vc6_sd.lib LibJPEG_vc6_sd.lib AGG_vc6_sd.lib FoundationKit_vc6_sd.lib GraphicsKit_vc6_sd.lib ApplicationKit_vc6_sd.lib HTMLKit_vc6_sd.lib libxml_vc6_sd.lib libxslt_vc6_sd.lib FoundationKit_vc6_sd.lib XMLKit_vc6_sd.lib FoundationKit_vc6_sd.lib InternetKit_vc6_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_sd.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 vc6 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_vc6_s\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_s.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_vc6_s.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib HTMLKit_vc6_s.lib libxml_vc6_s.lib libxslt_vc6_s.lib FoundationKit_vc6_s.lib XMLKit_vc6_s.lib FoundationKit_vc6_s.lib InternetKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib ZLib_vc6_s.lib LibPNG_vc6_s.lib LibJPEG_vc6_s.lib AGG_vc6_s.lib FoundationKit_vc6_s.lib GraphicsKit_vc6_s.lib ApplicationKit_vc6_s.lib HTMLKit_vc6_s.lib libxml_vc6_s.lib libxslt_vc6_s.lib FoundationKit_vc6_s.lib XMLKit_vc6_s.lib FoundationKit_vc6_s.lib InternetKit_vc6_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_vc6_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_vc6_s.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_d\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_d.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_d.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib HTMLKit_d.lib libxml_sd.lib libxslt_sd.lib FoundationKit_d.lib XMLKit_d.lib FoundationKit_d.lib InternetKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_d.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_d.lib GraphicsKit_d.lib ApplicationKit_d.lib HTMLKit_d.lib libxml_sd.lib libxslt_sd.lib FoundationKit_d.lib XMLKit_d.lib FoundationKit_d.lib InternetKit_d.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_d.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_d.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "APPLICATIONKIT_DLL" /D "HTMLKIT_DLL" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /D "FOUNDATIONKIT_DLL" /D "XMLKIT_DLL" /D "FOUNDATIONKIT_DLL" /D "INTERNETKIT_DLL" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /d "FOUNDATIONKIT_DLL" /d "GRAPHICSKIT_DLL" /d "APPLICATIONKIT_DLL" /d "HTMLKIT_DLL" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d "LIBXSLT_STATIC" /d "FOUNDATIONKIT_DLL" /d "XMLKIT_DLL" /d "FOUNDATIONKIT_DLL" /d INTERNETKIT_DLL
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib HTMLKit.lib libxml_s.lib libxslt_s.lib FoundationKit.lib XMLKit.lib FoundationKit.lib InternetKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit.lib GraphicsKit.lib ApplicationKit.lib HTMLKit.lib libxml_s.lib libxslt_s.lib FoundationKit.lib XMLKit.lib FoundationKit.lib InternetKit.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_sd\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_sd.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD CPP /nologo /FD /MDd /Od /Gm /GR /EHsc /W1 /I "..\..\..\..\src" /Zi /Fd..\..\..\..\examples\LOLCats\LOLCats_sd.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD BASE MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "_DEBUG" /D "_DEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
# ADD RSC /l 0x409 /d "_DEBUG" /d "_DEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib HTMLKit_sd.lib libxml_sd.lib libxslt_sd.lib FoundationKit_sd.lib XMLKit_sd.lib FoundationKit_sd.lib InternetKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_sd.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib ZLib_sd.lib LibPNG_sd.lib LibJPEG_sd.lib AGG_sd.lib FoundationKit_sd.lib GraphicsKit_sd.lib ApplicationKit_sd.lib HTMLKit_sd.lib libxml_sd.lib libxslt_sd.lib FoundationKit_sd.lib XMLKit_sd.lib FoundationKit_sd.lib InternetKit_sd.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_sd.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /debug /pdb:"..\..\..\..\examples\LOLCats\LOLCats_sd.pdb"

!ELSEIF  "$(CFG)" == "LOLCats - Win32 LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "..\..\..\..\examples\LOLCats"
# PROP BASE Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\LOLCats"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\examples\LOLCats"
# PROP Intermediate_Dir "..\..\..\..\lib\msvc6prj_s\LOLCats"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_s.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD CPP /nologo /FD /MD /O2 /GR /EHsc /W1 /I "..\..\..\..\src" /Fd..\..\..\..\examples\LOLCats\LOLCats_s.pdb /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\ZLib" /I "..\..\..\..\src\thirdparty\common\LibPNG" /I "..\..\..\..\src\thirdparty\common\LibJPEG" /I "..\..\..\..\src\thirdparty\common\agg\include" /I "..\..\..\..\src\thirdparty\common\libxml\include" /I "..\..\..\..\src\thirdparty\common\libxslt" /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /c
# ADD BASE MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD MTL /nologo /D "WIN32" /D "NDEBUG" /D "_WIN32" /D "WIN32" /D "VCF_DISABLE_PRAGMA_LINKING" /D "_WINDOWS" /D "LIBXML_STATIC" /D "LIBXML_STATIC" /D "LIBXSLT_STATIC" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
# ADD RSC /l 0x409 /d "NDEBUG" /d "_WIN32" /d "WIN32" /d "VCF_DISABLE_PRAGMA_LINKING" /i "..\..\..\..\src" /d "_WINDOWS" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\ZLib" /i "..\..\..\..\src\thirdparty\common\LibPNG" /i "..\..\..\..\src\thirdparty\common\LibJPEG" /i "..\..\..\..\src\thirdparty\common\agg\include" /i "..\..\..\..\src\thirdparty\common\libxml\include" /d "LIBXML_STATIC" /i "..\..\..\..\src\thirdparty\common\libxslt" /d "LIBXML_STATIC" /d LIBXSLT_STATIC
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib HTMLKit_s.lib libxml_s.lib libxslt_s.lib FoundationKit_s.lib XMLKit_s.lib FoundationKit_s.lib InternetKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_s.pdb"
# ADD LINK32 rpcrt4.lib odbc32.lib odbccp32.lib version.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib ws2_32.lib opengl32.lib glu32.lib shlwapi.lib imm32.lib oleacc.lib urlmon.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib ZLib_s.lib LibPNG_s.lib LibJPEG_s.lib AGG_s.lib FoundationKit_s.lib GraphicsKit_s.lib ApplicationKit_s.lib HTMLKit_s.lib libxml_s.lib libxslt_s.lib FoundationKit_s.lib XMLKit_s.lib FoundationKit_s.lib InternetKit_s.lib /nologo /machine:i386 /out:"..\..\..\..\examples\LOLCats\LOLCats_s.exe" /libpath:"..\..\..\..\lib" /subsystem:windows /ENTRY:"mainCRTStartup" /pdb:"..\..\..\..\examples\LOLCats\LOLCats_s.pdb"

!ENDIF

# Begin Target

# Name "LOLCats - Win32 vc6 DLL Debug"
# Name "LOLCats - Win32 vc6 DLL Release"
# Name "LOLCats - Win32 vc6 LIB Debug"
# Name "LOLCats - Win32 vc6 LIB Release"
# Name "LOLCats - Win32 DLL Debug"
# Name "LOLCats - Win32 DLL Release"
# Name "LOLCats - Win32 LIB Debug"
# Name "LOLCats - Win32 LIB Release"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\..\..\..\examples\LOLCats\LOLCats.cpp
# End Source File
# End Group
# End Target
# End Project

