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

OUTDIR=.\Release
INTDIR=.\Release\obj

ALL : "..\..\..\lib\GraphicsKit.lib"


CLEAN :
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\Basic3DBorder.obj"
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
	-@erase "$(INTDIR)\OpenGLContext.obj"
	-@erase "$(INTDIR)\Polygon.obj"
	-@erase "$(INTDIR)\UIGraphicsToolKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vector2D.obj"
	-@erase "$(INTDIR)\Win32Context.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32Image.obj"
	-@erase "$(INTDIR)\Win32OpenGLPeer.obj"
	-@erase "..\..\..\lib\GraphicsKit.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\GraphicsKit.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
LIB32_FLAGS=/nologo /out:"..\..\..\lib\GraphicsKit.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\Basic3DBorder.obj" \
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
	"$(INTDIR)\OpenGLContext.obj" \
	"$(INTDIR)\Polygon.obj" \
	"$(INTDIR)\UIGraphicsToolKit.obj" \
	"$(INTDIR)\Vector2D.obj" \
	"$(INTDIR)\Win32Context.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32Image.obj" \
	"$(INTDIR)\Win32OpenGLPeer.obj"

"..\..\..\lib\GraphicsKit.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GraphicsKit - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug\obj

ALL : "..\..\..\lib\GraphicsKit_d.lib"


CLEAN :
	-@erase "$(INTDIR)\AbstractImage.obj"
	-@erase "$(INTDIR)\Basic3DBorder.obj"
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
	-@erase "$(INTDIR)\OpenGLContext.obj"
	-@erase "$(INTDIR)\Polygon.obj"
	-@erase "$(INTDIR)\UIGraphicsToolKit.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vector2D.obj"
	-@erase "$(INTDIR)\Win32Context.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32Image.obj"
	-@erase "$(INTDIR)\Win32OpenGLPeer.obj"
	-@erase "..\..\..\lib\GraphicsKit_d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\Graphics" /I "..\..\..\include\Core" /I "..\..\..\include\DragDrop" /I "..\..\..\include\Implementer" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\ImplementerKit" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D _WIN32_WINNT=0x400 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
LIB32_FLAGS=/nologo /out:"..\..\..\lib\GraphicsKit_d.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractImage.obj" \
	"$(INTDIR)\Basic3DBorder.obj" \
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
	"$(INTDIR)\OpenGLContext.obj" \
	"$(INTDIR)\Polygon.obj" \
	"$(INTDIR)\UIGraphicsToolKit.obj" \
	"$(INTDIR)\Vector2D.obj" \
	"$(INTDIR)\Win32Context.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32Image.obj" \
	"$(INTDIR)\Win32OpenGLPeer.obj"

"..\..\..\lib\GraphicsKit_d.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

"$(INTDIR)\AbstractImage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Basic3DBorder.cpp

"$(INTDIR)\Basic3DBorder.obj" : $(SOURCE) "$(INTDIR)"
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


SOURCE=..\..\..\src\graphics\OpenGLContext.cpp

"$(INTDIR)\OpenGLContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Polygon.cpp

"$(INTDIR)\Polygon.obj" : $(SOURCE) "$(INTDIR)"
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


SOURCE=..\..\..\src\ImplementerKit\Win32Image.cpp

"$(INTDIR)\Win32Image.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\implementerkit\Win32OpenGLPeer.cpp

"$(INTDIR)\Win32OpenGLPeer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

