
# make sure all sub-make process recieve the variables we define here
export

CC=cl.exe
CXX=cl.exe
CXXFLAGS=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od  /FD /GZ \
	/I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS"\
	/D "USE_FOUNDATIONKIT_DLL"\
	/D "USE_GRAPHICSKIT_DLL"\
	/D "USE_APPLICATIONKIT_DLL"\
	/D "USE_OPENGLKIT_DLL"

LD=link.exe
LDFLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
	shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib\
	/nologo /debug /subsystem:windows /machine:I386 /entry:"mainCRTStartup"\
	/libpath:"$(VCF_LIB)"


FLEX=flex
LFLAGS=

BISON=bison
YFLAGS=-d

OBJS=\
	labeltest.obj\
	TeXLabel.obj\
	TeXLabel.tab.obj\
	TeXLabel.scan.obj\
	TeXTypes.obj
	
.PHONY: all clean


%.obj: %.cpp
	$(CXX) $(CXXFLAGS) /c $< /Fo"$@"

%.tab.cpp %.tab.hpp: %.yy
	$(BISON) $(YFLAGS) $<
	mv $*.tab.cc $*.tab.cpp
	mv $*.tab.hh $*.tab.hpp
	
%.scan.cpp: %.ll %.tab.hpp
	$(FLEX) $(LFLAGS) -o$@ $<
	
all: labeltest.exe

labeltest.exe: $(OBJS)
	$(LD) $^ /OUT:"$@" $(LDFLAGS)
	
clean:
	rm -rf *.obj *.ilk *.pdb *.idb TeXLabel.tab.[ch]pp TeXLabel.scan.cpp

labeltest.obj:\
	labeltest.cpp\
	TeXLabel.hpp
TeXLabel.obj:\
	TeXLabel.cpp\
	TeXLabel.hpp\
	TeXTypes.hpp\
	TeXLabel.tab.hpp
TeXLabel.tab.obj:\
	TeXLabel.tab.cpp\
	TeXTypes.hpp
TeXLabel.scan.obj:\
	TeXLabel.scan.cpp\
	TeXLabel.tab.hpp\
	TeXTypes.hpp
TeXTypes.obj:\
	TeXTypes.cpp\
	TeXTypes.hpp
