# Microsoft Developer Studio Generated NMAKE File, Based on GraphicsKit.dsp
!IF "$(CFG)" == ""
CFG=GraphicsKit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to GraphicsKit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GraphicsKit - Win32 Release" && "$(CFG)" != "GraphicsKit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GraphicsKit.mak" CFG="GraphicsKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GraphicsKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "GraphicsKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "GraphicsKit - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\GraphicsKit_s.lib"

!ELSE 

ALL : "FoundationKit - Win32 Release" "$(OUTDIR)\GraphicsKit_s.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\AlphaGamma.obj"
	-@erase "$(INTDIR)\BasicFill.obj"
	-@erase "$(INTDIR)\BasicStroke.obj"
	-@erase "$(INTDIR)\Color.obj"
	-@erase "$(INTDIR)\DrawToolkit.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontState.obj"
	-@erase "$(INTDIR)\GlyphCollection.obj"
	-@erase "$(INTDIR)\GraphicsContext.obj"
	-@erase "$(INTDIR)\GraphicsKit.obj"
	-@erase "$(INTDIR)\GraphicsKit.pch"
	-@erase "$(INTDIR)\GraphicsObject.obj"
	-@erase "$(INTDIR)\ImageEvent.obj"
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
	-@erase "$(OUTDIR)\GraphicsKit_s.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\GraphicsKit.pch" /Yu"GraphicsKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GraphicsKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\GraphicsKit_s.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\AlphaGamma.obj" \
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
	"$(INTDIR)\Win32OpenGLPeer.obj" \
	"$(OUTDIR)\FoundationKit_s.lib"

"$(OUTDIR)\GraphicsKit_s.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\GraphicsKit_sd.lib"

!ELSE 

ALL : "FoundationKit - Win32 Debug" "$(OUTDIR)\GraphicsKit_sd.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\AlphaGamma.obj"
	-@erase "$(INTDIR)\BasicFill.obj"
	-@erase "$(INTDIR)\BasicStroke.obj"
	-@erase "$(INTDIR)\Color.obj"
	-@erase "$(INTDIR)\DrawToolkit.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FontState.obj"
	-@erase "$(INTDIR)\GlyphCollection.obj"
	-@erase "$(INTDIR)\GraphicsContext.obj"
	-@erase "$(INTDIR)\GraphicsKit.obj"
	-@erase "$(INTDIR)\GraphicsKit.pch"
	-@erase "$(INTDIR)\GraphicsObject.obj"
	-@erase "$(INTDIR)\ImageEvent.obj"
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
	-@erase "$(OUTDIR)\GraphicsKit_sd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\GraphicsKit.pch" /Yu"GraphicsKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\GraphicsKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\GraphicsKit_sd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\AlphaGamma.obj" \
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
	"$(INTDIR)\Win32OpenGLPeer.obj" \
	"$(OUTDIR)\FoundationKit_sd.lib"

"$(OUTDIR)\GraphicsKit_sd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("GraphicsKit.dep")
!INCLUDE "GraphicsKit.dep"
!ELSE 
!MESSAGE Warning: cannot find "GraphicsKit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "GraphicsKit - Win32 Release" || "$(CFG)" == "GraphicsKit - Win32 Debug"
SOURCE=..\..\..\src\Graphics\AbstractImage.cpp

"$(INTDIR)\AbstractImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\AlphaGamma.cpp

"$(INTDIR)\AlphaGamma.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\BasicFill.cpp

"$(INTDIR)\BasicFill.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\BasicStroke.cpp

"$(INTDIR)\BasicStroke.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Color.cpp

"$(INTDIR)\Color.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\DrawToolkit.cpp

"$(INTDIR)\DrawToolkit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Font.cpp

"$(INTDIR)\Font.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\FontState.cpp

"$(INTDIR)\FontState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GlyphCollection.cpp

"$(INTDIR)\GlyphCollection.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GraphicsContext.cpp

"$(INTDIR)\GraphicsContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\GraphicsKit.cpp

!IF  "$(CFG)" == "GraphicsKit - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\GraphicsKit.pch" /Yc"GraphicsKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\GraphicsKit.obj"	"$(INTDIR)\GraphicsKit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\GraphicsKit.pch" /Yc"GraphicsKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\GraphicsKit.obj"	"$(INTDIR)\GraphicsKit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\src\Graphics\GraphicsObject.cpp

"$(INTDIR)\GraphicsObject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ImageEvent.cpp

"$(INTDIR)\ImageEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Matrix2D.cpp

"$(INTDIR)\Matrix2D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\MicroTiles.cpp

"$(INTDIR)\MicroTiles.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\OpenGLContext.cpp

"$(INTDIR)\OpenGLContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\PixelBuffer.cpp

"$(INTDIR)\PixelBuffer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Polygon.cpp

"$(INTDIR)\Polygon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\RenderPaths.cpp

"$(INTDIR)\RenderPaths.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\UIGraphicsToolKit.cpp

"$(INTDIR)\UIGraphicsToolKit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Vector2D.cpp

"$(INTDIR)\Vector2D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Context.cpp

"$(INTDIR)\Win32Context.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Font.cpp

"$(INTDIR)\Win32Font.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FontManager.cpp

"$(INTDIR)\Win32FontManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Image.cpp

"$(INTDIR)\Win32Image.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32OpenGLPeer.cpp

"$(INTDIR)\Win32OpenGLPeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\GraphicsKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "GraphicsKit - Win32 Release"

"FoundationKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" 
   cd "..\GraphicsKit"

"FoundationKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\GraphicsKit"

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 Debug"

"FoundationKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" 
   cd "..\GraphicsKit"

"FoundationKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\GraphicsKit"

!ENDIF 


!ENDIF 

