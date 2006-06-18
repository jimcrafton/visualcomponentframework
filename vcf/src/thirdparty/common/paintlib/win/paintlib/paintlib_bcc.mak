#######################################################
# MAKEFILE for building paintlib_bcc_s(d).lib         #
#                                                     #
#                                                     #
# (c) 2006 by Darko Miletic                           #
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
SYSDEFINES=_LIB;USE_LIBTIFF_LIB;USE_LIBJPEG_LIB;USE_LIBPNG_LIB;USE_ZLIB_LIB;HAVE_MEMORY_H=1
OUTDIR=..\..\..\..\..\..\lib
TDIR=S

CFLAGS=$(CFLAGS) -w-8057 -w-8012
CPPFLAGS=$(CPPFLAGS) -w-8057 -w-8012 -w-8002 -w-8022 -w-8075

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	!message Building debug version of project
!endif

LIBNAME=paintlib_bcc_s$(DBG).lib
DLLNAME=
INCDIR=..\..\..\..\..\..\src;..\..\common;..\..\common\filter;..\..\..\LibTIFF;..\..\..\LibJPEG;..\..\..\LibPNG;..\..\..\ZLib;..\..\..\Libungif\lib;..\..\..\Libcurl\include
LIBDIR=..\..\..\..\..\..\lib
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=
SYSDEFINES=STRICT;WIN32;_MBCS;NO_MFC;$(SYSDEFINES)
.path.cpp=.;..\..\common;..\..\common\filter
.path.c=..\..\common
.path.obj=$(OBJ)         

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
CPPFILES= PLFilterContrast.cpp \
          PLFilterCrop.cpp \
          PLFilterFlip.cpp \
          PLFilterGetAlpha.cpp \
          PLFilterGrayscale.cpp \
          PLFilterIntensity.cpp \
          PLFilterLightness.cpp \
          PLFilterMirror.cpp \
          PLFilterQuantize.cpp \
          PLFilterResize.cpp \
          PLFilterResizeBilinear.cpp \
          PLFilterResizeBox.cpp \
          PLFilterResizeGaussian.cpp \
          PLFilterResizeHamming.cpp \
          PLFilterThreshold.cpp \
          PLFilter.cpp \
          plfiltercolorize.cpp \
          plfilterfliprgb.cpp \
          plfilterrotate.cpp \
          plfiltervideoinvert.cpp \
          plhsvconvert.cpp \
          plinplacefilter.cpp \
          jmemdest.cpp \
          jmemsrc.cpp \
          planybmp.cpp \
          planydec.cpp \
          plbitmap.cpp \
          plbmpbase.cpp \
          plbmpdec.cpp \
          plbmpenc.cpp \
          plbmpinfo.cpp \
          pldatasink.cpp \
          pldatasrc.cpp \
          plexcept.cpp \
          plexif.cpp \
          plfilesink.cpp \
          plfilesrc.cpp \
          pliff85dec.cpp \
          pljpegdec.cpp \
          pljpegenc.cpp \
          plmemsink.cpp \
          plmemsrc.cpp \
          PLObject.cpp \
          plpcxdec.cpp \
          plpgmdec.cpp \
          plpicdec.cpp \
          plpicenc.cpp \
          plpictdec.cpp \
          plpixelformat.cpp \
          plpngdec.cpp \
          plpngenc.cpp \
          plppmdec.cpp \
          plpsddec.cpp \
          plsgidec.cpp \
          plsubbmp.cpp \
          pltgadec.cpp \
          pltiffdec.cpp \
          pltiffenc.cpp \
          pltiffencex.cpp \
          pldibsect.cpp \
          plressrc.cpp \
          plStreamSink.cpp \
          plwemfdec.cpp \
          plwinbmp.cpp 

CFILES=tif_msrc.c

OBJFILES=$(CPPFILES:.cpp=.obj^ ) tif_msrc.obj
         
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
	-@if not exist bcc mkdir bcc
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

#$(PROJECT1): $(OBJFILES)
#  @$(LB) /P1024 $(BIN)\$(LIBNAME) /a$(OBJFILES)
    
#Dependencies - explicit rules

