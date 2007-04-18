
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/ApplicationKit/XCBMenuManagerPeer.h"
#include "vcf/ApplicationKit/XCBMenuBarPeer.h"
#include "vcf/ApplicationKit/XCBUIShellPeer.h"
#include "vcf/ApplicationKit/XCBApplicationPeer.h"
#include "vcf/ApplicationKit/XCBApplicationResourceBundlePeer.h"
#include "vcf/ApplicationKit/XCBCursorPeer.h"
#include "vcf/ApplicationKit/XCBWindowPeer.h"
#include "vcf/ApplicationKit/XCBControlContextPeer.h"

#include "vcf/ApplicationKit/XCBUIMetricsManager.h"
#include "vcf/ApplicationKit/XCBButton.h"



using namespace VCF;

XCBUIToolkit::XCBUIToolkit() :
consoleQuitHandlerCalled_(false)
{
	metricsMgr_ = new XCBUIMetricsManager();
	signal(SIGINT, XCBUIToolkit::consoleQuitHandler );
}

ControlPeer* XCBUIToolkit::internal_createControlPeer( Control* component, ComponentType componentType )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

ContextPeer* XCBUIToolkit::internal_createContextPeer( Control* control )
{
	return new XCBControlContextPeer( control->getPeer() );
}

ListviewPeer* XCBUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

TreePeer* XCBUIToolkit::internal_createTreePeer( TreeControl* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

TextPeer* XCBUIToolkit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

TextEditPeer* XCBUIToolkit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

ButtonPeer* XCBUIToolkit::internal_createButtonPeer( CommandButton* button )
{
	return new XCBButton(button);
}

DialogPeer* XCBUIToolkit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

DialogPeer* XCBUIToolkit::internal_createDialogPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

WindowPeer* XCBUIToolkit::internal_createWindowPeer( Control* component, Control* owner )
{
	return new XCBWindowPeer( component , owner );
}

ToolbarPeer* XCBUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

MenuItemPeer* XCBUIToolkit::internal_createMenuItemPeer( MenuItem* item )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

MenuBarPeer* XCBUIToolkit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return new XCBMenuBarPeer( menuBar );
}

PopupMenuPeer* XCBUIToolkit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

ClipboardPeer* XCBUIToolkit::internal_createClipboardPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

DragDropPeer* XCBUIToolkit::internal_createDragDropPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

DataObjectPeer* XCBUIToolkit::internal_createDataObjectPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

DropTargetPeer* XCBUIToolkit::internal_createDropTargetPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

ApplicationPeer* XCBUIToolkit::internal_createApplicationPeer()
{
	return new XCBApplicationPeer();
}

CommonFileDialogPeer* XCBUIToolkit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CommonFolderBrowseDialogPeer* XCBUIToolkit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CommonFileDialogPeer* XCBUIToolkit::internal_createCommonFileSaveDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CommonColorDialogPeer* XCBUIToolkit::internal_createCommonColorDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CommonFontDialogPeer* XCBUIToolkit::internal_createCommonFontDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CommonPrintDialogPeer* XCBUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

UIShellPeer* XCBUIToolkit::internal_createUIShellPeer( UIShell* shell )
{
	return new XCBUIShellPeer( shell );
}

ScrollPeer* XCBUIToolkit::internal_createScrollPeer( Control* control )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

CursorPeer* XCBUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
	return new XCBCursorPeer( cursor );
}

SystemTrayPeer* XCBUIToolkit::internal_createSystemTrayPeer()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

MenuManagerPeer* XCBUIToolkit::internal_createMenuManagerPeer()
{
	return new XCBMenuManagerPeer();
}

GraphicsResourceBundlePeer* XCBUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new XCBApplicationResourceBundlePeer( app );
}

bool XCBUIToolkit::internal_createCaret( Control* owningControl, Image* caretImage )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

