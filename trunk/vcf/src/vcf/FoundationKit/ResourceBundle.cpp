//ResourceBundle.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"



using namespace VCF;


ResourceBundle::ResourceBundle():
	Object(),
	peer_(NULL)
{
	peer_ = SystemToolkit::createResourceBundlePeer();
}

ResourceBundle::~ResourceBundle()
{
	delete peer_;
}

String ResourceBundle::getString( const ulong32& resourceID )
{
	return getString( StringUtils::toString( resourceID ) );
}

String ResourceBundle::getString( const String& resourceName )
{
	return peer_->getString( resourceName );
}

String ResourceBundle::getVFF( const String& resourceName )
{
	return peer_->getVFF( resourceName );
}

Resource* ResourceBundle::getResource( const String& resourceName )
{
	return peer_->getResource( resourceName );
}

ProgramInfo* ResourceBundle::getProgramInfo()
{
	ProgramInfo* result = peer_->getProgramInfo();

	if ( NULL == result ) {

		String resDir = System::findResourceDirectory();

		int pos = resDir.rfind( "Resources" );

		if ( pos != String::npos ) {
			resDir.erase( pos, resDir.size()-pos );
			String infoFilename = resDir + "Info.plist";

			bool found = false;
			if ( File::exists( infoFilename ) ) {
				found = true;
			}
			else {
				infoFilename = resDir + "Info.xml";
				if ( File::exists( infoFilename ) ) {
					found = true;
				}
			}	

			if ( found ) {
				String name;
				String programFileName;
				String author;
				String copyright;
				String company;
				String description;
				String programVersion;
				String fileVersion;

				CommandLine cmdLine = FoundationKit::getCommandLine();
				programFileName = cmdLine.getArgument(0);

				XMLParser xmlParser;
				FileInputStream fs(infoFilename);
				xmlParser.parse( &fs );				
				fs.close();

				XMLNode* dictNode = NULL;
				Enumerator<XMLNode*>* nodes = xmlParser.getParsedNodes();
				while ( nodes->hasMoreElements() ) {
					XMLNode* node = nodes->nextElement();
					if ( node->getName() == L"plist" ) {
						dictNode = node->getNodeByName( L"dict" );
						break;
					}
				}

				if ( NULL != dictNode ) {
					nodes = dictNode->getChildNodes();
					while ( nodes->hasMoreElements() ) {
						XMLNode* node = nodes->nextElement();
						XMLNode* val = NULL;

						if ( nodes->hasMoreElements() ) {
							val = nodes->nextElement();
						}

						if ( (NULL != val) && (node->getName() == "key") ) {
							String cdata = node->getCDATA();
							StringUtils::trimWhiteSpaces( cdata );

							if ( cdata == "CFBundleName" ) {
								name = val->getCDATA();
								StringUtils::trimWhiteSpaces( name );
							}
							else if ( cdata == "CFBundleDisplayName" ) {
								name = val->getCDATA();
								StringUtils::trimWhiteSpaces( name );
							}
							else if ( cdata == "CFBundleVersion" ) {
								fileVersion = programVersion = val->getCDATA();
								StringUtils::trimWhiteSpaces( fileVersion );
							}
							else if ( cdata == "CFBundleGetInfoString" ) {
								copyright = programVersion = val->getCDATA();
								StringUtils::trimWhiteSpaces( copyright );
							}
							else if ( cdata == "NSHumanReadableCopyright" ) {
								copyright = programVersion = val->getCDATA();							
								StringUtils::trimWhiteSpaces( copyright );
							}

							
							//VCF cross platform keys
							else if ( cdata == "ProgramVersion" ) {
								programVersion = val->getCDATA();
								StringUtils::trimWhiteSpaces( programVersion );
							}
							else if ( cdata == "FileVersion" ) {
								programVersion = val->getCDATA();
								StringUtils::trimWhiteSpaces( programVersion );
							}
							else if ( cdata == "ProductName" ) {
								name = val->getCDATA();
								StringUtils::trimWhiteSpaces( name );
							}
							else if ( cdata == "Copyright" ) {
								copyright = val->getCDATA();
								StringUtils::trimWhiteSpaces( copyright );
							}
							else if ( cdata == "Author" ) {
								author = val->getCDATA();
								StringUtils::trimWhiteSpaces( author );
							}
							else if ( cdata == "Company" ) {
								company = val->getCDATA();
								StringUtils::trimWhiteSpaces( company );
							}
							else if ( cdata == "Description" ) {
								description = val->getCDATA();
								StringUtils::trimWhiteSpaces( description );
							}
						}
					}

					result = new ProgramInfo( name, programFileName, author, copyright, company, description, programVersion, fileVersion );
				}
			}
		}
	}

	return result;
}

String ResourceBundle::getResourcesDirectory()
{
	return System::findResourceDirectory();
}



/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/24 14:58:24  ddiego
*bug fix for program info extraction.
*
*Revision 1.4  2005/01/08 20:52:47  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.2.1  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.2  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.5  2004/11/17 04:52:49  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.1.2.4  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.1.2.3  2004/09/16 03:26:26  ddiego
*fixed it so we can now get program information from a resource bundle. This can be embedded in the exe like in windows, or read from an external file a la OS X info.plist xml files.
*
*Revision 1.1.2.2  2004/09/15 21:14:28  ddiego
*added support for getting program info from resource bundle.
*
*Revision 1.1.2.1  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*/

