//AbstractX11Control.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/AbstractX11Control.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"




using namespace VCF;

std::map<xLib::Window,AbstractX11Control*> AbstractX11Control::xwndControlMap;


AbstractX11Control::AbstractX11Control():
	wndHandle_(0),
	control_(NULL),
	parent_(NULL),
	currentButtonState_(0),
	currentKeyState_(0),
	enabled_(true)
{

}

AbstractX11Control::~AbstractX11Control()
{
	if ( NULL != wndHandle_ ) {
		AbstractX11Control::unRegisterX11Control( this );

		X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		XDestroyWindow( grafToolkit->getX11Display(), wndHandle_ );
	}
}

void AbstractX11Control::registerX11Control( AbstractX11Control* x11Control )
{
	AbstractX11Control::xwndControlMap[x11Control->wndHandle_] = x11Control;
}

void AbstractX11Control::unRegisterX11Control( AbstractX11Control* x11Control )
{
	XwndControlMap::iterator found = AbstractX11Control::xwndControlMap.find( x11Control->wndHandle_ );
	if ( found != AbstractX11Control::xwndControlMap.end() ) {
		AbstractX11Control::xwndControlMap.erase( found );
	}

	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );

	toolkit->removeControlFromPaintEventQueue( x11Control );
}

AbstractX11Control* AbstractX11Control::getX11ControlFromXWindow( xLib::Window wndHandle )
{
	AbstractX11Control* result = NULL;

	XwndControlMap::iterator found = AbstractX11Control::xwndControlMap.find( wndHandle );
	if ( found != AbstractX11Control::xwndControlMap.end() ) {
		result = found->second;
	}

	return result;
}

/**
 * returns a text associated with the component. This usually gets used in the Control::getCaption() method.
 */
String AbstractX11Control::getText()
{
	String result;
	return result;
}

/**
 * sets the text for the widget
 */
void AbstractX11Control::setText( const String& text )
{

}

/**
 * sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
 */
void AbstractX11Control::setBounds( Rect* rect )
{
	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

	bounds_ = *rect;
	int l = (long)bounds_.left_;
	int t = (long)bounds_.top_;
	int w = (long)maxVal<double>(bounds_.getWidth(), 1.0 );
	int h = (long)maxVal<double>(bounds_.getHeight(), 1.0 );

	XMoveResizeWindow( grafToolkit->getX11Display(), wndHandle_, l, t, w, h );

}

/**
*advanced function for changing the size of multiple child windows
*/
bool AbstractX11Control::beginSetBounds( const ulong32& numberOfChildren )
{
	//X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	//XSync( grafToolkit->getX11Display(), False );
	return true;
}

void AbstractX11Control::endSetBounds()
{

}

/**
 * returns the bounds of the component in the coordinate system of the parent.
 */
Rect* AbstractX11Control::getBounds()
{
	/*
	xLib::Window rootWnd = 0;

	int x = 0;
	int y = 0;

	unsigned int width = 0;
	unsigned int  height = 0;

	unsigned int borderWidth = 0;
	unsigned int depth = 0;
	if ( NULL == wndHandle_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("wndHandle_ is NULL!!!") );
	}

	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();



	XGetGeometry( grafToolkit->getX11Display(), wndHandle_, &rootWnd, &x, &y, &width, &height, &borderWidth, &depth );


	bounds_.left_ = x;
	bounds_.top_ = y;
	bounds_.right_ = bounds_.left_ + (double)width;
	bounds_.bottom_ = bounds_.top_ + (double)height;
	*/
	return &bounds_;
}

/**
 * shows or hides the component.
 * This does NOT close the component (if invoked on a frame based component ).
 */
void AbstractX11Control::setVisible( const bool& visible )
{
	if ( visible != visible_ ) {
		X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
		if ( true == visible ) {
			XMapWindow( grafToolkit->getX11Display(), wndHandle_ );
		}
		else {
			XUnmapWindow( grafToolkit->getX11Display(), wndHandle_ );
		}
	}
	visible_ = visible;
}

/**
 * returns wether or not the component is currently visible.
 */
bool AbstractX11Control::getVisible()
{
	return visible_;
}

/**
 * returns a bit-masked unsigned long that contains style constants.
 *  These style constants are defined in the VCF, and must
 * be translated to the particular windowing system being used.
 */
