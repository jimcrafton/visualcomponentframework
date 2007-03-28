###############################################################################
#VCF Documentation makefile
#
###############################################################################


#This is the version number for the core VCF - make sure to modify this for new releases
VERSION = $(shell cat ../VERSION)


#version number for the XMake program
XMAKE_VERSION = 1.0.5


HTMLHELP_COMPILER = "c:/Program Files/HTML Help Workshop/hhc.exe"
XSL_DOCBOOK_DIR = "f:/code/docbook-xsl-1.69.1"
XSL_HTMLHELP_IMPORT = "$(XSL_DOCBOOK_DIR)/htmlhelp/htmlhelp.xsl"
XSL_HTML_IMPORT = "$(XSL_DOCBOOK_DIR)/html/docbook.xsl"


RAW_CHM_FILENAME = vcf-docbook.chm
RAW_CHI_FILENAME = vcf-docbook.chi

RAW_SRC_CHM_FILENAME = vcf-docbook-with-src.chm
RAW_SRC_CHI_FILENAME = vcf-docbook-with-src.chi


RAW_VCF_BUILDER_CHM_FILENAME = vcfbuilder_docs.chm
RAW_VCF_BUILDER_CHI_FILENAME = vcfbuilder_docs.chi

VERSIONED_CHM_FILENAME = VCFDocs.$(VERSION).chm
VERSIONED_CHI_FILENAME = VCFDocs.$(VERSION).chi

VERSIONED_XMAKE_CHM_FILENAME = XMakeDocs.$(XMAKE_VERSION).chm
VERSIONED_XMAKE_CHI_FILENAME = XMakeDocs.$(XMAKE_VERSION).chi

VERSIONED_SRC_HHP_FILENAME = VCFSrcDocs.$(VERSION).hhp
VERSIONED_SRC_CHM_FILENAME = VCFSrcDocs.$(VERSION).chm
VERSIONED_SRC_CHI_FILENAME = VCFSrcDocs.$(VERSION).chi

HTML_TAR_FILENAME = VCFDocs-$(VERSION).tar
HTML_ONLINE_TAR_FILENAME = VCFDocs-online-$(VERSION).tar
HTML_ONLINE_SRC_TAR_FILENAME = VCFDocs-src-online-$(VERSION).tar


ONLINE_SRC_DOC_DIR = src_manual
ONLINE_DOCS_DIR = ref_manual

UPLOADS_DIR	= ../uploadToSF

#FULL_ONLINE_SRC_DOC_DIR = $(ONLINE_DOCS_REF_DIR)/$(ONLINE_SRC_DOC_DIR)


VCF_DOCS = corelib_FAQ.xml \
corelib_applicationKit.xml \
corelib_componentAuthoring.xml \
corelib_foundationKit.xml \
corelib_graphicsKit.xml \
corelib_networkKit.xml \
corelib_remoteObjectKit.xml \
general.xml \
getting_started.xml \
tutorials.xml \
vcf_docbook.xml \
vcf_intro.xml \
vcf.css \
vcf.dsl \
vcf.xsl


VCF_BUILDER_DOCS = vcf.css vcfbuilder.xsl \
vcfbuilder_docbook.xml \
vcfbuilder_ui.xml \
vcfbuilder_building.xml \
vcfbuilder_faq.xml \
vcfbuilder_versionctrl.xml \
vcfbuilder_debug.xml \
vcfbuilder_ide.xml \
vcfbuilder_wspprj.xml \
vcfbuilder_design.xml \
vcfbuilder_intro.xml \
vcfbuilder_designer.xml \
vcfbuilder_quicktut.xml 


