###############################################################################
#VCF Documentation makefile
#
#$Log$
#Revision 1.4  2003/05/18 23:09:37  ddiego
#fixes some mistakes in the docs/Makefile and adds some extra documentation.
#
#Revision 1.3  2003/05/17 20:58:39  ddiego
#removed some old files, mostly script junk that are no longer needed
#----------------------------------------------------------------------
#
#Revision 1.2  2003/05/17 20:36:51  ddiego
#this is the checkin for the 0.6.1 release - represents the merge over from
#the devmain-0-6-0 branch plus a few minor bug fixes
#
#Revision 1.1.2.14  2003/05/15 03:00:59  ddiego
#added initial osx source( FoundationKit only),
#plus some fixes to compile under GCC 3.x compilers
#
#Revision 1.1.2.13  2003/04/17 04:29:44  ddiego
#updated scintilla, added gtk support for the application kit, with stubs
#for the basic peers.
#
#Revision 1.1.2.12  2003/04/07 03:38:46  ddiego
#did some documentation work, and got everything to compile cleanly with some
#of the new additions, particularly the chnages inteh Image/ImageBits classes.
#
#
#
###############################################################################


#This is the version number for the core VCF - make sure to modify this for new releases
VERSION = 0.6.1

#version number for the VCF Builder
VCFB_VERSION = 1.0.5

#version number for the XMake program
XMAKE_VERSION = 1.0.5


HTMLHELP_COMPILER = "D:/Program Files/HTML Help Workshop/hhc.exe"

XSL_HTMLHELP_IMPORT = d:/docbook/xsl/htmlhelp/htmlhelp.xsl

RAW_CHM_FILENAME = vcf_docs.chm
RAW_CHI_FILENAME = vcf_docs.chi

RAW_VCF_BUILDER_CHM_FILENAME = vcfbuilder_docs.chm
RAW_VCF_BUILDER_CHI_FILENAME = vcfbuilder_docs.chi

VERSIONED_CHM_FILENAME = VCFDocs.$(VERSION).chm
VERSIONED_CHI_FILENAME = VCFDocs.$(VERSION).chi

VERSIONED_VCFBUILDER_CHM_FILENAME = VCFBuilderDocs.$(VCFB_VERSION).chm
VERSIONED_VCFBUILDER_CHI_FILENAME = VCFBuilderDocs.$(VCFB_VERSION).chi

VERSIONED_XMAKE_CHM_FILENAME = XMakeDocs.$(XMAKE_VERSION).chm
VERSIONED_XMAKE_CHI_FILENAME = XMakeDocs.$(XMAKE_VERSION).chi

VERSIONED_SRC_HHP_FILENAME = VCFSrcDocs.$(VERSION).hhp
VERSIONED_SRC_CHM_FILENAME = VCFSrcDocs.$(VERSION).chm
VERSIONED_SRC_CHI_FILENAME = VCFSrcDocs.$(VERSION).chi

HTML_TAR_FILENAME = VCFDocs-$(VERSION).tar


ONLINE_SRC_DOC_DIR = srcdocs
ONLINE_DOCS_REF_DIR = docs/ref

UPLOADS_DIR	= ../uploadToSF

FULL_ONLINE_SRC_DOC_DIR = $(ONLINE_DOCS_REF_DIR)/$(ONLINE_SRC_DOC_DIR)


VCF_DOCS = corelib_FAQ.sgml \
corelib_applicationKit.sgml \
corelib_componentAuthoring.sgml \
corelib_foundationKit.sgml \
corelib_graphicsKit.sgml \
corelib_networkKit.sgml \
corelib_remoteObjectKit.sgml \
general.sgml \
getting_started.sgml \
tutorials.sgml \
vcf_docbook.sgml \
vcf_intro.sgml \
vcf.css \
vcf.dsl \
vcf.xsl