unsigned long AbstractX11Control::getStyleMask()
{
	return 0;
}

/**
 * sets the current style mask.
 *  Should cause a repaint of the component, if neccessary.
 */
void AbstractX11Control::setStyleMask( const unsigned long& styleMask )
{

}

/**
 * returns the component that this Peer is attached to.
 */
Control* AbstractX11Control::getControl()
{
	return control_;
}

/**
 * attahces the Peer to a particular component. This should only be done once.
 */
void AbstractX11Control::setControl( Control* component )
{
	control_ = component;
}

void AbstractX11Control::setCursor( Cursor* cursor )
{
	if ( NULL != cursor ) {
		X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
		if ( Cursor::SCT_DEFAULT == cursor->getCursorID() ) {
			XUndefineCursor( grafToolkit->getX11Display(), wndHandle_ );
		}
		else {
			XDefineCursor( grafToolkit->getX11Display(), wndHandle_, (xLib::Cursor)cursor->getPeer()->getCursorHandleID() );
		}
	}
}

void AbstractX11Control::setParent( Control* parent )
{
	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	if ( NULL == parent ) {
		parent_ = NULL;

		XReparentWindow( grafToolkit->getX11Display(), wndHandle_, NULL,
						(long)bounds_.left_, (long)bounds_.top_ );
	}
	else {
		parent_ = dynamic_cast<AbstractX11Control*>( parent->getPeer() );
		if ( NULL == parent_ ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2("Invalid peer type being used as a parent") );
		}

		XReparentWindow( grafToolkit->getX11Display(), wndHandle_, parent_->wndHandle_,
						(long)bounds_.left_, (long)bounds_.top_ );
	}


}

Control* AbstractX11Control::getParent()
{
	Control* result = NULL;

	if ( NULL != parent_ ) {
		result = parent_->getControl();
	}

	return result;
}

bool AbstractX11Control::isFocused()
{
	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	xLib::Window focusWnd = 0;
	int revert = 0;

	XGetInputFocus( grafToolkit->getX11Display(), &focusWnd, &revert );

	return focusWnd == wndHandle_;
}

void AbstractX11Control::setFocus( const bool& focused )
{
	if ( focused ) {
		if ( !isFocused() ) {
			try {
				X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
				//XSetInputFocus( grafToolkit->getX11Display(), wndHandle_, RevertToNone, CurrentTime );
			}
			catch ( BasicException& ) {
				printf( "can't set focus\n" );
			}
		}
		//printf( "XSetInputFocus( %p, %p, %d, %d )\n",
			//		grafToolkit->getX11Display(), wndHandle_, RevertToNone, CurrentTime );

		//this is not working at the momement
	}
	else {

	}
}

bool AbstractX11Control::isEnabled()
{
	return enabled_;
}

void AbstractX11Control::setEnabled( const bool& enabled )
{
	if ( enabled == enabled_ ) {
			return;
	}
	enabled_ = enabled;
	Container* container = control_->getContainer();
	if ( NULL != container ) {
		Enumerator<Control*>* children = container->getChildren();
		while ( children->hasMoreElements() ) {
			Control* child = children->nextElement();
			child->setEnabled( enabled_ );
		}
	}
	repaint();
}

void AbstractX11Control::setFont( Font* font )
{

}

void AbstractX11Control::repaint( Rect* repaintRect )
{
	Rect * bounds = NULL;
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );
	if ( NULL == repaintRect ) {
		toolkit->repaintControl( this, bounds_ );
	}
	else {
		toolkit->repaintControl( this, *repaintRect );
	}
}

/**
*this keeps the mouse events being sent to this control, even is the
*mouse leaves the physical bounds of the control
*/
void AbstractX11Control::keepMouseEvents()
{
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );
	toolkit->xGrabPointer( this );
}

/**
*releases mouse events - goes back to normal event handling
*/

void AbstractX11Control::releaseMouseEvents()
{
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );
	toolkit->xUnGrabPointer( this );
}

void AbstractX11Control::handleXEvent( xLib::Window wndHandle, XEvent* x11Event )
{
	AbstractX11Control* target = AbstractX11Control::getX11ControlFromXWindow( wndHandle );
	if ( NULL != target ) {
		target->handleEvent( x11Event );
	}
}

