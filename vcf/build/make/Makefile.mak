## generic makefile included from builddir

SRC=../../../../src
LIB=../../../../lib



OBJECTS  := $(SOURCES:.cpp=.o) 

CXXFLAGS  = -DVCF_POSIX -Wno-multichar -I$(SRC) 
#CXXFLAGS += -DVCF_GTK $(shell pkg-config gtk+-2.0 --cflags)

LDFLAGS   = -L$(LIB)
#LDFLAGS  +=  $(shell pkg-config gtk+-2.0 --libs)
LDFLAGS  += -lpthread -lrt -ldl -shared

ARFLAGS   = -cru


## GraphicsKit
ifeq ($(KIT), GraphicsKit)
   ifeq ($(BUILD), Debug)
      OBJECTS += $(LIB)/libAGG_$(COMPILER)_d.a
   else
      OBJECTS += $(LIB)/libAGG_$(COMPILER).a
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
debug:   LDFLAGS  := $(LDFLAGS:Kit=Kit_$(COMPILER)_d)
debug:   $(TARGET)

release: CXXFLAGS += -DNDEBUG -Os
release:   LDFLAGS  := $(LDFLAGS:Kit=Kit_$(COMPILER))
release: $(TARGET)

$(TARGET): $(OBJECTS)
ifeq ($(KIT), LibAGG)
	$(AR) $(ARFLAGS) $(LIB)/$@ $^
else
	$(CXX) $(LDFLAGS) -o $(LIB)/$@ $^
endif

