#!/usr/bin/env python
#
# Author: Jim Crafton
#
# creates basic docbook xml for a given example

import sys
import os
import os.path
import shutil
import getopt
import string


VCFCOPYRIGHT="<!--\n\n"\
"Copyright (c) 2003, Author Name\n\n"\
"-->\n"



def main():
	
	exampleName = sys.argv[1:][0]
	
	os.chdir( '../examples' )
	
	if not os.path.exists( exampleName ) :
		os.mkdir( exampleName )
	
	os.chdir( exampleName )
	
	
	
	article = "<?xml version=\"1.0\" standalone=\"no\"?>""\n"\
			  "<!DOCTYPE  book  PUBLIC \"-//OASIS//DTD DocBook XML V4.2//EN\"""\n"\
			  "\t""\"http://www.oasis-open.org/docbook/xml/4.2/docbookx.dtd\" [""\n"\
			  "\t""<!ENTITY $1 SYSTEM \"" + exampleName + ".xml\">""\n"\
			  "]>""\n"\
			  "\n"\
			  "\n"\
			  "<article>""\n"\
			  "  &" + exampleName + ";	""\n"\
			  "</article>""\n"
	
	
	
	fs = file( exampleName + "Article.xml", 'w' )
	fs.write( article )
	fs.close()
	
	
	docs = VCFCOPYRIGHT + "\n\n<section><title>" + exampleName + "</title>\n"\
						  "\t<para>\n"\
						  "\t\tYour content here, explaining the usage/functioning of your example.\n"\
						  "\t</para>\n"\
						  "</section>\n\n\n\n\n"\
						  "<!--\n"\
						  "CVS Log info\n"\
						  "\$Log: " + exampleName + ".xml,v \n"\
						  "-->\n\n"  


	
	fs = file( exampleName + ".xml", 'w' )
	fs.write( docs )
	fs.close()
	
	return

if __name__ == '__main__':
    main()
	
    pass