#######################################################
# MAKEFILE for building LibJPEG_bcc_s(d).lib          #
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

PROJECT=$(PROJECT1)
SYSDEFINES=_LIB;BUILD_LIBJPEG_LIB
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

!include <..\..\..\..\..\..\build\bcc\defaultmake.inc>

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


LIBNAME=LibJPEG_bcc_s$(DBG).lib
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
OBJFILES=$(OBJ)\jcapimin.obj \
	$(OBJ)\jcapistd.obj \
	$(OBJ)\jccoefct.obj \
	$(OBJ)\jccolor.obj \
	$(OBJ)\jcdctmgr.obj \
	$(OBJ)\jchuff.obj \
	$(OBJ)\jcinit.obj \
	$(OBJ)\jcmainct.obj \
	$(OBJ)\jcmarker.obj \
	$(OBJ)\jcmaster.obj \
	$(OBJ)\jcomapi.obj \
	$(OBJ)\jcparam.obj \
	$(OBJ)\jcphuff.obj \
	$(OBJ)\jcprepct.obj \
	$(OBJ)\jcsample.obj \
	$(OBJ)\jctrans.obj \
	$(OBJ)\jdapimin.obj \
	$(OBJ)\jdapistd.obj \
	$(OBJ)\jdatadst.obj \
	$(OBJ)\jdatasrc.obj \
	$(OBJ)\jdcoefct.obj \
	$(OBJ)\jdcolor.obj \
	$(OBJ)\jddctmgr.obj \
	$(OBJ)\jdhuff.obj \
	$(OBJ)\jdinput.obj \
	$(OBJ)\jdmainct.obj \
	$(OBJ)\jdmarker.obj \
	$(OBJ)\jdmaster.obj \
	$(OBJ)\jdmerge.obj \
	$(OBJ)\jdphuff.obj \
	$(OBJ)\jdpostct.obj \
	$(OBJ)\jdsample.obj \
	$(OBJ)\jdtrans.obj \
	$(OBJ)\jerror.obj \
	$(OBJ)\jfdctflt.obj \
	$(OBJ)\jfdctfst.obj \
	$(OBJ)\jfdctint.obj \
	$(OBJ)\jidctflt.obj \
	$(OBJ)\jidctfst.obj \
	$(OBJ)\jidctint.obj \
	$(OBJ)\jidctred.obj \
	$(OBJ)\jmemmgr.obj \
	$(OBJ)\jmemnobs.obj \
	$(OBJ)\jquant1.obj \
	$(OBJ)\jquant2.obj \
	$(OBJ)\jutils.obj
         
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
$(OBJ)\jcapimin.obj:   .\jcapimin.c
$(OBJ)\jcapistd.obj:   .\jcapistd.c
$(OBJ)\jccoefct.obj:   .\jccoefct.c
$(OBJ)\jccolor.obj:    .\jccolor.c 
$(OBJ)\jcdctmgr.obj:   .\jcdctmgr.c
$(OBJ)\jchuff.obj:     .\jchuff.c  
$(OBJ)\jcinit.obj:     .\jcinit.c  
$(OBJ)\jcmainct.obj:   .\jcmainct.c
$(OBJ)\jcmarker.obj:   .\jcmarker.c
$(OBJ)\jcmaster.obj:   .\jcmaster.c
$(OBJ)\jcomapi.obj:    .\jcomapi.c 
$(OBJ)\jcparam.obj:    .\jcparam.c 
$(OBJ)\jcphuff.obj:    .\jcphuff.c 
$(OBJ)\jcprepct.obj:   .\jcprepct.c
$(OBJ)\jcsample.obj:   .\jcsample.c
$(OBJ)\jctrans.obj:    .\jctrans.c 
$(OBJ)\jdapimin.obj:   .\jdapimin.c
$(OBJ)\jdapistd.obj:   .\jdapistd.c
$(OBJ)\jdatadst.obj:   .\jdatadst.c
$(OBJ)\jdatasrc.obj:   .\jdatasrc.c
$(OBJ)\jdcoefct.obj:   .\jdcoefct.c
$(OBJ)\jdcolor.obj:    .\jdcolor.c 
$(OBJ)\jddctmgr.obj:   .\jddctmgr.c
$(OBJ)\jdhuff.obj:     .\jdhuff.c  
$(OBJ)\jdinput.obj:    .\jdinput.c 
$(OBJ)\jdmainct.obj:   .\jdmainct.c
$(OBJ)\jdmarker.obj:   .\jdmarker.c
$(OBJ)\jdmaster.obj:   .\jdmaster.c
$(OBJ)\jdmerge.obj:    .\jdmerge.c 
$(OBJ)\jdphuff.obj:    .\jdphuff.c 
$(OBJ)\jdpostct.obj:   .\jdpostct.c
$(OBJ)\jdsample.obj:   .\jdsample.c
$(OBJ)\jdtrans.obj:    .\jdtrans.c 
$(OBJ)\jerror.obj:     .\jerror.c  
$(OBJ)\jfdctflt.obj:   .\jfdctflt.c
$(OBJ)\jfdctfst.obj:   .\jfdctfst.c
$(OBJ)\jfdctint.obj:   .\jfdctint.c
$(OBJ)\jidctflt.obj:   .\jidctflt.c
$(OBJ)\jidctfst.obj:   .\jidctfst.c
$(OBJ)\jidctint.obj:   .\jidctint.c
$(OBJ)\jidctred.obj:   .\jidctred.c
$(OBJ)\jmemmgr.obj:    .\jmemmgr.c 
$(OBJ)\jmemnobs.obj:   .\jmemnobs.c
$(OBJ)\jquant1.obj:    .\jquant1.c 
$(OBJ)\jquant2.obj:    .\jquant2.c 
$(OBJ)\jutils.obj:     .\jutils.c  
