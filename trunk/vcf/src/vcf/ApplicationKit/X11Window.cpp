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
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:59  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:41  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:12:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.12  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.1.2.11  2003/01/27 05:04:02  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Revision 1.1.2.10  2003/01/23 04:38:25  ddiego
*fixes to x port - issues with lightweight controls not quite drawing right. - a
*bug in the line drawing code when the origin is not 0,0
*
*Revision 1.1.2.9  2003/01/19 20:18:21  ddiego
*changes to try and optimize painting. didn't work for this go around :(
*
*Revision 1.1.2.8  2003/01/16 04:46:53  ddiego
*added support for default X11 cursors
*added support for translating coordinates from screen to client
*and client to screen, where  the screen is the RootWindow
*
*Revision 1.1.2.7  2003/01/08 03:49:18  ddiego
*fixes to ensure that move and size events get sent properly. Not sure
*I am happy with how it is currently working. Fix to X11Cursor so that the cursorID
*has a valid initial value.
*
*Revision 1.1.2.6  2003/01/04 06:12:25  ddiego
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
*Revision 1.1.2.3  2003/01/01 05:06:30  ddiego
*changes start propagating VCF::Event instances back into the main Control
*event loop from native X11 events.
*
*Revision 1.1.2.2  2002/12/31 07:02:19  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.1.2.1  2002/12/30 03:59:26  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
Auto generated C++ implementation for class X11Window
*/


