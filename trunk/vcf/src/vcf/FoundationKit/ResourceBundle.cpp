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

String ResourceBundle::getString( const uint32& resourceID )
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
			resDir = resDir.erase( pos, resDir.size()-pos );
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
$Id$
*/
