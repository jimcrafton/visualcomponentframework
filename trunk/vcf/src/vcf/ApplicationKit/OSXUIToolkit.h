#ifndef _VCF_OSXUITOOLKIT_H__
#define _VCF_OSXUITOOLKIT_H__
//OSXUIToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "thirdparty/macOSX/HIView/TCarbonEvent.h"
#include "thirdparty/macOSX/HIView/TView.h"



template <typename ViewType >
class ViewCreator {
public:

	static OSStatus create( HIViewRef* outControl,
							const HIRect* inBounds = NULL,
							WindowRef inWindow = NULL ) {

		OSStatus			err;
		EventRef			event = TObject::CreateInitializationEvent();
		ControlRef			root = NULL;

		// Register this class
		VCF::CFTextString classID;
		VCF::String className = VCF::StringUtils::getClassNameFromTypeInfo( typeid(ViewType) );
		classID = className;

		ViewCreator<ViewType>::RegisterClass(classID);


		// Make a new instantiation of this class
		err = HIObjectCreate( classID, event, (HIObjectRef*) outControl );

		ReleaseEvent( event );

		if ( err == noErr ) {
			if ( inWindow != NULL ) {
				GetRootControl( inWindow, &root );
				HIViewAddSubview( root, *outControl );
			}

			HIViewSetFrame( *outControl, inBounds );
		}
		return err;
	}

	static void RegisterClass( CFStringRef classID ) {
		static bool sRegistered;

		if ( !sRegistered ) {

			TView::RegisterSubclass( classID, ViewCreator<ViewType>::Constructor );
			sRegistered = true;
		}
	}

	static OSStatus	Constructor( HIObjectRef inObjectRef,
	                           TObject** outObject ) {

		*outObject = new ViewType( (HIViewRef) inObjectRef );

		return noErr;
	}
};




namespace VCF {






/**
this class is used as a wrapper around an XEvent.
*/
class OSXEventMsg {
public:
	OSXEventMsg( EventRef event, Control* control ): osxEvent_(event), control_(control) {}


	EventRef osxEvent_;
	Control* control_;
};



class TimeOutHandler {
public:
	TimeOutHandler():source_(NULL), handler_(NULL), timerRef_(0) {

	}

	Object* source_;
	EventHandler* handler_;
	EventLoopTimerRef timerRef_;
};

/**
*/
class OSXUIToolkit :  public UIToolkit {
public:
    enum {
        CustomEventClass = 'vcfc', //VCF Event Class
        EventPosted = 'vcpe', //Event fired when the toolkit's postEvent is called
        EventHandler = 'hdlr', //Event handler name for postEvent event
        EventHandlerEvent = 'hdev', //Event handler event name for a postEvent
        DeletePostedEvent = 'dele', //indicates whether to delete an event created for postEvent
        SizeOfEventHandler = sizeof(UInt32),
        SizeOfEventHandlerEvent = sizeof(UInt32),
        SizeOfDeletePostedEvent = sizeof(Boolean)


    };

	OSXUIToolkit();

	virtual ~OSXUIToolkit();

	virtual ApplicationPeer* internal_createApplicationPeer();

	virtual TextPeer* internal_createTextPeer( TextControl* component, const bool& isMultiLineControl, ComponentType componentType=CT_DEFAULT);

	virtual TreePeer* internal_createTreePeer( TreeControl* component, ComponentType componentType=CT_DEFAULT);

	virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component, ComponentType componentType=CT_DEFAULT);

	virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component, ComponentType componentType=CT_DEFAULT );

	virtual DialogPeer* internal_createDialogPeer();

	virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType);

	virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner, ComponentType componentType);

	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar );

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ButtonPeer* internal_createButtonPeer( CommandButton* component, ComponentType componentType);

	virtual HTMLBrowserPeer* internal_createHTMLBrowserPeer( Control* control );

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

	virtual bool internal_createCaret( Control* owningControl, Image* caretImage  );

	virtual bool internal_destroyCaret( Control* owningControl );

	virtual void internal_setCaretVisible( const bool& caretVisible );

	virtual void internal_setCaretPos( Point* point );

	virtual void internal_postEvent( VCF::EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void internal_registerTimerHandler( Object* source, VCF::EventHandler* handler, const ulong32& timeoutInMilliSeconds );

	virtual void internal_unregisterTimerHandler( VCF::EventHandler* handler );

	virtual void internal_runEventLoop();

	virtual ModalReturnType internal_runModalEventLoopFor( Control* control );

	virtual void internal_quitCurrentEventLoop();

	/**
	*@param void* in this implementation, the eventData represents a
	*pointer to an OSX EventRef structure.
	*/
	virtual VCF::Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();


	//static void  internal_osxEventHandler( EventRef osxEvent, gpointer data);

	//static gboolean internal_gdkIdleHandler(gpointer data);
    static EventRef createUserCarbonEvent( UInt32 eventType );
protected:
	//VirtualKeyCode translateKeyCode( guint code );
	//ulong32 translateKeyMask( GdkModifierType keyState );
	//ulong32 translateButtonMask( GdkModifierType buttonState );

	static OSStatus handleOSXApplicationEvents( EventHandlerCallRef nextHandler,
                                                EventRef osxEvent, void* userData );

    OSStatus handleAppEvents( EventHandlerCallRef nextHandler, EventRef osxEvent );

	std::map<EventLoopTimerRef,TimeOutHandler> timeoutHandlers_;
    bool quitEventLoop_;
    EventHandlerRef eventHandlerRef_;
    EventHandlerUPP handlerUPP_;
    EventLoopTimerUPP timerUPP_;
    EventLoopIdleTimerUPP idleTimerUPP_;
    EventLoopTimerRef idleTimerRef_;
    void processOSXEvent( EventRecord* eventRec );

    static void handleTimerEvent( EventLoopTimerRef inTimer, void * inUserData );
    static void handleIdleTimer( EventLoopTimerRef inTimer, EventLoopIdleTimerMessage inState, void *inUserData );


};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/16 02:39:01  ddiego
*OSX code updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/25 05:17:55  ddiego
*updates to ApplicationKit to support posting events and timer and idle time handlers for the OSX UI Toolkit.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXUITOOLKIT_H__


