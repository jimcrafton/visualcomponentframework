//RadioButtonControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/RadioButtonControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


RadioButtonControl::RadioButtonControl()
{
	setVisible( true );

	useFixedRadioButtonSize_ = true;

	groupID_ = 0;

	fixedRadioButtonHeight_ = UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htRadioBoxHeight );
}

RadioButtonControl::~RadioButtonControl()
{

}

double RadioButtonControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
}

double RadioButtonControl::getPreferredWidth()
{
	return 100;
}

void RadioButtonControl::paint( GraphicsContext* context )
{
	ToggledButton::paint( context );

	Rect r( 0.0, 0.0, getWidth(), getHeight() );

	Rect radioBtnRect = r;

	if ( true == useFixedRadioButtonSize_ ) {

		radioBtnRect.top_ = maxVal<double>( 0.0, r.top_ + (r.getHeight() / 2.0 - fixedRadioButtonHeight_/2.0));

		radioBtnRect.bottom_ = minVal<double>( r.bottom_, radioBtnRect.top_ + fixedRadioButtonHeight_ );
	}
	else {
		radioBtnRect.inflate( -3.0, -3.0 );
	}

	//radioBtnRect.left_ += 3.0;

	//radioBtnRect.right_ = radioBtnRect.left_ + radioBtnRect.getHeight();

	//r.left_ = radioBtnRect.right_;

	ButtonState state;
	state.setActive( true );
	state.setEnabled( isEnabled() );
	state.setPressed( checked_ );
	state.setFocused( isFocused() );
	state.buttonCaption_ = caption_;
	if ( getUseLocaleStrings() ) {
		state.buttonCaption_ = System::getCurrentThreadLocale()->translate( caption_ );
	}	
	
	context->drawThemeRadioButtonRect( &radioBtnRect, state );
}


void RadioButtonControl::setFixedRadioButtonHeight( const double& fixedRadioButtonHeight )
{
	fixedRadioButtonHeight_ = minVal<>( fixedRadioButtonHeight, getHeight() );
	repaint();
}

void RadioButtonControl::setUseFixedRadioButtonSize( const bool& fixedRadioButtonSize )
{
	useFixedRadioButtonSize_ = fixedRadioButtonSize;
	repaint();
}

void RadioButtonControl::setGroupID( const long& groupID )
{
	groupID_ = groupID;
}

void RadioButtonControl::setChecked( const bool& checked )
{	
	Control* parent = getParent();
	if ( NULL != parent ) {
		Container* container = parent->getContainer();
		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();

			while ( (children->hasMoreElements()) ) {
				Control* child = children->nextElement();
				RadioButtonControl* radioControl = dynamic_cast<RadioButtonControl*>( child );
				if ( NULL != radioControl ) {
					if ( (radioControl != this) && (radioControl->getGroupID() == groupID_) ) {
						radioControl->internal_setChecked( false );
					}
				}
			}

			if ( checked ) {
				ToggledButton::setChecked( checked  );
			}		
		}
		else {
			//Ooh this is very bad !!
			throw BadComponentStateException();
		}
	}
	else {
		ToggledButton::setChecked( checked  );
	}
}

RadioButtonControl* RadioButtonControl::getSelectedRadioButtonFromGroup()
{
	RadioButtonControl* result = NULL;
	Container* parent = getParent()->getContainer();
	if ( NULL != parent ) {
		Enumerator<Control*>* children = parent->getChildren();
		while ( true == children->hasMoreElements() ) {
			Control* child = children->nextElement();
			RadioButtonControl* radioControl = dynamic_cast<RadioButtonControl*>( child );
			if ( NULL != radioControl ) {
				if ( (radioControl->getGroupID() == groupID_) && (true == radioControl->isChecked()) ) {
					result = radioControl;
					break;
				}
			}
		}
	}
	else {
		//Ooh this is very bad !!
		throw BadComponentStateException();
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/11 22:08:06  ddiego
*fixed an accidental checkin that resulted in scrolled
*drawing not showing up correctly
*
*Revision 1.1.2.4  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.2  2003/09/15 02:52:36  ddiego
*miscellaneous changes
*
*Revision 1.10.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.10  2003/08/09 02:56:45  ddiego
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
*Revision 1.9.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.9  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.8.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.2.1  2003/03/12 03:13:20  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.2.4  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7.2.3  2003/01/02 04:07:47  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.7.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.7.2.1  2002/12/27 23:05:08  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.7  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.6.4.1  2002/09/28 02:37:38  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.6  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.6.1  2002/08/02 23:15:27  ddiego
*touch up to blackbox and adding form support back in
*
*Revision 1.5  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.4  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


