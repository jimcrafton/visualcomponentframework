#######################################################
# MAKEFILE for building GraphicsKit_bcc_s(d).lib      #
#                   and GraphicsKit_bcc_(d).dll       #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

!ifndef BMODE
BMODE = RELEASE
!endif

!ifndef TARGET
TARGET = LIB
!endif

!if $(BMODE) != RELEASE && $(BMODE) != DEBUG
!  error Illegal value for BMODE option
!endif

!if $(TARGET) != LIB && $(TARGET) != DLL
!  error Illegal value for TARGET option
!endif

!include <..\defaultmake.inc>

!if $(TARGET) == LIB
PROJECT=$(PROJECT1)
SYSDEFINES=_LIB
OUTDIR=..\..\..\lib
TDIR=S
!else
PROJECT=$(PROJECT2)
SYSDEFINES=_WINDOWS;_USRDLL;USE_FOUNDATIONKIT_DLL;GRAPHICSKIT_DLL;GRAPHICSKIT_EXPORTS
OUTDIR=..\..\..\bin
TDIR=DLL
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	LPARAMS=/P64
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	LPARAMS=/P256
	!message Building debug version of project
!endif


LIBNAME=GraphicsKit_bcc_s$(DBG).lib
DLLNAME=GraphicsKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;BUILD_GRAPHICSKIT_LIB;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\AbstractImage.obj \
	$(OBJ)\BasicFill.obj \
	$(OBJ)\BasicStroke.obj \
	$(OBJ)\BezierCurve.obj \
	$(OBJ)\Color.obj \
	$(OBJ)\Font.obj \
	$(OBJ)\GlyphCollection.obj \
	$(OBJ)\GraphicsContext.obj \
	$(OBJ)\GraphicsKit.obj \
	$(OBJ)\GraphicsToolKit.obj \
	$(OBJ)\ImageEvent.obj \
	$(OBJ)\Matrix2D.obj \
	$(OBJ)\Point.obj \
	$(OBJ)\Rect.obj \
	$(OBJ)\Vector2D.obj \
	$(OBJ)\Win32Context.obj \
	$(OBJ)\Win32Font.obj \
	$(OBJ)\Win32FontManager.obj \
	$(OBJ)\Win32GraphicsToolkit.obj \
	$(OBJ)\Win32Image.obj
         
LIBFILES=ODBC32.LIB UUID.LIB
DEFFILE=
ALLOBJS=$(OBJFILES)
BCC32STARTUP=c0d32.obj
ALLOBJS2=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS2=$(LIBFILES) import32.lib $(BCC32RTLIB)

all: dirs $(RESFILE) $(PROJECT)

cleanobj:: 
	-@echo Deleting intermediate files for project
	-@if exist $(OBJ)\*.obj del $(OBJ)\*.obj
	-@if exist $(OBJ)\*.res del $(OBJ)\*.res
	-@if exist $(OBJ)\. rd $(OBJ)
!if $(BMODE) == RELEASE
	-@if exist $(BIN)\*.tds del $(BIN)\*.tds
	-@if exist $(BIN)\*.map del $(BIN)\*.map
!endif

cleantgt::
	-@echo Deleting output files for project
	-@if exist $(PROJECT) del $(PROJECT)

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@md bcc
	-@md $(OBJ)
	-@md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1): $(OBJFILES)
  @$(LB) $(LPARAMS) $(BIN)\$(LIBNAME) /a$(OBJFILES)

$(PROJECT2):: $(OBJFILES)
    $(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS2) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\GraphicsKit_bcc$(DBGDLL).lib move $(BIN)\GraphicsKit_bcc$(DBGDLL).lib $(LIBDIR)
    
#Dependencies - explicit rules
$(OBJ)\AbstractImage.obj:           ..\..\..\src\vcf\GraphicsKit\AbstractImage.cpp             
$(OBJ)\BasicFill.obj:               ..\..\..\src\vcf\GraphicsKit\BasicFill.cpp                 
$(OBJ)\BasicStroke.obj:             ..\..\..\src\vcf\GraphicsKit\BasicStroke.cpp               
$(OBJ)\BezierCurve.obj:             ..\..\..\src\vcf\GraphicsKit\BezierCurve.cpp               
$(OBJ)\Color.obj:                   ..\..\..\src\vcf\GraphicsKit\Color.cpp                     
$(OBJ)\Font.obj:                    ..\..\..\src\vcf\GraphicsKit\Font.cpp                      
$(OBJ)\GlyphCollection.obj:         ..\..\..\src\vcf\GraphicsKit\GlyphCollection.cpp           
$(OBJ)\GraphicsContext.obj:         ..\..\..\src\vcf\GraphicsKit\GraphicsContext.cpp           
$(OBJ)\GraphicsKit.obj:             ..\..\..\src\vcf\GraphicsKit\GraphicsKit.cpp               
$(OBJ)\GraphicsToolKit.obj:         ..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.cpp              
$(OBJ)\ImageEvent.obj:              ..\..\..\src\vcf\GraphicsKit\ImageEvent.cpp                  
$(OBJ)\Matrix2D.obj:                ..\..\..\src\vcf\GraphicsKit\Matrix2D.cpp                  
$(OBJ)\Point.obj:                   ..\..\..\src\vcf\GraphicsKit\Point.cpp                         
$(OBJ)\Rect.obj:                    ..\..\..\src\vcf\GraphicsKit\Rect.cpp                          
$(OBJ)\Vector2D.obj:                ..\..\..\src\vcf\GraphicsKit\Vector2D.cpp                  
$(OBJ)\Win32Context.obj:            ..\..\..\src\vcf\GraphicsKit\Win32Context.cpp        
$(OBJ)\Win32Font.obj:               ..\..\..\src\vcf\GraphicsKit\Win32Font.cpp           
$(OBJ)\Win32FontManager.obj:        ..\..\..\src\vcf\GraphicsKit\Win32FontManager.cpp    
$(OBJ)\Win32GraphicsToolkit.obj:    ..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.cpp
$(OBJ)\Win32Image.obj:              ..\..\..\src\vcf\GraphicsKit\Win32Image.cpp          