TUTORIAL_ARTICLES = ../examples/HelloWorld/HelloWorldArticle.xml \
../examples/ApplicationIcons/ApplicationIconsArticle.xml \
../examples/FilesAndDirectories/FilesAndDirectoriesArticle.xml \
../examples/GraphicsAndMouseMoves/GraphicsAndMouseMovesArticle.xml \
../examples/Strings/StringsArticle.xml \
../examples/CopyAndPaste/CopyAndPasteArticle.xml \
../examples/GraphicsBasics/GraphicsBasicsArticle.xml \
../examples/StrokesAndFills/StrokesAndFillsArticle.xml \
../examples/DragAndDrop/DragAndDropArticle.xml \
../examples/HelloWorld/HelloWorldArticle.xml \
../examples/EventBasics/EventBasicsArticle.xml \
../examples/HelloWorld2/HelloWorld2Article.xml \
../examples/TextLayout/TextLayoutArticle.xml \
../examples/HelloWorld3/HelloWorld3Article.xml \
../examples/ThreadBasics/ThreadBasicsArticle.xml \
../examples/ImageBasics/ImageBasicsArticle.xml \
../examples/ThreadsInGUI/ThreadsInGUIArticle.xml \
../examples/ImageViewer/ImageViewerArticle.xml \
../examples/WorkingWithEnumerators/WorkingWithEnumeratorsArticle.xml \
../examples/Scrolling/ScrollingArticle.xml \
../examples/SharedLibraries/SharedLibrariesArticle.xml \
../examples/HeavyAndLight/HeavyAndLightArticle.xml \
../examples/Alignment/AlignmentArticle.xml \
../examples/Alignment/AdvancedAlignmentArticle.xml \
../examples/Alignment/AnchorsArticle.xml \
../examples/Sliders/SlidersArticle.xml \
../examples/ProgressBars/ProgressBarsArticle.xml \
../examples/Labels/LabelsArticle.xml \
../examples/Dictionaries/DictionariesArticle.xml \
../examples/Actions/ActionsArticle.xml \
../examples/Toolbars/ToolbarsArticle.xml \
../examples/DateTimeUI/DateTimeUIArticle.xml \
../examples/DatesAndTime/DatesAndTimeArticle.xml \
../examples/Conditions/ConditionsArticle.xml \
../examples/Dictionaries/DictionariesArticle.xml \
../examples/Localization/LocalizationArticle.xml \
../examples/Reflection/ReflectionArticle.xml \
../examples/Splitters/SplittersArticle.xml \
../examples/Tables/TablesArticle.xml \
../examples/VisualFormFiles/VisualFormFilesArticle.xml 








XMAKE_DOCS = vcf.css xmake_book.xml xmake_docbook.xml



coredocs :  $(VCF_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
	xsltproc --nonet vcf.xsl vcf_docbook.xml
	mv vcf_book.xml.bak vcf_book.xml

#xsltproc --nonet -o vcfbook.fo $(XSL_DOCBOOK_DIR)/fo/docbook.xsl vcf_docbook.xml
coredocs-fo :  $(VCF_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
	xsltproc --nonet -o vcfbook.fo $(XSL_DOCBOOK_DIR)/fo/docbook.xsl vcf_docbook.xml	
	mv vcf_book.xml.bak vcf_book.xml

coredocs_online :  $(VCF_DOCS) test_tools 
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
	xsltproc --nonet vcf_online.xsl vcf_docbook.xml	
	mv vcf_book.xml.bak vcf_book.xml


coredocs_hh : coredocs vcf-docbook.hhp 
	-$(HTMLHELP_COMPILER) vcf-docbook.hhp
	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME)



tutorials : test_tools
	for file in $(TUTORIAL_ARTICLES);\
	do\
		out=`dirname $$file`/`basename $$file .xml`.html;\
		echo $$out;\
		xsltproc --nonet $(XSL_HTML_IMPORT) $$file > $$out;\
	done



#steps - this one is a bit complex
#creates source code docs, and creates the html help for them
#create the docbook generated html using the vcf_with_source_docs stylesheet
#which turns on the generation of linkage to the source code docs
#then we back up our orginal .hhp and .toc files (these have the VCF-SOURCE-CHM
#variables). The VCF-SOURCE-CHM occurences all get replaced with the right
#file name of the chm file, and we then go and produce our master
#doc chm. Finally we restore the altered .hhp and .hhc files to their
#original contents

#doxy doxy_hh
coredocs_hh_with_source : $(VCF_DOCS) test_tools 
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
	xsltproc --nonet vcf_with_source_docs.xsl vcf_docbook.xml
	cp vcf-docbook.hhp vcf-docbook.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" vcf-docbook.hhp > vcf-docbook.hhp.tmp
	mv vcf-docbook.hhp.tmp vcf-docbook.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) vcf-docbook.hhp
	mv vcf-docbook.hhp.bak vcf-docbook.hhp
	mv toc.hhc.bak toc.hhc

	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_CHI_FILENAME) )\
	then\
		mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
	fi
	mv vcf_book.xml.bak vcf_book.xml	

	


