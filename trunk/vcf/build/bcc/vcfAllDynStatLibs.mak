#######################################################
# MAKEFILE for building all dynamic/static libs       #
#                                                     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

MK=make
VCFBUILDROOT=$(VCF_BIN)\..\build\bcc
VCFBIN=$(VCF_BIN)

!ifndef FREECOMP
FREECOMP = TRUE
!endif

!if $(FREECOMP) != TRUE && $(FREECOMP) != FALSE
!  error Illegal value for FREECOMP option
!endif

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

!if $(FREECOMP) == TRUE
all: FoundationKit GraphicsKit ImageFormats NetworkKit InternetKit RemoteObjectKit ApplicationKit OpenGLKit
!else
all: FoundationKit GraphicsKit ImageFormats NetworkKit InternetKit RemoteObjectKit ApplicationKit HTMLKit OpenGLKit
!endif

clean::
	-@cd $(VCFBUILDROOT)\ApplicationKit
	-@$(MK) -fApplicationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\FoundationKit
	-@$(MK) -fFoundationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -fRegExx.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBUILDROOT)\GraphicsKit
	-@$(MK) -fImageFormats.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -fGraphicsKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -flibAGG.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\NetworkKit
	-@$(MK) -fNetworkKit.mak -DFREECOMP=$(FREECOMP) -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\RemoteObjectKit
	-@$(MK) -fRemoteObjectKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\HTMLKit
	-@$(MK) -fHTMLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\OpenGLKit
	-@$(MK) -fOpenGLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean	
	-@cd $(VCFBUILDROOT)\InternetKit
	-@$(MK) -fInternetKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean		
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\FreeImageLib
	-@$(MK) -fFreeImageLib_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\LibJPEG
	-@$(MK) -fLibJPEG_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibMNG
	-@$(MK) -fLibMNG_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\LibPNG
	-@$(MK) -fLibPNG_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibTIFF
	-@$(MK) -fLibTIFF_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\ZLib
	-@$(MK) -fZLib_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) clean
	-@cd $(VCFBUILDROOT)

ApplicationKit:: FoundationKit GraphicsKit
	@cd $(VCFBUILDROOT)\ApplicationKit
	@$(MK) -fApplicationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

ApplicationKit_dll:: FoundationKit_dll GraphicsKit_dll
	@cd $(VCFBUILDROOT)\ApplicationKit
	@$(MK) -fApplicationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)
	
FoundationKit:: RegExx
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

FoundationKit_dll::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)

FoundationKit_stat::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

ImageFormats:: thirdparty FoundationKit GraphicsKit ApplicationKit
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fImageFormats.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit:: FoundationKit libAGG thirdparty
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit_dll:: FoundationKit_dll libAGG thirdparty
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)

OpenGLKit:: GraphicsKit ApplicationKit 
	@cd $(VCFBUILDROOT)\OpenGLKit
	@$(MK) -fOpenGLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

InternetKit:: FoundationKit 
	@cd $(VCFBUILDROOT)\InternetKit
	@$(MK) -fInternetKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit_stat:: FoundationKit_stat libAGG thirdparty
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

libAGG::
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -flibAGG.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

RegExx::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fRegExx.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

NetworkKit:: FoundationKit
	@cd $(VCFBUILDROOT)\NetworkKit
	@$(MK) -fNetworkKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

RemoteObjectKit:: FoundationKit NetworkKit
	@cd $(VCFBUILDROOT)\RemoteObjectKit
	@$(MK) -fRemoteObjectKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

HTMLKit:: FoundationKit GraphicsKit ApplicationKit
	@cd $(VCFBUILDROOT)\HTMLKit
	@$(MK) -fHTMLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

HTMLKit_dll:: FoundationKit_dll GraphicsKit_dll ApplicationKit_dll
	@cd $(VCFBUILDROOT)\HTMLKit
	@$(MK) -fHTMLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)

HTMLKit_stat:: 
	@cd $(VCFBUILDROOT)\HTMLKit
	@$(MK) -fHTMLKit.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

thirdparty: FreeImageLib

FreeImageLib:: LibJPEG LibMNG LibPNG LibTIFF ZLib
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\FreeImageLib
	@$(MK) -fFreeImageLib_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibJPEG::
	@cd $(VCFBIN)\..\src\thirdparty\common\LibJPEG
	@$(MK) -fLibJPEG_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibMNG::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibMNG
	@$(MK) -fLibMNG_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)
LibPNG::
	@cd $(VCFBIN)\..\src\thirdparty\common\LibPNG
	@$(MK) -fLibPNG_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibTIFF::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibTIFF
	@$(MK) -fLibTIFF_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

ZLib::
	@cd $(VCFBIN)\..\src\thirdparty\common\ZLib
	@$(MK) -fZLib_bcc.mak -DFREECOMP=$(FREECOMP) -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)
