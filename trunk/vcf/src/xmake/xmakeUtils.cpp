//xmakeUtils.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "xmakeUtils.h"
#include "XMLParser.h"
#include "CmdLine.h"
#include "FilePath.h"
#include <exception>
#include <stdexcept>




using namespace xmake;

String XMakeUtils::generateMakefile( const String& project, const String& makefileName, XMLMake& xmakeObj )
{
	String result;

	String currentDir = xmakeObj.getCurrentDirectory();

	/*
	xmakeObj.initializeXMLNodes();
	
	
	xmakeObj.parsedNodes_->reset();

	

	XMLNode* configNode = xmakeObj.getConfigNode();
	

	xmakeObj.initializeFromConfiguration( configNode );


	StringList filesToProcess;
	xmakeObj.generateSourceFileList( filesToProcess, configNode );

	String ccFlags;
	String linkFlags;

	String bar = "###############################################################################";
	result = bar + "\n#\n";
	result += "#makefile for " + project + "\n#\n";
	result += "#\n" + bar + "\n\n\n\n\n";

	String outputDir = ".";
	result += "OUTPUTDIR=" + outputDir + "\n";
	result += "OBJEXT=" + xmakeObj.srcBinExt_ + "\n\n\n";
	result += "CC=g++\n";
	result += "CC_FLAGS=" + ccFlags + "\n";

	result += "OUTPUT=" + xmakeObj.projectOutput_ + "\n";
	result += "OBJFILES=";

	StringList::iterator it = filesToProcess.begin();
	FilePath fp;

	while ( it != filesToProcess.end() ) {
		static bool first = true;
		fp = *it;			
		if ( first ) {
			
			result += "$(OUTPUTDIR)/" + fp.getName() + ".$(OBJEXT) \\\n";
		}
		else {
			if ( it == (filesToProcess.begin() + filesToProcess.size() -1) ) {
				result += "\t$(OUTPUTDIR)/" + fp.getName() + ".$(OBJEXT)\n\n\n";
			}
			else {
				result += "\t$(OUTPUTDIR)/" + fp.getName() + ".$(OBJEXT) \\\n";
			}
		}
		first = false;
		it ++;
	}

	result += "\n\n\n";

	result += bar += "\n";
	result += "# Build targets\n\n\n";


	result += "$(OUTPUT) : $(OBJFILES)\n";
	result += "\t" + xmakeObj.linker_ + " " + xmakeObj.linkerFlags_ + "$(OBJFILES)\n";

  */




	return result;
}



/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:27  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*/


