//Dialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DialogPeer.h"
#include "vcf/ApplicationKit/WindowPeer.h"

using namespace VCF;

void Dialog_postClose( Event* e )
{
	e->getSource()->free();
}

void Dialog_onClose( WindowEvent* e )
{
	Dialog* dialog = (Dialog*)e->getSource();
	if ( !dialog->isModal() ) {
		EventHandler* ev = new StaticEventHandlerInstance<Event>( &Dialog_postClose, e->getSource() );
		UIToolkit::postEvent( ev, new Event( e->getSource() ) );
	}
}

Dialog::Dialog( Control* owner )
{
	owner_ = owner;

	modal_ = false;

	previousFocusedControl_ = Control::currentFocusedControl;

	returnValue_ = UIToolkit::mrNone;

	Frame* activeFrame = Frame::getActiveFrame();


	Application* app = Application::getRunningInstance();
	if ( NULL == owner_ ) {
		if ( NULL != activeFrame ) {
			owner_ = activeFrame;
		}
		else if ( NULL != app ) {
			owner_ = app->getMainWindow();
		}
	}

	dialogPeer_ = UIToolkit::createDialogPeer( owner_, this );

	peer_ = dynamic_cast<ControlPeer*>(dialogPeer_);


	windowPeer_ = dynamic_cast<WindowPeer*>(dialogPeer_);

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );

	peer_->setControl( this );

	setFrameStyle( fstFixed );

	//add a close handler to get notified of the closing window
	FrameClose.addHandler( new StaticEventHandlerInstance<WindowEvent>( &Dialog_onClose, this, "Dialog_onClose" ) );
}


Dialog::~Dialog()
{

}

void Dialog::paint(GraphicsContext * context)
{
	Frame::paint( context );
}

void Dialog::setCaption( const String& caption )
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}	

	caption_ = caption;

	String text = caption_;
	
	if ( getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( text );
	}

	peer_->setText( text );
}

Rect Dialog::getClientBounds(const bool& includeBorder)
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	return windowPeer_->getClientBounds();
}

void  Dialog::setClientBounds( Rect* bounds )
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->setClientBounds( bounds );
}

/*
void Dialog::resizeChildren()
{
	Rect* bounds = getClientBounds();
	Rect rect( 0.0, 0.0, bounds->getWidth(), bounds->getHeight() );

	resizeChildrenUsingBounds( &rect );
}
*/

class ControlHolder : public ObjectWithEvents {
public:
	ControlHolder(): control_(NULL) {

	}

	ControlHolder( Control* control ): control_(control) {
		updateEventHandler();
	}

	ControlHolder( const ControlHolder& rhs ) {
		*this = rhs;
	}

	virtual ~ControlHolder() {
		if ( NULL != control_ ) {
			EventHandler* ev = getEventHandler( "onDestroy" );
			if ( NULL != ev ) {
				control_->ComponentDeleted -= ev;
			}
		}
	}

	ControlHolder& operator=( const ControlHolder& rhs ) {
		control_ = rhs.control_;
		updateEventHandler();
		return *this;
	}

	ControlHolder& operator=( Control* rhs ) {
		control_ = rhs;
		updateEventHandler();
		return *this;
	}

	operator Control* () {
		return control_;
	}

	void onDestroy( VCF::ComponentEvent* e ) {
		control_ = NULL;
	}

	Control* operator ->() {
		return control_;
	}
protected:
	void updateEventHandler() {
		if ( NULL != control_ ) {
			EventHandler* ev = getEventHandler( "onDestroy" );
			if ( NULL == ev ) {
				ev = new ComponentEventHandler<ControlHolder>(this, &ControlHolder::onDestroy, "onDestroy" );
			}
			control_->ComponentDeleted += ev;
		}
	}
	Control* control_;
};

UIToolkit::ModalReturnType Dialog::showModal()
{
	modal_ = true;

	UIToolkit::ModalReturnType result = UIToolkit::mrNone;

	ControlHolder prevFocusedControl = previousFocusedControl_;

	Control* owningControl = owner_;

	if ( NULL != owner_ ) {

		owningControl->setEnabled( false );
	}

	show();
	result = UIToolkit::runModalEventLoopFor( this );
	if ( result == UIToolkit::mrTrue ) {
		result = getModalReturnValue();
	}

	if ( prevFocusedControl != NULL ) {
		prevFocusedControl->setFocused();
	}
	else if ( NULL != Control::getCurrentFocusedControl() ) {
		Control::getCurrentFocusedControl()->setFocused();
	}

	//kill off the internal contained compoennts and controls
	destroy();

	previousFocusedControl_ = prevFocusedControl;

	return result;
}

