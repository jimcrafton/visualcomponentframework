//X11UIToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11UIToolkit.h"
#include "vcf/ApplicationKit/X11Desktop.h"
#include "vcf/ApplicationKit/X11Application.h"
#include "vcf/ApplicationKit/X11Control.h"
#include "vcf/ApplicationKit/X11Window.h"
#include "vcf/ApplicationKit/X11ControlContext.h"
#include "vcf/ApplicationKit/X11Cursor.h"
#include "vcf/ApplicationKit/LightweightComponent.h"
#include "vcf/ApplicationKit/X11Dialog.h"
#include "vcf/ApplicationKit/X11SimpleTextControl.h"

#include <signal.h>
#include <X11/keysym.h>
#include <X11/Xproto.h>

#define X_KEYBUFFER_SIZE	100


//get rid of the stupip fscking warning from GCC
#define NULL 0




using namespace VCF;


//UIMetricsManager implementation for X11
class X11UIMetricsManager : public UIMetricsManager {
public:
	X11UIMetricsManager(){}

	virtual ~X11UIMetricsManager(){}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result("ARIAL", 10);

		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {

			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {

			}
			break;

			case UIMetricsManager::ftControlFont :  case UIMetricsManager::ftSystemFont : {

			}
			break;

			case UIMetricsManager::ftMessageFont : {

			}
			break;

			case UIMetricsManager::ftToolTipFont : {

			}
			break;
		}

		return result;
	}

	virtual double getDefaultHeightFor( const UIMetricsManager::HeightType& type )  {
		double result = 0.0;
		switch ( type ) {
			case UIMetricsManager::htLabelHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = f.getHeight() * 1.75;
			}
			break;

			case UIMetricsManager::htComboBoxHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = f.getHeight() * 2.0;
			}
			break;

			case UIMetricsManager::htListItemHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = f.getHeight() * 1.65;
			}
			break;

			case UIMetricsManager::htButtonHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = (f.getHeight() * 1.75) + 2.50;
			}
			break;

			case UIMetricsManager::htRadioBoxHeight : case UIMetricsManager::htCheckBoxHeight : {
				//in Win32 a radio box or check box is ALWAYS 10 dialog units high
				//dialog units are converted by
				//(2 * average char height dialog font / average char height system font pixels
				//where average char height dialog font = TEXTMETRIC.tmHeight field or a Font::getHeight()


				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = (9.0 * ((2.0 * f.getHeight()) / f.getHeight())) - 4.0;//0.590909;
			}
			break;

			case UIMetricsManager::htToolTipHeight : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftToolTipFont );
				result = f.getHeight() * 1.2222;
			}
			break;

			case UIMetricsManager::htSeparatorHeight : {
				result = 2.0;
			}
			break;

			case UIMetricsManager::htInformationalControl : {
				VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
				result = f.getHeight() * 1.75;
			}
			break;
		}
		return result;

	}

	virtual double getPreferredSpacingFor( const UIMetricsManager::SpacingType& type )  {
		double result = 0.0;

		//values largely derived from the Apple HIG at
		//http://developer.apple.com/techpubs/macosx/Essentials/AquaHIGuidelines/AHIGLayout/index.html
		switch ( type ) {
			case UIMetricsManager::stWindowBorderDelta : {
				result = 20.0;
			}
			break;

			case UIMetricsManager::stContainerBorderDelta : {
				result = 8.0;
			}
			break;

			case UIMetricsManager::stControlVerticalSpacing : {
				result = 14.0;
			}
			break;

			case UIMetricsManager::stControlHorizontalSpacing : {
				result = 10.0;
			}
			break;

			case UIMetricsManager::stInformationControlTopSpacer : {
				result = 2.0;
			}
			break;

			case UIMetricsManager::stInformationControlBottomSpacer : {
				result = 8.0;
			}
			break;
		}

		return result;
	}

	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;

		//where the hell do we get these ????
		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;


		return result;
	}

	virtual Size getDefaultVerticalScrollButtonDimensions()  {
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultHorizontalScrollButtonDimensions()  {
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultTabDimensions( const String& caption )  {
		Size result;

		return result;
	}
};










X11UIToolkit::X11UIToolkit():
	defaultParentWnd_(0),
	x11Display_(NULL),
	consoleQuitHandlerCalled_(false),
	quitEventLoopMsg_(0),
	deleteWindowMsg_(0),
	vcfCreateWindowMsg_(0)
{
	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();
	x11Display_ = toolkit->getX11Display();

	//install the X11 error handler here
	XSetErrorHandler( X11UIToolkit::x11ErrorHandler );


	metricsMgr_ = new X11UIMetricsManager();
	createDefaultParentWnd();

	//install the quit handler for Ctrl+C
	signal(SIGINT, X11UIToolkit::consoleQuitHandler );

	//create internal atoms
	deleteWindowMsg_ = XInternAtom(x11Display_, VCF_X11_DELETEWND_ATOM, False);
	vcfCreateWindowMsg_ = XInternAtom(x11Display_, VCF_X11_VCFCREATEWND_ATOM, False);
	quitEventLoopMsg_ = XInternAtom(x11Display_, VCF_X11_QUITEVENTLOOP_ATOM, False);

	vcfPaintWindowMsg_ = XInternAtom(x11Display_, VCF_X11_PAINTWND_ATOM, False);
}

X11UIToolkit::~X11UIToolkit()
{
	timerList_.clear();
	paintEventQueue_.clear();

	std::deque<X11ToolkitMsg*>::iterator it = toolkitMessages_.begin();
	while ( it != toolkitMessages_.end() ) {
		X11ToolkitMsg* msg = *it;
		delete msg;
		it ++;
	}
	toolkitMessages_.clear();

	if ( NULL != defaultParentWnd_ ) {
		XDestroyWindow( x11Display_, defaultParentWnd_ );
	}
}

ApplicationPeer* X11UIToolkit::createApplicationPeer()
{
	return new X11Application();
}

TextPeer* X11UIToolkit::createTextPeer( TextControl* component, const bool& isMultiLineControl, ComponentType componentType=CT_DEFAULT)
{
	return new X11SimpleTextControl( component, isMultiLineControl );
}

TreePeer* X11UIToolkit::createTreePeer( TreeControl* component, ComponentType componentType=CT_DEFAULT)
{
	return NULL;
}

ListviewPeer* X11UIToolkit::createListViewPeer( ListViewControl* component, ComponentType componentType=CT_DEFAULT)
{
	return NULL;
}

DialogPeer* X11UIToolkit::createDialogPeer( Control* owner, Dialog* component, ComponentType componentType=CT_DEFAULT )
{
	return new X11Dialog( owner, component );
}

DialogPeer* X11UIToolkit::createDialogPeer()
{
	return new X11Dialog();
}

ControlPeer* X11UIToolkit::createControlPeer( Control* component, ComponentType componentType)
{
	ControlPeer* result = NULL;

	switch ( componentType ){
		case CT_LIGHTWEIGHT:{
			result = new LightweightComponent( component );
		}
		break;

		case CT_DEFAULT: case CT_HEAVYWEIGHT:{
			result = new X11Control( component );
		}
		break;
	}
	return result;
}

WindowPeer* X11UIToolkit::createWindowPeer( Control* component, Control* owner, ComponentType componentType)
{
	return new X11Window( component, owner );
}

MenuItemPeer* X11UIToolkit::createMenuItemPeer( MenuItem* item )
{
	return NULL;
}

MenuBarPeer* X11UIToolkit::createMenuBarPeer( MenuBar* menuBar )
{
	return NULL;
}

PopupMenuPeer* X11UIToolkit::createPopupMenuPeer( PopupMenu* popupMenu )
{
	return NULL;
}

ButtonPeer* X11UIToolkit::createButtonPeer( CommandButton* component, ComponentType componentType)
{
	return NULL;
}

HTMLBrowserPeer* X11UIToolkit::createHTMLBrowserPeer( Control* control )
{
	return NULL;
}

ContextPeer* X11UIToolkit::createContextPeer( Control* component )
{
	return new X11ControlContext( component->getPeer() );
}

CommonFileDialogPeer* X11UIToolkit::createCommonFileOpenDialogPeer( Control* owner )
{
	return NULL;
}

CommonFileDialogPeer* X11UIToolkit::createCommonFileSaveDialogPeer( Control* owner )
{
	return NULL;
}

CommonColorDialogPeer* X11UIToolkit::createCommonColorDialogPeer( Control* owner )
{
	return NULL;
}

CommonFolderBrowseDialogPeer* X11UIToolkit::createCommonFolderBrowseDialogPeer( Control* owner )
{
	return NULL;
}

CommonFontDialogPeer* X11UIToolkit::createCommonFontDialogPeer( Control* owner )
{
	return NULL;
}

DragDropPeer* X11UIToolkit::createDragDropPeer()
{
	return NULL;
}

DataObjectPeer* X11UIToolkit::createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* X11UIToolkit::createDropTargetPeer()
{
	return NULL;
}

DesktopPeer* X11UIToolkit::createDesktopPeer( Desktop* desktop )
{
	return new X11Desktop( desktop );
}

ScrollPeer* X11UIToolkit::createScrollPeer( Control* control )
{
	return NULL;
}

CursorPeer* X11UIToolkit::createCursorPeer( Cursor* cursor )
{
	return new X11Cursor(cursor);
}

ClipboardPeer* X11UIToolkit::createClipboardPeer()
{
	return NULL;
}

bool X11UIToolkit::createCaret( Control* owningControl, Image* caretImage  )
{
	bool result = false;

	return result;
}

bool X11UIToolkit::destroyCaret( Control* owningControl )
{
	bool result = false;

	return result;
}

void X11UIToolkit::setCaretVisible( const bool& caretVisible )
{

}

void X11UIToolkit::setCaretPos( Point* point )
{

}

void X11UIToolkit::postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{

}

void X11UIToolkit::registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds )
{

}

