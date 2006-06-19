
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/ApplicationKit/XCBMenuManagerPeer.h"
#include "vcf/ApplicationKit/XCBMenuBarPeer.h"
#include "vcf/ApplicationKit/XCBDesktopPeer.h"
#include "vcf/ApplicationKit/XCBApplicationPeer.h"
#include "vcf/ApplicationKit/XCBApplicationResourceBundlePeer.h"
#include "vcf/ApplicationKit/XCBCursorPeer.h"
#include "vcf/ApplicationKit/XCBWindowPeer.h"
#include "vcf/ApplicationKit/XCBControlContextPeer.h"

#include "vcf/ApplicationKit/XCBUIMetricsManager.h"

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

ButtonPeer* XCBUIToolkit::internal_createButtonPeer( CommandButton* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
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

DesktopPeer* XCBUIToolkit::internal_createDesktopPeer( Desktop* desktop )
{
	return new XCBDesktopPeer( desktop );
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

void XCBUIToolkit::internal_registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds )
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
		XCBConnection* connection = xcbGraphicsToolkit->getConnection();

		bool done = false;
		while(!done) {

			if(consoleQuitHandlerCalled_) {
				done = true;
				break;
			}

			if(XCBFlush(connection) == 0) {
				done = true;
				break;
			}

			XCBGenericEvent *event = NULL;
			int pollForEventError = 0;
			while( (event = XCBPollForEvent( connection, &pollForEventError )) != NULL ) {

                event->response_type &= ~0x80;
				switch (event->response_type)
				{

				case 0:
					done = handleError( *(XCBGenericError*)event );
					break;

				case XCBClientMessage:
					handleClientMessage( connection, *(XCBClientMessageEvent*)event );
					break;

				case XCBConfigureNotify:
					handleConfigureNotify( connection, *(XCBConfigureNotifyEvent*)event );
					break;

				case XCBExpose:
					handleExpose( *(XCBExposeEvent*)event );
					break;

				case XCBDestroyNotify:
					handleDestroyNotify( connection, *(XCBDestroyNotifyEvent*)event);
					done = true;
					break;

				default:
					handleDefault(*event);
					break;
				}

				::free (event);
				event = NULL;
			}

			if(pollForEventError != 0) {
				done = handlePollForEventError();
			}
			if(!done) {
				handleExposes(connection);
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

Event* XCBUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

Size XCBUIToolkit::internal_getDragDropDelta()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Size();	
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
		explicit SequenceFind(CARD16 sq) : sequence_(sq) {}
		bool operator()(const XCBUIToolkit::XCBCookieInfo &info) const
		{
			return info.cookie.sequence == sequence_;
		}

		CARD16 sequence_;
	};
}

bool XCBUIToolkit::handleError( const XCBGenericError& err )
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

void XCBUIToolkit::handleClientMessage( XCBConnection* connection, const XCBClientMessageEvent& event )
{
	XCBWindowPeer::internal_handleClientMessageEvent(*connection, event);
}

void XCBUIToolkit::handleConfigureNotify( XCBConnection* connection, const XCBConfigureNotifyEvent& event )
{
	XCBWindowPeer::internal_handleConfigureNotifyEvent(*connection, event);
}

void XCBUIToolkit::handleExpose( const XCBExposeEvent& event )
{
	exposeEvents_[event.window.xid] = event;
}

void XCBUIToolkit::handleExposes(XCBConnection* connection)
{
	ExposeEventXIDMap::iterator it =  exposeEvents_.begin();
	while ( it != exposeEvents_.end() ) {
		XCBWindowPeer::internal_handleExposeEvent(*connection, it->second);
		it ++;
	}
	exposeEvents_.clear();
}

void XCBUIToolkit::handleDestroyNotify( XCBConnection* connection, const XCBDestroyNotifyEvent& event )
{
	XCBWindowPeer::internal_handleDestroyNotify(*connection, event);
}

void XCBUIToolkit::handleDefault( const XCBGenericEvent& event )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBUIToolkit::handlePollForEventError()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBUIToolkit::internal_addVoidCookie( const XCBVoidCookie &cookie, const String &extraInfo )
{
	XCBCookieInfo info = { cookie, extraInfo };
	cookieInfos_.push_back(info);
}

/**
$Id$
*/

