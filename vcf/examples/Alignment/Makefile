#makefile for Alignment
DEBUG_OUT = Debug
RELEASE_OUT = Release

OBJECTFILES_D = $(DEBUG_OUT)/Alignment.o
OBJECTFILES = $(RELEASE_OUT)/Alignment.o


GTK_CXX_FLAGS = -I/target/build/include/gtk-2.0 -I/target/build/lib/gtk-2.0/include -I/target/include/atk-1.0 -I/target/build/include/pango-1.0 -I/target/build/include/glib-2.0 -I/target/build/lib/glib-2.0/include 
CXX_FLAGS_D=-ggdb -DVCF_GCC -DVCF_GTK -DVCF_POSIX -D_DEBUG -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -c
CXX_FLAGS=-DVCF_GCC -DVCF_GTK -DVCF_POSIX -I $(VCF_INCLUDE) $(GTK_CXX_FLAGS) -O2 -c

GTK_LINKER_FLAGS = -L/target/build/lib -L/target/lib -lgtk-win32-2.0 -lgdk-win32-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lpangowin32-1.0 -lgdi32 -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -lglib-2.0 -lintl -liconv 
APPKIT_LIBS_D = -lpthread -lFoundationKit_d -lGraphicsKit_d -lApplicationKit_d
APPKIT_LIBS = -lpthread -lFoundationKit -lGraphicsKit -lApplicationKit
LINKER_FLAGS_D = -L$(VCF_LIB) -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPKIT_LIBS_D) -ggdb -o 

LINKER_FLAGS = -L$(VCF_BIN) $(GTK_LINKER_FLAGS) $(APPKIT_LIBS) -o


CXX = g++

LINKER = g++


OUT_D = $(DEBUG_OUT)/Alignment
OUT = $(RELEASE_OUT)/Alignment

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

$(DEBUG_OUT)/Alignment.o : Alignment.cpp
	$(CXX) $(CXX_FLAGS_D) Alignment.cpp -o $(DEBUG_OUT)/Alignment.o

$(RELEASE_OUT)/Alignment.o : Alignment.cpp
	$(CXX) $(CXX_FLAGS) Alignment.cpp -o $(RELEASE_OUT)/Alignment.o

