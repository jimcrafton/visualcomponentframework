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
		size_t pos = ext.find(".");
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
*Revision 1.3  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.2.1  2005/11/10 02:02:39  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.2  2005/07/09 23:06:00  ddiego
*added missing gtk files
*
*Revision 1.1.2.2  2005/06/23 01:26:56  ddiego
*build updates
*
*/



