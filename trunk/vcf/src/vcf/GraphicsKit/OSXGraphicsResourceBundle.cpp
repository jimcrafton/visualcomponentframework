/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//OSXGraphicsResourceBundle.cpp
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/OSXGraphicsResourceBundle.h"


using namespace VCF;




OSXGraphicsResourceBundle::OSXGraphicsResourceBundle()
{

}

OSXGraphicsResourceBundle::~OSXGraphicsResourceBundle()
{

}

Image* OSXGraphicsResourceBundle::getImage( const String& resourceName )
{
	Image* result = NULL;
	
	CFBundleRef bundle = getBundle();
	
	FilePath fp(resourceName);
	String ext = fp.getExtension();
	if ( !ext.empty() ){
		int pos = ext.find(".");
		if ( pos != String::npos ) {
			ext.erase( pos, 1 );
		}
	}
	
	if ( StringUtils::lowerCase(ext) == "jpg" ||
			StringUtils::lowerCase(ext) == "jpeg" ||
			StringUtils::lowerCase(ext) == "png" ) {
			
		CFTextString resName(fp.getBaseName());
		CFTextString resType(ext);
	
		CFRefObject<CFURLRef> resURL = CFBundleCopyResourceURL( bundle, resName, resType, NULL );
				
		result = new OSXImage( resURL, ext );	
	}	

	return result;
}






/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:06:00  ddiego
*added missing gtk files
*
*Revision 1.1.2.2  2005/06/23 01:26:56  ddiego
*build updates
*
*/



