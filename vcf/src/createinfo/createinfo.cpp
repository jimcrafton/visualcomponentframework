//createinfo.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


/**
createinfo is a little utility to create or update an INfo.xml file.
It provides a very simple command line interface that allows you send in 
the author, version and bundle name. It does everything else. If an
output dir is specified and the Info.plsit/xml file exists, then an update
is performed, otherwise a new file is created.
If no output directory is specified, then the program outputs to stdout.
*/

#define USAGE "Proper arguments to send to me are:\n"\
				"\t-version <version number>\n"\
				"\t-author <author name, in double quotes!>\n"\
				"\t[-out <output directory - if one is not specified, then output is to stdout>]\n"\
				"\t-name <bundle name for the info file>\n"\
				"\t-exe <executable name - NOT the path, just the name and extension."



int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	CommandLine cmdLine = FoundationKit::getCommandLine();
	if ( !cmdLine.hasSwitch( "-author" ) ) {
		System::println( "Please supply an author value!" );
		System::println( USAGE );
		return 1;	
	}
	
	if ( !cmdLine.hasSwitch( "-version" ) ) {
		System::println( "Please supply an version number value!" );
		System::println( USAGE );
		return 1;	
	}

	if ( !cmdLine.hasSwitch( "-name" ) ) {
		System::println( "Please supply a bundle name!" );
		System::println( USAGE );
		return 1;	
	}

	if ( !cmdLine.hasSwitch( "-exe" ) ) {
		System::println( "Please supply an executable name!" );
		System::println( USAGE );
		return 1;	
	}

	String version = cmdLine.getArgument( "-version", 0 );
	String author = cmdLine.getArgument( "-author", 0 );
	
	String bundleName = cmdLine.getArgument( "-name", 0 );

	String exeName = cmdLine.getArgument( "-exe", 0 );

	String outDir;

	if ( cmdLine.hasSwitch( "-out" ) ) {
		FilePath fp = cmdLine.getArgument( "-out", 0 );
		
		if ( fp.isRelativePath() ) {
			//expand it completely using hte current working dir
			
			outDir = FilePath::makeDirectoryName( fp.expandRelativePathName( System::getCurrentWorkingDirectory() ) );
		}
	}

	DateTime date = DateTime::now();

	String crlf = "\n";

	String copyright = StringUtils::toString( date.getYear() ) + " " + author;

	String infoFileName = outDir + "Info.plist";
	String infoXML;

	//does the file already exist???
	if ( !outDir.empty() && File::exists( infoFileName ) ) {
		
		XMLParser xmlParser;
		FileInputStream fs(infoFileName);
		xmlParser.parse( &fs );				
		fs.close();

		XMLNode* topNode = NULL;
		XMLNode* dictNode = NULL;
		Enumerator<XMLNode*>* nodes = xmlParser.getParsedNodes();
		while ( nodes->hasMoreElements() ) {
			XMLNode* node = nodes->nextElement();
			if ( NULL == topNode ) {
				topNode = node; //store off the first node
			}
			if ( node->getName() == L"plist" ) {
				dictNode = node->getNodeByName( L"dict" );
				break;
			}
		}

		if ( NULL != dictNode ) {
			nodes = dictNode->getChildNodes();
			bool needsProgramVersion = true;
			bool needsExecutable = true;
			bool needsFileVersion = true;
			bool needsProductName = true;
			bool needsCopyright = true;
			bool needsAuthor = true;

			while ( nodes->hasMoreElements() ) {
				XMLNode* key = nodes->nextElement();
				XMLNode* val = NULL;
				
				if ( nodes->hasMoreElements() ) {
					val = nodes->nextElement();
				}
				
				if ( (NULL != val) && (key->getName() == "key") ) {
					String cdata = key->getCDATA();
					StringUtils::trimWhiteSpaces( cdata );
					key->setCDATA( cdata );

					if ( cdata == "ProgramVersion" ) {
						val->setCDATA( version );
						needsProgramVersion = false;
					}
					else if ( cdata == "Executable" ) {
						val->setCDATA( exeName );
						needsExecutable = false;
					}
					else if ( cdata == "FileVersion" ) {
						val->setCDATA( version );
						needsFileVersion = false;
					}
					else if ( cdata == "ProductName" ) {
						val->setCDATA( bundleName );
						needsProductName = false;
					}
					else if ( cdata == "Copyright" ) {
						val->setCDATA( copyright );
						needsCopyright = false;
					}
					else if ( cdata == "Author" ) {
						val->setCDATA( author );
						needsAuthor = false;
					}
					else { //strip out trailing white space
						cdata = val->getCDATA();
						StringUtils::trimWhiteSpaces( cdata );
						val->setCDATA( cdata );
					}
				}
			}
			
			XMLNode* key = NULL;
			XMLNode* value = NULL;
			if ( needsProgramVersion ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "ProgramVersion" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( version );
			}

			if ( needsExecutable ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "Executable" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( exeName );
			}

			if ( needsFileVersion ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "FileVersion" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( version );
			}

			if ( needsProductName ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "ProductName" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( bundleName );
			}

			if ( needsCopyright ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "Copyright" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( copyright );
			}

			if ( needsAuthor ) {
				key = dictNode->addChildNode( "key" );
				key->setCDATA( "Author" );

				value = dictNode->addChildNode( "string" );
				value->setCDATA( author );
			}

			String createinfoComments = "Info.xml file updated by createinfo on " + StringUtils::format( date, "%a %B %d, %Y %H:%M:%S" );
		
			String xmlHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
			
			infoXML = xmlHeader + crlf + "<!--" + createinfoComments + "-->" + crlf;
		

			infoXML += topNode->toString();
		}
		else {
			System::println( "Invalid Info.xml file!" );
			return 1;
		}		
	}	
	else {
		
		String createinfoComments = "Info.xml file created by createinfo on " + StringUtils::format( date, "%a %B %d, %Y %H:%M:%S" );
		
		String xmlHeader = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";		
		
		infoXML += xmlHeader + crlf + "<!--" + createinfoComments + "-->" + crlf;
		
		
		XMLNode plist;
		plist.setName( "plist" );
		
		XMLNode* dict = plist.addChildNode( "dict" );
		XMLNode* key = dict->addChildNode( "key" );
		key->setCDATA( "ProgramVersion" );
		
		XMLNode* value = dict->addChildNode( "string" );
		value->setCDATA( version );
		
		key = dict->addChildNode( "key" );
		key->setCDATA( "Executable" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( exeName );


		key = dict->addChildNode( "key" );
		key->setCDATA( "FileVersion" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( version );
		
		key = dict->addChildNode( "key" );
		key->setCDATA( "ProductName" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( bundleName );
		
		key = dict->addChildNode( "key" );
		key->setCDATA( "Copyright" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( copyright );
		
		key = dict->addChildNode( "key" );
		key->setCDATA( "Author" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( author );
		
		key = dict->addChildNode( "key" );
		key->setCDATA( "Company" );
		
		value = dict->addChildNode( "string" );
		value->setCDATA( "Your company" );
		
		infoXML += plist.toString();
		
	}


	if ( !outDir.empty() && !infoFileName.empty() ) {

		//check if we need to create the directory!
		if ( !File::exists( outDir ) ) {
			//yep, go ahead and create it!

			Directory infoDir;
			infoDir.create( outDir, File::ofRead | File::ofWrite );
		}

		FileOutputStream fs( infoFileName );
		TextOutputStream ts(&fs);

		ts << infoXML;
	}
	else {
		System::println( infoXML );
	}	

	FoundationKit::terminate();
	return 0;
}



/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:34:58  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.2.1  2005/11/02 16:07:16  ddiego
*updates to createinfo program.
*
*Revision 1.2  2005/07/09 23:14:49  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.3  2004/12/22 02:59:14  marcelloptr
*added cvs log section
*
*/


