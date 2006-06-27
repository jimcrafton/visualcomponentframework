//X11Dialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/PushButton.h"

#include "vcf/ApplicationKit/X11Dialog.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"

#include <X11/Xatom.h>
#include <X11/Xmd.h>


using namespace VCF;


class X11MessageBox : public Dialog {
public:

	void init( const String& message, const String& caption,
				const int32& messageButtons, const Dialog::MessageStyle& messageStyle ) {

		X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>(UIToolkit::getDefaultUIToolkit());

		setCaption( caption );

		Label* label = new Label();
		label->setCaption( message );

		const VCFChar* P = message.c_str();
		const VCFChar* start = P;
		const VCFChar* line = P;

		double maxWidth = 150.0;
		double height = 0.0;
		double x,y;
		x = y = 0.0;

		while ( (P-start) < message.size() ) {
			if ( (*P == '\n') || ((*P == '\r') && (*(P+1) == '\n')) ) {
				String text;
				text.append( line, P-line );

				height += getContext()->getTextHeight( text );
				maxWidth = maxVal<double>( maxWidth, getContext()->getTextWidth( text ) );

				line = P;
				line ++;
				if ( *P == '\r' ) {
					line ++;
					P++;
				}
			}
			P++;
		}

		if ( line < P ) {
			String text;
			text.append( line, P-line );
			height += getContext()->getTextHeight( text );
			maxWidth = maxVal<double>( maxWidth, getContext()->getTextWidth( text ) );
		}

		label->setBounds( 10, 10, maxWidth, height + label->getFont()->getHeight()/2.0 );

		add( label );

		maxWidth = label->getWidth() + toolkit->getUIMetricsManager()->getPreferredSpacingFor( UIMetricsManager::stContainerBorderDelta ) * 2;

		/*
		mbOK = 1,
		mbHelp = 2,
		mbYesNo = 4,
		mbYesNoCancel = 8,
		mbOKCancel = 16,
		mbRetryCancel = 32,
		mbAbortRetryIgnore = 64
		*/

		PushButton* button = new PushButton();


		int buttonCount = 1;

		if ( (Dialog::mbYesNo & messageButtons) || (Dialog::mbOKCancel & messageButtons) || (Dialog::mbRetryCancel & messageButtons) ) {
			buttonCount = 2;
		}
		else if ( (Dialog::mbAbortRetryIgnore & messageButtons) || (Dialog::mbYesNoCancel & messageButtons) ) {
			buttonCount = 3;
		}

		if ( (Dialog::mbHelp & messageButtons) ) {
			buttonCount ++;
		}

		double spacer = toolkit->getUIMetricsManager()->getPreferredSpacingFor( UIMetricsManager::stControlHorizontalSpacing );

		y = label->getTop() + label->getHeight() + toolkit->getUIMetricsManager()->getPreferredSpacingFor( UIMetricsManager::stContainerBorderDelta );

		double buttonWidth = button->getPreferredWidth();

		x = maxWidth - ( button->getPreferredWidth() + toolkit->getUIMetricsManager()->getPreferredSpacingFor( UIMetricsManager::stContainerBorderDelta ) );

		height = y;
		for ( int i=0;i<buttonCount;i++ ) {

			if ( i > 0 ) {
				button = new PushButton();
			}

			switch( i ) {
				case 0 : {
					if ( (Dialog::mbOK & messageButtons) || (Dialog::mbOKCancel & messageButtons) ) {
						button->setCommandType( BC_OK );
						button->setCaption( "OK" );
					}
					else if ( (Dialog::mbYesNo & messageButtons) || (Dialog::mbYesNoCancel & messageButtons) ) {
						button->setCommandType( BC_YES );
						button->setCaption( "Yes" );
					}
					else if ( Dialog::mbAbortRetryIgnore & messageButtons ){
						button->setCommandType( BC_ABORT );
						button->setCaption( "Abort" );
					}
					else if ( Dialog::mbRetryCancel & messageButtons ) {
						button->setCommandType( BC_RETRY );
						button->setCaption( "Retry" );
					}
					button->setDefault( true );
					button->setFocus( true );
				}
				break;

				case 1 : {
					if ( (Dialog::mbYesNo & messageButtons) || (Dialog::mbYesNoCancel & messageButtons) ) {
						button->setCommandType( BC_NO );
						button->setCaption( "No" );
					}
					else if ( (Dialog::mbOKCancel & messageButtons) || (Dialog::mbRetryCancel & messageButtons) ) {
						button->setCommandType( BC_CANCEL );
						button->setCaption( "Cancel" );
					}
					else if  ( Dialog::mbAbortRetryIgnore & messageButtons )  {
						button->setCommandType( BC_RETRY );
						button->setCaption( "Retry" );
					}
					else if ( Dialog::mbHelp & messageButtons )  {
						button->setCommandType( BC_HELP );
						button->setCaption( "Help" );
					}
				}
				break;

				case 2 : {
					if ( Dialog::mbAbortRetryIgnore & messageButtons ) {
						button->setCommandType( BC_IGNORE );
						button->setCaption( "Ignore" );
					}
					else if ( Dialog::mbYesNoCancel & messageButtons ) {
						button->setCommandType( BC_CANCEL );
						button->setCaption( "Cancel" );
					}
					else if ( Dialog::mbHelp & messageButtons )  {
						button->setCommandType( BC_HELP );
						button->setCaption( "Help" );
					}
				}
				break;

				case 3 : {
					if ( Dialog::mbHelp & messageButtons )  {
						button->setCommandType( BC_HELP );
						button->setCaption( "Help" );
					}
				}
				break;

			}

			button->setBounds( x, y, buttonWidth, button->getPreferredHeight() );
			add( button );

			x += buttonWidth + spacer;
		}

		maxWidth = maxVal<double>( x , maxWidth );

		height += button->getHeight() + toolkit->getUIMetricsManager()->getPreferredSpacingFor( UIMetricsManager::stContainerBorderDelta );

		setHeight( height );
		setWidth( maxWidth );
	}

};





