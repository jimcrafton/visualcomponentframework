#######################################################
# MAKEFILE for building RegExx_bcc_s(d).lib           #
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

OUTDIR=..\..\..\lib

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=Release
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=Debug
	!message Building debug version of project
!endif

LIBNAME=RegExx_bcc_s$(DBG).lib
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=..\..\..\src\vcf\FoundationKit
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
SYSDEFINES=STRICT;WIN32;_MBCS;_LIB;$(SYSDEFINES)

.path.cpp=$(SRC)
.path.c=..\..\..\src\thirdparty\common\pcre
.path.obj=$(OBJ)

################################
# Target
################################
PROJECT=$(OUTDIR)\$(LIBNAME)
CFILES=	get.c        \
	maketables.c \
	pcre.c       \
	pcreposix.c  \
	study.c
CPPFILES=regexx.cpp
	
OBJFILES=$(CFILES:.c=.obj^ ) $(CPPFILES:.cpp=.obj^ )

all: dirs $(PROJECT)

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
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	
##################################
# Output
##################################
$(PROJECT): $(OBJFILES)
   @echo Linking $(<F) static library
   @$(LB) @&&|
   $< $(LPARAM) &
   -+$(?: = &^
   -+)
   
| > NUL:
  

