//X11Window.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Window.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"

#include <X11/Xatom.h>
#include <X11/Xmd.h>

using namespace VCF;

X11Window::X11Window( Control* control, Control* owner ):
	wmProtocols_(0)
{

	control_ = control;

	X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
	X11UIToolkit* toolkit = (X11UIToolkit*)UIToolkit::getDefaultUIToolkit();

	Display* display = grafToolkit->getX11Display();

	wmProtocols_ = XInternAtom( display, "WM_PROTOCOLS", False );

	XSetWindowAttributes attrs;
	memset( &attrs, 0, sizeof(XSetWindowAttributes) );
	attrs.background_pixmap = None;
	attrs.background_pixel = 0;
	attrs.border_pixmap = CopyFromParent;
	attrs.border_pixel = 0;
	attrs.bit_gravity = ForgetGravity;
	attrs.win_gravity = NorthWestGravity;
	attrs.backing_store = NotUseful;
	attrs.colormap = CopyFromParent;
	attrs.backing_planes = 0xffffffff;
	attrs.cursor = None;

	attrs.override_redirect = False;

	wndHandle_ = XCreateWindow( display,
										DefaultRootWindow( display ),
										0, 0, 1, 1, 0,
										CopyFromParent,
										InputOutput,
										CopyFromParent,
										0,
										&attrs );


	if ( NULL != wndHandle_ ) {
		int eventMask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;
		eventMask |= FocusChangeMask | PropertyChangeMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask;
		eventMask |= PointerMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask;
		eventMask |= VisibilityChangeMask;// | SubstructureNotifyMask;

		Atom deleteWndMsgAtom = toolkit->getDeleteWindowMsg();
		XSetWMProtocols( display, wndHandle_, &deleteWndMsgAtom, 1);

		registerX11Control( this );
		//this may not be the right place ???

		XSelectInput( display, wndHandle_, eventMask );

		control_->getContext()->getPeer()->setContextID( (ulong32)wndHandle_ );

		toolkit->postToolkitMessage( toolkit->getVCFCreateWindowMsg(), (void*)control_ );
	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("XCreateWindow returned a NULL window ID in creating the peer wind") );
	}

}

X11Window::~X11Window()
{

}

Rect* X11Window::getClientBounds()
{
	clientBounds_ = *getBounds();
	return &clientBounds_;
}

void  X11Window::setClientBounds( Rect* bounds )
{
	setBounds( bounds );
	clientBounds_ = *bounds;
}

void X11Window::close()
{

	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>(UIToolkit::getDefaultUIToolkit());
	X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());

	XEvent closeEvent;
	closeEvent.type = ClientMessage;
	closeEvent.xclient.message_type = wmProtocols_;
	closeEvent.xclient.window = wndHandle_;
	closeEvent.xclient.send_event = 0;
	closeEvent.xclient.display = 0;
	closeEvent.xclient.format = 8;
	memset( &closeEvent.xclient.data.b[0], 0, 20*sizeof(char) );

	closeEvent.xclient.data.l[0] = toolkit->getDeleteWindowMsg();

	XSendEvent( grafToolkit->getX11Display(), wndHandle_, False, 0, &closeEvent );
}

void X11Window::setFrameStyle( const FrameStyleType& frameStyle )
{

}

void X11Window::setFrameTopmost( const bool& isTopmost )
{
	if ( true == isTopmost ) {
		XSizeHints size_hints;
		size_hints.flags = PSize | PPosition | PWinGravity;
		size_hints.x = bounds_.left_;
		size_hints.y = bounds_.top_;
		size_hints.width = bounds_.getWidth();
		size_hints.height = bounds_.getHeight();
		size_hints.win_gravity = NorthWestGravity;

		X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
		Display* display = grafToolkit->getX11Display();

		XSetWMNormalHints( display, wndHandle_, &size_hints);

		xLib::Window xroot = DefaultRootWindow( display );
        XSetTransientForHint( display, wndHandle_, xroot );
	}

}

bool X11Window::isMaximized()
{
	return false;
}

void X11Window::setMaximized( const bool maximised )
{

}

bool X11Window::isMinimized()
{
	return false;
}

void X11Window::setMinimized( const bool& minimized )
{

}

void X11Window::restore()
{

}

void X11Window::setIconImage( Image* icon )
{

}

void X11Window::handleEvent( XEvent* x11Event )
{
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>(UIToolkit::getDefaultUIToolkit());
	switch( x11Event->type ) {
		case ClientMessage : {
			if ( x11Event->xclient.message_type == wmProtocols_ ) {
				Atom atom = x11Event->xclient.data.l[0];
				if ( atom == toolkit->getDeleteWindowMsg() ) {
					printf( "Delete window requested!\n" );

					VCF::Window* window = reinterpret_cast<VCF::Window*>( getControl() );

					if ( window->allowClose() ) {

						VCF::WindowEvent event( getControl(), WINDOW_EVENT_CLOSE );

						window->fireOnFrameClose( &event );

						//check if the main window is clossing - if it is
						//then close the app !

						Application* app = Application::getRunningInstance();
						if ( NULL != app ){
							Window* mainWindow = app->getMainWindow();
							if ( mainWindow == window ){
								//quit
								toolkit->postQuitMessage(0);
							}
						}

						X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());

					}
				}
			}
			else {
				AbstractX11Control::handleEvent( x11Event );
			}
		}
		break;

		default : {
			AbstractX11Control::handleEvent( x11Event );
		}
		break;
	}
}


String X11Window::getText()
{
	return text_;
}

/**
 * sets the text for the widget
 */
void X11Window::setText( const String& text )
{
	if ( text == text_ ) {
		return;
	}

	text_ = text;
	XTextProperty textProperty;
	const char* textPtr = text_.c_str();
    const char **textData = &textPtr;
	if ( !XStringListToTextProperty((char**)textData, 1, &textProperty ) ) {
		//throw exception
	}
	else {
		X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
        XSetWMName( grafToolkit->getX11Display(), wndHandle_, &textProperty );
		XSetWMIconName( grafToolkit->getX11Display(), wndHandle_, &textProperty );
        XFree(textProperty.value);
    }
}


/**
$Id$
*/