X11Dialog::X11Dialog( Control* owner, Dialog* component ) :
	owner_(owner),
	runningModal_(false)
{
	control_ = component;

	X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>( UIToolkit::getDefaultUIToolkit() );

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

	attrs.override_redirect = true;

	int createWndAttrMask = 0;

	wndHandle_ = XCreateWindow( display,
										DefaultRootWindow( display ),
										0, 0, 1, 1, 0,
										CopyFromParent,
										InputOutput,
										CopyFromParent,
										createWndAttrMask,
										&attrs );


	if ( NULL != wndHandle_ ) {
		int eventMask = ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask;
		eventMask |= FocusChangeMask | PropertyChangeMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask;
		eventMask |= PointerMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask;
		eventMask |= VisibilityChangeMask;// | SubstructureNotifyMask;



		Atom deleteWndMsgAtom = toolkit->getDeleteWindowMsg();
		XSetWMProtocols( display, wndHandle_, &deleteWndMsgAtom, 1);

		xLib::Window mainWndHandle = NULL;

		Application* app = Application::getRunningInstance();
		if ( NULL != app ) {
			Window* mainWind = app->getMainWindow();

			mainWndHandle = (xLib::Window) mainWind->getPeer()->getHandleID();
		}

		if ( NULL != mainWndHandle ) {
			XSetTransientForHint( display, wndHandle_, mainWndHandle );
		}

		registerX11Control( this );
		//this may not be the right place ???

		XSelectInput( display, wndHandle_, eventMask );

		control_->getContext()->getPeer()->setContextID( (uint32)wndHandle_ );

		toolkit->postToolkitMessage( toolkit->getVCFCreateWindowMsg(), (void*)control_ );

	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("XCreateWindow returned a NULL window ID in creating the peer wind") );
	}
}

X11Dialog::X11Dialog():
	owner_(NULL),
	runningModal_(false)
{
	control_ = NULL;
}

