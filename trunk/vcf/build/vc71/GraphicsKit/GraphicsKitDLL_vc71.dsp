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
# PROP Output_Dir "../../../lib/"
# PROP Intermediate_Dir "vc71/ReleaseDLL/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /I "$(VCF_INCLUDE)/../thirdparty/common/agg/include/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FRAMEWORK_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /D "BUILD_GRAPHICSKIT_LIB" /Yu"GraphicsKit.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/GraphicsKit_vc71.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../../bin/GraphicsKit_vc71.dll" /libpath:"../../../lib"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GraphicsKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "GraphicsKitDLL___Win32_Debug"
# PROP BASE Intermediate_Dir "GraphicsKitDLL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../lib/"
# PROP Intermediate_Dir "vc71/DebugDLL/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USE_FRAMEWORK_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /D "BUILD_GRAPHICSKIT_LIB" /Yu"GraphicsKit.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/GraphicsKit_vc71_d.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /profile /machine:I386 /out:"../../../bin/GraphicsKit_vc71_d.dll" /debug /libpath:"../../../lib"

!ENDIF 

# Begin Target

# Name "GraphicsKitDLL - Win32 Release"
# Name "GraphicsKitDLL - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=../../../include/graphics/AbstractImage.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/AggCommon.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Basic3DBorder.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/BasicFill.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/BasicRectangle.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/BasicStroke.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/BezierCurve.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Border.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Circle.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/ClippingRegion.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Color.h
# End Source File
# Begin Source File

SOURCE=../../../include/implementer/Contextpeer.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Ellipse.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Fill.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Filter.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Font.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/FontPeer.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Glyph.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/GlyphCollection.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/GraphicsContext.h
# End Source File
# Begin Source File

SOURCE=../../../include/GraphicsKit.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/GraphicsKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/GraphicsToolKit.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Image.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/ImageBits.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/ImageList.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/ImageLoader.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Matrix2D.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/MatrixFunction.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Path.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/PixelFormats.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/Point.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Printable.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/PrintContext.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/Rect.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/Size.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Stroke.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/VCFOpenGL.h
# End Source File
# Begin Source File

SOURCE=../../../include/graphics/Vector2D.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=../../../src/Graphics/AbstractImage.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/BasicFill.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/BasicStroke.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/graphics/BezierCurve.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/Color.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/Font.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/GlyphCollection.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/GraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/GraphicsKit.cpp
# ADD CPP /Yc"GraphicsKit.h"
# End Source File
# Begin Source File

SOURCE=../../../include/GraphicsKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/GraphicsToolKit.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Events/ImageEvent.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/Matrix2D.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/core/Point.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/core/Rect.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/Graphics/Vector2D.cpp
# End Source File
# End Group
# Begin Group "Peers"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Context.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Context.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Font.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Font.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32FontManager.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32GraphicsToolkit.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32GraphicsToolkit.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Image.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Image.h
# End Source File
# Begin Source File

SOURCE=../../../include/implementerkit/Win32OpenGLPeer.h
# End Source File
# End Group
# End Target
# End Project
