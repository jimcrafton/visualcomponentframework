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

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\FoundationKit.obj \
	 $(OBJ)\Library.obj \
	 $(OBJ)\Win32Condition.obj \
	 $(OBJ)\Win32FilePeer.obj \
	 $(OBJ)\Win32FileStream.obj \
	 $(OBJ)\Win32LibraryPeer.obj \
	 $(OBJ)\Win32LocalePeer.obj \
	 $(OBJ)\Win32Mutex.obj \
	 $(OBJ)\Win32Peer.obj \
	 $(OBJ)\Win32ProcessIORedirector.obj \
	 $(OBJ)\Win32ProcessPeer.obj \
	 $(OBJ)\Win32Registry.obj \
	 $(OBJ)\Win32SemaphorePeer.obj \
	 $(OBJ)\Win32SystemPeer.obj \
	 $(OBJ)\Win32SystemToolkit.obj \
	 $(OBJ)\Win32Thread.obj \
	 $(OBJ)\BasicException.obj \
	 $(OBJ)\Event.obj \
	 $(OBJ)\EventHandler.obj \
	 $(OBJ)\PropertyChangeEvent.obj \
	 $(OBJ)\ThreadEvent.obj \
	 $(OBJ)\BasicInputStream.obj \
	 $(OBJ)\BasicOutputStream.obj \
	 $(OBJ)\Directory.obj \
	 $(OBJ)\File.obj \
	 $(OBJ)\FilePath.obj \
	 $(OBJ)\FileStream.obj \
	 $(OBJ)\MemoryStream.obj \
	 $(OBJ)\Stream.obj \
	 $(OBJ)\TextInputStream.obj \
	 $(OBJ)\TextOutputStream.obj \
	 $(OBJ)\CommandLine.obj \
	 $(OBJ)\Condition.obj \
	 $(OBJ)\DateTime.obj \
	 $(OBJ)\Dictionary.obj \
	 $(OBJ)\ErrorLog.obj \
	 $(OBJ)\Locales.obj \
	 $(OBJ)\MessageLoader.obj \
	 $(OBJ)\MIMEType.obj \
	 $(OBJ)\Mutex.obj \
	 $(OBJ)\PackageInfo.obj \
	 $(OBJ)\Parser.obj \
	 $(OBJ)\ProcessWithRedirectedIO.obj \
	 $(OBJ)\Registry.obj \
	 $(OBJ)\Semaphore.obj \
	 $(OBJ)\StringsMessageLoader.obj \
	 $(OBJ)\StringUtils.obj \
	 $(OBJ)\System.obj \
	 $(OBJ)\SystemToolkit.obj \
	 $(OBJ)\TextCodec.obj \
	 $(OBJ)\Thread.obj \
	 $(OBJ)\VCFMath.obj \
	 $(OBJ)\VCFProcess.obj \
	 $(OBJ)\VCFString.obj \
	 $(OBJ)\XMLParser.obj \
	 $(OBJ)\Object.obj \
	 $(OBJ)\ObjectWithEvents.obj \
	 $(OBJ)\Class.obj \
	 $(OBJ)\ClassRegistry.obj \
	 $(OBJ)\InterfaceClass.obj \
	 $(OBJ)\VariantData.obj
         
LIBFILES=ODBC32.LIB UUID.LIB
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

$(PROJECT2):: $(OBJFILES)
    $(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS2) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist $(BIN)\FoundationKit_bcc$(DBGDLL).lib move $(BIN)\FoundationKit_bcc$(DBGDLL).lib $(LIBDIR)
    