X11Dialog::~X11Dialog()
{

}

Rect* X11Dialog::getClientBounds()
{
	return &clientBounds_;
}

void  X11Dialog::setClientBounds( Rect* bounds )
{
	setBounds( bounds );
	clientBounds_ = *bounds;
}

void X11Dialog::show()
{
	setVisible( true );
}

void X11Dialog::close()
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

void X11Dialog::setFrameStyle( const FrameStyleType& frameStyle )
{
	/*
	XSetWindowAttributes attrs;
	memset( &attrs, 0, sizeof(XSetWindowAttributes) );
	attrs.override_redirect = true;

	int createWndAttrMask = 0;
	createWndAttrMask |= CWOverrideRedirect;
	XChangeWindowAttributes( display, wndHandle_, createWndAttrMask, &attrs );
	*/
}

void X11Dialog::setIconImage( Image* icon )
{

}

void X11Dialog::setBounds( Rect* rect )
{
	X11GraphicsToolkit* grafToolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

	AbstractX11Control::setBounds( rect );

	Frame* frame = reinterpret_cast<VCF::Frame*>( getControl() );
	if ( frame->getFrameStyle() != fstSizeable ) {
		XSizeHints sh;
		sh.flags = PMinSize | PMaxSize;
		sh.min_width = sh.max_width = (int)bounds_.getWidth();
		sh.min_height= sh.max_height= (int)bounds_.getHeight();
		XSetWMSizeHints( grafToolkit->getX11Display(), wndHandle_, &sh, XA_WM_NORMAL_HINTS );
	}
}

String X11Dialog::getText()
{
	return text_;
}

/**
 * sets the text for the widget
 */
void X11Dialog::setText( const String& text )
{
	if ( text == text_ ) {
		return;
	}

	text_ = text;
	XTextProperty textProperty;
	const char* textPtr = text_.c_str();
    const char **textData = &textPtr;
	if ( !XStringListToTextProperty((char**)textData, 1, &textProperty ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("XStringListToTextProperty failed in X11Dialog::setText()") );
	}
	else {
		X11GraphicsToolkit* grafToolkit = reinterpret_cast<X11GraphicsToolkit*>(GraphicsToolkit::getDefaultGraphicsToolkit());
        XSetWMName( grafToolkit->getX11Display(), wndHandle_, &textProperty );
		XSetWMIconName( grafToolkit->getX11Display(), wndHandle_, &textProperty );
        XFree(textProperty.value);
    }
}

void X11Dialog::setCaption( const String& caption )
{
	setText( caption );
}

void X11Dialog::showMessage( const String& message, const String& caption )
{
	showMessage( message, caption, Dialog::mbOK, Dialog::msDefault );
}

UIToolkit::ModalReturnType X11Dialog::showMessage( const String& message, const String& caption,
												const int32& messageButtons,	const Dialog::MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result;
	X11MessageBox dlg;
	dlg.init( message, caption, messageButtons, messageStyle );
	result = dlg.showModal();
	return result;
}

void X11Dialog::handleEvent( XEvent* x11Event )
{
	X11UIToolkit* toolkit = reinterpret_cast<X11UIToolkit*>(UIToolkit::getDefaultUIToolkit());
	switch( x11Event->type ) {

		case VisibilityNotify : {
			setText( getText() );
		}
		break;

		case ClientMessage : {
			if ( x11Event->xclient.message_type == wmProtocols_ ) {
				Atom atom = x11Event->xclient.data.l[0];
				if ( atom == toolkit->getDeleteWindowMsg() ) {
					printf( "Delete window requested!\n" );

					VCF::Dialog* dialog = reinterpret_cast<VCF::Dialog*>( getControl() );

					if ( dialog->allowClose() ) {

						VCF::WindowEvent event( getControl(), WINDOW_EVENT_CLOSE );

						dialog->fireOnFrameClose( &event );

						//check if the main window is clossing - if it is
						//then close the app !

						//quit modal event loop
						toolkit->postQuitMessage(0);
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


/**
$Id$
*/