bool XCBUIToolkit::internal_destroyCaret( Control* owningControl )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBUIToolkit::internal_setCaretVisible( const bool& caretVisible )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_setCaretPos( Point* point )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_unregisterTimerHandler( EventHandler* handler )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_runEventLoop()
{
	GraphicsToolkit* graphicsToolkit = GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	XCBGraphicsToolkit* xcbGraphicsToolkit = dynamic_cast<XCBGraphicsToolkit*>(graphicsToolkit);
	if(xcbGraphicsToolkit != NULL)
	{
		xcb_connection_t* connection = xcbGraphicsToolkit->getConnection();

		bool done = false;
		while(!done) {

			if(consoleQuitHandlerCalled_) {
				done = true;
				break;
			}

			xcb_generic_event_t *event = NULL;


			bool moreEvents = true;
			int exposeCount = 0;

			while( moreEvents ) {
				if ( NULL == event ) {
					event = xcb_wait_for_event( connection );
				}

                event->response_type &= ~0x80;
				switch (event->response_type) {

					case 0: {
						done = handleError( *(xcb_generic_error_t*)event );
					}
					break;

					case XCB_CLIENT_MESSAGE: {
						handleClientMessage( connection, *(xcb_client_message_event_t*)event );
					}
					break;

					case XCB_CONFIGURE_NOTIFY: {
						handleConfigureNotify( connection, *(xcb_configure_notify_event_t*)event );
					}
					break;

					case XCB_EXPOSE: {
						handleExpose( *(xcb_expose_event_t*)event );
						exposeCount ++;
					}
					break;

					case XCB_BUTTON_RELEASE: case XCB_BUTTON_PRESS: case XCB_MOTION_NOTIFY:
						case XCB_ENTER_NOTIFY: case XCB_LEAVE_NOTIFY: {
						XCBWindowPeer::internal_handleMouseEvents( *connection, *event );
					}
					break;


					case XCB_KEY_PRESS:  case XCB_KEY_RELEASE:  {
						XCBWindowPeer::internal_handleKeyboardEvents( *connection, *event );
					}
					break;

					case XCB_DESTROY_NOTIFY: {
						handleDestroyNotify( connection, *(xcb_destroy_notify_event_t*)event);
						done = true;
					}
					break;

					default: {
						handleDefault(*event);
					}
					break;
				}

				::free (event);
				event = xcb_poll_for_event( connection );
				moreEvents = (NULL != event) ? true : false;
			}

			if(xcb_connection_has_error(connection)) {
				done = handlePollForEventError();
			}

			if( !done && (exposeCount > 0) ) {
			    static unsigned int count = 0;
				handleExposes(connection);
				printf( "handleExposes called %u times!\n", count );
				count ++;
				exposeCount = 0;
			}
		}
	}
}

UIToolkit::ModalReturnType XCBUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return UIToolkit::mrNone;
}

void XCBUIToolkit::internal_quitCurrentEventLoop()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}


uint32 translateButtonMask( uint32 state )
{
	uint32 result = 0;

	if ( state & XCB_BUTTON_MASK_1 ) {
		result |= VCF::mbmLeftButton;
	}
	if ( state & XCB_BUTTON_MASK_2 ) {
		result |= VCF::mbmMiddleButton;
	}
	if ( state & XCB_BUTTON_MASK_3 ) {
		result |= VCF::mbmRightButton;
	}

	return result;
}

uint32 translateKeyMask( uint32 state )
{
	uint32 result = VCF::kmUndefined;

	if ( state & XCB_MOD_MASK_SHIFT ) {
		result |= VCF::kmShift;
	}
	if ( state & XCB_MOD_MASK_CONTROL ) {
		result |= VCF::kmCtrl;
	}

	if ( state & XCB_MOD_MASK_1 ) {
		result |= VCF::kmAlt;
	}

	//need to figure out the Alt key.....

	return result;
}


Event* XCBUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
	Event* result = NULL;
	XCBEventMessage* message = (XCBEventMessage*)eventData;

	VCF_ASSERT(NULL != message);
	VCF_ASSERT(NULL != message->event);
	VCF_ASSERT(NULL != message->control);

	switch ( message->event->response_type ) {
		case XCB_CONFIGURE_NOTIFY: {
			//VCF::Size sz( message->event->width, message->event->height );
			//result = new ControlEvent( message->control, sz );
			//not handled here....
		}
		break;

		case XCB_DESTROY_NOTIFY: {
			result = new VCF::ComponentEvent( message->control, Component::COMPONENT_DESTROYED );
		}
		break;

		case XCB_BUTTON_PRESS : {
			xcb_button_press_event_t* ev = (xcb_button_press_event_t*)message->event;
			VCF::Point pt( ev->event_x, ev->event_y );

			Scrollable* scrollable = message->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent ( message->control,
											Control::MOUSE_DOWN,
											translateButtonMask( ev->state ),
											translateKeyMask( ev->state ),
											&pt );
		}
		break;

		case XCB_BUTTON_RELEASE : {
			xcb_button_release_event_t* ev = (xcb_button_release_event_t*)message->event;

			VCF::Point pt( ev->event_x, ev->event_y );

			Scrollable* scrollable = message->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent ( message->control,
											Control::MOUSE_UP,
											translateButtonMask( ev->state ),
											translateKeyMask( ev->state ),
											&pt );
		}
		break;

		case XCB_MOTION_NOTIFY : {
			xcb_motion_notify_event_t* ev = (xcb_motion_notify_event_t*)message->event;

			VCF::Point pt( ev->event_x, ev->event_y );

			Scrollable* scrollable = message->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}


			result = new VCF::MouseEvent( message->control,
											Control::MOUSE_MOVE,
											translateButtonMask( ev->state ),
											translateButtonMask( ev->state ),
											&pt );
		}
		break;

		case XCB_ENTER_NOTIFY : {
			xcb_enter_notify_event_t* ev = (xcb_enter_notify_event_t*)message->event;

			VCF::Point pt( ev->event_x, ev->event_y );

			Scrollable* scrollable = message->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}

			result = new VCF::MouseEvent( message->control,
											Control::MOUSE_ENTERED,
											translateButtonMask( ev->state ),
											translateButtonMask( ev->state ),
											&pt );
		}
		break;

		case XCB_LEAVE_NOTIFY : {
			xcb_leave_notify_event_t* ev = (xcb_leave_notify_event_t*)message->event;

			VCF::Point pt( ev->event_x, ev->event_y );

			Scrollable* scrollable = message->control->getScrollable();
			if ( NULL != scrollable ) {
				pt.x_ += scrollable->getHorizontalPosition();
				pt.y_ += scrollable->getVerticalPosition();
			}


			result = new VCF::MouseEvent( message->control,
											Control::MOUSE_LEAVE,
											translateButtonMask( ev->state ),
											translateButtonMask( ev->state ),
											&pt );
		}
		break;

		case XCB_KEY_PRESS : {

		}
		break;

		case XCB_KEY_RELEASE : {

		}
		break;
	}

	return result;
}

