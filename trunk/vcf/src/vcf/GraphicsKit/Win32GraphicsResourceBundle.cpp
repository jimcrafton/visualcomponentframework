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
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.2.1  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.2  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.5  2004/11/21 00:19:11  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.1.2.4  2004/11/18 06:45:44  ddiego
*updated toolbar btn bug, and added text edit sample.
*
*Revision 1.1.2.3  2004/09/15 04:25:53  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.1.2.2  2004/08/27 03:50:47  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*/



