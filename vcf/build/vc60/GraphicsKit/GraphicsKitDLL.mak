# Microsoft Developer Studio Generated NMAKE File, Based on GraphicsKitDLL.dsp
!IF "$(CFG)" == ""
CFG=GraphicsKitDLL - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GraphicsKitDLL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GraphicsKitDLL - Win32 Release" && "$(CFG)" != "GraphicsKitDLL - Win32 Debug" && "$(CFG)" != "GraphicsKitDLL - Win32 Fake Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GraphicsKitDLL.mak" CFG="GraphicsKitDLL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphicsKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GraphicsKitDLL - Win32 Fake Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "GraphicsKitDLL - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseDLL\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\GraphicsKitDLL.dll"


CLEAN :
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\AlphaGamma.obj"
	-@erase "$(INTDIR)\ArtStroke.obj"
	-@erase "$(INTDIR)\BasicFill.obj"
	-@erase "$(INTDIR)\BasicStroke.obj"
	-@erase "$(INTDIR)\Color.obj"
	-@erase "$(INTDIR)\DrawToolkit.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontState.obj"
	-@erase "$(INTDIR)\GlyphCollection.obj"
	-@erase "$(INTDIR)\GraphicsContext.obj"
	-@erase "$(INTDIR)\GraphicsKit.obj"
	-@erase "$(INTDIR)\GraphicsObject.obj"
	-@erase "$(INTDIR)\ImageEvent.obj"
	-@erase "$(INTDIR)\ImageList.obj"
	-@erase "$(INTDIR)\ImageListEvent.obj"
	-@erase "$(INTDIR)\Matrix2D.obj"
	-@erase "$(INTDIR)\MicroTiles.obj"
	-@erase "$(INTDIR)\OpenGLContext.obj"
	-@erase "$(INTDIR)\PixelBuffer.obj"
	-@erase "$(INTDIR)\Polygon.obj"
	-@erase "$(INTDIR)\RenderPaths.obj"
	-@erase "$(INTDIR)\UIGraphicsToolKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vector2D.obj"
	-@erase "$(INTDIR)\Win32Context.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32FontManager.obj"
	-@erase "$(INTDIR)\Win32Image.obj"
	-@erase "$(INTDIR)\Win32OpenGLPeer.obj"
	-@erase "$(OUTDIR)\GraphicsKitDLL.dll"
	-@erase "$(OUTDIR)\GraphicsKitDLL.exp"
	-@erase "$(OUTDIR)\GraphicsKitDLL.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GraphicsKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=FoundationKitDLL.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\GraphicsKitDLL.pdb" /machine:I386 /out:"$(OUTDIR)\GraphicsKitDLL.dll" /implib:"$(OUTDIR)\GraphicsKitDLL.lib" /libpath:"\vcf\lib" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\AlphaGamma.obj" \
	"$(INTDIR)\ArtStroke.obj" \
	"$(INTDIR)\BasicFill.obj" \
	"$(INTDIR)\BasicStroke.obj" \
	"$(INTDIR)\Color.obj" \
	"$(INTDIR)\DrawToolkit.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FontState.obj" \
	"$(INTDIR)\GlyphCollection.obj" \
	"$(INTDIR)\GraphicsContext.obj" \
	"$(INTDIR)\GraphicsKit.obj" \
	"$(INTDIR)\GraphicsObject.obj" \
	"$(INTDIR)\ImageEvent.obj" \
	"$(INTDIR)\ImageList.obj" \
	"$(INTDIR)\ImageListEvent.obj" \
	"$(INTDIR)\Matrix2D.obj" \
	"$(INTDIR)\MicroTiles.obj" \
	"$(INTDIR)\OpenGLContext.obj" \
	"$(INTDIR)\PixelBuffer.obj" \
	"$(INTDIR)\Polygon.obj" \
	"$(INTDIR)\RenderPaths.obj" \
	"$(INTDIR)\UIGraphicsToolKit.obj" \
	"$(INTDIR)\Vector2D.obj" \
	"$(INTDIR)\Win32Context.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32FontManager.obj" \
	"$(INTDIR)\Win32Image.obj" \
	"$(INTDIR)\Win32OpenGLPeer.obj"

"$(OUTDIR)\GraphicsKitDLL.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GraphicsKitDLL - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugDLL\obj

ALL : "..\..\..\Debug\GraphicsKitDLL_d.dll"


