#######################################################
# MAKEFILE for building ZLib_bcc_s(d).lib             #
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
SYSDEFINES=_LIB;BUILD_ZLIB_LIB
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

LIBNAME=ZLib_bcc_s$(DBG).lib
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
OBJFILES=$(OBJ)\adler32.obj \
	$(OBJ)\compress.obj \
	$(OBJ)\crc32.obj \
	$(OBJ)\deflate.obj \
	$(OBJ)\gzio.obj \
	$(OBJ)\infblock.obj \
	$(OBJ)\infcodes.obj \
	$(OBJ)\inffast.obj \
	$(OBJ)\inflate.obj \
	$(OBJ)\inftrees.obj \
	$(OBJ)\infutil.obj \
	$(OBJ)\trees.obj \
	$(OBJ)\uncompr.obj \
	$(OBJ)\zutil.obj
         
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
$(OBJ)\adler32.obj:    .\adler32.c 
$(OBJ)\compress.obj:   .\compress.c
$(OBJ)\crc32.obj:      .\crc32.c   
$(OBJ)\deflate.obj:    .\deflate.c 
$(OBJ)\gzio.obj:       .\gzio.c    
$(OBJ)\infblock.obj:   .\infblock.c
$(OBJ)\infcodes.obj:   .\infcodes.c
$(OBJ)\inffast.obj:    .\inffast.c 
$(OBJ)\inflate.obj:    .\inflate.c 
$(OBJ)\inftrees.obj:   .\inftrees.c
$(OBJ)\infutil.obj:    .\infutil.c 
$(OBJ)\trees.obj:      .\trees.c   
$(OBJ)\uncompr.obj:    .\uncompr.c 
$(OBJ)\zutil.obj:      .\zutil.c   
            
            
