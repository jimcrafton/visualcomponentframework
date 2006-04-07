## generic makefile included from builddir

CXX=mingw32-g++
AR =ar

SRC=../../../../src
LIB=../../../../lib

OBJECTS  := $(SOURCES:.cpp=.o) 

CXXFLAGS  = -DVCF_GCC -DVCF_MINGW -DVCF_WIN32 -Wno-multichar -I$(SRC) 

LDFLAGS   = -L$(LIB)
LDFLAGS  += -lrpcrt4 -shared

ARFLAGS   = -cru

## GraphicsKit
ifeq ($(KIT), GraphicsKit)
   ifeq ($(BUILD), Debug)
      OBJECTS += $(LIB)/libagg_d.a
      #OBJECTS += $(LIB)/libjpeg_d.a
      #OBJECTS += $(LIB)/libpng_d.a
   else
      OBJECTS += $(LIB)/libagg.a
      #OBJECTS += $(LIB)/libjpeg.a
      #OBJECTS += $(LIB)/libpng.a
   endif
   LDFLAGS += -lFoundationKit
endif

## ApplicationKit
ifeq ($(KIT), ApplicationKit)
   LDFLAGS += -lFoundationKit -lGraphicsKit
endif

## NetworkKit
ifeq ($(KIT), NetworkKit)
   LDFLAGS += -lFoundationKit
endif

## OpenGLKit
ifeq ($(KIT), OpenGLKit)
   LDFLAGS += -lFoundationKit -lGraphicsKit -lApplicationKit
endif

## RemoteObjectKit
ifeq ($(KIT), RemoteObjectKit)
   LDFLAGS += -lFoundationKit -lNetworkKit
endif

## LibAGG
ifeq ($(KIT), LibAGG)
   CXXFLAGS += -I$(SRC)/thirdparty/common/agg/include
   VPATH = $(SRC)/thirdparty/common/agg/src
else
   VPATH = $(SRC)/vcf/$(KIT)
endif

## LibJPEG
#ifeq ($(KIT), LibJPEG)
   #CXXFLAGS += -I$(SRC)/thirdparty/common/LibJPEG
   #VPATH = $(SRC)/thirdparty/common/LibJPEG
#endif

## LibPNG
#ifeq ($(KIT), LibPNG)
   #CXXFLAGS += -I$(SRC)/thirdparty/common/LibPNG
   #VPATH = $(SRC)/thirdparty/common/LibPNG
#else
  # VPATH = $(SRC)/vcf/$(KIT)
#endif

all: debug release

%.dep: %.cpp
	@set -e; echo "Building dependencies: $(notdir $<)";\
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

%.dep: %.c
	@set -e; echo "Building dependencies: $(notdir $<)";\
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

-include $(SOURCES:.cpp=.dep)

debug:   CXXFLAGS += -ggdb -D_DEBUG
debug:   LDFLAGS  += -ggdb
debug:   LDFLAGS  := $(LDFLAGS:Kit=Kit_d)
debug:   $(TARGET)

release: CXXFLAGS += -DNDEBUG -Os
release: $(TARGET)

$(TARGET): $(OBJECTS)
#ifeq ($(KIT), LibAGG)
	$(AR) $(ARFLAGS) $(LIB)/$@ $^
#else
#	$(CXX) $(LDFLAGS) -o $(LIB)/$@ $^
#endif