VCF_BUILDER_DOCS = vcf.css vcfbuilder.xsl \
vcfbuilder_docbook.sgml \
vcfbuilder_ui.sgml \
vcfbuilder_building.sgml \
vcfbuilder_faq.sgml \
vcfbuilder_versionctrl.sgml \
vcfbuilder_debug.sgml \
vcfbuilder_ide.sgml \
vcfbuilder_wspprj.sgml \
vcfbuilder_design.sgml \
vcfbuilder_intro.sgml \
vcfbuilder_designer.sgml \
vcfbuilder_quicktut.sgml 


XMAKE_DOCS = vcf.css xmake_book.sgml xmake_docbook.sgml



coredocs :  $(VCF_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml
	xsltproc --nonet vcf.xsl vcf_docbook.sgml
	mv vcf_book.sgml.bak vcf_book.sgml

	
coredocs_online :  $(VCF_DOCS) test_tools 
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml
	xsltproc --nonet vcf_online.xsl vcf_docbook.sgml	
	mv vcf_book.sgml.bak vcf_book.sgml


coredocs_hh : htmlhelp.hhp coredocs
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME)




	



#steps - this one ios a bit complex
#creates source code docs, and creates the html help for them
#create the docbook generated html using the vcf_with_source_docs stylesheet
#which turns on the generation of linkage to the source code docs
#then we back up our orginal .hhp and .toc files (these have the VCF-SOURCE-CHM
#variables). The VCF-SOURCE-CHM occurences all get replaced with the right
#file name of the chm file, and we then go and produce our master
#doc chm. Finally we restore the altered .hhp and .hhc files to their
#original contents

coredocs_hh_with_source : $(VCF_DOCS) test_tools doxy doxy_hh
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml
	xsltproc --nonet vcf_with_source_docs.xsl vcf_docbook.sgml
	cp htmlhelp.hhp htmlhelp.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" htmlhelp.hhp > htmlhelp.hhp.tmp
	mv htmlhelp.hhp.tmp htmlhelp.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv htmlhelp.hhp.bak htmlhelp.hhp
	mv toc.hhc.bak toc.hhc

	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_CHI_FILENAME) )\
	then\
		mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
	fi
	mv vcf_book.sgml.bak vcf_book.sgml	

	
strip_online_docs :  stripper
	for file in *.html;\
	do\
		echo post processing $$file with stripper...;\
		./stripper $$file;\
	done




alldocs : $(VCF_DOCS) test_tools $(VCF_BUILDER_DOCS) $(XMAKE_DOCS)
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml

	sed "s?VERSION-NUMBER?$(XMAKE_VERSION)?g" xmake_book.sgml > xmake_book.sgml.tmp
	cp xmake_book.sgml xmake_book.sgml.bak
	mv xmake_book.sgml.tmp xmake_book.sgml

	sed "s?VERSION-NUMBER?$(VCFB_VERSION)?g" vcfbuilder_book.sgml > vcfbuilder_book.sgml.tmp
	cp vcfbuilder_book.sgml vcfbuilder_book.sgml.bak
	mv vcfbuilder_book.sgml.tmp vcfbuilder_book.sgml
	
	xsltproc --nonet vcf.xsl vcf_website_docs.sgml

	mv vcf_book.sgml.bak vcf_book.sgml
	mv xmake_book.sgml.bak xmake_book.sgml
	mv vcfbuilder_book.sgml.bak vcfbuilder_book.sgml



alldocs_hh : alldocs htmlhelp.hhp 
	cp htmlhelp.hhp htmlhelp.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" htmlhelp.hhp > htmlhelp.hhp.tmp
	mv htmlhelp.hhp.tmp htmlhelp.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv htmlhelp.hhp.bak htmlhelp.hhp
	mv toc.hhc.bak toc.hhc
	
	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_CHI_FILENAME) )\
	then\
		mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
	fi	


