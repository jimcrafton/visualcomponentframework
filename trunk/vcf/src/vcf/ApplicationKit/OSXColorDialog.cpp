//OSXColorDialog.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXColorDialog.h"


namespace VCF {

	
OSXColorDialog::OSXColorDialog( Control* owner )
{

}

OSXColorDialog::~OSXColorDialog()
{

}

Color* OSXColorDialog::getSelectedColor()
{
	return &color_;
}

void OSXColorDialog::setSelectedColor( Color* selectedColor )
{
	color_ = *selectedColor;
}

void OSXColorDialog::setTitle( const String& title )
{
	title_ = title;
}

bool OSXColorDialog::execute()
{
	NColorPickerInfo info ;
	memset( &info, 0, sizeof(info) );
	info.placeWhere = kCenterOnMainScreen;
	info.flags = kColorPickerDialogIsMoveable | kColorPickerDialogIsModal;
	info.theColor.color.rgb.red     = color_.getRed() * 0xffff;
	info.theColor.color.rgb.green   = color_.getGreen() * 0xffff;
	info.theColor.color.rgb.blue    = color_.getBlue() * 0xffff;
	
	//CopyCStringToPascal( "Hello World", &info.prompt );
	
	bool result = false;
	OSStatus err = NPickColor ( &info );
	
	if ((err == noErr) && info.newColorChosen)	{
		result = true;
		color_.setRed( ((double)info.theColor.color.rgb.red) / ((double)0xFFFF) );
		color_.setGreen( ((double)info.theColor.color.rgb.green) / ((double)0xFFFF) );
		color_.setBlue( ((double)info.theColor.color.rgb.blue) / ((double)0xFFFF) );
	}
	
	return result;
}



};