void X11UIToolkit::unregisterTimerHandler( EventHandler* handler )
{

}

/**
Notes:
There are multiple places where we check hte internal status of toolkit registered timers. This is
to ensure that we notify folks of timer events as close as possible to when they are actually ready.

It is almost a certainty that we will NOT have 100% accuracy here, thus anything that truly needs
realtime timers should use something else. However this is no different than other window systems,
for example on Win32 WM_TIMER messages are not guaranteed to be super accurate either.

Also the System::sleep() call is to ensure that we don't race the CPU to 100% - without this in the loop
we get 100% CPU utilization. I beleive this is because we are use a non blocking equivalent to XPending()
so we always go through the inner loop phases, as opposed to blocking on XPending(). Note there
are many way to implement this, if someone sees a better way, please suggest it!
*/
void X11UIToolkit::runEventLoop()
{
	printf( "starting X11UIToolkit runEventLoop()...\n" );

	std::vector<TimerEntry> availableTimers;

	Application* runningApp = Application::getRunningInstance();
	//initial outer loop - this will have idle time processing if possible
	bool idleTime = true;

	while ( true ) {
		//quit if we get a Ctrl+C from the console
		if ( consoleQuitHandlerCalled_ ) {
			return;
		}

		XFlush(x11Display_);


		//check timers
		timersAvailable( availableTimers );
		if ( !availableTimers.empty() ) {
			fireTimers( availableTimers );
		}

		//phase 1 of event inner loop - idle processing

		while ( (!xPending() ) && (true == idleTime) ) {

			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}

			//only allow one cycle for now...
			idleTime = false;
		}

		//sleep just a bit
		System::sleep(1);

		XEvent x11event;
		Rect updateRect;
		/**
		phase 2 of inner event loop
		this phase will capture XEvents and pass them along
		to the various registered control peers.
		*/
		bool quitMessageReceived = false;
		do {

			if ( consoleQuitHandlerCalled_ ) {
				return;
			}

			//handle toolkit messages
			if ( !handleToolkitMessages() ) {
				//oops looks like we got a quit message
				quitMessageReceived = true;
				printf( "quitMessageReceived = true, handleToolkitMessages() returned false\n" );

			}

			/**
			Why is this here? We do a quick check to see if there are truly any events in the
			queue - if there are not tehn we do NOT want to call XNextEvent, which will BLOCK
			till there are events in the queue. By placing this here, we ensure that we will complete
			a cycle of the loop and not cause it to hang here waiting for events
			*/
			if ( xPending() ) {
				XNextEvent( x11Display_, &x11event );

				bool doTranslateAndDispatch = true;

				switch ( x11event.type ) {
					case KeyPress :  {
						AbstractX11Control* xwndControl = AbstractX11Control::getX11ControlFromXWindow( x11event.xkey.window );
						Control* control = NULL;

						if ( NULL != xwndControl ) {
							control = xwndControl->getControl();
							Control* currentFocusedControl = Control::getCurrentFocusedControl();
							if ( NULL != currentFocusedControl ) {
								if ( (control != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
									control = currentFocusedControl;
								}
							}
						}


						X11EventMsg eventMsg( &x11event, control );
						VCF::Event* event = createEventFromNativeOSEventData( (void*)&eventMsg );
						if ( NULL != event ) {
							//handle tabbing here
							handleKeyboardEvent( reinterpret_cast<KeyboardEvent*>( event ) );
							if ( event->isConsumed() ) {
								doTranslateAndDispatch = false;
							}
						}

						delete event;
					}
					break;

					case Expose: case GraphicsExpose: {

						updateRect.setRect( x11event.xexpose.x, x11event.xexpose.y,
											x11event.xexpose.x + x11event.xexpose.width,
											x11event.xexpose.y + x11event.xexpose.height );

						//adds a new update rect to the list

						AbstractX11Control* xwndControl = AbstractX11Control::getX11ControlFromXWindow( x11event.xexpose.window );
						if ( NULL != xwndControl ) {
							xwndControl->addUpdateRect( updateRect );
							paintEventQueue_[xwndControl] = xwndControl;
						}

						//don't dispatch the xevent - we'll handle this as a special case
						doTranslateAndDispatch = false;
					}
					break;

					default : {
						//need to figure out what a quit message is
					}
					break;
				}

				/**
				if we have some to deal with lets do so here
				*/
				if ( doTranslateAndDispatch ) {
					AbstractX11Control::handleXEvent( x11event.xany.window, &x11event );
				}
			}

			//check timers
			timersAvailable( availableTimers );
			if ( !availableTimers.empty() ) {
				fireTimers( availableTimers );
			}

		} while ( xPending() );

		if ( quitMessageReceived ) {
			while ( xPending() ) {
				XNextEvent( x11Display_, &x11event );
			}
			printf( "quitMessageReceived! leaving the X11UIToolkit::runEventLoop()!\n" );
			return;
		}

		handlePaintEvents();

		//check timers
		timersAvailable( availableTimers );
		if ( !availableTimers.empty() ) {
			fireTimers( availableTimers );
		}

		//reset the idle flag
		idleTime = true;
	}
}


