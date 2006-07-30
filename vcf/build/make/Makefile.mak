## generic makefile included from builddir

SRC=../../../../src
LIB=../../../../lib
BIN=../../../../bin



OBJECTS  := $(SOURCES:.cpp=.o) 

CXXFLAGS  = -Wno-multichar -pipe -frtti -fexceptions -I$(SRC) 


LDFLAGS   = -L$(LIB) -L$(BIN)
LDFLAGS  += -Wl -lpthread -lrt -ldl -luuid -shared

ARFLAGS   = -cru


## GraphicsKit
ifeq ($(KIT), GraphicsKit)
   ifeq ($(BUILD), Debug)
      OBJECTS += $(LIB)/libAGG_sd.a
   else
      OBJECTS += $(LIB)/libAGG_s.a
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


all: debug release

%.dep: %.cpp
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
release:   LDFLAGS  := $(LDFLAGS:Kit=Kit)
release: $(TARGET)

$(TARGET): $(OBJECTS)
ifeq ($(KIT), LibAGG)
	$(AR) $(ARFLAGS) $(LIB)/$@ $^
else
	$(CXX) $(LDFLAGS) -o $(BIN)/$@ $^
endif

