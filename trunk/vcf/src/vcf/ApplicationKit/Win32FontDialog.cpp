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
$Id$
*/