UIToolkit::ModalReturnType X11UIToolkit::runModalEventLoopFor( Control* control )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrFalse;
	printf( "starting X11UIToolkit runModalEventLoopFor( %p )...\n", control );

	std::vector<TimerEntry> availableTimers;

	Application* runningApp = Application::getRunningInstance();
	//initial outer loop - this will have idle time processing if possible
	bool idleTime = true;

	while ( true ) {
		//quit if we get a Ctrl+C from the console
		if ( consoleQuitHandlerCalled_ ) {
			return result;
		}

		XFlush(x11Display_);


		//check timers
		timersAvailable( availableTimers );
		if ( !availableTimers.empty() ) {
			fireTimers( availableTimers );
		}

		//phase 1 of event inner loop - idle processing

		while ( (!xPending() ) && (true == idleTime) ) {

			if ( NULL != runningApp ) {
				runningApp->idleTime();
			}

			//check library apps;
			Enumerator<LibraryApplication*>* registeredLibs = LibraryApplication::getRegisteredLibraries();
			while ( true == registeredLibs->hasMoreElements() ) {
				LibraryApplication* libraryApp = registeredLibs->nextElement();
				libraryApp->idleTime();
			}

			//only allow one cycle for now...
			idleTime = false;
		}

		//sleep just a bit
		System::sleep(1);

		XEvent x11event;
		Rect updateRect;
		/**
		phase 2 of inner event loop
		this phase will capture XEvents and pass them along
		to the various registered control peers.
		*/
		bool quitMessageReceived = false;
		do {

			if ( consoleQuitHandlerCalled_ ) {
				return result;
			}

			//handle toolkit messages
			if ( !handleToolkitMessages() ) {
				//oops looks like we got a quit message
				quitMessageReceived = true;
				printf( "quitMessageReceived = true, handleToolkitMessages() returned false\n" );

				XFlush(x11Display_);
				break;
			}

			/**
			Why is this here? We do a quick check to see if there are truly any events in the
			queue - if there are not tehn we do NOT want to call XNextEvent, which will BLOCK
			till there are events in the queue. By placing this here, we ensure that we will complete
			a cycle of the loop and not cause it to hang here waiting for events
			*/
			if ( xPending() ) {
				XNextEvent( x11Display_, &x11event );

				bool doTranslateAndDispatch = true;

				switch ( x11event.type ) {
					case KeyPress :  {
						AbstractX11Control* xwndControl = AbstractX11Control::getX11ControlFromXWindow( x11event.xkey.window );
						Control* control = NULL;

						if ( NULL != xwndControl ) {
							control = xwndControl->getControl();
							Control* currentFocusedControl = Control::getCurrentFocusedControl();
							if ( NULL != currentFocusedControl ) {
								if ( (control != currentFocusedControl) && (currentFocusedControl->isLightWeight()) ) {
									control = currentFocusedControl;
								}
							}
						}


						X11EventMsg eventMsg( &x11event, control );
						VCF::Event* event = createEventFromNativeOSEventData( (void*)&eventMsg );
						if ( NULL != event ) {
							//handle tabbing here
							handleKeyboardEvent( reinterpret_cast<KeyboardEvent*>( event ) );
							if ( event->isConsumed() ) {
								doTranslateAndDispatch = false;
							}
						}

						delete event;
					}
					break;

					case KeyRelease : {

						XKeyEvent xkey = x11event.xkey;
						int keyCode = xkey.keycode;
						KeySym keySym;
						memset(&keySym, 0, sizeof(KeySym) );

						char keyBuffer[X_KEYBUFFER_SIZE];
						memset( keyBuffer, 0, sizeof(keyBuffer) );

						int count = XLookupString( &xkey, keyBuffer, X_KEYBUFFER_SIZE-1, &keySym, 0 );
						VirtualKeyCode code = translateKeyCode( keySym );
						if ( code == vkEscape ) {
							quitMessageReceived = true;
							XFlush(x11Display_);
							break;
						}
					}
					break;

					case Expose: case GraphicsExpose: {

						updateRect.setRect( x11event.xexpose.x, x11event.xexpose.y,
											x11event.xexpose.x + x11event.xexpose.width,
											x11event.xexpose.y + x11event.xexpose.height );

						//adds a new update rect to the list

						AbstractX11Control* xwndControl = AbstractX11Control::getX11ControlFromXWindow( x11event.xexpose.window );
						if ( NULL != xwndControl ) {
							xwndControl->addUpdateRect( updateRect );
							paintEventQueue_[xwndControl] = xwndControl;
						}

						//don't dispatch the xevent - we'll handle this as a special case
						doTranslateAndDispatch = false;
					}
					break;

					default : {
						//need to figure out what a quit message is
					}
					break;
				}

				/**
				if we have some to deal with lets do so here
				*/
				if ( doTranslateAndDispatch ) {
					AbstractX11Control::handleXEvent( x11event.xany.window, &x11event );
				}
			}

			//check timers
			timersAvailable( availableTimers );
			if ( !availableTimers.empty() ) {
				fireTimers( availableTimers );
			}

		} while ( xPending() );

		if ( quitMessageReceived ) {
			while ( xPending() ) {
				XNextEvent( x11Display_, &x11event );
			}
			printf( "quitMessageReceived! leaving the X11UIToolkit::runModalEventLoopFor()!\n" );
			return result;
		}

		handlePaintEvents();

		//check timers
		timersAvailable( availableTimers );
		if ( !availableTimers.empty() ) {
			fireTimers( availableTimers );
		}

		//reset the idle flag
		idleTime = true;
	}

	return result;
}

