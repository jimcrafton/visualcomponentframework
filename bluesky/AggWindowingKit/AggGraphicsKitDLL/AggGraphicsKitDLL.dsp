# Microsoft Developer Studio Project File - Name="AggGraphicsKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AggGraphicsKitDLL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AggGraphicsKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AggGraphicsKitDLL.mak" CFG="AggGraphicsKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AggGraphicsKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AggGraphicsKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AggGraphicsKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AGGGRAPHICSKITDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AGGGRAPHICSKITDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "AggGraphicsKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AGGGRAPHICSKITDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "../" /I "$(VCF_ROOT)/src/thirdparty/common/agg/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FOUNDATIONKIT_DLL" /D "AGG_GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /D "VCF_AGG" /D "GRAPHICSKIT_DLL" /Yu"vcf/GraphicsKit/GraphicsKit.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\AggGraphicsKit_vc6_d.dll" /implib:"../AggGraphicsKit_vc6_d.lib" /pdbtype:sept /libpath:"$(VCF_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "AggGraphicsKitDLL - Win32 Release"
# Name "AggGraphicsKitDLL - Win32 Debug"
# Begin Group "Peers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\vcf\src\thirdparty\common\agg\src\agg_font_win32_tt.cpp

!IF  "$(CFG)" == "AggGraphicsKitDLL - Win32 Release"

!ELSEIF  "$(CFG)" == "AggGraphicsKitDLL - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AggGraphicsPeers.cpp
# End Source File
# Begin Source File

SOURCE=..\AggGraphicsPeers.h
# End Source File
# Begin Source File

SOURCE=..\AggGraphicsToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\AggGraphicsToolkit.h
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\AbstractImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\AbstractImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\AggCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BasicFill.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BasicFill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BasicRectangle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BasicStroke.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BasicStroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BezierCurve.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\BezierCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Circle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Color.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Contextpeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\DrawUIState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Fill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\FontPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GradientFills.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GrayScaleImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GrayScaleImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\ApplicationKit\ImageList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\ImageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\JPEGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\JPEGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Matrix2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Matrix2D.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\MatrixFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PixelFormats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Pixels.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PNGLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PNGLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Point.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Printable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PrintContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PrintEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PrintSession.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\PrintSessionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Rect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Size.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\Stroke.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsKit.cpp
# ADD CPP /Yc"vcf/GraphicsKit/GraphicsKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsToolKit.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\vcf\src\vcf\GraphicsKit\GraphicsToolKit.h
# End Source File
# End Group
# End Target
# End Project
