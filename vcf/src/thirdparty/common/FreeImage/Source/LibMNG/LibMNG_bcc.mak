#######################################################
# MAKEFILE for building LibMNG_bcc_s(d).lib           #
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
SYSDEFINES=_LIB;BUILD_LIBMNG_LIB
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

CFLAGS=$(CFLAGS) -w-8057

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=LibMNG_bcc_s$(DBG).lib
DLLNAME=
INCDIR=..\..\..\..\..\..\src;..\libjpeg;..\Zlib
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
OBJFILES=$(OBJ)\libmng_callback_xs.obj \
	$(OBJ)\libmng_chunk_io.obj \
	$(OBJ)\libmng_chunk_prc.obj \
	$(OBJ)\libmng_chunk_xs.obj \
	$(OBJ)\libmng_cms.obj \
	$(OBJ)\libmng_display.obj \
	$(OBJ)\libmng_dither.obj \
	$(OBJ)\libmng_error.obj \
	$(OBJ)\libmng_filter.obj \
	$(OBJ)\libmng_hlapi.obj \
	$(OBJ)\libmng_jpeg.obj \
	$(OBJ)\libmng_object_prc.obj \
	$(OBJ)\libmng_pixels.obj \
	$(OBJ)\libmng_prop_xs.obj \
	$(OBJ)\libmng_read.obj \
	$(OBJ)\libmng_trace.obj \
	$(OBJ)\libmng_write.obj \
	$(OBJ)\libmng_zlib.obj
         
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
	-@md bcc
	-@md $(OBJ)
	-@md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1): $(OBJFILES)
  @$(LB) /P1024 $(BIN)\$(LIBNAME) /a$(OBJFILES)
    
#Dependencies - explicit rules
$(OBJ)\libmng_callback_xs.obj:   .\libmng_callback_xs.c
$(OBJ)\libmng_chunk_io.obj:      .\libmng_chunk_io.c   
$(OBJ)\libmng_chunk_prc.obj:     .\libmng_chunk_prc.c  
$(OBJ)\libmng_chunk_xs.obj:      .\libmng_chunk_xs.c   
$(OBJ)\libmng_cms.obj:           .\libmng_cms.c        
$(OBJ)\libmng_display.obj:       .\libmng_display.c    
$(OBJ)\libmng_dither.obj:        .\libmng_dither.c     
$(OBJ)\libmng_error.obj:         .\libmng_error.c      
$(OBJ)\libmng_filter.obj:        .\libmng_filter.c     
$(OBJ)\libmng_hlapi.obj:         .\libmng_hlapi.c      
$(OBJ)\libmng_jpeg.obj:          .\libmng_jpeg.c       
$(OBJ)\libmng_object_prc.obj:    .\libmng_object_prc.c 
$(OBJ)\libmng_pixels.obj:        .\libmng_pixels.c     
$(OBJ)\libmng_prop_xs.obj:       .\libmng_prop_xs.c    
$(OBJ)\libmng_read.obj:          .\libmng_read.c       
$(OBJ)\libmng_trace.obj:         .\libmng_trace.c      
$(OBJ)\libmng_write.obj:         .\libmng_write.c      
$(OBJ)\libmng_zlib.obj:          .\libmng_zlib.c       