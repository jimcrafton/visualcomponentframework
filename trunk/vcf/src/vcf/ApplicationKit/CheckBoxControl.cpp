//CheckBoxControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;

CheckBoxControl::CheckBoxControl()
{
	setVisible( true );

	useFixedCheckboxSize_ = true;

	fixedCheckboxHeight_ = UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htCheckBoxHeight );
}

CheckBoxControl::~CheckBoxControl()
{

}

double CheckBoxControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
}

double CheckBoxControl::getPreferredWidth()
{
	return 100;
}

void CheckBoxControl::paint( GraphicsContext* context )
{
	ToggledButton::paint( context );

	Rect r( 0.0, 0.0, getWidth(), getHeight() );

	Rect checkBtnRect = r;
	if ( true == useFixedCheckboxSize_ ) {
		checkBtnRect.top_ = maxVal<double>( 0, r.top_ + (r.getHeight() / 2.0 - fixedCheckboxHeight_/2.0));
		checkBtnRect.bottom_ = minVal<double>( r.bottom_, checkBtnRect.top_ + fixedCheckboxHeight_ );
	}
	
	ButtonState buttonState;
	buttonState.setActive( isActive() );
	buttonState.setEnabled( isEnabled() );
	//buttonState.setPressed( checked_ );
	buttonState.setToggled( checked_ );
	buttonState.setFocused( isFocused() && buttonState.isActive() );

	if ( getUseLocaleStrings() ) {
		buttonState.buttonCaption_ = System::getCurrentThreadLocale()->translate( caption_ );
	}
	else {
		buttonState.buttonCaption_ = caption_;
	}

	
	context->drawThemeCheckboxRect( &checkBtnRect, buttonState );
}


void CheckBoxControl::setFixedCheckboxHeight( const double& fixedCheckboxHeight )
{
	fixedCheckboxHeight_ = minVal<double>( fixedCheckboxHeight, getHeight() );
	repaint();
}

void CheckBoxControl::setUseFixedCheckboxSize( const bool& fixedCheckboxSize )
{
	useFixedCheckboxSize_ = fixedCheckboxSize;
	repaint();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2.2.2  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.13  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.2.1  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.12  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.11.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.11  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:12:59  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.2.3  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.2.1  2002/12/27 23:04:58  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.8.4.1  2002/09/28 02:37:38  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.8  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.6.2  2002/08/02 23:15:27  ddiego
*touch up to blackbox and adding form support back in
*
*Revision 1.7.6.1  2002/08/01 19:16:26  ddiego
*added support for create new files from the File | New... menu
*this displays a list of file templates which are read from the Object
*Repository. The FilePath had a bug with the FilePath::isRelative() function
*fixed a display bug with the CheckBoxControl and the fixed size of hte
*of the check box being too small
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