/**
*@param void* in this implementation, the eventData represents a
*pointer to an X11 XEvent structure.
*/
VCF::Event* X11UIToolkit::createEventFromNativeOSEventData( void* eventData )
{
	X11EventMsg* eventMsg = (X11EventMsg*)eventData;
	XEvent* x11Event = eventMsg->x11event_;
	VCF::Event* result = NULL;

	switch ( x11Event->type ) {
		case KeyRelease : case KeyPress :  {
			XKeyEvent xkey = x11Event->xkey;

			//note - the Qt folks generously note that HPUX seems to have
			//a clusterfuck in their implementation - should we ever have the misfortune to
			//run on these systems we may have to fix things witrh state


			int keyCode = xkey.keycode;
			KeySym keySym;
			memset(&keySym, 0, sizeof(KeySym) );

			char keyBuffer[X_KEYBUFFER_SIZE];
			memset( keyBuffer, 0, sizeof(keyBuffer) );

			int count = XLookupString( &xkey, keyBuffer, X_KEYBUFFER_SIZE-1, &keySym, 0 );

			ulong32 eventType = (x11Event->type == KeyPress) ? Control::KEYBOARD_DOWN : Control::KEYBOARD_UP;

			result = new VCF::KeyboardEvent( eventMsg->control_,
											eventType,
											1,
											translateKeyMask(xkey.state),
											keyBuffer[0],
											translateKeyCode( keySym ) );
		}
		break;

		case ButtonPress : case ButtonRelease : {

			VCF::Point pt( x11Event->xbutton.x, x11Event->xbutton.y );
			ulong32 eventType = (x11Event->type == ButtonPress) ? Control::MOUSE_DOWN : Control::MOUSE_UP;
			result = new VCF::MouseEvent ( eventMsg->control_, eventType,
											translateButtonMask( x11Event->xbutton.button ),
											translateKeyMask( x11Event->xbutton.state ), &pt );

		}
		break;

		case MotionNotify : {
			VCF::Point pt( x11Event->xmotion.x, x11Event->xmotion.y );
			result = new VCF::MouseEvent ( eventMsg->control_, Control::MOUSE_MOVE,
											translateButtonMask( x11Event->xmotion.state ),
											translateKeyMask( x11Event->xmotion.state ), &pt );
		}
		break;


		case LeaveNotify : case EnterNotify :  {
			VCF::Point pt( x11Event->xcrossing.x, x11Event->xcrossing.y );
			ulong32 eventType = (x11Event->type == EnterNotify) ? Control::MOUSE_ENTERED : Control::MOUSE_LEAVE;
			//the peer will fill out the button and key masks
			result = new VCF::MouseEvent ( eventMsg->control_, eventType,
											0,	0, &pt );
		}
		break;


		case FocusIn : {
			result = new VCF::FocusEvent ( eventMsg->control_, Control::FOCUS_GAINED );
		}
		break;

		case FocusOut : {
			result = new VCF::FocusEvent ( eventMsg->control_, Control::FOCUS_LOST );
		}
		break;

		case NoExpose : {

		}
		break;


		case CreateNotify : {

		}
		break;


		case DestroyNotify : {
			result = new VCF::ComponentEvent( eventMsg->control_, Component::COMPONENT_DELETED );
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
			//we are going to return NULL here -
			//the problem is that there are two separate VCF event objects that
			//need to be created, so we are going to let teh AbstractX11Control deal
			//with this directly

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

		}
		break;

		case MappingNotify : {

		}
		break;

		case KeymapNotify : {

		}
		break;
	}

	return result;
}

Size X11UIToolkit::getDragDropDelta()
{
	//this is completely arbitrary - need to read this from a file
	Size result(4,4);

	return result;
}

String X11UIToolkit::getX11ErrorMessage( XID id )
{
	String result;

	return result;
}

void X11UIToolkit::createDefaultParentWnd()
{

	X11GraphicsToolkit* toolkit = (X11GraphicsToolkit*)GraphicsToolkit::getDefaultGraphicsToolkit();

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

	defaultParentWnd_ = XCreateWindow( x11Display_,
										DefaultRootWindow( x11Display_ ),
										0, 0, 1, 1, 0,
										CopyFromParent,//DefaultDepth( x11Display_, toolkit->getX11ScreenID() ),
										InputOutput,
										CopyFromParent,//DefaultVisual( x11Display_, toolkit->getX11ScreenID() ),
										1,
										&attrs );
	if ( NULL != defaultParentWnd_ ) {
		//XMapWindow( x11Display_, defaultParentWnd_ );
	}
	else {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("XCreateWindow returned a NULL window ID in creating the default parent wnd") );
	}
}

void X11UIToolkit::consoleQuitHandler( int sig )
{
	signal(sig, SIG_IGN);
	X11UIToolkit* toolkit = (X11UIToolkit*) UIToolkit::getDefaultUIToolkit();
	toolkit->consoleQuitHandlerCalled_ = true;
}

