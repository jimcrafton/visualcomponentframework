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
	return &this->color_;
}

void Win32ColorDialog::setSelectedColor( Color* selectedColor )
{
	this->color_.copy( selectedColor );
}

void Win32ColorDialog::setTitle( const String& title )
{
	this->title_ = title;
}

bool Win32ColorDialog::execute()
{
	bool result = false;

	CHOOSECOLOR color;
	memset( &color, 0, sizeof(CHOOSECOLOR) );
	color.lStructSize = sizeof(CHOOSECOLOR);
	COLORREF customColors[16];
	color.lpCustColors =
		customColors;
	color.hInstance = NULL;
	color.hwndOwner = NULL;

	if ( NULL != owner_ ){
		ControlPeer* impl = owner_->getPeer();
		color.hwndOwner = (HWND) impl->getHandleID();
	}

	color.rgbResult = this->color_.getRGB();

	color.Flags = CC_ANYCOLOR | CC_FULLOPEN;

	if ( ChooseColor( &color ) ){
		result = true;
		uchar r = GetRValue( color.rgbResult );
		uchar g = GetGValue( color.rgbResult );
		uchar b = GetBValue( color.rgbResult );
		this->color_.setRGB( r, g, b );
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:12:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:25  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.8  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


