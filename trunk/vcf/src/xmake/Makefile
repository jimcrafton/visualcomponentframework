#make file for xmake

XMAKE_VERSION = 2.0.0

#this is the output directory
OUTDIR=./Objects

DOCDIR=./docs


#this is the install directory - you must root privilege
#to install the software
INSTALLDIR=/usr/local/bin

LIBOBJFILES=$(OUTDIR)/CmdLine.o $(OUTDIR)/XMLParser.o $(OUTDIR)/xmake.o $(OUTDIR)/xmakeUtils.o
OBJFILES=$(OUTDIR)/StdAfx.o $(OUTDIR)/main.o $(OUTDIR)/FilePath.o
CXX=g++ -DGCC -I../ -I./ -O2 -c

VCF_LIB_OUTPUT=../lib

LIBXMAKE=libXmake.a



HTMLHELP_COMPILER = "d:/Program Files/HTML Help Workshop/hhc.exe"



#distribution files
DIST_ROOT_DIR=xmake-$(XMAKE_VERSION)
DIST_TAR_FILE=$(DIST_ROOT_DIR).tar
DIST_FILES=StdAfx.cpp StdAfx.h FilePath.h FilePath.cpp CmdLine.cpp CmdLine.h \
			XMLParser.cpp XMLParser.h \
			xmake.cpp xmake.h \
			DependencyNodes.h \
			xmake.kdevprj \
			xmake.dsp xmake.dsw libXmake.dsp \
			xmake.vcproj libXmake.vcproj \
			xmakeUtils.h xmakeUtils.cpp \
			Enumerator.h \
			main.cpp \
			xmake.xsl \
			xmake_docs.xml \
			$(DOCDIR)/xmake_docs.chm \
			xmake.pbproj/project.pbxproj \
			COPYING \
			readme.html README \
			Makefile 








#this is the default to build
xmake : $(LIBXMAKE) $(OBJFILES)
	g++ -o $(OUTDIR)/xmake $(OBJFILES) $(LIBXMAKE)
	cp $(OUTDIR)/xmake ./



#build the lib
$(LIBXMAKE) : test_dirs $(LIBOBJFILES)
	ar -cru $(LIBXMAKE) $(LIBOBJFILES)
	-cp $(LIBXMAKE) $(VCF_LIB_OUTPUT)/$(LIBXMAKE)


$(OUTDIR)/StdAfx.o : StdAfx.cpp StdAfx.h
	$(CXX) StdAfx.cpp -o $(OUTDIR)/StdAfx.o

$(OUTDIR)/CmdLine.o : CmdLine.cpp CmdLine.h
	$(CXX) CmdLine.cpp -o $(OUTDIR)/CmdLine.o

$(OUTDIR)/FilePath.o : FilePath.cpp FilePath.h
	$(CXX) FilePath.cpp -o $(OUTDIR)/FilePath.o

$(OUTDIR)/XMLParser.o : XMLParser.cpp XMLParser.h
	$(CXX) XMLParser.cpp -o $(OUTDIR)/XMLParser.o

$(OUTDIR)/xmake.o : xmake.cpp xmake.h
	cp xmake.cpp xmake.tmp
	if ( ! (test -z `grep XMAKE-VERSION xmake.cpp`) ) \
	then\
		sed "s?XMAKE-VERSION?$(XMAKE_VERSION)?g" xmake.cpp > xmake.cpp.2;\
		mv xmake.cpp.2 xmake.cpp;\
	fi
	$(CXX) xmake.cpp -o $(OUTDIR)/xmake.o
	mv xmake.tmp xmake.cpp

$(OUTDIR)/xmakeUtils.o : xmakeUtils.cpp xmakeUtils.h
	$(CXX) xmakeUtils.cpp -o $(OUTDIR)/xmakeUtils.o

$(OUTDIR)/main.o : main.cpp
	$(CXX) main.cpp -o $(OUTDIR)/main.o



#this will remove the binary .o files
clean :
	rm $(OBJFILES)
	rm $(LIBOBJFILES)
	rm $(LIBXMAKE)
	rm -rf $(DOCDIR)
	rm -rf $(OUTDIR)
	

docs : test_doc_dirs
	cd $(DOCDIR); \
	xsltproc ../xmake.xsl ../xmake_docs.xml

chm : test_tools docs
	cd $(DOCDIR)
	-$(HTMLHELP_COMPILER) $(DOCDIR)/htmlhelp.hhp

test_dirs :
	if ! `test -d $(OUTDIR)`;then mkdir $(OUTDIR);fi;

test_doc_dirs :
	if ! `test -d $(DOCDIR)`;then mkdir $(DOCDIR);fi;

dist : chm
	tar -cf tmp.tar $(DIST_FILES)
	mkdir tmp
	mkdir tmp/$(DIST_ROOT_DIR)
	mv tmp.tar tmp/$(DIST_ROOT_DIR)/
	cp -r examples/ tmp/$(DIST_ROOT_DIR)/	
	tar -x -C ./tmp/$(DIST_ROOT_DIR)/ -f ./tmp/$(DIST_ROOT_DIR)/tmp.tar
	rm ./tmp/$(DIST_ROOT_DIR)/tmp.tar
	tar -c -C ./tmp/ -f ./tmp/$(DIST_TAR_FILE) $(DIST_ROOT_DIR)
	mv ./tmp/$(DIST_TAR_FILE) ./
	rm -rf tmp
	gzip $(DIST_TAR_FILE)

	

test_tools : 
	if ( test -f $(HTMLHELP_COMPILER) )\
	then\
		echo HTML Help compiler found;\
	else\
		echo Html Help compiler not found;\
		exit 1;\
	fi


#this will install xmake on your system - you must be
#logged in as root for this to work
install :
	cp $(OUTDIR)/xmake $(INSTALLDIR)/; strip $(INSTALLDIR)/xmake; echo xmake is now installed!

#this will uninstall xmake from your system - you must
#be logged in as root to do this
uninstall :
	rm $(INSTALLDIR)/xmake; echo xmake is now removed from your system