VirtualKeyCode X11UIToolkit::translateKeyCode( KeySym code )
{
	VirtualKeyCode result;

	/**
	please note: all codes from X11/keysymdef.h
	*/
	switch ( code ) {

		case XK_F1 :{
			result = VCF::vkF1;
		}
		break;

		case XK_F2 :{
			result = VCF::vkF2;
		}
		break;

		case XK_F3 :{
			result = VCF::vkF3;
		}
		break;

		case XK_F4 :{
			result = VCF::vkF4;
		}
		break;

		case XK_F5 :{
			result = VCF::vkF5;
		}
		break;

		case XK_F6 :{
			result = VCF::vkF6;
		}
		break;

		case XK_F7 :{
			result = VCF::vkF7;
		}
		break;

		case XK_F8 :{
			result = VCF::vkF8;
		}
		break;

		case XK_F9 :{
			result = VCF::vkF9;
		}
		break;

		case XK_F10 :{
			result = VCF::vkF10;
		}
		break;

		case XK_F11 :{
			result = VCF::vkF11;
		}
		break;

		case XK_F12 :{
			result = VCF::vkF12;
		}
		break;

		case XK_KP_Up : case XK_Up :{
			result = VCF::vkUpArrow;
		}
		break;

		case XK_KP_Down : case XK_Down :{
			result = VCF::vkDownArrow;
		}
		break;

		case XK_KP_Left : case XK_Left :{
			result = VCF::vkLeftArrow;
		}
		break;

		case XK_KP_Right : case XK_Right :{
			result = VCF::vkRightArrow;
		}
		break;

		case XK_Delete :{
			result = VCF::vkDelete;
		}
		break;

		case XK_Return :{
			result = VCF::vkReturn;
		}
		break;

		case XK_BackSpace :{
			result = VCF::vkBackSpace;
		}
		break;

		case XK_space :{
			result = VCF::vkSpaceBar;
		}
		break;

		case XK_Escape :{
			result = VCF::vkEscape;
		}
		break;

		case XK_Page_Down :{
			result = VCF::vkPgDown;
		}
		break;

		case XK_Page_Up :{
			result = VCF::vkPgUp;
		}
		break;

		case XK_Home :{
			result = VCF::vkHome;
		}
		break;

		case XK_End :{
			result = VCF::vkEnd;
		}
		break;

		case XK_Control_R : case XK_Control_L :{
			result = VCF::vkCtrl;
		}
		break;

		case XK_Alt_R : case XK_Alt_L :{
			result = VCF::vkAlt;
		}
		break;

		case XK_Shift_R : case XK_Shift_L :{
			result = VCF::vkShift;
		}
		break;

		case XK_Tab :{
			result = VCF::vkTab;
		}
		break;

		case XK_0 : case XK_KP_0 :{
			result = VCF::vkNumber0;
		}
		break;

		case XK_1 : case XK_KP_1 :{
			result = VCF::vkNumber1;
		}
		break;

		case XK_2 : case XK_KP_2 :{
			result = VCF::vkNumber2;
		}
		break;

		case XK_3 : case XK_KP_3 :{
			result = VCF::vkNumber3;
		}
		break;

		case XK_4 : case XK_KP_4 :{
			result = VCF::vkNumber4;
		}
		break;

		case XK_5 : case XK_KP_5 :{
			result = VCF::vkNumber5;
		}
		break;

		case XK_6 : case XK_KP_6 :{
			result = VCF::vkNumber6;
		}
		break;

		case XK_7 : case XK_KP_7 :{
			result = VCF::vkNumber7;
		}
		break;

		case XK_8 : case XK_KP_8 :{
			result = VCF::vkNumber8;
		}
		break;

		case XK_9 : case XK_KP_9 :{
			result = VCF::vkNumber9;
		}
		break;

		case XK_a : case XK_A :{
			result = VCF::vkLetterA;
		}
		break;

		case XK_b : case XK_B :{
			result = VCF::vkLetterB;
		}
		break;

		case XK_c : case XK_C :{
			result = VCF::vkLetterC;
		}
		break;

		case XK_d : case XK_D :{
			result = VCF::vkLetterD;
		}
		break;

		case XK_e : case XK_E :{
			result = VCF::vkLetterE;
		}
		break;

		case XK_f : case XK_F :{
			result = VCF::vkLetterF;
		}
		break;

		case XK_g : case XK_G :{
			result = VCF::vkLetterG;
		}
		break;

		case XK_h : case XK_H :{
			result = VCF::vkLetterH;
		}
		break;

		case XK_i : case XK_I :{
			result = VCF::vkLetterI;
		}
		break;

		case XK_j : case XK_J :{
			result = VCF::vkLetterJ;
		}
		break;

		case XK_k : case XK_K :{
			result = VCF::vkLetterK;
		}
		break;

		case XK_l : case XK_L :{
			result = VCF::vkLetterL;
		}
		break;

		case XK_m : case XK_M :{
			result = VCF::vkLetterM;
		}
		break;

		case XK_n : case XK_N :{
			result = VCF::vkLetterN;
		}
		break;

		case XK_o : case XK_O :{
			result = VCF::vkLetterO;
		}
		break;

		case XK_p : case XK_P :{
			result = VCF::vkLetterP;
		}
		break;

		case XK_q : case XK_Q :{
			result = VCF::vkLetterQ;
		}
		break;

		case XK_r : case XK_R :{
			result = VCF::vkLetterR;
		}
		break;

		case XK_s : case XK_S :{
			result = VCF::vkLetterS;
		}
		break;

		case XK_t : case XK_T :{
			result = VCF::vkLetterT;
		}
		break;

		case XK_u : case XK_U :{
			result = VCF::vkLetterU;
		}
		break;

		case XK_v : case XK_V :{
			result = VCF::vkLetterV;
		}
		break;

		case XK_w : case XK_W :{
			result = VCF::vkLetterW;
		}
		break;

		case XK_x : case XK_X :{
			result = VCF::vkLetterX;
		}
		break;

		case XK_y : case XK_Y :{
			result = VCF::vkLetterY;
		}
		break;

		case XK_z : case XK_Z :{
			result = VCF::vkLetterZ;
		}
		break;

		case XK_Print :{
			result = VCF::vkPrintScreen;
		}
		break;

		case XK_Pause :{
			result = VCF::vkPause;
		}
		break;

		case XK_Scroll_Lock :{
			result = VCF::vkScrollLock;
		}
		break;

		case XK_KP_Multiply : case XK_multiply :{
			result = VCF::vkMultiplySign;
		}
		break;

		case XK_plus : case XK_KP_Add :{
			result = VCF::vkPlusSign;
		}
		break;

		case XK_minus : case XK_KP_Subtract :{
			result = VCF::vkMinusSign;
		}
		break;

		case XK_period : case XK_KP_Decimal :{
			result = VCF::vkPeriod;
		}
		break;

		case XK_slash : case XK_KP_Divide :{
			result = VCF::vkDivideSign;
		}
		break;

		case XK_backslash :{
			result = VCF::vkBackSlash;
		}
		break;

		case XK_bracketleft :{
			result = VCF::vkOpenBracket;
		}
		break;

		case XK_braceleft :{
			result = VCF::vkOpenBrace;
		}
		break;

		case XK_bracketright :{
			result = VCF::vkCloseBracket;
		}
		break;


		case XK_braceright :{
			result = VCF::vkCloseBrace;
		}
		break;

		case XK_semicolon :{
			result = VCF::vkSemiColon;
		}
		break;

		case XK_colon :{
			result = VCF::vkColon;
		}
		break;

		case XK_quoteright : case XK_quoteleft :{
			result = VCF::vkSingleQuote;
		}
		break;

		case XK_quotedbl :{
			result = VCF::vkDoubleQuote;
		}
		break;

		case XK_comma :{
			result = VCF::vkComma;
		}
		break;

		case XK_less :{
			result = VCF::vkLessThan;
		}
		break;

		case XK_greater :{
			result = VCF::vkGreaterThan;
		}
		break;


		case XK_question :{
			result = VCF::vkQuestionMark;
		}
		break;
	}

	return result;
}

