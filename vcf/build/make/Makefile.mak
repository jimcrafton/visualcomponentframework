## generic makefile included from builddir

SRC=../../../../src
LIB=../../../../lib

OBJECTS  := $(SOURCES:.cpp=.o) 

CXXFLAGS  = -DVCF_GCC -DVCF_POSIX -Wno-multichar -I$(SRC) 
CXXFLAGS += -DVCF_GTK $(shell pkg-config gtk+-2.0 --cflags)

LDFLAGS   = -L$(LIB)
LDFLAGS  +=  $(shell pkg-config gtk+-2.0 --libs)
LDFLAGS  += -lpthread -ldl -shared

ARFLAGS   = -cru

## FoundationKit
ifeq ($(KIT), FoundationKit)
   LDFLAGS += -lpcre
endif

## GraphicsKit
ifeq ($(KIT), GraphicsKit)
   ifeq ($(BUILD), Debug)
      OBJECTS += $(LIB)/libagg_d.a
   else
      OBJECTS += $(LIB)/libagg.a
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

debug:   CXXFLAGS += -ggdb3 -D_DEBUG
debug:   LDFLAGS  += -ggdb3
debug:   LDFLAGS  := $(LDFLAGS:Kit=Kit_d)
debug:   $(TARGET)

release: CXXFLAGS += -DNDEBUG -Os
release: $(TARGET)

$(TARGET): $(OBJECTS)
ifeq ($(KIT), LibAGG)
	$(AR) $(ARFLAGS) $(LIB)/$@ $^
else
	$(CXX) $(LDFLAGS) -o $(LIB)/$@ $^
endif