alldocs_online : $(VCF_DOCS) test_tools $(VCF_BUILDER_DOCS) $(XMAKE_DOCS)
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml

	sed "s?VERSION-NUMBER?$(XMAKE_VERSION)?g" xmake_book.sgml > xmake_book.sgml.tmp
	cp xmake_book.sgml xmake_book.sgml.bak
	mv xmake_book.sgml.tmp xmake_book.sgml

	sed "s?VERSION-NUMBER?$(VCFB_VERSION)?g" vcfbuilder_book.sgml > vcfbuilder_book.sgml.tmp
	cp vcfbuilder_book.sgml vcfbuilder_book.sgml.bak
	mv vcfbuilder_book.sgml.tmp vcfbuilder_book.sgml

	xsltproc --nonet vcf_online.xsl vcf_website_docs.sgml

	mv vcf_book.sgml.bak vcf_book.sgml
	mv xmake_book.sgml.bak xmake_book.sgml
	mv vcfbuilder_book.sgml.bak vcfbuilder_book.sgml


alldocs_hh_with_source : $(VCF_DOCS) test_tools $(VCF_BUILDER_DOCS) $(XMAKE_DOCS) doxy doxy_hh
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.sgml > vcf_book.sgml.tmp
	cp vcf_book.sgml vcf_book.sgml.bak
	mv vcf_book.sgml.tmp vcf_book.sgml

	sed "s?VERSION-NUMBER?$(XMAKE_VERSION)?g" xmake_book.sgml > xmake_book.sgml.tmp
	cp xmake_book.sgml xmake_book.sgml.bak
	mv xmake_book.sgml.tmp xmake_book.sgml

	sed "s?VERSION-NUMBER?$(VCFB_VERSION)?g" vcfbuilder_book.sgml > vcfbuilder_book.sgml.tmp
	cp vcfbuilder_book.sgml vcfbuilder_book.sgml.bak
	mv vcfbuilder_book.sgml.tmp vcfbuilder_book.sgml

	xsltproc --nonet vcf_with_source_docs.xsl vcf_website_docs.sgml

	mv vcf_book.sgml.bak vcf_book.sgml
	mv xmake_book.sgml.bak xmake_book.sgml
	mv vcfbuilder_book.sgml.bak vcfbuilder_book.sgml


	cp htmlhelp.hhp htmlhelp.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" htmlhelp.hhp > htmlhelp.hhp.tmp
	mv htmlhelp.hhp.tmp htmlhelp.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv htmlhelp.hhp.bak htmlhelp.hhp
	mv toc.hhc.bak toc.hhc

	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_CHI_FILENAME) )\
	then\
		mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
	fi
	
	if ( test -d $(UPLOADS_DIR) )\
	then \
		mkdir tmp;\
		mkdir tmp/vcf-$(VERSION);\
		mkdir tmp/vcf-$(VERSION)/docs;\
		cp $(VERSIONED_CHM_FILENAME) tmp/vcf-$(VERSION)/docs/;\
		if ( test -f $(VERSIONED_CHI_FILENAME) )\
		then\
			cp $(VERSIONED_CHI_FILENAME) tmp/vcf-$(VERSION)/docs/;\
		fi;\
		if ( test -f $(VERSIONED_SRC_CHM_FILENAME) )\
		then\
			cp $(VERSIONED_SRC_CHM_FILENAME) tmp/vcf-$(VERSION)/docs/;\
		fi;\
		if ( test -f $(VERSIONED_SRC_CHI_FILENAME) )\
		then\
			cp $(VERSIONED_SRC_CHI_FILENAME) tmp/vcf-$(VERSION)/docs/;\
		fi;\
		cd tmp;\
		tar -cf vcf-$(VERSION)-htmlhelp.tar vcf-$(VERSION)/;\
		gzip -f vcf-$(VERSION)-htmlhelp.tar;\
		cd ../;\
		mv tmp/vcf-$(VERSION)-htmlhelp.tar.gz $(UPLOADS_DIR)/;\
		rm -rf tmp;\
	fi
		