ulong32 X11UIToolkit::translateButtonMask( ulong32 xButtonState )
{
	ulong32 result = 0;

	if ( xButtonState & Button1 ) {
		result |= VCF::mbmLeftButton;
	}
	if ( xButtonState & Button3 ) {
		result |= VCF::mbmMiddleButton;
	}
	if ( xButtonState & Button3 ) {
		result |= VCF::mbmRightButton;
	}

	return result;
}

ulong32 X11UIToolkit::translateKeyMask( ulong32 xKeyState )
{
	ulong32 result = VCF::kmUndefined;

	if ( xKeyState & ShiftMask ) {
		result |= VCF::kmShift;
	}
	if ( xKeyState & ControlMask ) {
		result |= VCF::kmCtrl;
	}
	//need to figure out the Alt key.....

	return result;
}

void X11UIToolkit::postToolkitMessage( int type, void* data )
{
	toolkitMessages_.push_back( new X11ToolkitMsg(type,data) );
}

void X11UIToolkit::postToolkitMessage( X11ToolkitMsg* msg )
{
	toolkitMessages_.push_back( msg );
}

void X11UIToolkit::postQuitMessage( int exitValue )
{
	toolkitMessages_.push_back( new X11ToolkitMsg(quitEventLoopMsg_) );
}

void X11UIToolkit::repaintControl( AbstractX11Control* control, Rect& bounds )
{
	control->addUpdateRect( bounds );
	paintEventQueue_[control] = control;
}

void X11UIToolkit::addTimer( const TimerEntry& entry )
{
	timerList_.push_back( entry );
}

void X11UIToolkit::removeTimer( const TimerEntry& entry )
{
	std::vector<TimerEntry>::iterator found = std::find( timerList_.begin(), timerList_.end(), entry );
	if ( found != timerList_.end() ) {
		timerList_.erase( found );
	}
}

void X11UIToolkit::timersAvailable( std::vector<TimerEntry>& availableTimers )
{
	availableTimers.clear();
	struct timeval now;
	struct	timezone timeZone;
	::gettimeofday( &now, &timeZone );

	std::vector<TimerEntry>::iterator it = timerList_.begin();
	while ( it != timerList_.end() ) {
		TimerEntry& e = *it;
		if ( e.getMillisecondsDifference( &now ) >= e.getFrequency() ) {
			e.resetCurrentTime();
			availableTimers.push_back( e );
		}
		it ++;
	}
}

void X11UIToolkit::fireTimers( std::vector<TimerEntry>& availableTimers )
{
	std::vector<TimerEntry>::iterator it = availableTimers.begin();
	while ( it != availableTimers.end() ) {
		TimerEntry& e = *it;
		printf( "fired event for timer: e@%p, frequency: %d\n",
					&e, e.getFrequency() );
		it ++;
	}
}

bool X11UIToolkit::handleToolkitMessages()
{
	bool result = true;
	if ( !toolkitMessages_.empty() ) {
		X11ToolkitMsg* msg = toolkitMessages_.front();
		toolkitMessages_.pop_front();

		if ( vcfCreateWindowMsg_ == msg->type_ ) {
			Control* control  =  (Control*)msg->data_;

			VCF::ComponentEvent createEvent( control, Component::COMPONENT_CREATED );

			control->handleEvent( &createEvent );
		}
		else if ( msg->type_ == quitEventLoopMsg_	) {
			result = false;
		}

		delete msg;
	}

	return result;
}

void X11UIToolkit::handlePaintEvents()
{
	//check to see if the paint queue is empty, if not process the events
	if ( !paintEventQueue_.empty() ) {
		std::vector<PaintUpdateMap::iterator> removalList;

		PaintUpdateMap::iterator it =  paintEventQueue_.begin();
		while ( it != paintEventQueue_.end() ) {
			//store off the iterator so we can remove it later
			removalList.push_back( it );

			it->second->handlePaintEvent();

			it ++;
		}

		std::vector<PaintUpdateMap::iterator>::iterator it2 = removalList.begin();
		while ( it2 != removalList.end() ) {
			paintEventQueue_.erase( *it2 );
			it2++;
		}
	}
}


bool X11UIToolkit::xPending()
{
	return 0 == XEventsQueued( x11Display_, QueuedAfterFlush ) ? false : true;
}

void X11UIToolkit::xGrabPointer( AbstractX11Control* control )
{
	int eventMask = ButtonPressMask | ButtonReleaseMask;
		eventMask |= PointerMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask;

	int result = XGrabPointer( x11Display_, (xLib::Window)control->getHandleID(), False, eventMask,
								GrabModeAsync, GrabModeAsync, None, None, CurrentTime );
}

void X11UIToolkit::xUnGrabPointer( AbstractX11Control* control )
{
	XUngrabPointer( x11Display_, CurrentTime );
}

