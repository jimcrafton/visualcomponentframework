#######################################################
# MAKEFILE for building FreeImage_bcc_s(d).lib        #
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
SYSDEFINES=_LIB;USE_LIBMNG_LIB;USE_LIBJPEG_LIB;USE_LIBPNG_LIB;USE_LIBTIFF_LIB;USE_ZLIB_LIB;BUILD_FREEIMAGE_LIB
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

CPPFLAGS=$(CPPFLAGS) -w-8012 -w-8066 -w-8027 -w-8004 -w-8057 -w-8098 -w-8008

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif


LIBNAME=FreeImage_bcc_s$(DBG).lib
DLLNAME=
INCDIR=..\;..\FreeImage;..\..\..\..\..\..\src
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
OBJFILES=$(OBJ)\NNQuantizer.obj \
	$(OBJ)\WuQuantizer.obj \
	$(OBJ)\Conversion.obj \
	$(OBJ)\Conversion16_555.obj \
	$(OBJ)\Conversion16_565.obj \
	$(OBJ)\Conversion24.obj \
	$(OBJ)\Conversion32.obj \
	$(OBJ)\Conversion8.obj \
	$(OBJ)\Plugin.obj \
	$(OBJ)\PluginBMP.obj \
	$(OBJ)\PluginICO.obj \
	$(OBJ)\PluginIFF.obj \
	$(OBJ)\PluginJPEG.obj \
	$(OBJ)\PluginKOALA.obj \
	$(OBJ)\PluginMNG.obj \
	$(OBJ)\PluginPCD.obj \
	$(OBJ)\PluginPCX.obj \
	$(OBJ)\PluginPNG.obj \
	$(OBJ)\PluginPNM.obj \
	$(OBJ)\PluginPSD.obj \
	$(OBJ)\PluginRAS.obj \
	$(OBJ)\PluginTARGA.obj \
	$(OBJ)\PluginTIFF.obj \
	$(OBJ)\PluginWBMP.obj \
	$(OBJ)\BitmapAccess.obj \
	$(OBJ)\FreeImage.obj \
	$(OBJ)\FreeImageIO.obj \
	$(OBJ)\GetType.obj \
	$(OBJ)\LoadFunctions.obj
         
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
$(OBJ)\NNQuantizer.obj:       ..\FreeImage\NNQuantizer.cpp     
$(OBJ)\WuQuantizer.obj:       ..\FreeImage\WuQuantizer.cpp     
$(OBJ)\Conversion.obj:        ..\FreeImage\Conversion.cpp      
$(OBJ)\Conversion16_555.obj:  ..\FreeImage\Conversion16_555.cpp
$(OBJ)\Conversion16_565.obj:  ..\FreeImage\Conversion16_565.cpp
$(OBJ)\Conversion24.obj:      ..\FreeImage\Conversion24.cpp    
$(OBJ)\Conversion32.obj:      ..\FreeImage\Conversion32.cpp    
$(OBJ)\Conversion8.obj:       ..\FreeImage\Conversion8.cpp     
$(OBJ)\Plugin.obj:            ..\FreeImage\Plugin.cpp          
$(OBJ)\PluginBMP.obj:         ..\FreeImage\PluginBMP.cpp       
$(OBJ)\PluginICO.obj:         ..\FreeImage\PluginICO.cpp       
$(OBJ)\PluginIFF.obj:         ..\FreeImage\PluginIFF.cpp       
$(OBJ)\PluginJPEG.obj:        ..\FreeImage\PluginJPEG.cpp      
$(OBJ)\PluginKOALA.obj:       ..\FreeImage\PluginKOALA.cpp     
$(OBJ)\PluginMNG.obj:         ..\FreeImage\PluginMNG.cpp       
$(OBJ)\PluginPCD.obj:         ..\FreeImage\PluginPCD.cpp       
$(OBJ)\PluginPCX.obj:         ..\FreeImage\PluginPCX.cpp       
$(OBJ)\PluginPNG.obj:         ..\FreeImage\PluginPNG.cpp       
$(OBJ)\PluginPNM.obj:         ..\FreeImage\PluginPNM.cpp       
$(OBJ)\PluginPSD.obj:         ..\FreeImage\PluginPSD.cpp       
$(OBJ)\PluginRAS.obj:         ..\FreeImage\PluginRAS.cpp       
$(OBJ)\PluginTARGA.obj:       ..\FreeImage\PluginTARGA.cpp     
$(OBJ)\PluginTIFF.obj:        ..\FreeImage\PluginTIFF.cpp      
$(OBJ)\PluginWBMP.obj:        ..\FreeImage\PluginWBMP.cpp      
$(OBJ)\BitmapAccess.obj:      ..\FreeImage\BitmapAccess.cpp    
$(OBJ)\FreeImage.obj:         ..\FreeImage\FreeImage.cpp       
$(OBJ)\FreeImageIO.obj:       ..\FreeImage\FreeImageIO.cpp     
$(OBJ)\GetType.obj:           ..\FreeImage\GetType.cpp         
$(OBJ)\LoadFunctions.obj:     ..\FreeImage\LoadFunctions.cpp   

