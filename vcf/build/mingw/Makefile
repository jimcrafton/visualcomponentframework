LIB = ../../lib

target:
	@echo Please choose either debug, release or all '(for both debug and release)'

all: debug release

debug: FoundationKit-debug \
	GraphicsKit-debug \
	ApplicationKit-debug \
	NetworkKit-debug \
	OpenGLKit-debug \
	RemoteObjectKit-debug

release: FoundationKit-release \
	GraphicsKit-release \
	ApplicationKit-release \
	NetworkKit-release \
	OpenGLKit-release \
	RemoteObjectKit-release


## FoundationKit
FoundationKit-debug: BUILD      = Debug
FoundationKit-debug: KIT        = FoundationKit
FoundationKit-debug: TARGET     = libFoundationKit_d.a
FoundationKit-debug: FoundationKit/Debug/Makefile FK-make-debug
clean-FoundationKit-debug:
	 -rm FoundationKit/Debug/*
	 -rm $(LIB)/libFoundationKit_d.a

FoundationKit-release: BUILD    = Release
FoundationKit-release: KIT      = FoundationKit
FoundationKit-release: TARGET   = libFoundationKit.a
FoundationKit-release: FoundationKit/Release/Makefile FK-make-release
clean-FoundationKit-release:
	 -rm FoundationKit/Release/*
	 -rm $(LIB)/libFoundationKit.a

## GraphicsKit
GraphicsKit-debug: BUILD        = Debug
GraphicsKit-debug: KIT          = GraphicsKit
GraphicsKit-debug: TARGET       = libGraphicsKit_d.a
GraphicsKit-debug: GraphicsKit/Debug/Makefile LibAGG-debug GK-make-debug
clean-GraphicsKit-debug:
	 -rm GraphicsKit/Debug/*
	 -rm $(LIB)/libGraphicsKit_d.a

GraphicsKit-release: BUILD      = Release
GraphicsKit-release: KIT        = GraphicsKit
GraphicsKit-release: TARGET     = libGraphicsKit.a
#GraphicsKit-release: GraphicsKit/Release/Makefile LibAGG-release LibJPEG-release LibPNG-release GK-make-release
GraphicsKit-release: GraphicsKit/Release/Makefile LibAGG-release GK-make-release
clean-GraphicsKit-release:
	 -rm GraphicsKit/Release/*
	 -rm $(LIB)/libGraphicsKit.a

## ApplicationKit
ApplicationKit-debug: BUILD     = Debug
ApplicationKit-debug: KIT       = ApplicationKit
ApplicationKit-debug: TARGET    = libApplicationKit_d.a
ApplicationKit-debug: ApplicationKit/Debug/Makefile AK-make-debug
clean-ApplicationKit-debug:
	 -rm ApplicationKit/Debug/*
	 -rm $(LIB)/libApplicationKit_d.a

ApplicationKit-release: BUILD   = Release
ApplicationKit-release: KIT     = ApplicationKit
ApplicationKit-release: TARGET  = libApplicationKit.a
ApplicationKit-release: ApplicationKit/Release/Makefile AK-make-release
clean-ApplicationKit-release:
	 -rm ApplicationKit/Release/*
	 -rm $(LIB)/libApplicationKit.a

## NetworkKit
NetworkKit-debug: BUILD         = Debug
NetworkKit-debug: KIT           = NetworkKit
NetworkKit-debug: TARGET        = libNetworkKit_d.a
NetworkKit-debug: NetworkKit/Debug/Makefile NK-make-debug
clean-NetworkKit-debug:
	 -rm NetworkKit/Debug/*
	 -rm $(LIB)/libNetworkKit_d.a

NetworkKit-release: BUILD       = Release
NetworkKit-release: KIT         = NetworkKit
NetworkKit-release: TARGET      = libNetworkKit.a
NetworkKit-release: NetworkKit/Release/Makefile NK-make-release
clean-NetworkKit-release:
	 -rm NetworkKit/Release/*
	 -rm $(LIB)/libNetworkKit.a

## OpenGLKit
OpenGLKit-debug: BUILD          = Debug
OpenGLKit-debug: KIT            = OpenGLKit
OpenGLKit-debug: TARGET         = libOpenGLKit_d.a
OpenGLKit-debug: OpenGLKit/Debug/Makefile OK-make-debug
clean-OpenGLKit-debug:
	 -rm OpenGLKit/Debug/*
	 -rm $(LIB)/libOpenGLKit_d.a

OpenGLKit-release: BUILD        = Release
OpenGLKit-release: KIT          = OpenGLKit
OpenGLKit-release: TARGET       = libOpenGLKit.a
OpenGLKit-release: OpenGLKit/Release/Makefile OK-make-release
clean-OpenGLKit-release:
	 -rm OpenGLKit/Release/*
	 -rm $(LIB)/libOpenGLKit.a

## RemoteObjectKit
RemoteObjectKit-debug: BUILD    = Debug
RemoteObjectKit-debug: KIT      = RemoteObjectKit
RemoteObjectKit-debug: TARGET   = libRemoteObjectKit_d.a
RemoteObjectKit-debug: RemoteObjectKit/Debug/Makefile RK-make-debug
clean-RemoteObjectKit-debug:
	-rm RemoteObjectKit/Debug/*
	-rm $(LIB)/libRemoteObjectKit_d.a

RemoteObjectKit-release: BUILD  = Release
RemoteObjectKit-release: KIT    = RemoteObjectKit
RemoteObjectKit-release: TARGET = libRemoteObjectKit.a
RemoteObjectKit-release: RemoteObjectKit/Release/Makefile RK-make-release
clean-RemoteObjectKit-release:
	-rm RemoteObjectKit/Release/*
	-rm $(LIB)/libRemoteObjectKit.a

## LibAGG
LibAGG-debug: BUILD    = Debug
LibAGG-debug: KIT      = LibAGG
LibAGG-debug: TARGET   = libagg_d.a
LibAGG-debug: LibAGG/Debug/Makefile AGG-make-debug
clean-LibAGG-debug:
	-rm LibAGG/Debug/*
	-rm $(LIB)/libagg_d.a

LibAGG-release: BUILD  = Release
LibAGG-release: KIT    = LibAGG
LibAGG-release: TARGET = libagg.a
LibAGG-release: LibAGG/Release/Makefile AGG-make-release
clean-LibAGG-release:
	-rm LibAGG/Release/*
	-rm $(LIB)/libagg.a

## LibJPEG
#LibJPEG-release: BUILD  = Release
#LibJPEG-release: KIT    = LibJPEG
#LibJPEG-release: TARGET = libjpeg.a
#LibJPEG-release: LibJPEG/Release/Makefile JPEG-make-release
#clean-LibJPEG-release:
	#-rm LibJPEG/Release/*
	#-rm $(LIB)/libjpeg.a

## LibPNG
#LibPNG-release: BUILD  = Release
#LibPNG-release: KIT    = LibPNG
#LibPNG-release: TARGET = libpng.a
#LibPNG-release: LibPNG/Release/Makefile PNG-make-release
#clean-LibPNG-release:
	#-rm LibPNG/Release/*
	#-rm $(LIB)/libpng.a
	
clean-release: clean-FoundationKit-release \
	clean-GraphicsKit-release \
	clean-ApplicationKit-release \
	clean-NetworkKit-release \
	clean-OpenGLKit-release \
	clean-RemoteObjectKit-release \
	clean-LibAGG-release \
	#clean-LibJPEG-release \
	#clean-LibPNG-release 

clean-debug: clean-FoundationKit-debug \
	clean-GraphicsKit-debug \
	clean-ApplicationKit-debug \
	clean-NetworkKit-debug \
	clean-OpenGLKit-debug \
	clean-RemoteObjectKit-debug \
	clean-LibAGG-debug

clean: clean-release clean-debug

distclean: clean
	-rm -rf FoundationKit
	-rm -rf GraphicsKit
	-rm -rf ApplicationKit
	-rm -rf NetworkKit
	-rm -rf OpenGLKit
	-rm -rf RemoteObjectKit
	-rm -rf LibAGG
	#-rm -rf LibJPEG
	#-rm -rf LibPNG

%Makefile:
	@[ -d $(LIB) ] || mkdir $(LIB); \
	[ -d $(KIT)/$(BUILD) ] || mkdir -p $(KIT)/$(BUILD); \
	\
	echo "BUILD  = $(BUILD)"                > ./$(KIT)/$(BUILD)/Makefile; \
	echo "KIT = $(KIT)"                    >> ./$(KIT)/$(BUILD)/Makefile; \
	echo "TARGET = $(TARGET)"              >> ./$(KIT)/$(BUILD)/Makefile; \
	echo "include ../../$(KIT).mak"        >> ./$(KIT)/$(BUILD)/Makefile; \
	echo "include ../../Makefile.mak"      >> ./$(KIT)/$(BUILD)/Makefile;

%make-debug:
	$(MAKE) -C $(KIT)/$(BUILD) debug

%make-release:
	$(MAKE) -C $(KIT)/$(BUILD) release


