#makefile for Conditions
DEBUG_OUT = Debug
RELEASE_OUT = Release

OBJECTFILES_D = $(DEBUG_OUT)/Conditions.o
OBJECTFILES = $(RELEASE_OUT)/Conditions.o


CXX_FLAGS_D=-ggdb -DVCF_GCC -DVCF_POSIX -D_DEBUG -I $(VCF_INCLUDE) -c
CXX_FLAGS=-DVCF_GCC -DVCF_POSIX -I $(VCF_INCLUDE) -Os -c

FOUNDATIONKIT_LIBS_D = -lpthread -lFoundationKit_d
FOUNDATIONKIT_LIBS = -lpthread -lFoundationKit
LINKER_FLAGS_D = -L$(VCF_LIB) -L$(VCF_BIN) $(FOUNDATIONKIT_LIBS_D) -ggdb -o 

LINKER_FLAGS = -L$(VCF_BIN) $(FOUNDATIONKIT_LIBS) -o


CXX = g++

LINKER = g++


OUT_D = $(DEBUG_OUT)/Conditions
OUT = $(RELEASE_OUT)/Conditions

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

$(DEBUG_OUT)/Conditions.o : Conditions.cpp
	$(CXX) $(CXX_FLAGS_D) Conditions.cpp -o $(DEBUG_OUT)/Conditions.o

$(RELEASE_OUT)/Conditions.o : Conditions.cpp
	$(CXX) $(CXX_FLAGS) Conditions.cpp -o $(RELEASE_OUT)/Conditions.o