alldocs : $(VCF_DOCS) test_tools 
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
		
	xsltproc --nonet vcf.xsl vcf_docbook.xml

	mv vcf_book.xml.bak vcf_book.xml


alldocs_hh : alldocs 
	cp vcf-docbook.hhp vcf-docbook.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" vcf-docbook.hhp > vcf-docbook.hhp.tmp
	mv vcf-docbook.hhp.tmp vcf-docbook.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) vcf-docbook.hhp
	mv vcf-docbook.hhp.bak vcf-docbook.hhp
	mv toc.hhc.bak toc.hhc
	
	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_CHI_FILENAME) )\
	then\
		mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
	fi	


alldocs_online : $(VCF_DOCS) test_tools $(VCF_BUILDER_DOCS) $(XMAKE_DOCS)
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml

	xsltproc --nonet vcf_online.xsl vcf_website_docs.xml

	mv vcf_book.xml.bak vcf_book.xml

alldocs_hh_with_source : $(VCF_DOCS) test_tools doxy doxy_hh
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml

	xsltproc --nonet vcf_with_source_docs.xsl vcf_docbook.xml

	mv vcf_book.xml.bak vcf_book.xml

	cp vcf-docbook-with-src.hhp vcf-docbook-with-src.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" vcf-docbook-with-src.hhp > vcf-docbook-with-src.hhp.tmp
	mv vcf-docbook-with-src.hhp.tmp vcf-docbook-with-src.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) vcf-docbook-with-src.hhp
	mv vcf-docbook-with-src.hhp.bak vcf-docbook-with-src.hhp
	mv toc.hhc.bak toc.hhc

	mv $(RAW_SRC_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	if ( test -f $(RAW_SRC_CHI_FILENAME) )\
	then\
		mv $(RAW_SRC_CHI_FILENAME) $(VERSIONED_CHI_FILENAME);\
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
		


alldocs_hh_src_separate : $(VCF_DOCS) test_tools $(VCF_BUILDER_DOCS) $(XMAKE_DOCS) doxy doxy_hh
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml

	xsltproc --nonet vcf.xsl vcf_website_docs.xml

	mv vcf_book.xml.bak vcf_book.xml

	cp vcf-docbook.hhp vcf-docbook.hhp.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" vcf-docbook.hhp > vcf-docbook.hhp.tmp
	mv vcf-docbook.hhp.tmp vcf-docbook.hhp
	cp toc.hhc toc.hhc.bak
	sed "s?VCF-SOURCE-CHM?$(VERSIONED_SRC_CHM_FILENAME)?g" toc.hhc > toc.hhc.tmp
	mv toc.hhc.tmp toc.hhc
	-$(HTMLHELP_COMPILER) vcf-docbook.hhp
	mv vcf-docbook.hhp.bak vcf-docbook.hhp
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



doxy : 
	cp Doxyfile Doxyfile.bak
	sed "s?VERSION-NUMBER?$(VERSION)?g" Doxyfile > Doxyfile.tmp
	mv Doxyfile.tmp Doxyfile
	doxygen
	mv Doxyfile.bak Doxyfile
	cp -r gfx/ doxy_html/
	cp vcf.css doxy_html/
	cp vcf_tabs.css doxy_html/


online_doxy :  
	cp Doxyfile.online Doxyfile.bak
	sed "s?VERSION-NUMBER?$(VERSION)?g" Doxyfile.online > Doxyfile.tmp
	mv Doxyfile.tmp Doxyfile.online
	doxygen Doxyfile.online
	mv Doxyfile.bak Doxyfile.online
	cp -r gfx/ doxy_html/
	cp vcf.css doxy_html/
	cp vcf_tabs.css doxy_html/
		



doxy_hh : doxy_html/index.hhp
	sed -i "s?tabs.css?vcf_tabs.css?g" doxy_html/index.hhp
	sed -i "s?tab_b.gif?gfx/vcf_tab_b.gif?g" doxy_html/index.hhp
	sed -i "s?tab_l.gif?gfx/vcf_tab_l.gif?g" doxy_html/index.hhp
	sed -i "s?tab_r.gif?gfx/vcf_tab_r.gif?g" doxy_html/index.hhp
	sed -i "s?0x23520?0x53520?g" doxy_html/index.hhp
	mv doxy_html/index.hhp doxy_html/$(VERSIONED_SRC_HHP_FILENAME)
	-$(HTMLHELP_COMPILER) doxy_html/$(VERSIONED_SRC_HHP_FILENAME)	
	mv doxy_html/$(VERSIONED_SRC_CHM_FILENAME) ./
	mv doxy_html/$(VERSIONED_SRC_CHI_FILENAME) ./
	

mshelp2_doxy_hh : 
	cp Doxyfile_mshelp2 Doxyfile_mshelp2.bak
	sed "s?VERSION-NUMBER?$(VERSION)?g" Doxyfile_mshelp2 > Doxyfile_mshelp2.tmp
	mv Doxyfile_mshelp2.tmp Doxyfile_mshelp2
	doxygen Doxyfile_mshelp2
	mv Doxyfile_mshelp2.bak Doxyfile_mshelp2
	cp -r gfx/ doxy_mshelp2_html/
	cp vcf.css doxy_mshelp2_html/
	cp vcf_tabs.css doxy_mshelp2_html/
	sed -i "s?tabs.css?vcf_tabs.css?g" doxy_mshelp2_html/index.hhp
	sed -i "s?tab_b.gif?gfx/vcf_tab_b.gif?g" doxy_mshelp2_html/index.hhp
	sed -i "s?tab_l.gif?gfx/vcf_tab_l.gif?g" doxy_mshelp2_html/index.hhp
	sed -i "s?tab_r.gif?gfx/vcf_tab_r.gif?g" doxy_mshelp2_html/index.hhp
	sed -i "s?0x23520?0x53520?g" doxy_mshelp2_html/index.hhp
	mv doxy_mshelp2_html/index.hhp doxy_mshelp2_html/$(VERSIONED_SRC_HHP_FILENAME)
	-$(HTMLHELP_COMPILER) doxy_mshelp2_html/$(VERSIONED_SRC_HHP_FILENAME)

mshelp2_coredocs :  $(VCF_DOCS) test_tools
	sed "s?VERSION-NUMBER?$(VERSION)?g" vcf_book.xml > vcf_book.xml.tmp
	cp vcf_book.xml vcf_book.xml.bak
	mv vcf_book.xml.tmp vcf_book.xml
	xsltproc --nonet vcf.xsl vcf_docbook.xml
	mv vcf_book.xml.bak vcf_book.xml

mshelp2_coredocs_hh : mshelp2_coredocs vcf-docbook.hhp 
	-$(HTMLHELP_COMPILER) vcf-docbook.hhp
	mv $(RAW_CHM_FILENAME) $(VERSIONED_CHM_FILENAME)
	mv $(RAW_CHI_FILENAME) $(VERSIONED_CHI_FILENAME)

#dist : coredocs hh 
#	find *.html > files.out
#	find gfx/ -type f -name '*' > images.out
#	cat files.out images.out > all.out
#	echo Creating tar file...
#	tar -cf $(HTML_TAR_FILENAME) -T all.out
#	gzip $(HTML_TAR_FILENAME)
#	echo HTML files tarred and compressed as $(HTML_TAR_FILENAME).gz		
#	rm all.out
#	rm files.out
#	rm images.out

dist_all : 
	-mkdir VCFDocs-$(VERSION)	
	cp *.html VCFDocs-$(VERSION)/
	cp *.css VCFDocs-$(VERSION)/
	cp -r gfx/ VCFDocs-$(VERSION)/
	tar -cf VCFDocs-$(VERSION).tar VCFDocs-$(VERSION)/ 
	gzip VCFDocs-$(VERSION).tar
	rm -rf VCFDocs-$(VERSION)/
	if ( test -d $(UPLOADS_DIR) )\
	then \
		mv VCFDocs-$(VERSION).tar.gz $(UPLOADS_DIR)/;\
	fi
	

	
	
dist_all_hh : alldocs_hh
	-mkdir VCFDocs-$(VERSION)	
	cp $(VERSIONED_CHM_FILENAME) VCFDocs-$(VERSION)/
	-cp $(VERSIONED_CHI_FILENAME) VCFDocs-$(VERSION)/	
	-cp $(VERSIONED_SRC_CHM_FILENAME) VCFDocs-$(VERSION)/
	-cp $(VERSIONED_SRC_CHI_FILENAME) VCFDocs-$(VERSION)/
	tar -cf VCFHtmlHelpDocs-$(VERSION).tar VCFDocs-$(VERSION)/ 
	gzip VCFHtmlHelpDocs-$(VERSION).tar
	rm -rf VCFDocs-$(VERSION)/	

dist_doxy : 
	@echo creating tmp directory in VCFHTMLDocs-$(VERSION)
	-mkdir VCFHTMLDocs-$(VERSION)
	@echo copying over files...
	cp -r doxy_html/* VCFHTMLDocs-$(VERSION)/
	@echo creating tar file VCFHtmlDocs-$(VERSION).tar from files...
	tar -cf VCFHtmlDocs-$(VERSION).tar VCFHTMLDocs-$(VERSION)/	
	@echo compressing tar file VCFHtmlDocs-$(VERSION).tar...
	gzip VCFHtmlDocs-$(VERSION).tar
	@echo Removing tmp directory VCFHTMLDocs-$(VERSION)/
	-rm -rf VCFHTMLDocs-$(VERSION)/	

	

dist_online : coredocs_online  
	find *.html > files.out
	find gfx/ -type f -name '*' > images.out
	cat files.out images.out > all.out
	@echo Creating tar file...
	tar -cf $(HTML_ONLINE_TAR_FILENAME) -T all.out vcf.css 
	-rm -f $(HTML_ONLINE_TAR_FILENAME).gz
	gzip $(HTML_ONLINE_TAR_FILENAME)
	@echo HTML files tarred and compressed as $(HTML_ONLINE_TAR_FILENAME).gz		
	-rm all.out
	-rm files.out
	-rm images.out


dist_doxy_online : online_doxy  	
	echo Creating tar file...
	cd doxy_html; tar -cf ../$(HTML_ONLINE_SRC_TAR_FILENAME) ./
	rm -f $(HTML_ONLINE_SRC_TAR_FILENAME).gz	
	gzip $(HTML_ONLINE_SRC_TAR_FILENAME)
	echo HTML files tarred and compressed as $(HTML_ONLINE_SRC_TAR_FILENAME).gz			

#alldocs_online online_doxy
dist_all_online : dist_online dist_doxy_online
	
	if ( test -d $(UPLOADS_DIR) )\
	then \
		mv $(HTML_ONLINE_TAR_FILENAME).gz $(UPLOADS_DIR)/;\
		mv $(HTML_ONLINE_SRC_TAR_FILENAME).gz $(UPLOADS_DIR)/;\
	fi


dist : dist_all_online alldocs_hh_with_source dist_all
	

clean :
	mv doxy_footer.html doxy_footer.html.bak
	mv doxy_header.html doxy_header.html.bak
	mv doxy_header.mshelp2.html doxy_header.mshelp2.html.bak
	mv doxy_footer.mshelp2.html doxy_footer.mshelp2.html.bak
	rm -f *.html
	rm -f $(HTML_TAR_FILENAME).gz
	rm -f $(HTML_ONLINE_TAR_FILENAME).gz
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
	mv doxy_header.mshelp2.html.bak doxy_header.mshelp2.html
	mv doxy_footer.mshelp2.html.bak doxy_footer.mshelp2.html



###############################################################################
#$Id$
