#######################################################
# MAKEFILE for building LibTIFF_bcc_s(d).lib          #
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
SYSDEFINES=_LIB;BUILD_LIBTIFF_LIB
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

CFLAGS=$(CFLAGS) -w-8057 -w-8012 

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=LibTIFF_bcc_s$(DBG).lib
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
OBJFILES=$(OBJ)\fax3sm_winnt.obj \
	$(OBJ)\tif_aux.obj \
	$(OBJ)\tif_close.obj \
	$(OBJ)\tif_codec.obj \
	$(OBJ)\tif_compress.obj \
	$(OBJ)\tif_dir.obj \
	$(OBJ)\tif_dirinfo.obj \
	$(OBJ)\tif_dirread.obj \
	$(OBJ)\tif_dirwrite.obj \
	$(OBJ)\tif_dumpmode.obj \
	$(OBJ)\tif_error.obj \
	$(OBJ)\tif_fax3.obj \
	$(OBJ)\tif_flush.obj \
	$(OBJ)\tif_getimage.obj \
	$(OBJ)\tif_jpeg.obj \
	$(OBJ)\tif_luv.obj \
	$(OBJ)\tif_lzw.obj \
	$(OBJ)\tif_next.obj \
	$(OBJ)\tif_open.obj \
	$(OBJ)\tif_packbits.obj \
	$(OBJ)\tif_pixarlog.obj \
	$(OBJ)\tif_predict.obj \
	$(OBJ)\tif_print.obj \
	$(OBJ)\tif_read.obj \
	$(OBJ)\tif_strip.obj \
	$(OBJ)\tif_swab.obj \
	$(OBJ)\tif_thunder.obj \
	$(OBJ)\tif_tile.obj \
	$(OBJ)\tif_version.obj \
	$(OBJ)\tif_warning.obj \
	$(OBJ)\tif_write.obj \
	$(OBJ)\tif_zip.obj
         
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
$(OBJ)\fax3sm_winnt.obj:    .\fax3sm_winnt.c   
$(OBJ)\tif_aux.obj:         .\tif_aux.c     
$(OBJ)\tif_close.obj:       .\tif_close.c   
$(OBJ)\tif_codec.obj:       .\tif_codec.c   
$(OBJ)\tif_compress.obj:    .\tif_compress.c
$(OBJ)\tif_dir.obj:         .\tif_dir.c     
$(OBJ)\tif_dirinfo.obj:     .\tif_dirinfo.c 
$(OBJ)\tif_dirread.obj:     .\tif_dirread.c 
$(OBJ)\tif_dirwrite.obj:    .\tif_dirwrite.c
$(OBJ)\tif_dumpmode.obj:    .\tif_dumpmode.c
$(OBJ)\tif_error.obj:       .\tif_error.c   
$(OBJ)\tif_fax3.obj:        .\tif_fax3.c    
$(OBJ)\tif_flush.obj:       .\tif_flush.c   
$(OBJ)\tif_getimage.obj:    .\tif_getimage.c
$(OBJ)\tif_jpeg.obj:        .\tif_jpeg.c    
$(OBJ)\tif_luv.obj:         .\tif_luv.c     
$(OBJ)\tif_lzw.obj:         .\tif_lzw.c     
$(OBJ)\tif_next.obj:        .\tif_next.c    
$(OBJ)\tif_open.obj:        .\tif_open.c    
$(OBJ)\tif_packbits.obj:    .\tif_packbits.c
$(OBJ)\tif_pixarlog.obj:    .\tif_pixarlog.c
$(OBJ)\tif_predict.obj:     .\tif_predict.c 
$(OBJ)\tif_print.obj:       .\tif_print.c   
$(OBJ)\tif_read.obj:        .\tif_read.c    
$(OBJ)\tif_strip.obj:       .\tif_strip.c   
$(OBJ)\tif_swab.obj:        .\tif_swab.c    
$(OBJ)\tif_thunder.obj:     .\tif_thunder.c 
$(OBJ)\tif_tile.obj:        .\tif_tile.c    
$(OBJ)\tif_version.obj:     .\tif_version.c 
$(OBJ)\tif_warning.obj:     .\tif_warning.c 
$(OBJ)\tif_write.obj:       .\tif_write.c   
$(OBJ)\tif_zip.obj:         .\tif_zip.c     

