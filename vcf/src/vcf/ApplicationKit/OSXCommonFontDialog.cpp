/*
 Copyright 2000-3007 The VCF Project, Jim Crafton.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXCommonFontDialog.h"


namespace VCF {

OSXFontDialog::OSXFontDialog( Control* owner )
{
	
}

OSXFontDialog::~OSXFontDialog()
{
	
}

void OSXFontDialog::setTitle( const String& title )
{
	
}

bool OSXFontDialog::execute()
{
	return true;
}

Font* OSXFontDialog::getSelectedFont()
{
	return &font_;
}

void OSXFontDialog::setSelectedFont( Font* selectedFont )
{
	
}

}


