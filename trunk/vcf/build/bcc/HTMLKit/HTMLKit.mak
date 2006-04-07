#######################################################
# MAKEFILE for building HTMLKit_bcc_s(d).lib          #
#                   and HTMLKit_bcc_(d).dll           #
#                                                     #
# (c) 2006 by Darko Miletic                           #
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
TDIR=S
OUTDIR=..\..\..\lib
SYSDEFINES=_LIB;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATION_LIB
!else
PROJECT=$(RESFILE) $(PROJECT2)
TDIR=DLL
OUTDIR=..\..\..\bin
SYSDEFINES=_WINDOWS;_USRDLL;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;HTMLKIT_DLL;HTMLKIT_EXPORTS
!endif


!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	LPARAM=/P2048
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	LPARAM=/P4096
	!message Building debug version of project
!endif

      
LIBNAME=HTMLKit_bcc_s$(DBG).lib
DLLNAME=HTMLKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src;..\..\..\src\thirdparty\win32
LIBDIR=..\..\..\lib;$(MAKEDIR)\..\Lib\PSDK
SRC=..\..\..\src\vcf\HTMLKit
RESSRC=..\..\resources\win32
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
SYSDEFINES=STRICT;_MBCS;WIN32;NO_MFC;BUILD_HTMLKIT_LIB;$(SYSDEFINES)
RFLAGS=$(RFLAGS) /l0x409 -d_DEBUG
.path.cpp=$(SRC)
.path.obj=$(OBJ)         
.path.res=$(OBJ)
.path.rc=$(RESSRC)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
RESSRCFILE=
CPPFILES= HTMLBrowserControl.cpp \
          HTMLKit.cpp \
          HTMLToolkit.cpp \
          Win32HTMLBrowser.cpp \
          Win32HTMLDOMElements.cpp \
          Win32HTMLToolkit.cpp 
 

RESFILE=$(RESSRCFILE:.rc=.res^ )
OBJFILES=$(CPPFILES:.cpp=.obj^ ) $(NONFREEFILES:.cpp=.obj^ )

LIBFILES=comctl32.lib shell32.lib oleaut32.lib
DEFFILE=
BCC32STARTUP=c0d32.obj
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS=$(LIBFILES) import32.lib $(BCC32RTLIB)

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
	-@if exist $(PROJECT1) del $(PROJECT1)
	-@if exist $(PROJECT2) del $(PROJECT2)
	-@if exist ..\..\..\lib\HTMLKit_bcc$(DBGDLL).lib del ..\..\..\lib\HTMLKit_bcc$(DBGDLL).lib

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@if not exist .\bcc md bcc
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	

##################################
# Output
##################################
$(PROJECT1):: $(OBJFILES)
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
    @if exist ..\..\..\lib\HTMLKit_bcc$(DBGDLL).lib del ..\..\..\lib\HTMLKit_bcc$(DBGDLL).lib
    @if exist $(BIN)\HTMLKit_bcc$(DBGDLL).lib move $(BIN)\HTMLKit_bcc$(DBGDLL).lib ..\..\..\lib