Size XCBUIToolkit::internal_getDragDropDelta()
{
	//this is completely arbitrary - need to read this from a file
	Size result(4,4);

	return result;
}

void XCBUIToolkit::internal_displayHelpContents( const String& helpBookName, const String& helpDirectory )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBUIToolkit::internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBUIToolkit::internal_systemSettingsChanged()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBUIToolkit::consoleQuitHandler( int sig )
{
	signal(sig, SIG_IGN);
	UIToolkit* toolkit = UIToolkit::internal_getDefaultUIToolkit();

	XCBUIToolkit* xcbUIToolkit = dynamic_cast<XCBUIToolkit*>(toolkit);
	if(xcbUIToolkit != NULL)
	{
		xcbUIToolkit->consoleQuitHandlerCalled_ = true;
	}
}

namespace
{
	struct SequenceFind
	{
		explicit SequenceFind(uint16 sq) : sequence_(sq) {}
		bool operator()(const XCBUIToolkit::XCBCookieInfo &info) const
		{
			return info.cookie.sequence == sequence_;
		}

		uint16 sequence_;
	};
}

bool XCBUIToolkit::handleError( const xcb_generic_error_t& err )
{
	XCBCookieInfoVector::iterator it = std::find_if(cookieInfos_.begin(), cookieInfos_.end(), SequenceFind(err.sequence));
	if(it != cookieInfos_.end()) {
		StringUtils::trace(Format("Error Code      : %i\n"
								  "Sequence Number : %i\n"
								  "Extra Info : %s\n") % err.error_code % err.sequence % it->extraInfo);

	}
	else {
		StringUtils::trace(Format("Error Code      : %i\n"
								  "Sequence Number : %i\n") % err.error_code % err.sequence);
		StringUtils::trace("NO EXTRA INFO\n");
	}
	return false;
}

void XCBUIToolkit::handleClientMessage( xcb_connection_t* connection, const xcb_client_message_event_t& event )
{
	XCBWindowPeer::internal_handleClientMessageEvent(*connection, event);
}

void XCBUIToolkit::handleConfigureNotify( xcb_connection_t* connection, const xcb_configure_notify_event_t& event )
{
	XCBWindowPeer::internal_handleConfigureNotifyEvent(*connection, event);
}

void XCBUIToolkit::handleExpose( const xcb_expose_event_t& event )
{
	exposeEvents_[event.window] = event;
}

void XCBUIToolkit::handleExposes(xcb_connection_t* connection)
{
	ExposeEventXIDMap::iterator it =  exposeEvents_.begin();
	while ( it != exposeEvents_.end() ) {
		XCBWindowPeer::internal_handleExposeEvent(*connection, it->second);
		it ++;
	}
	exposeEvents_.clear();
}

void XCBUIToolkit::handleDestroyNotify( xcb_connection_t* connection, const xcb_destroy_notify_event_t& event )
{
	XCBWindowPeer::internal_handleDestroyNotify(*connection, event);
}

void XCBUIToolkit::handleDefault( const xcb_generic_event_t& event )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBUIToolkit::handlePollForEventError()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBUIToolkit::internal_addVoidCookie( const xcb_void_cookie_t &cookie, const String &extraInfo )
{
	XCBCookieInfo info = { cookie, extraInfo };
	cookieInfos_.push_back(info);
}

PopupWindowPeer* XCBUIToolkit::internal_createPopupWindowPeer( Frame* frame, Window* owner )
{
    return NULL;
}

TransparentWindowPeer* XCBUIToolkit::internal_createTransparentWindowPeer( Frame* frame )
{
    return NULL;
}

/**
$Id$
*/

