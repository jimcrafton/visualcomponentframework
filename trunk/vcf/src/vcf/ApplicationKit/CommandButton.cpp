//CommandButton.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/ApplicationKit/ButtonPeer.h"
#include "vcf/ApplicationKit/Action.h"

using namespace VCF;




CommandButton::CommandButton()
{
	buttonPeer_ = UIToolkit::createButtonPeer( this );

	if ( NULL == buttonPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_ =
		dynamic_cast<ControlPeer*>( buttonPeer_ );

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}


	peer_->create( this );
	peer_->setControl( this );



	commandType_ = BC_NONE;

	isPressed_ = false;

	setVisible( true );

	FocusGained.addHandler( new FocusEventHandler<CommandButton>( this,
																&CommandButton::onFocusGained,
																"CommandButton::onFocusGained" ) );

	FocusLost.addHandler( new FocusEventHandler<CommandButton>( this,
																&CommandButton::onFocusLost,
																"CommandButton::onFocusLost" ) );
}

CommandButton::~CommandButton()
{
	UIToolkit::removeDefaultButton( this );
}

void CommandButton::setName( const String& name )
{
	Control::setName( name );
	if ( isDesigning() && getCaption().empty() ) {
		setCaption( name );
	}
}


void CommandButton::setCaption( const String& caption )
{
	VirtualKeyCode keyCode = UIToolkit::findMnemonic( caption );

	if ( keyCode != vkUndefined ) {
		AcceleratorKey* newAccelKey = new AcceleratorKey( this, keyCode, kmAlt, NULL, true );
		addAcceleratorKey( newAccelKey );
	}

	this->peer_->setText( caption );
}

String CommandButton::getCaption()
{
	String result = peer_->getText();
	if ( getUseLocaleStrings() ) {
		result = System::getCurrentThreadLocale()->translate( result );
	}

	return result;
}

void CommandButton::setCommandType( const ButtonCommandType& commandType )
{
	commandType_ = commandType;
}

ButtonCommandType CommandButton::getCommandType()
{
	return this->commandType_;
}

double CommandButton::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htButtonHeight );
}

void CommandButton::mnemonicActivate()
{
	Control::mnemonicActivate();
	click();
}

void CommandButton::click()
{
	ButtonEvent event( this, 0 );
	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ButtonClicked.fireEvent( &event );
	}

	if ( BC_NONE != getCommandType() ) {
		//try and find hte parent that is a Dialog
		Control* parent = getParent();
		Frame* frame = dynamic_cast<Frame*>( parent );
		while ( (NULL == frame) && (parent != NULL) ) {
			parent = parent->getParent();
			frame = dynamic_cast<Frame*>( parent );
		}

		if ( NULL != frame ) {
			Dialog* dialog = dynamic_cast<Dialog*>( frame );
			if ( NULL != dialog ) {
				switch ( getCommandType() ){
					case BC_OK : {
						dialog->setModalReturnValue( UIToolkit::mrOK );
					}
					break;

					case BC_CANCEL : {
						dialog->setModalReturnValue( UIToolkit::mrCancel );
					}
					break;

					case BC_YES : {
						dialog->setModalReturnValue( UIToolkit::mrYes );
					}
					break;

					case BC_NO : {
						dialog->setModalReturnValue( UIToolkit::mrNo );
					}
					break;

					case BC_ABORT : {
						dialog->setModalReturnValue( UIToolkit::mrAbort );
					}
					break;

					case BC_IGNORE : {
						dialog->setModalReturnValue( UIToolkit::mrIgnore );
					}
					break;
				}
			}
			frame->close();
		}
	}
}

void CommandButton::paint(GraphicsContext * context)
{

	Rect rect = getClientBounds( true );

	rect.setRect( 0, 0, rect.getWidth(), rect.getHeight() );

	ButtonState state = buttonPeer_->getState();
	state.setActive( isActive() );

	state.setDefaultButton( this == UIToolkit::getDefaultButton() );
	state.buttonCaption_ = getCaption();

	context->setCurrentFont( getFont() );
	context->drawThemeButtonRect( &rect, state );
	if ( state.isFocused() ) {
		context->drawThemeButtonFocusRect( &rect ); // MP-
	}
}

void CommandButton::setDefault( const bool& defaultButton )
{
	if ( true == defaultButton ) {
		UIToolkit::setDefaultButton( this );
	}
	else {
		UIToolkit::removeDefaultButton( this );
	}
}

bool CommandButton::isDefault()
{
	return (this == UIToolkit::getDefaultButton());
}

void CommandButton::onFocusGained( FocusEvent* event )
{
	UIToolkit::setDefaultButton( this );
}

void CommandButton::onFocusLost( FocusEvent* event )
{
	UIToolkit::removeDefaultButton( this );
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/07/04 03:43:14  marcelloptr
*PushButton, toggled, needs also an image for FocusDown. Management images improved and fully tested.
*
*Revision 1.3.2.3  2005/06/26 01:27:53  marcelloptr
*added images to a PushButton
*
*Revision 1.3.2.2  2005/02/27 01:45:33  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.3.2.1  2005/02/21 16:20:00  ddiego
*minor changes to various things, property editors, and tree list control.
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.1  2004/09/06 23:05:55  ddiego
*fixed border in button class
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.22  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.21.2.1  2004/03/19 04:18:43  ddiego
*added more code to condition example, fixed some
*minor stuff in the table control
*
*Revision 1.21  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.20.2.2  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.20.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.20  2003/08/09 02:56:44  ddiego
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
*Revision 1.19.2.2  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.19.2.1  2003/05/27 04:45:39  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.19  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.18.2.2  2003/04/17 04:29:52  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.18.2.1  2003/03/12 03:13:01  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.18  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.17.2.5  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.17.2.4  2003/01/08 00:19:58  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.17.2.3  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.17.2.2  2002/12/27 23:04:59  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.17.2.1  2002/12/25 22:06:34  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.17  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.16.10.1  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.16  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.2  2002/04/27 15:52:41  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.15.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.15  2002/01/30 22:12:48  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.14  2002/01/26 15:11:09  ddiego
*Default button now working
*
*Revision 1.13  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


