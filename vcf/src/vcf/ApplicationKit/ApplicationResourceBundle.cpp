/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

//ApplicationResourceBundle.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/ApplicationKit/ApplicationResourceBundle.h"

using namespace VCF;

ApplicationResourceBundle::ApplicationResourceBundle( AbstractApplication* app ):
	GraphicsResourceBundle(),
	app_(app)
{
	//destroy the old peer
	delete graphicsResPeer_;

	graphicsResPeer_ = UIToolkit::createGraphicsResourceBundlePeer( app );
	if ( NULL == graphicsResPeer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create a graphics resource bundle instance for the application!") );
	}

	peer_ = dynamic_cast<ResourceBundlePeer*>( graphicsResPeer_ );
}

String ApplicationResourceBundle::getResourcesDirectory()
{
	return System::findResourceDirectoryForExecutable( app_->getFileName() );
}

