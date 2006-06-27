#ifndef _VCF_GTKUITOOLKIT_H__
#define _VCF_GTKUITOOLKIT_H__ 
//GTKUIToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include <deque>

namespace VCF
{

class AbstractX11Control;

/**
this class is used as a wrapper around an XEvent.
*/
class GTKEventMsg
{
public:
	GTKEventMsg( GdkEvent* event, Control* control ) : gdkEvent_( event ), control_( control )
	{}


	GdkEvent* gdkEvent_;
	Control* control_;
};



class TimeOutHandler
{
public:
	TimeOutHandler() : source_( NULL ), handler_( NULL ), timerID_( 0 )
	{}

	Object* source_;
	EventHandler* handler_;
	guint timerID_;
};

/**
*/
class GTKUIToolkit : public UIToolkit
{
public:

	GTKUIToolkit();

	virtual ~GTKUIToolkit();

	virtual ApplicationPeer* internal_createApplicationPeer();

	virtual TextPeer* internal_createTextPeer( TextControl* component, const bool& isMultiLineControl, ComponentType componentType = CT_DEFAULT );

	virtual DialogPeer* internal_createDialogPeer();

	virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType );

	virtual WindowPeer* internal_createWindowPeer( Control* component,
	                                               Control* owner );

	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar );

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ContextPeer* internal_createContextPeer( Control* component );

	virtual CommonFileDialogPeer* internal_createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* internal_createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* internal_createCommonColorDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* internal_createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* internal_createCommonFontDialogPeer( Control* owner );

	virtual DragDropPeer* internal_createDragDropPeer();

	virtual DataObjectPeer* internal_createDataObjectPeer();

	virtual DropTargetPeer* internal_createDropTargetPeer();

	virtual DesktopPeer* internal_createDesktopPeer( Desktop* desktop );

	virtual ScrollPeer* internal_createScrollPeer( Control* control );

	virtual CursorPeer* internal_createCursorPeer( Cursor* cursor );

	virtual ClipboardPeer* internal_createClipboardPeer();

	virtual bool internal_createCaret( Control* owningControl, Image* caretImage );

	virtual bool internal_destroyCaret( Control* owningControl );

	virtual void internal_setCaretVisible( const bool& caretVisible );

	virtual void internal_setCaretPos( Point* point );

	virtual void internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds );

	virtual void internal_unregisterTimerHandler( EventHandler* handler );

	virtual void internal_runEventLoop();

	virtual ModalReturnType internal_runModalEventLoopFor( Control* control );

	virtual void internal_quitCurrentEventLoop();

	/**
	*@param void* in this implementation, the eventData represents a
	*pointer to an GTK Event structure.
	*/
	virtual VCF::Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();

	GtkWidget* getDefaultParent()
	{
		return defaultParent_;
	}

	virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component );

	virtual TreePeer* internal_createTreePeer( TreeControl* component );

	virtual TextPeer* internal_createTextPeer( TextControl* component,
	                                           const bool& isMultiLineControl );

	virtual ButtonPeer* internal_createButtonPeer( CommandButton* component );

	virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component );

	virtual CommonPrintDialogPeer* internal_createCommonPrintDialogPeer( Control* owner );

	virtual SystemTrayPeer* internal_createSystemTrayPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer( AbstractApplication* app );

	static void internal_gdkEventHandler( GdkEvent* gdkEvent, gpointer data );

	static gboolean internal_gdkIdleHandler( gpointer data );

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined );

	virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl );

	virtual  MenuManagerPeer* internal_createMenuManagerPeer();

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection );

	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory );

	virtual void internal_systemSettingsChanged();

protected:
	VirtualKeyCode translateKeyCode( guint code );
	uint32 translateKeyMask( GdkModifierType keyState );
	uint32 translateButtonMask( GdkModifierType buttonState );

	bool handleGdkEvent( GdkEvent* gdkEvent );
	void createDefaultParentWnd();
	GtkWidget* defaultParent_;
	static gboolean gtkTimeOutHandler( gpointer data );

	std::map<EventHandler*, TimeOutHandler> timeoutHandlers_;
};


} //end of namespace VCF


#endif // _VCF_GTKUITOOLKIT_H__

/**
$Id$
*/
