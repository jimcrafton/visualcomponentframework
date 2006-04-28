//GraphicsResourceBundle.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/FoundationKit/ResourceBundle.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"


using namespace VCF;



GraphicsResourceBundle::GraphicsResourceBundle():
	ResourceBundle(),
	graphicsResPeer_(NULL)
{
	delete peer_;
	graphicsResPeer_ = GraphicsToolkit::createGraphicsResourceBundlePeer();
	if ( NULL == graphicsResPeer_ ) {
		//throw exception! Missing peer implementation!
	}

	peer_ = dynamic_cast<ResourceBundlePeer*>( graphicsResPeer_ );
	if ( NULL == peer_ ) {
		//throw exception! Bad peer implementation!
	}
}

GraphicsResourceBundle::~GraphicsResourceBundle()
{

}

Image* GraphicsResourceBundle::getImage( const String& resourceName )
{
	Image* result = graphicsResPeer_->getImage( resourceName );

	if ( NULL == result ) {
		String fileName = getResourcesDirectory() + resourceName;
		
		if ( File::exists( fileName ) ) {
			result = GraphicsToolkit::createImage( fileName );
		}
	}

	return result;
}

Image* GraphicsResourceBundle::getImage( const ulong32& resourceID )
{
	return getImage( StringUtils::toString(resourceID) );
}


/**
$Id$
*/
