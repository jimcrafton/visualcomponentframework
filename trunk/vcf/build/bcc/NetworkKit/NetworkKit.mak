#######################################################
# MAKEFILE for building NetworkKit_bcc_s(d).lib       #
#                   and NetworkKit_bcc_(d).dll        #
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
SYSDEFINES=_WINDOWS;_USRDLL;NETKIT_DLL;NETKIT_EXPORTS;USE_FOUNDATIONKIT_DLL
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


LIBNAME=NetworkKit_bcc_s$(DBG).lib
DLLNAME=NetworkKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;BUILD_NETWORKKIT_LIB;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\DatagramSocket.obj \
	$(OBJ)\NetToolkit.obj \
	$(OBJ)\ServerSocketEvent.obj \
	$(OBJ)\Socket.obj \
	$(OBJ)\SocketEvent.obj \
	$(OBJ)\SocketListeningLoop.obj \
	$(OBJ)\URL.obj \
	$(OBJ)\Win32DatagramSocketPeer.obj \
	$(OBJ)\Win32SocketPeer.obj
         
LIBFILES=UUID.LIB WS2_32.LIB
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
  @$(LB) $(LPARAM) $(BIN)\$(LIBNAME) /a$(OBJFILES)

$(PROJECT2):: $(OBJFILES)
    $(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS2) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\NetworkKit_bcc$(DBGDLL).lib move $(BIN)\NetworkKit_bcc$(DBGDLL).lib $(LIBDIR)
    
#Dependencies - explicit rules
$(OBJ)\DatagramSocket.obj:          ..\..\..\src\vcf\NetworkKit\DatagramSocket.cpp
$(OBJ)\NetToolkit.obj:              ..\..\..\src\vcf\NetworkKit\NetToolkit.cpp
$(OBJ)\ServerSocketEvent.obj:       ..\..\..\src\vcf\NetworkKit\ServerSocketEvent.cpp
$(OBJ)\Socket.obj:                  ..\..\..\src\vcf\NetworkKit\Socket.cpp
$(OBJ)\SocketEvent.obj:             ..\..\..\src\vcf\NetworkKit\SocketEvent.cpp
$(OBJ)\SocketListeningLoop.obj:     ..\..\..\src\vcf\NetworkKit\SocketListeningLoop.cpp
$(OBJ)\URL.obj:                     ..\..\..\src\vcf\NetworkKit\URL.cpp
$(OBJ)\Win32DatagramSocketPeer.obj: ..\..\..\src\vcf\NetworkKit\Win32DatagramSocketPeer.cpp
$(OBJ)\Win32SocketPeer.obj:         ..\..\..\src\vcf\NetworkKit\Win32SocketPeer.cpp

