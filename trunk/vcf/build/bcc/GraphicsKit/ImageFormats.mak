#######################################################
# MAKEFILE for building ImageFormats_bcc_(d).dll      #
#                                                     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

!ifndef BMODE
BMODE = RELEASE
!endif

!if $(BMODE) != RELEASE && $(BMODE) != DEBUG
!  error Illegal value for BMODE option
!endif

!include <..\defaultmake.inc>

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

PROJECT=$(PROJECT2)
SYSDEFINES=_WINDOWS;_USRDLL;IMAGEFORMATS_DLL;IMAGEFORMATS_EXPORTS;FREEIMAGE_LIB;USE_FREEIMAGE_LIB;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;BUILD_IMAGEFORMATS_LIB
OUTDIR=..\..\..\bin
TDIR=S
      
LIBNAME=
DLLNAME=ImageFormats_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=..\..\..\src\ImageFormats
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;$(SYSDEFINES)
.path.cpp=$(SRC)
.path.obj=$(OBJ)         

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
CPPFILES=ImageFormats.cpp
OBJFILES=$(CPPFILES:.cpp=.obj^ )

LIBFILES=ODBC32.LIB UUID.LIB
DEFFILE=
BCC32STARTUP=c0d32.obj
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS=$(LIBFILES) import32.lib $(BCC32RTLIB)

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
	-@if exist ..\..\..\lib\ImageFormats_bcc$(DBGDLL).lib del ..\..\..\lib\ImageFormats_bcc$(DBGDLL).lib

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@if not exist bcc md bcc
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1):: $(OBJFILES)
   @echo Linking $(<F) static library
   @$(LB) @&&|
   $< $(LPARAM) &
   -+$(?: = &^
   -+)
   
| > NUL:

$(PROJECT2):: $(OBJFILES)
    @echo Linking $(<F) dynamic library
    @$(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS) 
    $<,$*
    $(ALLLIBS)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\ImageFormats_bcc$(DBGDLL).lib move $(BIN)\ImageFormats_bcc$(DBGDLL).lib $(LIBDIR)
    