void AbstractX11Control::handleEvent( XEvent* x11Event )
{

	X11EventMsg eventMsg(x11Event, control_ );
	Event* event = UIToolkit::getDefaultUIToolkit()->createEventFromNativeOSEventData( &eventMsg );

	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );

	bool eventHandled = false;

	switch ( x11Event->type ) {
		case KeyPress :  {
			if ( true == enabled_ ) {
				currentKeyState_ = x11Event->xkey.state;
				if ( NULL != event ) {
					KeyboardEvent* srcEvent = (KeyboardEvent*)event;
					KeyboardEvent keyPressEvent( srcEvent->getSource(),
												Control::KEYBOARD_PRESSED,
												1,
												srcEvent->getKeyMask(),
												srcEvent->getKeyValue(),
												srcEvent->getVirtualCode() );

					//note - we may need to send then AFTER the KeyPress original event (a Control::KEYBOARD_DOWN
					//event)
					control_->handleEvent( &keyPressEvent );
				}
			}
			else {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case KeyRelease : {
			currentKeyState_ = x11Event->xkey.state;
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case ButtonPress : {
			currentKeyState_ = x11Event->xbutton.state;
			currentButtonState_ = x11Event->xbutton.button;
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case ButtonRelease : {
			currentKeyState_ = x11Event->xbutton.state;
			currentButtonState_ = x11Event->xbutton.button;
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case MotionNotify : {
			currentKeyState_ = x11Event->xmotion.state;
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;


		case EnterNotify : case LeaveNotify :  {
			MouseEvent* mouseEvent = reinterpret_cast<MouseEvent*>( event );
			MouseEvent* newEvent = new MouseEvent( event->getSource(), event->getType(),
													toolkit->translateButtonMask( currentButtonState_ ),
													toolkit->translateKeyMask( currentKeyState_ ),
													mouseEvent->getPoint() );

			delete event;
			event = newEvent;
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case FocusIn : {
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case FocusOut : {
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
		}
		break;

		case NoExpose : {

		}
		break;

		/*
		case VisibiltyNotify : {
			printf( "event VisibiltyNotify...\n" );
		}control_->handleEvent( event );
		break;
		*/


		case CreateNotify : {

		}
		break;


		case DestroyNotify : {
			control_->handleEvent( event );

			AbstractX11Control::unRegisterX11Control( this );
			//printf( "Destroy of %p in progress, notified Control: %s @ %p, and removed from event map...\n",
				//	this, typeid(*control_).name(), control_  );
			eventHandled = true;
			wndHandle_ = NULL;
		}
		break;


		case UnmapNotify : {

		}
		break;

		case MapNotify : {

		}
		break;

		case MapRequest : {

		}
		break;

		case ReparentNotify : {

		}
		break;

		case ConfigureNotify : {
			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
			else {
				int x = (int)bounds_.left_;
				int y = (int)bounds_.top_;
				int w = (int)bounds_.getWidth();
				int h = (int)bounds_.getHeight();

				bounds_.left_ = x11Event->xconfigure.x;
				bounds_.top_ = x11Event->xconfigure.y;
				bounds_.right_ = bounds_.left_ + (double)x11Event->xconfigure.width;
				bounds_.bottom_ = bounds_.top_ + (double)x11Event->xconfigure.height;

			/*
			printf( "ConfigureNotify: %p, %s\n\tx: %d, y: %d, w: %d, h: %d\n",
					wndHandle_, typeid(*control_).name(),
					x11Event->xconfigure.x , x11Event->xconfigure.y,x11Event->xconfigure.width, x11Event->xconfigure.height);
			printf( "\tbounds: %d, %d, %d, %d\n", x,y,w,h );
			*/

			//if ( (x != x11Event->xconfigure.x) || (y != x11Event->xconfigure.y) ) {
				VCF::Point pt( x11Event->xconfigure.x , x11Event->xconfigure.y );

				ControlEvent moveEvent( control_, pt );
				control_->handleEvent( &moveEvent );
				eventHandled = true;
			//}

			//if ( (w != x11Event->xconfigure.width) || (h != x11Event->xconfigure.height) ) {
				VCF::Size sz( x11Event->xconfigure.width, x11Event->xconfigure.height );

				ControlEvent sizeEvent( control_, sz );
				control_->handleEvent( &sizeEvent );
				eventHandled = true;
			//}
			}
		}
		break;

		case GravityNotify : {

		}
		break;

		case ResizeRequest : {

		}
		break;

		case ConfigureRequest : {

		}
		break;

		case CirculateNotify : {

		}
		break;

		case CirculateRequest : {

		}
		break;

		case PropertyNotify : {

		}
		break;

		case SelectionClear : {

		}
		break;


		case SelectionRequest : {

		}
		break;

		case SelectionNotify : {

		}
		break;

		case ColormapNotify : {

		}
		break;

		case ClientMessage : {
			X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );

			if ( false == enabled_ ) {
				//skip the event handling
				eventHandled = true;
			}
			else {

			}
		}
		break;

		case MappingNotify : {

		}
		break;

		case KeymapNotify : {

		}
		break;
	}

	if ( (!eventHandled) && (NULL != event) ) {
		control_->handleEvent( event );
	}

	if ( NULL != event ) {
		delete event;
		event = NULL;
	}
}

void AbstractX11Control::handlePaintEvent()
{
	GraphicsContext* gc = control_->getContext();
	if ( updateRects_.empty() ) {
		return;
	}

	std::vector<Rect>::iterator it = updateRects_.begin();

	Rect clipBounds = updateRects_.front();

	while ( it != updateRects_.end() ) {
		Rect& r = *it;

		clipBounds.left_ = minVal<double>( clipBounds.left_, r.left_ );
		clipBounds.top_ = minVal<double>( clipBounds.top_, r.top_ );

		clipBounds.right_ = maxVal<double>( clipBounds.right_, r.right_ );
		clipBounds.bottom_ = maxVal<double>( clipBounds.bottom_, r.bottom_ );

		it ++;
	}

	clipBounds.normalize();
	if ( (clipBounds.getHeight() <= 0.0) || (clipBounds.getWidth() <= 0.0) ) {
		return;
	}

	//printf( "%s clipBounds: %s\n", typeid(*control_).name(), clipBounds.toString().c_str() );

	//GraphicsContext gc2(clipBounds.getWidth(), clipBounds.getHeight() );

	//gc2.setOrigin( -clipBounds.left_, -clipBounds.top_ );
	//gc->setClippingRect( &clipBounds );

	gc->getPeer()->setContextID(wndHandle_);

	control_->paint( gc );

	//gc->setClippingRect( &Rect(0,0,0,0) );

	//gc2.setOrigin( 0, 0 );

	//gc->copyContext( clipBounds.left_, clipBounds.top_, &gc2 );

	updateRects_.clear();
}

void AbstractX11Control::addUpdateRect( const Rect& updateRect )
{
	updateRects_.push_back( updateRect );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.4.2  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.3.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.3  2003/05/17 20:37:31  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.15  2003/02/03 05:22:54  ddiego
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
*Revision 1.1.2.14  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.1.2.13  2003/01/27 05:04:02  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Revision 1.1.2.12  2003/01/19 20:18:21  ddiego
*changes to try and optimize painting. didn't work for this go around :(
*
*Revision 1.1.2.11  2003/01/19 03:11:59  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.1.2.10  2003/01/16 04:46:53  ddiego
*added support for default X11 cursors
*added support for translating coordinates from screen to client
*and client to screen, where  the screen is the RootWindow
*
*Revision 1.1.2.9  2003/01/13 04:57:03  ddiego
*added a fix for the X11COntext::gettextWidth and Height, now returns correct values
*static makefile for the various kits is now ready to use for all
*AbstractX11Controll::keepMouseEvents is now working correctly
*
*Revision 1.1.2.8  2003/01/11 23:17:25  ddiego
*added extra functionality to the static makefile in vcf/build/make
*added some bug fixes to X11
*
*Revision 1.1.2.7  2003/01/08 03:49:18  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.1.2.6  2003/01/04 06:12:24  ddiego
*fixed a crash in X11GraphicsToolkit - an error in how colors were being freed
*added support for titles, getting the focus control, and grabbing the mouse !
*
*Revision 1.1.2.5  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.1.2.4  2003/01/02 04:07:46  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.1.2.3  2003/01/01 05:06:29  ddiego
*changes start propagating VCF::Event instances back into the main Control
*event loop from native X11 events.
*
*Revision 1.1.2.2  2002/12/31 07:02:19  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.1.2.1  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
Auto generated C++ implementation for class AbstractX11Control
*/


