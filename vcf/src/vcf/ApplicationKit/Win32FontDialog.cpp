//Win32FontDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32FontDialog.h"


using namespace VCF;


Win32FontDialog::Win32FontDialog( Control* owner )
{
	owner_ = owner;
}

Win32FontDialog::~Win32FontDialog()
{

}

void Win32FontDialog::setTitle( const String& title )
{

}

bool Win32FontDialog::execute()
{
	bool result = false;

	if ( System::isUnicodeEnabled() ) {

		CHOOSEFONTW chooseFont;
		memset( &chooseFont, 0, sizeof(chooseFont) );
		chooseFont.lStructSize = sizeof(chooseFont);
		if ( NULL != owner_ ){
			chooseFont.hwndOwner = (HWND)owner_->getPeer()->getHandleID();
		}
		else {
			chooseFont.hwndOwner = GetActiveWindow();
		}
		LOGFONTW logFont;
		memset( &logFont, 0, sizeof(logFont) );

		memcpy( &logFont, (LOGFONTW*)font_.getFontPeer()->getFontHandleID(), sizeof(logFont) );

		chooseFont.lpLogFont = &logFont;
		chooseFont.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
		Color* c = font_.getColor();
		chooseFont.rgbColors = c->getColorRef32();

		if ( ChooseFontW( &chooseFont ) ){
			c->setColorRef32(chooseFont.rgbColors);
			LOGFONTW* fontLogFont = (LOGFONTW*)font_.getFontPeer()->getFontHandleID();
			memcpy( fontLogFont, chooseFont.lpLogFont, sizeof(LOGFONTW) );
			result = true;
		}

	}
	else {
		CHOOSEFONTA chooseFont;
		memset( &chooseFont, 0, sizeof(chooseFont) );
		chooseFont.lStructSize = sizeof(chooseFont);
		if ( NULL != owner_ ){
			chooseFont.hwndOwner = (HWND)owner_->getPeer()->getHandleID();
		}
		else {
			chooseFont.hwndOwner = GetActiveWindow();
		}
		LOGFONTA logFont;
		memset( &logFont, 0, sizeof(logFont) );

		memcpy( &logFont, (LOGFONTA*)font_.getFontPeer()->getFontHandleID(), sizeof(logFont) );

		chooseFont.lpLogFont = &logFont;
		chooseFont.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
		Color* c = font_.getColor();
		chooseFont.rgbColors = c->getColorRef32();

		if ( ChooseFontA( &chooseFont ) ){
			c->setColorRef32(chooseFont.rgbColors);
			LOGFONTA* fontLogFont = (LOGFONTA*)font_.getFontPeer()->getFontHandleID();
			memcpy( fontLogFont, chooseFont.lpLogFont, sizeof(LOGFONTA) );
			result = true;
		}
	}


	return result;
}

Font* Win32FontDialog::getSelectedFont()
{
	return &font_;
}

void Win32FontDialog::setSelectedFont( Font* selectedFont )
{
	font_.copy( selectedFont );
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/06/26 01:53:03  marcelloptr
*improvements to the Color class. The default, when packing the components into a single integer, is now cpsARGB instead than cpsABGR.
*
*Revision 1.2.4.1  2005/06/09 06:13:08  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.12.8.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.12  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:12:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10.14.2  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.10  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.9  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