CLEAN :
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\AlphaGamma.obj"
	-@erase "$(INTDIR)\ArtStroke.obj"
	-@erase "$(INTDIR)\BasicFill.obj"
	-@erase "$(INTDIR)\BasicStroke.obj"
	-@erase "$(INTDIR)\Color.obj"
	-@erase "$(INTDIR)\DrawToolkit.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontState.obj"
	-@erase "$(INTDIR)\GlyphCollection.obj"
	-@erase "$(INTDIR)\GraphicsContext.obj"
	-@erase "$(INTDIR)\GraphicsKit.obj"
	-@erase "$(INTDIR)\GraphicsObject.obj"
	-@erase "$(INTDIR)\ImageEvent.obj"
	-@erase "$(INTDIR)\ImageList.obj"
	-@erase "$(INTDIR)\ImageListEvent.obj"
	-@erase "$(INTDIR)\Matrix2D.obj"
	-@erase "$(INTDIR)\MicroTiles.obj"
	-@erase "$(INTDIR)\OpenGLContext.obj"
	-@erase "$(INTDIR)\PixelBuffer.obj"
	-@erase "$(INTDIR)\Polygon.obj"
	-@erase "$(INTDIR)\RenderPaths.obj"
	-@erase "$(INTDIR)\UIGraphicsToolKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vector2D.obj"
	-@erase "$(INTDIR)\Win32Context.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32FontManager.obj"
	-@erase "$(INTDIR)\Win32Image.obj"
	-@erase "$(INTDIR)\Win32OpenGLPeer.obj"
	-@erase "$(OUTDIR)\GraphicsKitDLL_d.exp"
	-@erase "$(OUTDIR)\GraphicsKitDLL_d.lib"
	-@erase "$(OUTDIR)\GraphicsKitDLL_d.pdb"
	-@erase "..\..\..\Debug\GraphicsKitDLL_d.dll"
	-@erase "..\..\..\Debug\GraphicsKitDLL_d.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /I "..\..\..\libart" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /D "LIBART_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GraphicsKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=FoundationKitDLL_d.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\GraphicsKitDLL_d.pdb" /debug /machine:I386 /out:"..\..\..\Debug/GraphicsKitDLL_d.dll" /implib:"$(OUTDIR)\GraphicsKitDLL_d.lib" /pdbtype:sept /libpath:"..\..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\AlphaGamma.obj" \
	"$(INTDIR)\ArtStroke.obj" \
	"$(INTDIR)\BasicFill.obj" \
	"$(INTDIR)\BasicStroke.obj" \
	"$(INTDIR)\Color.obj" \
	"$(INTDIR)\DrawToolkit.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FontState.obj" \
	"$(INTDIR)\GlyphCollection.obj" \
	"$(INTDIR)\GraphicsContext.obj" \
	"$(INTDIR)\GraphicsKit.obj" \
	"$(INTDIR)\GraphicsObject.obj" \
	"$(INTDIR)\ImageEvent.obj" \
	"$(INTDIR)\ImageList.obj" \
	"$(INTDIR)\ImageListEvent.obj" \
	"$(INTDIR)\Matrix2D.obj" \
	"$(INTDIR)\MicroTiles.obj" \
	"$(INTDIR)\OpenGLContext.obj" \
	"$(INTDIR)\PixelBuffer.obj" \
	"$(INTDIR)\Polygon.obj" \
	"$(INTDIR)\RenderPaths.obj" \
	"$(INTDIR)\UIGraphicsToolKit.obj" \
	"$(INTDIR)\Vector2D.obj" \
	"$(INTDIR)\Win32Context.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32FontManager.obj" \
	"$(INTDIR)\Win32Image.obj" \
	"$(INTDIR)\Win32OpenGLPeer.obj"

"..\..\..\Debug\GraphicsKitDLL_d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GraphicsKitDLL - Win32 Fake Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\Fake_Debug
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

ALL : "$(OUTDIR)\GraphicsKitDLL.dll"


CLEAN :
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\AlphaGamma.obj"
	-@erase "$(INTDIR)\ArtStroke.obj"
	-@erase "$(INTDIR)\BasicFill.obj"
	-@erase "$(INTDIR)\BasicStroke.obj"
	-@erase "$(INTDIR)\Color.obj"
	-@erase "$(INTDIR)\DrawToolkit.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontState.obj"
	-@erase "$(INTDIR)\GlyphCollection.obj"
	-@erase "$(INTDIR)\GraphicsContext.obj"
	-@erase "$(INTDIR)\GraphicsKit.obj"
	-@erase "$(INTDIR)\GraphicsObject.obj"
	-@erase "$(INTDIR)\ImageEvent.obj"
	-@erase "$(INTDIR)\ImageList.obj"
	-@erase "$(INTDIR)\ImageListEvent.obj"
	-@erase "$(INTDIR)\Matrix2D.obj"
	-@erase "$(INTDIR)\MicroTiles.obj"
	-@erase "$(INTDIR)\OpenGLContext.obj"
	-@erase "$(INTDIR)\PixelBuffer.obj"
	-@erase "$(INTDIR)\Polygon.obj"
	-@erase "$(INTDIR)\RenderPaths.obj"
	-@erase "$(INTDIR)\UIGraphicsToolKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vector2D.obj"
	-@erase "$(INTDIR)\Win32Context.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32FontManager.obj"
	-@erase "$(INTDIR)\Win32Image.obj"
	-@erase "$(INTDIR)\Win32OpenGLPeer.obj"
	-@erase "$(OUTDIR)\GraphicsKitDLL.dll"
	-@erase "$(OUTDIR)\GraphicsKitDLL.exp"
	-@erase "$(OUTDIR)\GraphicsKitDLL.lib"
	-@erase "$(OUTDIR)\GraphicsKitDLL.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /Zi /Od /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FRAMEWORK_DLL" /D "GRAPHICSKIT_DLL" /D "GRAPHICSKIT_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GraphicsKitDLL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=FoundationKitDLL.lib opengl32.lib glu32.lib glaux.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\GraphicsKitDLL.pdb" /debug /machine:I386 /out:"$(OUTDIR)\GraphicsKitDLL.dll" /implib:"$(OUTDIR)\GraphicsKitDLL.lib" /libpath:"\vcf\lib" 
