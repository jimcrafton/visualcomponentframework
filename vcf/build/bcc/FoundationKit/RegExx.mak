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

PROJECT=$(PROJECT1)
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
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;_LIB;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
OBJFILES=$(OBJ)\get.obj \
	$(OBJ)\maketables.obj \
	$(OBJ)\pcre.obj \
	$(OBJ)\pcreposix.obj \
	$(OBJ)\regexx.obj \
	$(OBJ)\study.obj
         
LIBFILES=
DEFFILE=
ALLOBJS=$(OBJFILES)

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
  @$(LB) $(BIN)\$(LIBNAME) /a$(OBJFILES)

    
#Dependencies - explicit rules
$(OBJ)\get.obj:         ..\..\..\src\thirdparty\common\pcre\get.c       
$(OBJ)\maketables.obj:  ..\..\..\src\thirdparty\common\pcre\maketables.c
$(OBJ)\pcre.obj:        ..\..\..\src\thirdparty\common\pcre\pcre.c      
$(OBJ)\pcreposix.obj:   ..\..\..\src\thirdparty\common\pcre\pcreposix.c 
$(OBJ)\regexx.obj:      ..\..\..\src\vcf\FoundationKit\regexx.cpp               
$(OBJ)\study.obj:       ..\..\..\src\thirdparty\common\pcre\study.c     

