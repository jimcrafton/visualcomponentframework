#######################################################
# MAKEFILE for building RemoteObjectKit_bcc_s(d).lib  #
#                   and RemoteObjectKit_bcc_(d).dll   #
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
SYSDEFINES=_LIB;USE_NETKIT_LIB
OUTDIR=..\..\..\lib
TDIR=S
!else
PROJECT=$(PROJECT2)
SYSDEFINES=_WINDOWS;_USRDLL;REMOTEKIT_DLL;REMOTEKIT_EXPORTS;USE_NETKIT_DLL;USE_FOUNDATIONKIT_DLL
OUTDIR=..\..\..\bin
TDIR=DLL
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	LPARAM=/P128
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=RemoteObjectKit_bcc_s$(DBG).lib
DLLNAME=RemoteObjectKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=..\..\..\src\vcf\RemoteObjectKit
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;BUILD_REMOTEOBJECTKIT_LIB;$(SYSDEFINES)
.path.cpp=$(SRC)
.path.obj=$(OBJ)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
CPPFILES=AbstractDistributedApplication.cpp \
	ClassRegistryEntry.cpp \
	ClassServerInstance.cpp \
	DistributedClassRegistry.cpp \
	DistributedException.cpp \
	InstanceID.cpp \
	Proxy.cpp \
	RemoteObjectKit.cpp

OBJFILES=$(CPPFILES:.cpp=.obj^ )         
LIBFILES=
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
	-@if exist ..\..\..\lib\RemoteObjectKit_bcc$(DBGDLL).lib del ..\..\..\lib\RemoteObjectKit_bcc$(DBGDLL).lib

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@if not exist bcc md bcc
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1): $(OBJFILES)
   @echo Linking $(<F) static library
   @$(LB) $< $(LPARAM) @&&|
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
    @if exist $(BIN)\RemoteObjectKit_bcc$(DBGDLL).lib move $(BIN)\RemoteObjectKit_bcc$(DBGDLL).lib $(LIBDIR)
    


