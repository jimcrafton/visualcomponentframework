# Microsoft Developer Studio Project File - Name="GraphicsKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GraphicsKitDLL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GraphicsKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GraphicsKitDLL.mak" CFG="GraphicsKitDLL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphicsKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GraphicsKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /Yu"vcf/GraphicsKit/GraphicsKit.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/GraphicsKit_vc6.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\..\bin\GraphicsKit_vc6.dll" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GraphicsKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /Fd"..\..\..\bin\GraphicsKit_vc6_d.pdb" /Yu"vcf/GraphicsKit/GraphicsKit.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/GraphicsKit_vc6_d.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /debug /machine:I386 /out:"..\..\..\bin\GraphicsKit_vc6_d.dll" /libpath:"..\..\..\lib"

!ENDIF 

# Begin Target

# Name "GraphicsKitDLL - Win32 Release"
# Name "GraphicsKitDLL - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.cpp
# ADD CPP /Yc"vcf/GraphicsKit/GraphicsKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.cpp
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter "h;hpp;hxx;hm;inl;cpp;c;cxx;rc;def;r;odl;idl;hpj"
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AggCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicRectangle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Circle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Contextpeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\DrawUIState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Fill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\FontPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GrayScaleImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageBits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\MatrixFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PixelFormats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Pixels.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Printable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSessionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Size.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Stroke.h
# End Source File
# End Group
# Begin Group "Peers"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32ThemeDLLWrapper.h
# End Source File
# End Group
# End Target
# End Project
