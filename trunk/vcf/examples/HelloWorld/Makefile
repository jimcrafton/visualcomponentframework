#makefile for HelloWorld

DEBUG_OUT = Debug
RELEASE_OUT = Release

OBJECTFILES_D = $(DEBUG_OUT)/HelloWorld.o
OBJECTFILES = $(RELEASE_OUT)/HelloWorld.o


GTK_CXX_FLAGS = `pkg-config gtk+-2.0 --cflags`
CXX_FLAGS_D=-ggdb -DVCF_GCC -DVCF_POSIX -Wno-multichar -c -DVCF_GTK -D_DEBUG -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -c
CXX_FLAGS=-DVCF_GCC -DVCF_POSIX -Wno-multichar -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -O2 -c

GTK_LINKER_FLAGS = `pkg-config gtk+-2.0 --libs`
APPLICATIONKIT_LIBS_D = -lpthread -lFoundationKit_d -lGraphicsKit_d -lApplicationKit_d
APPLICATIONKIT_LIBS = -lFoundationKit -lGraphicsKit -lApplicationKit
LINKER_FLAGS_D = -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPLICATIONKIT_LIBS_D) -ggdb -o

LINKER_FLAGS = -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPLICATIONKIT_LIBS) -o


CXX = g++

LINKER = g++


OUT_D = $(DEBUG_OUT)/HelloWorld
OUT = $(RELEASE_OUT)/HelloWorld


target : 
	echo please choose either "debug", "release" or "all" '(for both debug and release)'

prep_Debug_dirs: 
	if ! `test -d $(DEBUG_OUT)`;then mkdir $(DEBUG_OUT);fi;\
	
prep_Release_dirs: 
	if ! `test -d $(RELEASE_OUT)`;then mkdir $(RELEASE_OUT);fi;\	
	
debug : prep_Debug_dirs $(OUT_D)

$(OUT_D) : $(OBJECTFILES_D)
	$(LINKER) $(LINKER_FLAGS_D) $(OUT_D) $(OBJECTFILES_D)
	

$(DEBUG_OUT)/HelloWorld.o : HelloWorld.cpp
	$(CXX) $(CXX_FLAGS_D) HelloWorld.cpp -o $(DEBUG_OUT)/HelloWorld.o