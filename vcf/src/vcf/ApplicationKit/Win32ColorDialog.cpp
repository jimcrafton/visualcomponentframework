//Win32ColorDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32ColorDialog.h"


using namespace VCF;



Win32ColorDialog::Win32ColorDialog( Control* owner )
{
	owner_ = owner;
}

Win32ColorDialog::~Win32ColorDialog()
{

}

Color* Win32ColorDialog::getSelectedColor()
{
	return &color_;
}

void Win32ColorDialog::setSelectedColor( Color* selectedColor )
{
	color_.copy( selectedColor );
}

void Win32ColorDialog::setTitle( const String& title )
{
	title_ = title;
}

bool Win32ColorDialog::execute()
{
	bool result = false;

	CHOOSECOLOR color;
	memset( &color, 0, sizeof(CHOOSECOLOR) );
	color.lStructSize = sizeof(CHOOSECOLOR);
	COLORREF customColors[16];
	color.lpCustColors = customColors;

	color.hInstance = NULL;
	color.hwndOwner = NULL;

	if ( NULL != owner_ ){
		color.hwndOwner = (HWND)owner_->getPeer()->getHandleID();
	}
	else {
		color.hwndOwner = GetActiveWindow();
	}

	color.rgbResult = color_.getColorRef32();

	color.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;

	if ( ChooseColor( &color ) ){
		result = true;
		color_.setColorRef32( color.rgbResult );
	}

	return result;
}


/**
$Id$
*/
