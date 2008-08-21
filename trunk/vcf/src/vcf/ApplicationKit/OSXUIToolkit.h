#ifndef _VCF_OSXUITOOLKIT_H__
#define _VCF_OSXUITOOLKIT_H__
//OSXUIToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include <Cocoa/Cocoa.h>


namespace VCF {






/**
this class is used as a wrapper around an XEvent.
*/
class OSXEventMsg {
public:
	OSXEventMsg(): event(NULL),view(nil), control(NULL){}
	NSEvent* event;
	NSView* view;
	Control* control;
};



/**
*/
class OSXUIToolkit :  public UIToolkit {
public:
    
	OSXUIToolkit();

	virtual ~OSXUIToolkit();

	virtual ApplicationPeer* internal_createApplicationPeer();

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined );

    virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl );
	
	virtual TreePeer* internal_createTreePeer( TreeControl* component );

	virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component );

	virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component );

	virtual DialogPeer* internal_createDialogPeer();

	virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType);

	virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner );
    
    virtual PopupWindowPeer* internal_createPopupWindowPeer( Frame* frame, Window* owner );
    
	virtual TransparentWindowPeer* internal_createTransparentWindowPeer( Frame* frame );
	
	virtual DropDownPeer* internal_createDropDownPeer( Control* control );
	
	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar );

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ButtonPeer* internal_createButtonPeer( CommandButton* component );

	virtual ContextPeer* internal_createContextPeer( Control* component );

	virtual CommonFileDialogPeer* internal_createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* internal_createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* internal_createCommonColorDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* internal_createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* internal_createCommonFontDialogPeer( Control* owner );

	virtual CommonPrintDialogPeer* internal_createCommonPrintDialogPeer( Control* owner );
    
   	virtual UIShellPeer* internal_createUIShellPeer( UIShell* shell );

	virtual DragDropPeer* internal_createDragDropPeer();

	virtual DataObjectPeer* internal_createDataObjectPeer();

	virtual DropTargetPeer* internal_createDropTargetPeer();

	virtual ScrollPeer* internal_createScrollPeer( Control* control );

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer( AbstractApplication* app );
	
	virtual SystemTrayPeer* internal_createSystemTrayPeer();
	
	virtual  MenuManagerPeer* internal_createMenuManagerPeer();

	virtual CursorPeer* internal_createCursorPeer( Cursor* cursor );

	virtual ClipboardPeer* internal_createClipboardPeer();

	virtual bool internal_createCaret( Control* owningControl, Image* caretImage  );

	virtual bool internal_destroyCaret( Control* owningControl );

	virtual void internal_setCaretVisible( const bool& caretVisible );

	virtual void internal_setCaretPos( Point* point );

	virtual void internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds );

	virtual void internal_unregisterTimerHandler( EventHandler* handler );

	virtual void internal_runEventLoop();

	virtual ModalReturnType internal_runModalEventLoopFor( Control* control );

	virtual void internal_quitCurrentEventLoop();

	virtual void internal_systemSettingsChanged();
	
	virtual Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory );

	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection );	
protected:
	
    bool handleAppEvents( NSEvent* event );

	std::map<EventHandler*,NSTimer*> timeoutHandlers_;
    bool quitEventLoop_;
	
    
	NSObject* toolkitDelegate_;
	CFRunLoopObserverRef rlObserver_;
	DateTime lastRLDate_;
	
	
	static void handleRunLoopObserver ( CFRunLoopObserverRef observer, CFRunLoopActivity activity, 
									   void *info );
	
};


}; //end of namespace VCF


#endif // _VCF_OSXUITOOLKIT_H__

/**
$Id$
*/