void Dialog::show()
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	if ( NULL != owner_ ) {
		Rect bounds;

		bounds.left_ = owner_->getLeft() + ( owner_->getWidth()/2.0 - getWidth()/2.0 );
		bounds.top_ = owner_->getTop() + ( owner_->getHeight()/2.0 - getHeight()/2.0 );
		bounds.right_ = bounds.left_ + getWidth();
		bounds.bottom_ = bounds.top_ + getHeight();
		if ( NULL != owner_->getParent() ) {
			owner_->translateToScreenCoords( &bounds );
		}

		setBounds( &bounds );
	}

	peer_->setVisible(true);
}


void Dialog::showMessage( const String& message, const String& caption )
{
	DialogPeer* dialogPeer = UIToolkit::createDialogPeer();// owner, this );
	if ( NULL != dialogPeer ){
		String captionText = caption;
			
		captionText = System::getCurrentThreadLocale()->translate( captionText );

		String realCaption = captionText;

		if ( realCaption.empty() ) {
			Application* app = Application::getRunningInstance();
			if ( NULL != app ) {
				realCaption = app->getName();
			}
		}
		
		String msgText = message;
			
		msgText = System::getCurrentThreadLocale()->translate( msgText );

		dialogPeer->showMessage( msgText, captionText );
	}

	delete dialogPeer;
	dialogPeer = NULL;
}

UIToolkit::ModalReturnType Dialog::showMessage( const String& message, const String& caption,
														const long& messageButtons,
														const MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrOK;

	DialogPeer* dialogPeer = UIToolkit::createDialogPeer();// owner, this );
	if ( NULL != dialogPeer ){
		String captionText = caption;			
		captionText = System::getCurrentThreadLocale()->translate( captionText );

		String msgText = message;			
		msgText = System::getCurrentThreadLocale()->translate( msgText );

		result = dialogPeer->showMessage( msgText, captionText, messageButtons, messageStyle );
	}

	delete dialogPeer;
	dialogPeer = NULL;

	return result;
}

void Dialog::close()
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	windowPeer_->close();
}

void Dialog::setFrameStyle( const FrameStyleType& frameStyle )
{
		if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	frameStyle_ = frameStyle;

	if ( !(Component::csDesigning & getComponentState()) ){
		windowPeer_->setFrameStyle( frameStyle_ );
	}

}

void Dialog::setIconImage( Image* icon )
{
	windowPeer_->setIconImage( icon );
}

Image* Dialog::getIconImage()
{
	return NULL;
}

void Dialog::keyDown( KeyboardEvent* e )
{
	if ( vkEscape == e->getVirtualCode() ) {
		e->setConsumed(true);
		close();
	}
}

bool Dialog::isActiveFrame()
{
	return windowPeer_->isActiveWindow();
}


/*
void Dialog::onModalClose( WindowEvent* e )
{
	Application::getRunningInstance()->getMainWindow()->setEnabled( true );
}
*/


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/09 18:48:04  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.27  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.26  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.25.2.1  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.25  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.24.2.6  2003/09/08 05:23:21  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.24.2.5  2003/09/06 19:45:15  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.24.2.4  2003/08/28 21:46:56  ddiego
*added escape reponse...
*
*Revision 1.24.2.3  2003/08/26 21:41:17  ddiego
*miscellanesous stuff, minor bugs
*
*Revision 1.24.2.2  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.24.2.1  2003/08/17 21:48:22  ddiego
*fixed bug [ 788189 ] ComboBoxControl doesn't close when application loose
*focus. Also cleaned some old trace statements for debugging purposes.
*
*Revision 1.24  2003/08/09 02:56:45  ddiego
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
*Revision 1.23.2.7  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.23.2.6  2003/06/27 03:10:59  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.23.2.5  2003/06/13 03:06:40  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.23.2.4  2003/06/13 00:03:19  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.23.2.3  2003/06/09 03:57:16  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.23.2.2  2003/06/05 03:48:55  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.23.2.1  2003/05/27 04:45:39  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.23  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.3  2003/04/17 04:29:52  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.22.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:13:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.2.4  2003/02/03 05:22:54  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.21.2.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.21.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21.2.1  2002/12/27 23:05:01  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.21  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.20.10.1  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.20  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.19.4.2  2002/04/27 15:52:47  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.19.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.19  2002/01/30 22:12:48  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.18  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