LINK32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\AlphaGamma.obj" \
	"$(INTDIR)\ArtStroke.obj" \
	"$(INTDIR)\BasicFill.obj" \
	"$(INTDIR)\BasicStroke.obj" \
	"$(INTDIR)\Color.obj" \
	"$(INTDIR)\DrawToolkit.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FontState.obj" \
	"$(INTDIR)\GlyphCollection.obj" \
	"$(INTDIR)\GraphicsContext.obj" \
	"$(INTDIR)\GraphicsKit.obj" \
	"$(INTDIR)\GraphicsObject.obj" \
	"$(INTDIR)\ImageEvent.obj" \
	"$(INTDIR)\ImageList.obj" \
	"$(INTDIR)\ImageListEvent.obj" \
	"$(INTDIR)\Matrix2D.obj" \
	"$(INTDIR)\MicroTiles.obj" \
	"$(INTDIR)\OpenGLContext.obj" \
	"$(INTDIR)\PixelBuffer.obj" \
	"$(INTDIR)\Polygon.obj" \
	"$(INTDIR)\RenderPaths.obj" \
	"$(INTDIR)\UIGraphicsToolKit.obj" \
	"$(INTDIR)\Vector2D.obj" \
	"$(INTDIR)\Win32Context.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32FontManager.obj" \
	"$(INTDIR)\Win32Image.obj" \
	"$(INTDIR)\Win32OpenGLPeer.obj"

"$(OUTDIR)\GraphicsKitDLL.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("GraphicsKitDLL.dep")
!INCLUDE "GraphicsKitDLL.dep"
!ELSE 
!MESSAGE Warning: cannot find "GraphicsKitDLL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GraphicsKitDLL - Win32 Release" || "$(CFG)" == "GraphicsKitDLL - Win32 Debug" || "$(CFG)" == "GraphicsKitDLL - Win32 Fake Debug"
SOURCE=..\..\..\src\Graphics\AbstractImage.cpp

"$(INTDIR)\AbstractImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\graphics\AlphaGamma.cpp

"$(INTDIR)\AlphaGamma.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\ArtStroke.cpp

"$(INTDIR)\ArtStroke.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\BasicFill.cpp

"$(INTDIR)\BasicFill.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\BasicStroke.cpp

"$(INTDIR)\BasicStroke.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Color.cpp

"$(INTDIR)\Color.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\DrawToolkit.cpp

"$(INTDIR)\DrawToolkit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Font.cpp

"$(INTDIR)\Font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\FontState.cpp

"$(INTDIR)\FontState.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GlyphCollection.cpp

"$(INTDIR)\GlyphCollection.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GraphicsContext.cpp

"$(INTDIR)\GraphicsContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GraphicsKit.cpp

"$(INTDIR)\GraphicsKit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GraphicsObject.cpp

"$(INTDIR)\GraphicsObject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ImageEvent.cpp

"$(INTDIR)\ImageEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\ImageList.cpp

"$(INTDIR)\ImageList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ImageListEvent.cpp

"$(INTDIR)\ImageListEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Matrix2D.cpp

"$(INTDIR)\Matrix2D.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\MicroTiles.cpp

"$(INTDIR)\MicroTiles.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\OpenGLContext.cpp

"$(INTDIR)\OpenGLContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\PixelBuffer.cpp

"$(INTDIR)\PixelBuffer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Polygon.cpp

"$(INTDIR)\Polygon.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\RenderPaths.cpp

"$(INTDIR)\RenderPaths.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\UIGraphicsToolKit.cpp

"$(INTDIR)\UIGraphicsToolKit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Vector2D.cpp

"$(INTDIR)\Vector2D.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Context.cpp

"$(INTDIR)\Win32Context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Font.cpp

"$(INTDIR)\Win32Font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FontManager.cpp

"$(INTDIR)\Win32FontManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Image.cpp

"$(INTDIR)\Win32Image.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32OpenGLPeer.cpp

"$(INTDIR)\Win32OpenGLPeer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

