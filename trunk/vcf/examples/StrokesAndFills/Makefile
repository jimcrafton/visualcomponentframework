#makefile for StrokesAndFills
DEBUG_OUT = Debug
RELEASE_OUT = Release

OBJECTFILES_D = $(DEBUG_OUT)/StrokesAndFills.o
OBJECTFILES = $(RELEASE_OUT)/StrokesAndFills.o


GTK_CXX_FLAGS = `pkg-config gtk+-2.0 --cflags`
CXX_FLAGS_D=-ggdb -DVCF_GCC -DVCF_GTK -DVCF_POSIX -D_DEBUG -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -c
CXX_FLAGS=-DVCF_GCC -DVCF_GTK -DVCF_POSIX -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -O2 -c

GTK_LINKER_FLAGS = `pkg-config gtk+-2.0 --libs`
APPKIT_LIBS_D = -lpthread -lFoundationKit_d -lGraphicsKit_d -lApplicationKit_d
APPKIT_LIBS = -lpthread -lFoundationKit -lGraphicsKit -lApplicationKit
LINKER_FLAGS_D = -L$(VCF_LIB) -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPKIT_LIBS_D) -ggdb -o 

LINKER_FLAGS = -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPKIT_LIBS) -o


CXX = g++

LINKER = g++


OUT_D = $(DEBUG_OUT)/StrokesAndFills
OUT = $(RELEASE_OUT)/StrokesAndFills

target : 
	echo please choose either debug, release or all '(for both debug and release)'

prep_Debug_dirs: 
	if ! `test -d $(DEBUG_OUT)`;then mkdir $(DEBUG_OUT);fi;

prep_Release_dirs: 
	if ! `test -d $(RELEASE_OUT)`;then mkdir $(RELEASE_OUT);fi;

debug : prep_Debug_dirs $(OUT_D)

release : prep_Release_dirs $(OUT)



$(OUT_D) : $(OBJECTFILES_D)
	$(LINKER) $(LINKER_FLAGS_D) $(OUT_D) $(OBJECTFILES_D) 

$(OUT) : $(OBJECTFILES)
	$(LINKER) $(LINKER_FLAGS) $(OUT) $(OBJECTFILES) 

$(DEBUG_OUT)/StrokesAndFills.o : StrokesAndFills.cpp
	$(CXX) $(CXX_FLAGS_D) StrokesAndFills.cpp -o $(DEBUG_OUT)/StrokesAndFills.o

$(RELEASE_OUT)/StrokesAndFills.o : StrokesAndFills.cpp
	$(CXX) $(CXX_FLAGS) StrokesAndFills.cpp -o $(RELEASE_OUT)/StrokesAndFills.o

