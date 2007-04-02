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

#define VCF_PROPERTY_CREATOR			'VCFA'
#define VCF_PROPERTY_CONTROL_VAL		'VCFc'
#define VCF_PROPERTY_WINDOW_VAL			'VCFw'

#define VCF_WINDOW_MOUSE_RGN			'VCfW'
#define VCF_CONTROL_MOUSE_RGN			'VCfC'

class OSXUIUtils {
public:
static VCF::uint32 translateButtonMask( EventMouseButton button );

static VCF::uint32 translateKeyMask( UInt32 keyMod );

};


template <typename ViewType >
class ViewCreator {
public:

	static OSStatus create( HIViewRef* outControl,
							const HIRect* inBounds = NULL,
							WindowRef inWindow = NULL ) {

		OSStatus			err;
		EventRef			event = TObject::CreateInitializationEvent();
		
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
				//GetRootControl( inWindow, &root );
				//HIViewAddSubview( root, *outControl );
			}

			//HIViewSetFrame( *outControl, inBounds );
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
        SizeOfDeletePostedEvent = sizeof(Boolean),
		cmdRetry = 'VRty',
		cmdAbort = 'VAbt',
		cmdIgnore = 'VIgn',
		cmdYes = 'VYes',
		cmdNo = 'VNo '
    };

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

	virtual void internal_postEvent( VCF::EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void internal_registerTimerHandler( Object* source, VCF::EventHandler* handler, const uint32& timeoutInMilliSeconds );

	virtual void internal_unregisterTimerHandler( VCF::EventHandler* handler );

	virtual void internal_runEventLoop();

	virtual ModalReturnType internal_runModalEventLoopFor( Control* control );

	virtual void internal_quitCurrentEventLoop();

	virtual void internal_systemSettingsChanged();
	/**
	*@param void* in this implementation, the eventData represents a
	*pointer to an OSX EventRef structure.
	*/
	virtual VCF::Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory );

	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection );
	
	static EventRef createUserCarbonEvent( UInt32 eventType );
protected:
	//VirtualKeyCode translateKeyCode( guint code );
	//uint32 translateKeyMask( GdkModifierType keyState );
	//uint32 translateButtonMask( GdkModifierType buttonState );

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


#endif // _VCF_OSXUITOOLKIT_H__

/**
$Id$
*/