#Dependencies - explicit rules
$(OBJ)\FoundationKit.obj:                ..\..\..\src\vcf\FoundationKit\FoundationKit.cpp           
$(OBJ)\Library.obj:                      ..\..\..\src\vcf\FoundationKit\Library.cpp                 
$(OBJ)\Win32Condition.obj:               ..\..\..\src\vcf\FoundationKit\Win32Condition.cpp          
$(OBJ)\Win32FilePeer.obj:                ..\..\..\src\vcf\FoundationKit\Win32FilePeer.cpp           
$(OBJ)\Win32FileStream.obj:              ..\..\..\src\vcf\FoundationKit\Win32FileStream.cpp         
$(OBJ)\Win32LibraryPeer.obj:             ..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.cpp        
$(OBJ)\Win32LocalePeer.obj:              ..\..\..\src\vcf\FoundationKit\Win32LocalePeer.cpp         
$(OBJ)\Win32Mutex.obj:                   ..\..\..\src\vcf\FoundationKit\Win32Mutex.cpp              
$(OBJ)\Win32Peer.obj:                    ..\..\..\src\vcf\FoundationKit\Win32Peer.cpp               
$(OBJ)\Win32ProcessIORedirector.obj:     ..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.cpp
$(OBJ)\Win32ProcessPeer.obj:             ..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.cpp        
$(OBJ)\Win32Registry.obj:                ..\..\..\src\vcf\FoundationKit\Win32Registry.cpp           
$(OBJ)\Win32SemaphorePeer.obj:           ..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.cpp      
$(OBJ)\Win32SystemPeer.obj:              ..\..\..\src\vcf\FoundationKit\Win32SystemPeer.cpp         
$(OBJ)\Win32SystemToolkit.obj:           ..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.cpp      
$(OBJ)\Win32Thread.obj:                  ..\..\..\src\vcf\FoundationKit\Win32Thread.cpp             
$(OBJ)\BasicException.obj:               ..\..\..\src\vcf\FoundationKit\BasicException.cpp          
$(OBJ)\Event.obj:                        ..\..\..\src\vcf\FoundationKit\Event.cpp                   
$(OBJ)\EventHandler.obj:                 ..\..\..\src\vcf\FoundationKit\EventHandler.cpp            
$(OBJ)\PropertyChangeEvent.obj:          ..\..\..\src\vcf\FoundationKit\PropertyChangeEvent.cpp     
$(OBJ)\ThreadEvent.obj:                  ..\..\..\src\vcf\FoundationKit\ThreadEvent.cpp             
$(OBJ)\BasicInputStream.obj:             ..\..\..\src\vcf\FoundationKit\BasicInputStream.cpp        
$(OBJ)\BasicOutputStream.obj:            ..\..\..\src\vcf\FoundationKit\BasicOutputStream.cpp       
$(OBJ)\Directory.obj:                    ..\..\..\src\vcf\FoundationKit\Directory.cpp               
$(OBJ)\File.obj:                         ..\..\..\src\vcf\FoundationKit\File.cpp                    
$(OBJ)\FilePath.obj:                     ..\..\..\src\vcf\FoundationKit\FilePath.cpp                
$(OBJ)\FileStream.obj:                   ..\..\..\src\vcf\FoundationKit\FileStream.cpp              
$(OBJ)\MemoryStream.obj:                 ..\..\..\src\vcf\FoundationKit\MemoryStream.cpp            
$(OBJ)\Stream.obj:                       ..\..\..\src\vcf\FoundationKit\Stream.cpp                  
$(OBJ)\TextInputStream.obj:              ..\..\..\src\vcf\FoundationKit\TextInputStream.cpp         
$(OBJ)\TextOutputStream.obj:             ..\..\..\src\vcf\FoundationKit\TextOutputStream.cpp        
$(OBJ)\CommandLine.obj:                  ..\..\..\src\vcf\FoundationKit\CommandLine.cpp             
$(OBJ)\Condition.obj:                    ..\..\..\src\vcf\FoundationKit\Condition.cpp               
$(OBJ)\DateTime.obj:                     ..\..\..\src\vcf\FoundationKit\DateTime.cpp                
$(OBJ)\Dictionary.obj:                   ..\..\..\src\vcf\FoundationKit\Dictionary.cpp              
$(OBJ)\ErrorLog.obj:                     ..\..\..\src\vcf\FoundationKit\ErrorLog.cpp                
$(OBJ)\Locales.obj:                      ..\..\..\src\vcf\FoundationKit\Locales.cpp                 
$(OBJ)\MessageLoader.obj:                ..\..\..\src\vcf\FoundationKit\MessageLoader.cpp           
$(OBJ)\MIMEType.obj:                     ..\..\..\src\vcf\FoundationKit\MIMEType.cpp                
$(OBJ)\Mutex.obj:                        ..\..\..\src\vcf\FoundationKit\Mutex.cpp                   
$(OBJ)\PackageInfo.obj:                  ..\..\..\src\vcf\FoundationKit\PackageInfo.cpp             
$(OBJ)\Parser.obj:                       ..\..\..\src\vcf\FoundationKit\Parser.cpp                  
$(OBJ)\ProcessWithRedirectedIO.obj:      ..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.cpp 
$(OBJ)\Registry.obj:                     ..\..\..\src\vcf\FoundationKit\Registry.cpp                
$(OBJ)\Semaphore.obj:                    ..\..\..\src\vcf\FoundationKit\Semaphore.cpp               
$(OBJ)\StringsMessageLoader.obj:         ..\..\..\src\vcf\FoundationKit\StringsMessageLoader.cpp    
$(OBJ)\StringUtils.obj:                  ..\..\..\src\vcf\FoundationKit\StringUtils.cpp             
$(OBJ)\System.obj:                       ..\..\..\src\vcf\FoundationKit\System.cpp                  
$(OBJ)\SystemToolkit.obj:                ..\..\..\src\vcf\FoundationKit\SystemToolkit.cpp           
$(OBJ)\TextCodec.obj:                    ..\..\..\src\vcf\FoundationKit\TextCodec.cpp               
$(OBJ)\Thread.obj:                       ..\..\..\src\vcf\FoundationKit\Thread.cpp                  
$(OBJ)\VCFMath.obj:                      ..\..\..\src\vcf\FoundationKit\VCFMath.cpp                 
$(OBJ)\VCFProcess.obj:                   ..\..\..\src\vcf\FoundationKit\VCFProcess.cpp              
$(OBJ)\VCFString.obj:                    ..\..\..\src\vcf\FoundationKit\VCFString.cpp               
$(OBJ)\XMLParser.obj:                    ..\..\..\src\vcf\FoundationKit\XMLParser.cpp               
$(OBJ)\Object.obj:                       ..\..\..\src\vcf\FoundationKit\Object.cpp                  
$(OBJ)\ObjectWithEvents.obj:             ..\..\..\src\vcf\FoundationKit\ObjectWithEvents.cpp        
$(OBJ)\Class.obj:                        ..\..\..\src\vcf\FoundationKit\Class.cpp                   
$(OBJ)\ClassRegistry.obj:                ..\..\..\src\vcf\FoundationKit\ClassRegistry.cpp           
$(OBJ)\InterfaceClass.obj:               ..\..\..\src\vcf\FoundationKit\InterfaceClass.cpp          
$(OBJ)\VariantData.obj:                  ..\..\..\src\vcf\FoundationKit\VariantData.cpp             