vcf_builder_docs : $(VCF_BUILDER_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(VCFB_VERSION)?g" vcfbuilder_book.sgml > vcfbuilder_book.sgml.tmp
	cp vcfbuilder_book.sgml vcfbuilder_book.sgml.bak
	mv vcfbuilder_book.sgml.tmp vcfbuilder_book.sgml

	xsltproc --nonet vcfbuilder.xsl vcfbuilder_docbook.sgml

	mv vcfbuilder_book.sgml.bak vcfbuilder_book.sgml


vcf_builder_hh : vcf_builder_docs htmlhelp.hhp 
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv $(RAW_VCF_BUILDER_CHM_FILENAME) $(VERSIONED_VCFBUILDER_CHM_FILENAME)
	-mv $(RAW_VCF_BUILDER_CHI_FILENAME) $(VERSIONED_VCFBUILDER_CHI_FILENAME)


xmake_docs : $(XMAKE_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(XMAKE_VERSION)?g" xmake_book.sgml > xmake_book.sgml.tmp
	cp xmake_book.sgml xmake_book.sgml.bak
	mv xmake_book.sgml.tmp xmake_book.sgml

	xsltproc vcf.xsl xmake_docbook.sgml

	mv xmake_book.sgml.bak xmake_book.sgml

xmake_hh : htmlhelp.hhp xmake_docs
	-$(HTMLHELP_COMPILER) htmlhelp.hhp
	mv $(RAW_CHM_FILENAME) $(VERSIONED_XMAKE_CHM_FILENAME)
	mv $(RAW_CHI_FILENAME) $(VERSIONED_XMAKE_CHI_FILENAME)
	

test_tools : 
	if ( test -f $(HTMLHELP_COMPILER) )\
	then\
		echo HTML Help compiler found;\
	else\
		echo Html Help compiler not found;\
		exit 1;\
	fi

	if ( test -f $(XSL_HTMLHELP_IMPORT) )\
	then\
		echo stylesheet found;\
	else\
		echo XSL style sheet $(XSL_HTMLHELP_IMPORT) not found;\
		exit 1;\
	fi



stripper.o : stripper.cpp
	g++ -c -O2 stripper.cpp

stripper : stripper.o
	g++ -o stripper stripper.o


hrefmunger.o : hrefmunger.cpp
	g++ -c -O2 hrefmunger.cpp

hrefmunger : hrefmunger.o
	g++ -o hrefmunger hrefmunger.o


imgmunger.o : imgmunger.cpp
	g++ -c -O2 imgmunger.cpp

imgmunger : imgmunger.o
	g++ -o imgmunger imgmunger.o



doxy : 
	cp Doxyfile Doxyfile.bak
	sed "s?VERSION-NUMBER?$(VERSION)?g" Doxyfile > Doxyfile.tmp
	mv Doxyfile.tmp Doxyfile
	doxygen
	mv Doxyfile.bak Doxyfile
	cp -r gfx/ doxy_html/
	cp vcf.css doxy_html/

online_doxy : stripper hrefmunger imgmunger
	cp Doxyfile.online Doxyfile.bak
	sed "s?VERSION-NUMBER?$(VERSION)?g" Doxyfile.online > Doxyfile.tmp
	mv Doxyfile.tmp Doxyfile.online
	doxygen Doxyfile.online
	mv Doxyfile.bak Doxyfile.online
	cp -r gfx/ doxy_html/
	for file in doxy_html/*.html;\
	do\
		echo post processing $$file with stripper...;\
		./stripper $$file;\
		echo post processing all hrefs with hrefmunger...;\
		./hrefmunger $(ONLINE_SRC_DOC_DIR) $$file;\
		echo post processing all hrefs with imgmunger...;\
		./imgmunger gfx $$file;\
	done

	



doxy_hh : doxy_html/index.hhp
	mv doxy_html/index.hhp doxy_html/$(VERSIONED_SRC_HHP_FILENAME)
	-$(HTMLHELP_COMPILER) doxy_html/$(VERSIONED_SRC_HHP_FILENAME)	
	mv doxy_html/$(VERSIONED_SRC_CHM_FILENAME) ./
	mv doxy_html/$(VERSIONED_SRC_CHI_FILENAME) ./
	

dist : coredocs hh 
	find *.html > files.out
	find gfx/ -type f -name '*' > images.out
	cat files.out images.out > all.out
	echo Creating tar file...
	tar -cf $(HTML_TAR_FILENAME) -T all.out
	gzip $(HTML_TAR_FILENAME)
	echo HTML files tarred and compressed as $(HTML_TAR_FILENAME).gz		
	rm all.out
	rm files.out
	rm images.out

dist_all : alldocs
	-mkdir VCFDocs-$(VERSION)	
	cp *.html VCFDocs-$(VERSION)/
	cp *.css VCFDocs-$(VERSION)/
	cp -r gfx/ VCFDocs-$(VERSION)/
	tar -cf VCFDocs-$(VERSION).tar VCFDocs-$(VERSION)/ 
	gzip VCFDocs-$(VERSION).tar
	rm -rf VCFDocs-$(VERSION)/
	
dist_all_hh : alldocs_hh
	-mkdir VCFDocs-$(VERSION)	
	cp $(VERSIONED_CHM_FILENAME) VCFDocs-$(VERSION)/
	cp $(VERSIONED_CHI_FILENAME) VCFDocs-$(VERSION)/	
	tar -cf VCFHtmlHelpDocs-$(VERSION).tar VCFDocs-$(VERSION)/ 
	gzip VCFHtmlHelpDocs-$(VERSION).tar
	rm -rf VCFDocs-$(VERSION)/	

dist_online : coredocs_online strip_online_docs 
	find *.html > files.out
	find gfx/ -type f -name '*' > images.out
	cat files.out images.out > all.out
	echo Creating tar file...
	tar -cf $(HTML_TAR_FILENAME) -T all.out
	rm -f $(HTML_TAR_FILENAME).gz
	gzip $(HTML_TAR_FILENAME)
	echo HTML files tarred and compressed as $(HTML_TAR_FILENAME).gz		
	rm all.out
	rm files.out
	rm images.out


dist_all_online : alldocs_online strip_online_docs online_doxy
	-mkdir docs
	-mkdir $(ONLINE_DOCS_REF_DIR)
	-mkdir $(FULL_ONLINE_SRC_DOC_DIR)
	cp doxy_html/*.htm* $(FULL_ONLINE_SRC_DOC_DIR)/
	-mkdir gfx_bak
	cp gfx/*.* gfx_bak/
	rm -f gfx/*.*
	cp doxy_html/*.png gfx/
	
	cp *.html $(ONLINE_DOCS_REF_DIR)/
	find $(ONLINE_DOCS_REF_DIR)/*.html > files.out
	find gfx/ -type f -name '*' > images.out
	find $(FULL_ONLINE_SRC_DOC_DIR)/ -type f -name '*.html' > srcdocs.out
	cat files.out images.out srcdocs.out > all.out
	echo Creating tar file...
	tar -cf $(HTML_TAR_FILENAME) -T all.out
	rm -f $(HTML_TAR_FILENAME).gz
	gzip $(HTML_TAR_FILENAME)
	echo HTML files tarred and compressed as $(HTML_TAR_FILENAME).gz		
	rm all.out
	rm files.out
	rm images.out
	rm srcdocs.out
	rm -rf $(FULL_ONLINE_SRC_DOC_DIR)	
	rm -r gfx/*.*
	cp gfx_bak/*.* gfx/ 
	rm -rf gfx_bak/




clean :
	mv doxy_footer.html doxy_footer.html.bak
	mv doxy_header.html doxy_header.html.bak
	rm -f *.html
	rm -f $(HTML_TAR_FILENAME).gz
	rm -f $(VERSIONED_SRC_CHM_FILENAME)
	rm -f $(VERSIONED_CHM_FILENAME)
	rm -f *.hhp
	rm -f *.hhc
	rm -f *.hhk
	rm -rf doxy_html/
	rm -f stripper stripper.o
	rm -f hrefmunger hrefmunger.o
	mv doxy_footer.html.bak doxy_footer.html
	mv doxy_header.html.bak doxy_header.html
