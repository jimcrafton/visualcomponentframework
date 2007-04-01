#makefile for buttons.cpp

DEBUG_OUT = Debug
RELEASE_OUT = Release

OBJECTFILES_D = $(DEBUG_OUT)/buttons.o
OBJECTFILES = $(RELEASE_OUT)/buttons.o


CXX_FLAGS_D=-ggdb -DVCF_XCB -pipe -frtti -fexceptions -fmessage-length=0 -Wno-multichar -D_DEBUG -I $(VCF_ROOT)/src -c
CXX_FLAGS=-DVCF_GCC -DVCF_POSIX -Wno-multichar -I $(VCF_ROOT)/src -O2 -c


APPLICATIONKIT_LIBS_D = -lpthread -lFoundationKit_d -lGraphicsKit_d -lApplicationKit_d
APPLICATIONKIT_LIBS = -lFoundationKit -lGraphicsKit -lApplicationKit
LINKER_FLAGS_D = -L$(VCF_ROOT)/bin $(APPLICATIONKIT_LIBS_D) -ggdb -o

LINKER_FLAGS = -L$(VCF_ROOT)/bin $(APPLICATIONKIT_LIBS) -o


CXX = g++

LINKER = g++


OUT_D=$(DEBUG_OUT)/buttons
OUT = $(RELEASE_OUT)/buttons


target : 
	echo please choose either "debug", "release" or "all" '(for both debug and release)'

prep_Debug_dirs: 
	if ! `test -d $(DEBUG_OUT)`;then mkdir $(DEBUG_OUT);fi;\
	
prep_Release_dirs: 
	if ! `test -d $(RELEASE_OUT)`;then mkdir $(RELEASE_OUT);fi;\	
	
debug : prep_Debug_dirs $(OUT_D)

$(OUT_D) : $(OBJECTFILES_D)
	$(LINKER) $(LINKER_FLAGS_D) $(OUT_D) $(OBJECTFILES_D)
	

$(DEBUG_OUT)/buttons.o : buttons.cpp
	$(CXX) $(CXX_FLAGS_D) buttons.cpp -o $(DEBUG_OUT)/buttons.o
