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
FoundationKit-debug: TARGET     = libFoundationKit_d.so
FoundationKit-debug: FoundationKit/Debug/Makefile FK-make-debug
clean-FoundationKit-debug:
	 -rm FoundationKit/Debug/*
	 -rm $(LIB)/libFoundationKit_d.so

FoundationKit-release: BUILD    = Release
FoundationKit-release: KIT      = FoundationKit
FoundationKit-release: TARGET   = libFoundationKit.so
FoundationKit-release: FoundationKit/Release/Makefile FK-make-release
clean-FoundationKit-release:
	 -rm FoundationKit/Release/*
	 -rm $(LIB)/libFoundationKit.so

## GraphicsKit
GraphicsKit-debug: BUILD        = Debug
GraphicsKit-debug: KIT          = GraphicsKit
GraphicsKit-debug: TARGET       = libGraphicsKit_d.so
GraphicsKit-debug: GraphicsKit/Debug/Makefile LibAGG-debug GK-make-debug
clean-GraphicsKit-debug:
	 -rm GraphicsKit/Debug/*
	 -rm $(LIB)/libGraphicsKit_d.so

GraphicsKit-release: BUILD      = Release
GraphicsKit-release: KIT        = GraphicsKit
GraphicsKit-release: TARGET     = libGraphicsKit.so
GraphicsKit-release: GraphicsKit/Release/Makefile LibAGG-release GK-make-release
clean-GraphicsKit-release:
	 -rm GraphicsKit/Release/*
	 -rm $(LIB)/libGraphicsKit.so

## ApplicationKit
ApplicationKit-debug: BUILD     = Debug
ApplicationKit-debug: KIT       = ApplicationKit
ApplicationKit-debug: TARGET    = libApplicationKit_d.so
ApplicationKit-debug: ApplicationKit/Debug/Makefile AK-make-debug
clean-ApplicationKit-debug:
	 -rm ApplicationKit/Debug/*
	 -rm $(LIB)/libApplicationKit_d.so

ApplicationKit-release: BUILD   = Release
ApplicationKit-release: KIT     = ApplicationKit
ApplicationKit-release: TARGET  = libApplicationKit.so
ApplicationKit-release: ApplicationKit/Release/Makefile AK-make-release
clean-ApplicationKit-release:
	 -rm ApplicationKit/Release/*
	 -rm $(LIB)/libApplicationKit.so

## NetworkKit
NetworkKit-debug: BUILD         = Debug
NetworkKit-debug: KIT           = NetworkKit
NetworkKit-debug: TARGET        = libNetworkKit_d.so
NetworkKit-debug: NetworkKit/Debug/Makefile NK-make-debug
clean-NetworkKit-debug:
	 -rm NetworkKit/Debug/*
	 -rm $(LIB)/libNetworkKit_d.so

NetworkKit-release: BUILD       = Release
NetworkKit-release: KIT         = NetworkKit
NetworkKit-release: TARGET      = libNetworkKit.so
NetworkKit-release: NetworkKit/Release/Makefile NK-make-release
clean-NetworkKit-release:
	 -rm NetworkKit/Release/*
	 -rm $(LIB)/libNetworkKit.so

## OpenGLKit
OpenGLKit-debug: BUILD          = Debug
OpenGLKit-debug: KIT            = OpenGLKit
OpenGLKit-debug: TARGET         = libOpenGLKit_d.so
OpenGLKit-debug: OpenGLKit/Debug/Makefile OK-make-debug
clean-OpenGLKit-debug:
	 -rm OpenGLKit/Debug/*
	 -rm $(LIB)/libOpenGLKit_d.so

OpenGLKit-release: BUILD        = Release
OpenGLKit-release: KIT          = OpenGLKit
OpenGLKit-release: TARGET       = libOpenGLKit.so
OpenGLKit-release: OpenGLKit/Release/Makefile OK-make-release
clean-OpenGLKit-release:
	 -rm OpenGLKit/Release/*
	 -rm $(LIB)/libOpenGLKit.so

## RemoteObjectKit
RemoteObjectKit-debug: BUILD    = Debug
RemoteObjectKit-debug: KIT      = RemoteObjectKit
RemoteObjectKit-debug: TARGET   = libRemoteObjectKit_d.so
RemoteObjectKit-debug: RemoteObjectKit/Debug/Makefile RK-make-debug
clean-RemoteObjectKit-debug:
	-rm RemoteObjectKit/Debug/*
	-rm $(LIB)/libRemoteObjectKit_d.so

RemoteObjectKit-release: BUILD  = Release
RemoteObjectKit-release: KIT    = RemoteObjectKit
RemoteObjectKit-release: TARGET = libRemoteObjectKit.so
RemoteObjectKit-release: RemoteObjectKit/Release/Makefile RK-make-release
clean-RemoteObjectKit-release:
	-rm RemoteObjectKit/Release/*
	-rm $(LIB)/libRemoteObjectKit.so

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

clean-release: clean-FoundationKit-release \
	clean-GraphicsKit-release \
	clean-ApplicationKit-release \
	clean-NetworkKit-release \
	clean-OpenGLKit-release \
	clean-RemoteObjectKit-release \
	clean-LibAGG-release

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


