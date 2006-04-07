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
	String result = peer_->getVFF( resourceName );
	if ( result.empty() ) {
		String localeName = System::getCurrentThreadLocale()->getName();

		bool fileExists = false;
		String vffFile = getResourcesDirectory() + resourceName;

		if ( File::exists( vffFile ) ) {
			fileExists = true;
		}
		else {
			vffFile += ".vff";
			if ( File::exists( vffFile ) ) {
				fileExists = true;
			}
		}

		if ( fileExists ) {
			FileInputStream fs(vffFile);

			fs >> result;
		}
	}
	return result;
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

		size_t pos = resDir.rfind( "Resources" );

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
				String programFileName;
				
				CommandLine cmdLine = FoundationKit::getCommandLine();
				programFileName = cmdLine.getArgument(0);

				result = System::getProgramInfoFromInfoFile(infoFilename, programFileName);
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
*Revision 1.6  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.5  2006/03/26 22:37:35  ddiego
*minor update to source docs.
*
*Revision 1.4.2.4  2005/11/10 02:02:38  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.4.2.3  2005/09/19 04:55:56  ddiego
*minor updates.
*
*Revision 1.4.2.2  2005/09/07 04:19:55  ddiego
*filled in initial code for help support.
*
*Revision 1.4.2.1  2005/07/24 02:30:26  ddiego
*fixed bug in retreiving program info.
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

