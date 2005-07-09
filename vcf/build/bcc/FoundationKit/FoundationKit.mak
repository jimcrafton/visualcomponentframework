#######################################################
# MAKEFILE for building FoundationKit_bcc_s(d).lib    #
#                   and FoundationKit_bcc_(d).dll     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################

.autodepend

!ifndef BMODE
BMODE=RELEASE
!endif

!ifndef TARGET
TARGET=LIB
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
SYSDEFINES=_WINDOWS;_USRDLL;FOUNDATIONKIT_DLL;FOUNDATIONKIT_EXPORTS
OUTDIR=..\..\..\bin
TDIR=DLL
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=FoundationKit_bcc_s$(DBG).lib
DLLNAME=FoundationKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;BUILD_FRAMEWORK_LIB;$(SYSDEFINES)
.path.cpp=..\..\..\src\vcf\FoundationKit
.path.obj=$(OBJ)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
CPPFILES=FoundationKit.cpp \
	Win32Condition.cpp \
	Win32FilePeer.cpp \
	Win32FileStream.cpp \
	Win32LibraryPeer.cpp \
	Win32LocalePeer.cpp \
	Win32Mutex.cpp \
	Win32Peer.cpp \
	Win32ProcessIORedirector.cpp \
	Win32ProcessPeer.cpp \
	Win32Registry.cpp \
	Win32ResourceBundle.cpp \
	Win32SemaphorePeer.cpp \
	Win32SystemPeer.cpp \
	Win32SystemToolkit.cpp \
	Win32Thread.cpp \
	Win32ThreadManagerPeer.cpp \
	Win32RunLoopPeer.cpp \
	ThreadManager.cpp \
	RunLoop.cpp \
	BasicException.cpp \
	Event.cpp \
	EventHandler.cpp \
	PropertyChangeEvent.cpp \
	ThreadEvent.cpp \
	BasicInputStream.cpp \
	BasicOutputStream.cpp \
	Directory.cpp \
	File.cpp \
	FilePath.cpp \
	FileStream.cpp \
	MemoryStream.cpp \
	Stream.cpp \
	TextInputStream.cpp \
	TextOutputStream.cpp \
	CommandLine.cpp \
	Condition.cpp \
	DateTime.cpp \
	Dictionary.cpp \
	ErrorLog.cpp \
	Library.cpp \
	MessageLoader.cpp \
	MIMEType.cpp \
	Mutex.cpp \
	PackageInfo.cpp \
	Parser.cpp \
	ProcessWithRedirectedIO.cpp \
	Registry.cpp \
	Semaphore.cpp \
	StringsMessageLoader.cpp \
	StringUtils.cpp \
	System.cpp \
	SystemToolkit.cpp \
	TextCodec.cpp \
	Thread.cpp \
	VCFMath.cpp \
	VCFProcess.cpp \
	VCFString.cpp \
	XMLParser.cpp \
	Locales.cpp \
	Object.cpp \
	ObjectWithEvents.cpp \
	Resource.cpp \
	ResourceBundle.cpp \
	Class.cpp \
	ClassRegistry.cpp \
	InterfaceClass.cpp \
	VariantData.cpp
	
OBJFILES=$(CPPFILES:.cpp=.obj^ )         
LIBFILES=ODBC32.LIB UUID.LIB
DEFFILE=
BCC32STARTUP=c0d32.obj
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS2=$(LIBFILES) import32.lib $(BCC32RTLIB)
LPARAM=/P1024

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
	-@if exist ..\..\..\lib\FoundationKit_bcc$(DBGDLL).lib del ..\..\..\lib\FoundationKit_bcc$(DBGDLL).lib

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
   @$(LB) @&&|
   $< $(LPARAM) &
   -+$(?: = &^
   -+)
   
| > NUL:

$(PROJECT2):: $(OBJFILES)
    @echo Linking $(<F) dynamic library
    @$(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\FoundationKit_bcc$(DBGDLL).lib move $(BIN)\FoundationKit_bcc$(DBGDLL).lib $(LIBDIR)
    