String X11UIToolkit::x11GetRequestCodeString( int requestCode )
{
	String result;

	switch ( requestCode ) {
		case X_CreateWindow : {
			result = "X_CreateWindow";
		}
		break;

		case X_ChangeWindowAttributes : {
			result = "X_ChangeWindowAttributes";
		}
		break;

		case X_GetWindowAttributes : {
			result = "X_GetWindowAttributes";
		}
		break;

		case X_DestroyWindow   : {
			result = "X_DestroyWindow";
		}
		break;

		case X_DestroySubwindows : {
			result = "X_DestroySubwindows";
		}
		break;

		case X_ChangeSaveSet    : {
			result = "X_ChangeSaveSet";
		}
		break;

		case X_ReparentWindow  : {
			result = "X_ReparentWindow";
		}
		break;

		case X_MapWindow   : {
			result = "X_MapWindow";
		}
		break;

		case X_MapSubwindows : {
			result = "X_MapSubwindows";
		}
		break;

		case X_UnmapWindow : {
			result = "X_UnmapWindow";
		}
		break;

		case X_UnmapSubwindows : {
			result = "X_UnmapSubwindows";
		}
		break;

		case X_ConfigureWindow  : {
			result = "X_ConfigureWindow";
		}
		break;

		case X_CirculateWindow : {
			result = "X_CirculateWindow";
		}
		break;

		case X_GetGeometry : {
			result = "X_GetGeometry";
		}
		break;

		case X_QueryTree     : {
			result = "X_QueryTree";
		}
		break;

		case X_InternAtom   : {
			result = "X_InternAtom";
		}
		break;

		case X_GetAtomName  : {
			result = "X_GetAtomName";
		}
		break;

		case X_ChangeProperty : {
			result = "X_ChangeProperty";
		}
		break;

		case X_DeleteProperty  : {
			result = "X_DeleteProperty";
		}
		break;

		case X_GetProperty : {
			result = "X_GetProperty";
		}
		break;

		case X_ListProperties   : {
			result = "X_ListProperties";
		}
		break;

		case X_SetSelectionOwner  : {
			result = "X_SetSelectionOwner";
		}
		break;

		case X_GetSelectionOwner : {
			result = "X_GetSelectionOwner";
		}
		break;

		case X_ConvertSelection  : {
			result = "X_ConvertSelection";
		}
		break;

		case X_SendEvent   : {
			result = "X_SendEvent";
		}
		break;

		case X_GrabPointer : {
			result = "X_GrabPointer";
		}
		break;

		case X_UngrabPointer : {
			result = "X_UngrabPointer";
		}
		break;

		case X_GrabButton  : {
			result = "X_GrabButton";
		}
		break;

		case X_UngrabButton  : {
			result = "X_UngrabButton";
		}
		break;

		case X_ChangeActivePointerGrab  : {
			result = "X_ChangeActivePointerGrab";
		}
		break;

		case X_GrabKeyboard    : {
			result = "X_GrabKeyboard";
		}
		break;

		case X_UngrabKeyboard  : {
			result = "X_UngrabKeyboard";
		}
		break;

		case X_GrabKey    : {
			result = "X_GrabKey";
		}
		break;

		case X_UngrabKey  : {
			result = "X_UngrabKey";
		}
		break;

		case X_AllowEvents  : {
			result = "X_AllowEvents";
		}
		break;

		case X_GrabServer  : {
			result = "X_GrabServer";
		}
		break;

		case X_UngrabServer  : {
			result = "X_UngrabServer";
		}
		break;

		case X_QueryPointer  : {
			result = "X_QueryPointer";
		}
		break;

		case X_GetMotionEvents : {
			result = "X_GetMotionEvents";
		}
		break;

		case X_TranslateCoords  : {
			result = "X_TranslateCoords";
		}
		break;

		case X_WarpPointer  : {
			result = "X_WarpPointer";
		}
		break;

		case X_SetInputFocus     : {
			result = "X_SetInputFocus";
		}
		break;

		case X_GetInputFocus   : {
			result = "X_GetInputFocus";
		}
		break;

		case X_QueryKeymap   : {
			result = "X_QueryKeymap";
		}
		break;

		case X_OpenFont      : {
			result = "X_OpenFont";
		}
		break;

		case X_CloseFont   : {
			result = "X_CloseFont";
		}
		break;

		case X_QueryFont  : {
			result = "X_QueryFont";
		}
		break;

		case X_QueryTextExtents : {
			result = "X_QueryTextExtents";
		}
		break;

		case X_ListFonts      : {
			result = "X_ListFonts";
		}
		break;

		case X_ListFontsWithInfo    : {
			result = "X_ListFontsWithInfo";
		}
		break;

		case X_SetFontPath    : {
			result = "X_SetFontPath";
		}
		break;

		case X_GetFontPath: {
			result = "X_GetFontPath";
		}
		break;

		case X_CreatePixmap      : {
			result = "X_CreatePixmap";
		}
		break;

		case X_FreePixmap      : {
			result = "X_FreePixmap";
		}
		break;

		case X_CreateGC  : {
			result = "X_CreateGC";
		}
		break;

		case X_ChangeGC  : {
			result = "X_ChangeGC";
		}
		break;

		case X_CopyGC  : {
			result = "X_CopyGC";
		}
		break;

		case X_SetDashes  : {
			result = "X_SetDashes";
		}
		break;

		case X_SetClipRectangles : {
			result = "X_SetClipRectangles";
		}
		break;

		case X_FreeGC   : {
			result = "X_FreeGC";
		}
		break;

		case X_ClearArea   : {
			result = "X_ClearArea";
		}
		break;

		case X_CopyArea   : {
			result = "X_CopyArea";
		}
		break;

		case X_CopyPlane  : {
			result = "X_CopyPlane";
		}
		break;

		case X_PolyPoint  : {
			result = "X_PolyPoint";
		}
		break;

		case X_PolyLine   : {
			result = "X_PolyLine";
		}
		break;

		case X_PolySegment  : {
			result = "X_PolySegment";
		}
		break;

		case X_PolyRectangle : {
			result = "X_PolyRectangle";
		}
		break;

		case X_PolyArc      : {
			result = "X_PolyArc";
		}
		break;

		case X_FillPoly : {
			result = "X_FillPoly";
		}
		break;

		case X_PolyFillRectangle  : {
			result = "X_PolyFillRectangle";
		}
		break;

		case X_PolyFillArc   : {
			result = "X_PolyFillArc";
		}
		break;

		case X_PutImage : {
			result = "X_PutImage";
		}
		break;

		case X_GetImage   : {
			result = "X_GetImage";
		}
		break;

		case X_PolyText8 : {
			result = "X_PolyText8";
		}
		break;

		case X_PolyText16 : {
			result = "X_PolyText16";
		}
		break;

		case X_ImageText8   : {
			result = "X_ImageText8";
		}
		break;

		case X_ImageText16  : {
			result = "X_ImageText16";
		}
		break;

		case X_CreateColormap  : {
			result = "X_CreateColormap";
		}
		break;

		case X_FreeColormap   : {
			result = "X_FreeColormap";
		}
		break;

		case X_CopyColormapAndFree   : {
			result = "X_CopyColormapAndFree";
		}
		break;

		case X_InstallColormap : {
			result = "X_InstallColormap";
		}
		break;

		case X_UninstallColormap   : {
			result = "X_UninstallColormap";
		}
		break;

		case X_ListInstalledColormaps  : {
			result = "X_ListInstalledColormaps";
		}
		break;

		case X_AllocColor   : {
			result = "X_AllocColor";
		}
		break;

		case X_AllocNamedColor : {
			result = "X_AllocNamedColor";
		}
		break;

		case X_AllocColorCells : {
			result = "X_AllocColorCells";
		}
		break;

		case X_AllocColorPlanes : {
			result = "X_AllocColorPlanes";
		}
		break;

		case X_FreeColors : {
			result = "X_FreeColors";
		}
		break;

		case X_StoreColors    : {
			result = "X_StoreColors";
		}
		break;

		case X_StoreNamedColor : {
			result = "X_StoreNamedColor";
		}
		break;

		case X_QueryColors : {
			result = "X_QueryColors";
		}
		break;

		case X_LookupColor  : {
			result = "X_LookupColor";
		}
		break;

		case X_CreateCursor   : {
			result = "X_CreateCursor";
		}
		break;

		case X_CreateGlyphCursor   : {
			result = "X_CreateGlyphCursor";
		}
		break;

		case X_FreeCursor   : {
			result = "X_FreeCursor";
		}
		break;

		case X_RecolorCursor  : {
			result = "X_RecolorCursor";
		}
		break;

		case X_QueryBestSize   : {
			result = "X_QueryBestSize";
		}
		break;

		case X_QueryExtension   : {
			result = "X_QueryExtension";
		}
		break;

		case X_ListExtensions  : {
			result = "X_ListExtensions";
		}
		break;

		case X_ChangeKeyboardMapping : {
			result = "X_ChangeKeyboardMapping";
		}
		break;

		case X_GetKeyboardMapping : {
			result = "X_GetKeyboardMapping";
		}
		break;

		case X_ChangeKeyboardControl    : {
			result = "X_ChangeKeyboardControl";
		}
		break;

		case X_GetKeyboardControl  : {
			result = "X_GetKeyboardControl";
		}
		break;

		case X_Bell    : {
			result = "X_Bell";
		}
		break;

		case X_ChangePointerControl : {
			result = "X_ChangePointerControl";
		}
		break;

		case X_GetPointerControl  : {
			result = "X_GetPointerControl";
		}
		break;

		case X_SetScreenSaver : {
			result = "X_SetScreenSaver";
		}
		break;

		case X_GetScreenSaver    : {
			result = "X_GetScreenSaver";
		}
		break;

		case X_ChangeHosts  : {
			result = "X_ChangeHosts";
		}
		break;

		case X_ListHosts    : {
			result = "X_ListHosts";
		}
		break;

		case X_SetAccessControl  : {
			result = "X_SetAccessControl";
		}
		break;

		case X_SetCloseDownMode : {
			result = "X_SetCloseDownMode";
		}
		break;

		case X_KillClient      : {
			result = "X_KillClient";
		}
		break;

		case X_RotateProperties	  : {
			result = "X_RotateProperties";
		}
		break;

		case X_ForceScreenSaver	 : {
			result = "X_ForceScreenSaver";
		}
		break;

		case X_SetPointerMapping   : {
			result = "X_SetPointerMapping";
		}
		break;

		case X_GetPointerMapping    : {
			result = "X_GetPointerMapping";
		}
		break;

		case X_SetModifierMapping	: {
			result = "X_SetModifierMapping";
		}
		break;

		case X_GetModifierMapping	: {
			result = "X_GetModifierMapping";
		}
		break;

		case X_NoOperation      : {
			result = "X_NoOperation";
		}
		break;
	}
	return result;
}

