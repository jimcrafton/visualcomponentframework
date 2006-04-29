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
$Id$
*/
