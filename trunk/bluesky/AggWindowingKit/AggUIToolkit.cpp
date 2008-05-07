
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

#if defined(VCF_WIN)
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#endif 


#include "AggUIToolkit.h"

#include "AggMenuManagerPeer.h"
#include "AggMenuBarPeer.h"
#include "AggUIShellPeer.h"
#include "AggApplicationPeer.h"
#include "AggApplicationResourceBundlePeer.h"
#include "AggCursorPeer.h"
#include "AggWindowPeer.h"
#include "AggControlContextPeer.h"

#include "AggUIMetricsManager.h"
#include "AggButton.h"



using namespace VCF;

AggUIToolkit::AggUIToolkit() 
{
	metricsMgr_ = new AggUIMetricsManager();
}

ControlPeer* AggUIToolkit::internal_createControlPeer( Control* component, ComponentType componentType )
{
	
	return NULL;
}

ContextPeer* AggUIToolkit::internal_createContextPeer( Control* control )
{
	return new AggControlContextPeer( control->getPeer() );
}

ListviewPeer* AggUIToolkit::internal_createListViewPeer( ListViewControl* component )
{
	return NULL;
}

TreePeer* AggUIToolkit::internal_createTreePeer( TreeControl* component )
{
	return NULL;
}

TextPeer* AggUIToolkit::internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined )
{
	return NULL;
}

TextEditPeer* AggUIToolkit::internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl )
{
	return NULL;
}

ButtonPeer* AggUIToolkit::internal_createButtonPeer( CommandButton* button )
{
	return new AggButton(button);
}

DialogPeer* AggUIToolkit::internal_createDialogPeer( Control* owner, Dialog* component )
{
	return NULL;
}

DialogPeer* AggUIToolkit::internal_createDialogPeer()
{
	return NULL;
}

WindowPeer* AggUIToolkit::internal_createWindowPeer( Control* component, Control* owner )
{
	return new AggWindowPeer( component , owner );
}

ToolbarPeer* AggUIToolkit::internal_createToolbarPeer( Toolbar* toolbar )
{
	return NULL;
}

MenuItemPeer* AggUIToolkit::internal_createMenuItemPeer( MenuItem* item )
{
	return NULL;
}

MenuBarPeer* AggUIToolkit::internal_createMenuBarPeer( MenuBar* menuBar )
{
	return new AggMenuBarPeer( menuBar );
}

PopupMenuPeer* AggUIToolkit::internal_createPopupMenuPeer( PopupMenu* popupMenu )
{
	return NULL;
}

ClipboardPeer* AggUIToolkit::internal_createClipboardPeer()
{
	return NULL;
}

DragDropPeer* AggUIToolkit::internal_createDragDropPeer()
{
	return NULL;
}

DataObjectPeer* AggUIToolkit::internal_createDataObjectPeer()
{
	return NULL;
}

DropTargetPeer* AggUIToolkit::internal_createDropTargetPeer()
{
	return NULL;
}

ApplicationPeer* AggUIToolkit::internal_createApplicationPeer()
{
	return new AggApplicationPeer();
}

CommonFileDialogPeer* AggUIToolkit::internal_createCommonFileOpenDialogPeer( Control* owner )
{
	return NULL;
}

CommonFolderBrowseDialogPeer* AggUIToolkit::internal_createCommonFolderBrowseDialogPeer( Control* owner )
{
	return NULL;
}

CommonFileDialogPeer* AggUIToolkit::internal_createCommonFileSaveDialogPeer( Control* owner )
{

	return NULL;
}

CommonColorDialogPeer* AggUIToolkit::internal_createCommonColorDialogPeer( Control* owner )
{
	return NULL;
}

CommonFontDialogPeer* AggUIToolkit::internal_createCommonFontDialogPeer( Control* owner )
{
	return NULL;
}

CommonPrintDialogPeer* AggUIToolkit::internal_createCommonPrintDialogPeer( Control* owner )
{
	return NULL;
}

UIShellPeer* AggUIToolkit::internal_createUIShellPeer( UIShell* shell )
{
	return new AggUIShellPeer( shell );
}

ScrollPeer* AggUIToolkit::internal_createScrollPeer( Control* control )
{
	return NULL;
}

DropDownPeer* AggUIToolkit::internal_createDropDownPeer( Control* control )
{
	return NULL;
}


CursorPeer* AggUIToolkit::internal_createCursorPeer( Cursor* cursor )
{
	return new AggCursorPeer( cursor );
}

SystemTrayPeer* AggUIToolkit::internal_createSystemTrayPeer()
{
	return NULL;
}

MenuManagerPeer* AggUIToolkit::internal_createMenuManagerPeer()
{
	return new AggMenuManagerPeer();
}

GraphicsResourceBundlePeer* AggUIToolkit::internal_createGraphicsResourceBundlePeer( AbstractApplication* app )
{
	return new AggApplicationResourceBundlePeer( app );
}

bool AggUIToolkit::internal_createCaret( Control* owningControl, Image* caretImage )
{
	return false;
}

bool AggUIToolkit::internal_destroyCaret( Control* owningControl )
{
	return false;
}

void AggUIToolkit::internal_setCaretVisible( const bool& caretVisible )
{
	
}

void AggUIToolkit::internal_setCaretPos( Point* point )
{
	
}

void AggUIToolkit::internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	
}

void AggUIToolkit::internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds )
{
	
}

void AggUIToolkit::internal_unregisterTimerHandler( EventHandler* handler )
{
	
}

void AggUIToolkit::internal_runEventLoop()
{
	
}

UIToolkit::ModalReturnType AggUIToolkit::internal_runModalEventLoopFor( Control* control )
{
	
	return UIToolkit::mrNone;
}

void AggUIToolkit::internal_quitCurrentEventLoop()
{
	
}


uint32 translateButtonMask( uint32 state )
{
	uint32 result = 0;

	

	return result;
}

uint32 translateKeyMask( uint32 state )
{
	uint32 result = VCF::kmUndefined;

	

	//need to figure out the Alt key.....

	return result;
}



Size AggUIToolkit::internal_getDragDropDelta()
{
	//this is completely arbitrary - need to read this from a file
	Size result(4,4);

	return result;
}

void AggUIToolkit::internal_displayHelpContents( const String& helpBookName, const String& helpDirectory )
{
	
}

void AggUIToolkit::internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory )
{
	
}

void AggUIToolkit::internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection )
{
	
}

bool AggUIToolkit::internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory )
{
	return false;
}

void AggUIToolkit::internal_systemSettingsChanged()
{
	
}

PopupWindowPeer* AggUIToolkit::internal_createPopupWindowPeer( Frame* frame, Window* owner )
{
    return NULL;
}

TransparentWindowPeer* AggUIToolkit::internal_createTransparentWindowPeer( Frame* frame )
{
    return NULL;
}

Event* AggUIToolkit::internal_createEventFromNativeOSEventData( void* eventData )
{
	Event* result = NULL;

	return result;
}

/**
$Id$
*/

