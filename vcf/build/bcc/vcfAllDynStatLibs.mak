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

all: FoundationKit GraphicsKit ImageFormats NetworkKit RemoteObjectKit ApplicationKit Win32HTMLBrowser OpenGLKit

clean::
	-@cd $(VCFBUILDROOT)\ApplicationKit
	-@$(MK) -fApplicationKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\FoundationKit
	-@$(MK) -fFoundationKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -fRegExx.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBUILDROOT)\GraphicsKit
	-@$(MK) -fImageFormats.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -fGraphicsKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@$(MK) -flibAGG.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\NetworkKit
	-@$(MK) -fNetworkKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\RemoteObjectKit
	-@$(MK) -fRemoteObjectKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\Win32HTMLBrowser
	-@$(MK) -fWin32HTMLBrowser.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean
	-@cd $(VCFBUILDROOT)\OpenGLKit
	-@$(MK) -fOpenGLKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET) clean	
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\FreeImageLib
	-@$(MK) -fFreeImageLib_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibJPEG
	-@$(MK) -fLibJPEG_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibMNG
	-@$(MK) -fLibMNG_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibPNG
	-@$(MK) -fLibPNG_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibTIFF
	-@$(MK) -fLibTIFF_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\ZLib
	-@$(MK) -fZLib_bcc.mak -DBMODE=$(BMODE) clean
	-@cd $(VCFBUILDROOT)

ApplicationKit:: FoundationKit GraphicsKit Win32HTMLBrowser_stat
	@cd $(VCFBUILDROOT)\ApplicationKit
	@$(MK) -fApplicationKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

ApplicationKit_dll:: FoundationKit_dll GraphicsKit_dll
	@cd $(VCFBUILDROOT)\ApplicationKit
	@$(MK) -fApplicationKit.mak -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)
	
FoundationKit:: RegExx
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

FoundationKit_dll::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)

FoundationKit_stat::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fFoundationKit.mak -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

ImageFormats:: thirdparty FoundationKit GraphicsKit ApplicationKit_dll
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fImageFormats.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit:: FoundationKit libAGG
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit_dll:: FoundationKit_dll libAGG
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DBMODE=$(BMODE) -DTARGET=DLL
	@cd $(VCFBUILDROOT)

OpenGLKit:: GraphicsKit ApplicationKit 
	@cd $(VCFBUILDROOT)\OpenGLKit
	@$(MK) -fOpenGLKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

GraphicsKit_stat:: FoundationKit_stat libAGG
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -fGraphicsKit.mak -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

libAGG::
	@cd $(VCFBUILDROOT)\GraphicsKit
	@$(MK) -flibAGG.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

RegExx::
	@cd $(VCFBUILDROOT)\FoundationKit
	@$(MK) -fRegExx.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

NetworkKit:: FoundationKit
	@cd $(VCFBUILDROOT)\NetworkKit
	@$(MK) -fNetworkKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

RemoteObjectKit:: FoundationKit NetworkKit
	@cd $(VCFBUILDROOT)\RemoteObjectKit
	@$(MK) -fRemoteObjectKit.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

Win32HTMLBrowser:: FoundationKit GraphicsKit ApplicationKit
	@cd $(VCFBUILDROOT)\Win32HTMLBrowser
	@$(MK) -fWin32HTMLBrowser.mak -DBMODE=$(BMODE) -DTARGET=$(TARGET)
	@cd $(VCFBUILDROOT)

Win32HTMLBrowser_stat::
	@cd $(VCFBUILDROOT)\Win32HTMLBrowser
	@$(MK) -fWin32HTMLBrowser.mak -DBMODE=$(BMODE) -DTARGET=LIB
	@cd $(VCFBUILDROOT)

thirdparty: FreeImageLib

FreeImageLib:: LibJPEG LibMNG LibPNG LibTIFF ZLib
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\FreeImageLib
	@$(MK) -fFreeImageLib_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibJPEG::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibJPEG
	@$(MK) -fLibJPEG_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibMNG::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibMNG
	@$(MK) -fLibMNG_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)
LibPNG::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibPNG
	@$(MK) -fLibPNG_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

LibTIFF::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\LibTIFF
	@$(MK) -fLibTIFF_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)

ZLib::
	@cd $(VCFBIN)\..\src\thirdparty\common\FreeImage\Source\ZLib
	@$(MK) -fZLib_bcc.mak -DBMODE=$(BMODE)
	@cd $(VCFBUILDROOT)
