/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//GTKGraphicsResourceBundle.cpp
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/GTKGraphicsResourceBundle.h"


using namespace VCF;




GTKGraphicsResourceBundle::GTKGraphicsResourceBundle()
{

}

GTKGraphicsResourceBundle::~GTKGraphicsResourceBundle()
{

}

Image* GTKGraphicsResourceBundle::getImage( const String& resourceName )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	Image* result = NULL;
	return result;
}


/**
$Id$
*/
