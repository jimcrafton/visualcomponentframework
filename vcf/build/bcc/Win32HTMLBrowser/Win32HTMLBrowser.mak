#######################################################
# MAKEFILE for building Win32HTMLBrowser_bcc_s(d).lib #
#                   and Win32HTMLBrowser_bcc_(d).dll  #
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
SYSDEFINES=_WINDOWS;_USRDLL;WIN32HTMLBROWSER_DLL;WIN32HTMLBROWSER_EXPORTS;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;_ATL_STATIC_REGISTRY
OUTDIR=..\..\..\bin
TDIR=DLL
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	LPARAM=/P64
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif


LIBNAME=Win32HTMLBrowser_bcc_s$(DBG).lib
DLLNAME=Win32HTMLBrowser_bcc$(DBGDLL).dll
INCDIR=..\..\..\src;$(MAKEDIR)\..\include\atl
LIBDIR=..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;BUILD_WIN32HTMLBROWSER_LIB;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\Win32HTMLBrowser.obj
         
LIBFILES=UUID.LIB comsupp.lib
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
  @$(LB) $(LPARAM) $(BIN)\$(LIBNAME) /a$(OBJFILES)

$(PROJECT2):: $(OBJFILES)
    $(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS2) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\Win32HTMLBrowser_bcc$(DBGDLL).lib move $(BIN)\Win32HTMLBrowser_bcc$(DBGDLL).lib $(LIBDIR)
    
#Dependencies - explicit rules
$(OBJ)\Win32HTMLBrowser.obj: ..\..\..\src\vcf\ApplicationKit\Win32HTMLBrowser.cpp


