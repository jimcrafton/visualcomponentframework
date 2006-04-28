/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32GraphicsResourceBundle.cpp
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/Win32GraphicsResourceBundle.h"


using namespace VCF;




Win32GraphicsResourceBundle::Win32GraphicsResourceBundle()
{

}

Win32GraphicsResourceBundle::~Win32GraphicsResourceBundle()
{

}

Image* Win32GraphicsResourceBundle::getImage( const String& resourceName )
{
	Image* result = NULL;

	HBITMAP resBMP = NULL;
	if ( System::isUnicodeEnabled() ) {
		resBMP = (HBITMAP)LoadImageW( getResourceInstance(), resourceName.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		
		if ( NULL != resBMP ){
			result = new Win32Image( resBMP );
			DeleteObject( resBMP );
		}
		else {
			
			HICON ico = (HICON)LoadImageW( getResourceInstance(), resourceName.c_str(), IMAGE_ICON, 0, 0, LR_CREATEDIBSECTION );
		
			if ( NULL != ico ) {
				result = new Win32Image( ico );
				
				DestroyIcon( ico );
			}
			else { //last gasp - try a cursor
				HCURSOR cursor = (HICON)LoadImageW( getResourceInstance(), resourceName.c_str(), IMAGE_CURSOR, 0, 0, LR_CREATEDIBSECTION );

				if ( NULL != cursor ) {
					result = new Win32Image( (HICON)cursor );
				
					DestroyCursor( cursor );
				}
			}
		}
	}
	else {
		const char* resName = resourceName.ansi_c_str();

		resBMP = (HBITMAP)LoadImageA( getResourceInstance(), resName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
		
		if ( NULL != resBMP ){
			result = new Win32Image( resBMP );
			DeleteObject( resBMP );
		}
		else {
			
			HICON ico = (HICON)LoadImageA( getResourceInstance(), resName, IMAGE_ICON, 0, 0, LR_CREATEDIBSECTION );
		
			if ( NULL != ico ) {
				result = new Win32Image( ico );
				
				DestroyIcon( ico );
			}
			else { //last gasp - try a cursor
				HCURSOR cursor = (HICON)LoadImageA( getResourceInstance(), resName, IMAGE_CURSOR, 0, 0, LR_CREATEDIBSECTION );

				if ( NULL != cursor ) {
					result = new Win32Image( (HICON)cursor );
				
					DestroyCursor( cursor );
				}
			}
		}
	}


	return result;
}


/**
$Id$
*/
