#######################################################
# MAKEFILE for building LibPNG_bcc_s(d).lib          #
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

!include <..\..\..\..\..\..\build\bcc\defaultmake.inc>

PROJECT=$(PROJECT1)
SYSDEFINES=_LIB;BUILD_LIBPNG_LIB
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=LibPNG_bcc_s$(DBG).lib
DLLNAME=
INCDIR=..\..\..\..\..\..\src
LIBDIR=..\..\..\..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\png.obj \
	$(OBJ)\pngerror.obj \
	$(OBJ)\pnggccrd.obj \
	$(OBJ)\pngget.obj \
	$(OBJ)\pngmem.obj \
	$(OBJ)\pngpread.obj \
	$(OBJ)\pngread.obj \
	$(OBJ)\pngrio.obj \
	$(OBJ)\pngrtran.obj \
	$(OBJ)\pngrutil.obj \
	$(OBJ)\pngset.obj \
	$(OBJ)\pngtest.obj \
	$(OBJ)\pngtrans.obj \
	$(OBJ)\pngvcrd.obj \
	$(OBJ)\pngwio.obj \
	$(OBJ)\pngwrite.obj \
	$(OBJ)\pngwtran.obj \
	$(OBJ)\pngwutil.obj
         
LIBFILES=
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
	-@md $(OBJ)
	-@md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1): $(OBJFILES)
  @$(LB) /P1024 $(BIN)\$(LIBNAME) /a$(OBJFILES)
    
#Dependencies - explicit rules
$(OBJ)\png.obj:        .\png.c     
$(OBJ)\pngerror.obj:   .\pngerror.c
$(OBJ)\pnggccrd.obj:   .\pnggccrd.c
$(OBJ)\pngget.obj:     .\pngget.c  
$(OBJ)\pngmem.obj:     .\pngmem.c  
$(OBJ)\pngpread.obj:   .\pngpread.c
$(OBJ)\pngread.obj:    .\pngread.c 
$(OBJ)\pngrio.obj:     .\pngrio.c  
$(OBJ)\pngrtran.obj:   .\pngrtran.c
$(OBJ)\pngrutil.obj:   .\pngrutil.c
$(OBJ)\pngset.obj:     .\pngset.c  
$(OBJ)\pngtest.obj:    .\pngtest.c 
$(OBJ)\pngtrans.obj:   .\pngtrans.c
$(OBJ)\pngvcrd.obj:    .\pngvcrd.c 
$(OBJ)\pngwio.obj:     .\pngwio.c  
$(OBJ)\pngwrite.obj:   .\pngwrite.c
$(OBJ)\pngwtran.obj:   .\pngwtran.c
$(OBJ)\pngwutil.obj:   .\pngwutil.c