int X11UIToolkit::x11ErrorHandler( Display* display, XErrorEvent* xError )
{
	char errorText[256];
	memset( errorText, 0, sizeof(errorText) );
	XGetErrorText( display,  xError->error_code, errorText, 255 );
	String errorMsg;
	errorMsg = "X11 Error: ";
	errorMsg += errorText;
	errorMsg += ".\n\tXErrorEvent: error_code: " + StringUtils::toString( xError->error_code ) + "\n";
	errorMsg += "\t\t\tSerial Number: " + StringUtils::toString( xError->serial ) + "\n";
	errorMsg += "\t\t\tRequest code: " + StringUtils::toString( xError->request_code ) + "\n";
	errorMsg += "\t\t\tMinor code: " + StringUtils::toString( xError->minor_code ) + "\n";
	errorMsg += "\t\t\tResource ID: " + StringUtils::toString( xError->resourceid ) + "\n";
	errorMsg += "\t\t\tRequest Function: " + X11UIToolkit::x11GetRequestCodeString( xError->request_code ) + "\n";

	throw RuntimeException( errorMsg );

	return 0;
}

void X11UIToolkit::sendPaintEvent( AbstractX11Control* control )
{
	XEvent paintEvent;
	paintEvent.type = ClientMessage;
	paintEvent.xclient.message_type = getVCFPaintWindowMsg();
	paintEvent.xclient.window = (xLib::Window)control->getHandleID();
	paintEvent.xclient.send_event = 0;
	paintEvent.xclient.display = 0;
	paintEvent.xclient.format = 8;
	memset( &paintEvent.xclient.data.b[0], 0, 20*sizeof(char) );
	printf( "time to send an XEvent to notify we (%p) are ready to paint\n", control );
	XSendEvent( x11Display_, (xLib::Window)control->getHandleID(), False, 0, &paintEvent );
}

void X11UIToolkit::removeControlFromPaintEventQueue( AbstractX11Control* control )
{
	PaintUpdateMap::iterator found =  paintEventQueue_.find( control );
	if ( found != paintEventQueue_.end() ) {
		paintEventQueue_.erase( found );
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
*Revision 1.3  2003/05/17 20:37:40  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:45  ddiego
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
*Revision 1.1.2.19  2003/02/09 05:38:54  ddiego
*added a VERY simple editable text control. It is dog slow though, but
*better than nothing.
*
*Revision 1.1.2.18  2003/02/03 05:22:54  ddiego
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
*Revision 1.1.2.17  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.1.2.16  2003/01/27 05:04:02  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Revision 1.1.2.15  2003/01/23 04:38:25  ddiego
*fixes to x port - issues with lightweight controls not quite drawing right. - a
*bug in the line drawing code when the origin is not 0,0
*
*Revision 1.1.2.14  2003/01/19 20:18:21  ddiego
*changes to try and optimize painting. didn't work for this go around :(
*
*Revision 1.1.2.13  2003/01/19 03:12:00  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.1.2.12  2003/01/13 04:57:03  ddiego
*added a fix for the X11COntext::gettextWidth and Height, now returns correct values
*static makefile for the various kits is now ready to use for all
*AbstractX11Controll::keepMouseEvents is now working correctly
*
*Revision 1.1.2.11  2003/01/11 23:17:25  ddiego
*added extra functionality to the static makefile in vcf/build/make
*added some bug fixes to X11
*
*Revision 1.1.2.10  2003/01/04 06:12:25  ddiego
*fixed a crash in X11GraphicsToolkit - an error in how colors were being freed
*added support for titles, getting the focus control, and grabbing the mouse !
*
*Revision 1.1.2.9  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.1.2.8  2003/01/02 04:07:46  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.1.2.7  2003/01/01 05:06:29  ddiego
*changes start propagating VCF::Event instances back into the main Control
*event loop from native X11 events.
*
*Revision 1.1.2.6  2002/12/31 07:02:19  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.1.2.5  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.1.2.4  2002/12/27 06:44:45  ddiego
*added initial control peer for X11 controls
*
*Revision 1.1.2.3  2002/12/26 04:32:12  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Revision 1.1.2.2  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*/


