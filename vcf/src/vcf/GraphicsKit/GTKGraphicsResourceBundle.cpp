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
	Image* result = NULL;


	return result;
}






/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:05:58  ddiego
*added missing gtk files
*
*Revision 1.1.2.1  2005/04/17 16:11:32  ddiego
*brought the foundation, agg, and graphics kits uptodate on linux
*
*/



