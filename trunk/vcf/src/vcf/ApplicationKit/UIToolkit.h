#ifndef _VCF_UITOOLKIT_H__
#define _VCF_UITOOLKIT_H__
//UIToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


enum ComponentType{
        CT_DEFAULT=0,
        CT_LIGHTWEIGHT,
        CT_HEAVYWEIGHT
};

namespace VCF{

#define STANDARD_CATEGORY		"Standard"
#define ADDITIONAL_CATEGORY		"Additional"
#define SYSTEM_CATEGORY			"System"
#define DIALOG_CATEGORY			"Dialogs"
#define NETWORKING_CATEGORY		"Networking"
#define BORDER_CATEGORY			"Borders"
#define CONTAINER_CATEGORY		"Containers"
#define MODEL_CATEGORY			"Models"
#define VIEW_CATEGORY			"Views"

class ListviewPeer;
class ComboBoxPeer;
class TextPeer;
class TextEditPeer;
class RichTextPeer;
class ControlPeer;
class TreePeer;
class ButtonPeer;
class ScrollbarPeer;
class TabbedPagesPeer;
class HeaderPeer;
class DialogPeer;
class WindowPeer;
class ToolbarPeer;
class ClipboardPeer;
class DragDropPeer;
class DataObjectPeer;
class DropTargetPeer;
class Component;
class ContextPeer;
class ApplicationPeer;
class TextControl;
class TreeControl;
class ListViewControl;
class Dialog;
class MenuItem;
class MenuItemPeer;
class MenuBar;
class MenuBarPeer;
class ComboBoxControl;
class CommandButton;
class CommonFileDialogPeer;
class CommonColorDialogPeer;
class CommonPrintDialogPeer;
class Color;
class Clipboard;
class GraphicsToolkit;
class PopupMenuPeer;
class PopupMenu;
class Frame;
class Control;
class CommonFolderBrowseDialogPeer;
class CommonFontDialogPeer;

class DesktopPeer;
class Desktop;

class ComponentInfo;
class ScrollPeer;
class AcceleratorKey;
class Button;
class Toolbar;
class TimerEvent;

class SystemTrayPeer;

class MenuManagerPeer;





/**
\class UIToolkit UIToolkit.h "vcf/ApplicationKit/UIToolkit.h"  
The UIToolkit is used to create instances of various peer's needed by the VCF,
as well as providing certain low level services, such as modal and non-modal
event loops, and getting at UI metrics. Each system the VCF is ported to has
a concrete implementation of the UIToolkit. The UIToolkit is a singleton, and
there should only be one instance for a given process running the VCF libraries.

To work with the toolkit you just call it's static functions. These
in turn forward the call to the toolkit instance. 

The UIToolkit is a singleton, meaning there is only ever one single instance of it.
Developers porting the VCF to another platform will have to create a derived class
from UIToolkit and implement the various virtual functions.
*/
class APPLICATIONKIT_API UIToolkit : public ObjectWithEvents {
public:

	/**
	*These enum values specify the various return values that a modal loop can return.
	*The most typical values are mrTrue or mrFalse. If used in conjuction with displaying
	* a modal dialog then some of the other values may come into play ot indicate a
	*common button that was clicked, such as OK, Cancel, Yes, No, etc.
	*/
	enum ModalReturnType {
		mrNone = 0,
		mrOK,
		mrCancel,
		mrYes,
		mrNo,
		mrRetry,
		mrIgnore,
		mrHelp,
		mrAbort,
		mrTrue,
		mrFalse
	};

	enum {
		defaultUpdateSpeed = 200
	};

    UIToolkit();

	virtual ~UIToolkit();

	void init();
	/**
	*Initializes the toolkit. the default toolkit is created and any other initialization
	*functions called
	*/
	static void initToolKit();

	/**
	*cleans up the toolkit instance and deletes it
	*/
	static void closeToolkit();
	/**
	*creates a new instance of a ControlPeer
	*the component passed in represents the component the implmenter will get attached to.
	*/
    static ControlPeer* createControlPeer( Control* component, ComponentType componentType=CT_DEFAULT);

	/**
	creates a context peer for a control
	*/
	static ContextPeer* createContextPeer( Control* component );

	/**
	creates a context peer given a windowing specific context id. This simply
	calls the GraphicsToolkit's createContextPeer().
	@see GraphicsToolkit::createContextPeer
	*/
	static ContextPeer* createContextPeer( OSHandleID contextID );

	/**
	creates a memory based context peer given a width and height.
	This simply	calls the GraphicsToolkit's createContextPeer().
	@see GraphicsToolkit::createContextPeer
	*/
	static ContextPeer* createContextPeer( const unsigned long& width, const unsigned long& height );

	/**
	This creates a peer that implements the ListviewPeer interface. A ListviewPeer allows you to
	view a list of data in multiple ways. For Win32 systems this is equivalent to
	creating a window handle with the WC_LISTVIEW window class name.
	*/
    static ListviewPeer* createListViewPeer( ListViewControl* component);

	/**
	This creates a peer that implements the TreePeer interface. A TreePeer allows you to
	view a data in an outline or hierarchical style. For Win32 systems this is equivalent to
	creating a window handle with the WC_TREEVIEW window class name.
	*/
    static TreePeer* createTreePeer( TreeControl* component);

	
	/**
	This creates a peer that implements the TextPeer interface. A TextPeer allows you to
	view and edit text, either in a single line edit control, or a multiline edit control.
	For Win32 systems this is equivalent to creating a Richedit window handle.
	*/
    static TextPeer* createTextPeer( const bool& autoWordWrap, const bool& multiLined );

	static TextEditPeer* createTextEditPeer( TextControl* component, const bool& isMultiLineControl);

	/**
	This creates a peer that implements the ButtonPeer interface. This ensures that you have a button
	control that correctly implements ALL the look and feel requirements for the windowing system.
	Some windowing systems have a more complex button control than others, making it more complicated
	to try and emulate, as opposed to just providing a peer that creates a native button control.
	For Win32 systems this is equivalent to creating a window handle with the BUTTON window class name.
	*/
    static ButtonPeer* createButtonPeer( CommandButton* component);


    static DialogPeer* createDialogPeer( Control* owner, Dialog* component);

	static DialogPeer* createDialogPeer();

    static WindowPeer* createWindowPeer( Control* component, Control* owner );


	static ToolbarPeer* createToolbarPeer( Toolbar* toolbar );

	static MenuItemPeer* createMenuItemPeer( MenuItem* item );

	static MenuBarPeer* createMenuBarPeer( MenuBar* menuBar );

	static PopupMenuPeer* createPopupMenuPeer( PopupMenu* popupMenu );

    static ClipboardPeer* createClipboardPeer();

    static DragDropPeer* createDragDropPeer();

	static DataObjectPeer* createDataObjectPeer();

	static DropTargetPeer* createDropTargetPeer();

	static ApplicationPeer* createApplicationPeer();

	static Clipboard* getSystemClipboard();

	static CommonFileDialogPeer* createCommonFileOpenDialogPeer( Control* owner );

	static CommonFolderBrowseDialogPeer* createCommonFolderBrowseDialogPeer( Control* owner );

	static CommonFileDialogPeer* createCommonFileSaveDialogPeer( Control* owner );

	static CommonColorDialogPeer* createCommonColorDialogPeer( Control* owner );

	static CommonFontDialogPeer* createCommonFontDialogPeer( Control* owner );

	static CommonPrintDialogPeer* createCommonPrintDialogPeer( Control* owner );
	

	static DesktopPeer* createDesktopPeer( Desktop* desktop );

	static ScrollPeer* createScrollPeer( Control* control );

	static CursorPeer* createCursorPeer( Cursor* cursor );

	static SystemTrayPeer* createSystemTrayPeer();

	static MenuManagerPeer* createMenuManagerPeer();

	static GraphicsResourceBundlePeer* createGraphicsResourceBundlePeer( AbstractApplication* app );

	static bool createCaret( Control* owningControl, Image* caretImage  );

	static bool destroyCaret( Control* owningControl );

	static void setCaretVisible( const bool& caretVisible );

	static void setCaretPos( Point* point );

	/**
	
	This method posts an event to the underlying platform's windowing system. 
	The event handler instance that is passed in is called when the event is 
	processed later on in the event queue. Once this happens the handler's 
	invoke() method is called and the event that was passed in to this method 
	is passed into the EventHandler::invoke() method. Once invoke() returns, 
	the event is deleted and the event handler is delete \em only if the 
	deleteHandler parameter to postEvent() was true, otherwise it is left 
	alone. 
	@param EventHandler the event handler instance to use when the event is 
	retrieved off the event queue later on.
	@param Event the event to pass to the eventHandler's invoke() method. This
	instance is managed by the UIToolkit, and \em must be created on the heap. If
	you create the event instance on the stack you'll corrupt memory and crash
	your program. Consider yourself warned.
	@param bool this parameter tells the UIToolkit whether or not it should 
	delete the event handler instance.	This means that you have a choice when
	calling the postEvent function - you can either have the UIToolkit clean
	up the event handler instance for you (deleteHandler=true), or you can 
	manage this instance yourself. If you choose to let the UIToolkit manage
	the event handler instance, then make sure you don't maintain ownership
	of the event handler. If you are using EventHandlerInstance classes (
	like GenericEventHandler, etc) then you can do the following:
    \code
	//note that we don't pass in a name for the event handler
	EventHandler* ev = new GenericEventHandler<MyClass>( this, &MyClass::onMyEvent ); 
	Event* event = //create some event instance
	UIToolkit::postEvent( ev, event ); //defaults to deleting the event handler
	\endcode 
	Note that in our example above we did \em not give the event handler a name.
	This prevents the event handler from being added to it's source, and insures 
	that it will not be owned, allowing the UIToolkit to safely delete it.
	 
	If we want to manage the event handler ourselves, then we might do the following:
	\code
	//assuming that we are in an object instance that derives from ObjectWithEvents.
	//all control classes do inherit from ObjectWithEvents.
	EventHandler* ev = getEventHandler( "MyClass::onMyEvent" );
	if ( NULL == ev ) {
		ev = new GenericEventHandler<MyClass>( this, &MyClass::onMyEvent ); 
	}
	Event* event = //create some event instance
	UIToolkit::postEvent( ev, event, false ); //defaults to deleting the event handler
	\endcode 

	@see Event
	@see EventHandler
	@see EventHandlerInstance
	*/
	static void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true );

	static void registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds );

	static void unregisterTimerHandler( EventHandler* handler );

	/*
	*this runs an event loop - the imeplementation is entirely system specific and
	*in implemented in subclasses of UIToolkit
	*/
	static void runEventLoop();

	static ModalReturnType runModalEventLoopFor( Control* control );


	/**
	this will attempt to send a message/event to the underlying windowing system's
	event loop (started due to a call to runEventLoop() or runModalEventLoopFor(...) )
	and get it to quit running. It will not block and will return immediately.
	If an event loop ends, and there are no more event loops running then the
	application may quit cleanly.
	<p>On the Win32 system this is implemented with a PostQuitMessage(0)
	*/
	static void quitCurrentEventLoop();

	/**
	*This method creates a new event from native windowing OS event
	*data. Each UIToolkit implementation must implement this method
	*and since we can't possibly know the event data at this point,
	*we just specify a void*. The concrete implementation will have to
	*typecast this to the specific datatype or structure.
	*/
	static Event* createEventFromNativeOSEventData( void* eventData );

	/**
	*Override this - this should return whatever the appropriate x/y deltas
	*are for starting a drag drop operation are for the specific windowing system
	*/
	static Size getDragDropDelta();

	static const Image* getStandardStopImage();

	static const Image* getStandardWarningImage();

	static const Image* getStandardQuestionImage();

	static const Image* getStandardInformationImage();

	static void registerComponentInfo( const String& componentUUID, ComponentInfo* info );

	static void removeComponentInfo( ComponentInfo* info );

	static void registerAccelerator( AcceleratorKey* accelerator );

	static void removeAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask, Object* src );

	static Button* getDefaultButton();

	static void setDefaultButton( Button* defaultButton );

	static void removeDefaultButton( Button* defaultButton );

	static AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask, Object* src );

	/**
	Finds all the matching accelerators and store them in a list.
	A matching accelerator is defined as an accelerator that has the same key code, 
	modifier mask, and event handler. This let the synchronize the state of all
	the matching accelerators when one of them has its changed enabled/disabled state.
	*/
	static bool findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators );

	static void removeAcceleratorKeysForControl( Control* control );

	static void removeAcceleratorKeysForMenuItem( MenuItem* item );

	static void removeAcceleratorKeysForObject( Object* src );

	static void handleKeyboardEvent( KeyboardEvent* event );

	static VirtualKeyCode findMnemonic( const String& caption );

	static ComponentInfo* getComponentInfo( const String& componentUUID );

	static ComponentInfo* getComponentInfo( Class* componentClass );

	static UIMetricsManager* getUIMetricsManager();

	static double getUIMetricValue( const UIMetricsManager::MetricType& type, const String& text="" );

	static Size getUIMetricSize( const UIMetricsManager::MetricType& type, const String& text="" );

	static Rect getUIMetricRect( const UIMetricsManager::MetricType& type, Rect* rect=NULL );

	static UIPolicyManager* getUIPolicyManager();

	/**
	
	This attempts to to display the help contents for the application.
	
	It first checks to see if there's a running Application instance.
	If there is, then it calls the Application's virtual displayHelpContents()
	which lets the application have first crack at this. If 
	Application::displayHelpContents() returns true, then the function exits,
	if it does not then it attempts to determine the help book and help directory
	using this set of methods:
	\li it checks for the running app instance, and if it finds it, then it 
	requests the application to fill in the help book and help directory
	(these are virtual methods that can be overridden). 
	\li if no app is found or the help dir or help book entries are still
	empty, then the toolkit attempts to extract this from the resource bundle's 
	book and help directory entries.
	\li if the entries are still empty, then the help book becomes the 
	applications name (Application::getName()) or the executables name (
	without the extension), and the help directory is assumed to be "Help".

	
	So if you do nothing all, provide no overridden functions, or 
	resource bundle support for program info entries, then the default
	help would be look something like this, assuming the 
	app is in c:/Program Files/MyApp/MyApp.exe, the help book
	would be "MyApp" and the the peers would look in the directory
	c:/Program Files/MyApp/Help/ for the help content.

	@see Application::displayHelpContents()
	@see Application::getHelpInfo()
	*/
	static void displayHelpContents();

	/**
	
	This attempts to to display the help index for the application.
	
	It first checks to see if there's a running Application instance.
	If there is, then it calls the Application's virtual displayHelpContents()
	which lets the application have first crack at this. If 
	Application::displayHelpContents() returns true, then the function exits,
	if it does not then it attempts to determine the help book and help directory
	using this set of methods:
	\li it checks for the running app instance, and if it finds it, then it 
	requests the application to fill in the help book and help directory
	(these are virtual methods that can be overridden). 
	\li if no app is found or the help dir or help book entries are still
	empty, then the toolkit attempts to extract this from the resource bundle's 
	book and help directory entries.
	\li if the entries are still empty, then the help book becomes the 
	applications name (Application::getName()) or the executables name (
	without the extension), and the help directory is assumed to be "Help".

	
	So if you do nothing all, provide no overridden functions, or 
	resource bundle support for program info entries, then the default
	help would be look something like this, assuming the 
	app is in c:/Program Files/MyApp/MyApp.exe, the help book
	would be "MyApp" and the the peers would look in the directory
	c:/Program Files/MyApp/Help/ for the help content.

	@see Application::displayHelpContents()
	@see Application::getHelpInfo()
	*/
	static void displayHelpIndex();


	/**
	
	This attempts to to display a specific help section for a given
	help book and help directory. The help section is normally assumed 
	to be an anchor ref. This method allows you exact control over what 
	gets loaded. The helpBookName and helpDirectory may be
	be empty strings.
	
	If the helpBookName or helpDirectory are empty the toolkit
	first checks to see if there's a running Application instance.
	It then attempts to determine the help book and help directory
	using this set of methods:
	\li it checks for the running app instance, and if it finds it, then it 
	requests the application to fill in the help book and help directory
	(these are virtual methods that can be overridden). 
	\li if no app is found or the help dir or help book entries are still
	empty, then the toolkit attempts to extract this from the resource bundle's 
	book and help directory entries.
	\li if the entries are still empty, then the help book becomes the 
	applications name (Application::getName()) or the executables name (
	without the extension), and the help directory is assumed to be "Help".

	So if you do nothing all, provide no overridden functions, or 
	resource bundle support for program info entries, then the default
	help would be look something like this, assuming the 
	app is in c:/Program Files/MyApp/MyApp.exe, the help book
	would be "MyApp" and the the peers would look in the directory
	c:/Program Files/MyApp/Help/ for the help content.



	@see Application::displayHelpContents()
	@see Application::getHelpInfo()
	*/
	static void displayHelpSection( const String& helpSection, const String& helpBookName="", const String& helpDirectory="" );

	/**
	
	This attempts to display the context sensitive help for a control. It is 
	triggered by the underlying windowing platform, usually as a result of 
	the user hitting the F1 key.
	When this is called it first calls the toolkit's internal_displayContextHelpForControl(),
	this is turn will trigger the control's ControlHelpRequested delegate and fire and
	event. The WhatsThisHelpEvent has a member variable called helpString, and can be
	set to override the the value of the control's getWhatThisHelpString(). If the
	event's helpString member is not empty, \em or the controls getWhatThisHelpString()
	returns a non empty string, then the OS specific portion of the context help display
	should take place and the internal_displayContextHelpForControl() will return true.
	For Win32 systems this generally means the display of popup help.
	
	However, if internal_displayContextHelpForControl() returns false, then the toolkit 
	performs the following actions:
	\li It first fires a HelpEvent on the control's HelpRequested delegate. When this returns
	if the event's helpSection value is an empty string, then the toolkit gets the
	control's parent and does the same thing, continuing to do so until it receives 
	a NULL parent, or finds a non empty helpSection string. 
	\li if the helpSection from the event is not empty the toolkit will then call 
	UIToolkit::displayHelpSection() passing in the values of the event's helpSection,
	helpBook, and helpDirectory.
	*/
	static void displayContextHelpForControl( Control* control );

	/**
	public so platform implementers can get at it easily
	*/
	static UIToolkit* internal_getDefaultUIToolkit();

	static void addToUpdateList( Component* component );
	static void removeFromUpdateList( Component* component );
	static void setUpdateTimerSpeed( const unsigned long& milliseconds );

	static void systemSettingsChanged();
protected:
	static UIToolkit* toolKitInstance;

	std::map<String,ComponentInfo*> componentInfoMap_;
	std::multimap<ulong32,AcceleratorKey*> acceleratorMap_;
	std::vector<Control*> visitedContainers_;
	Clipboard* systemClipboard_;
    GraphicsToolkit * graphicsToolKit_;
	Image* stopImage_;
	Image* warningImage_;
	Image* informationImage_;
	Image* questionImage_;
	EventHandler* acceleratorMnemonicHandler_;
	EventHandler* defaultButtonHandler_;
	UIMetricsManager* metricsMgr_;
	UIPolicyManager* policyMgr_;
	std::vector<Button*> defaultButtonList_;

	std::vector<Component*> componentsToUpdate_;




	void onAcceleratorMnemonic( KeyboardEvent* event );

	void onDefaultButton( KeyboardEvent* event );

	/**
	*creates a new instance of a ControlPeer
	*the component passed in represents the component the implmenter will get attached to.
	*/
    virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType=CT_DEFAULT) = 0;

	virtual ContextPeer* internal_createContextPeer( Control* component );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height );

    virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component) = 0;

    virtual TreePeer* internal_createTreePeer( TreeControl* component) = 0;

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined ) = 0;

    virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl ) = 0;

    virtual ButtonPeer* internal_createButtonPeer( CommandButton* component) = 0;

    virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component) = 0;

	virtual DialogPeer* internal_createDialogPeer() = 0;

    virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner) = 0;


	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar ) = 0;

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item ) = 0;

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar ) = 0;

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu ) = 0;

    virtual ClipboardPeer* internal_createClipboardPeer() = 0;

    virtual DragDropPeer* internal_createDragDropPeer() = 0;

	virtual DataObjectPeer* internal_createDataObjectPeer() = 0;

	virtual DropTargetPeer* internal_createDropTargetPeer() = 0;

	virtual ApplicationPeer* internal_createApplicationPeer() = 0;

	virtual Clipboard* internal_getSystemClipboard();

	virtual CommonFileDialogPeer* internal_createCommonFileOpenDialogPeer( Control* owner ) = 0;

	virtual CommonFolderBrowseDialogPeer* internal_createCommonFolderBrowseDialogPeer( Control* owner ) = 0;

	virtual CommonFileDialogPeer* internal_createCommonFileSaveDialogPeer( Control* owner ) = 0;

	virtual CommonColorDialogPeer* internal_createCommonColorDialogPeer( Control* owner ) = 0;

	virtual CommonFontDialogPeer* internal_createCommonFontDialogPeer( Control* owner ) = 0;

	virtual CommonPrintDialogPeer* internal_createCommonPrintDialogPeer( Control* owner ) = 0;

	virtual DesktopPeer* internal_createDesktopPeer( Desktop* desktop ) = 0;

	virtual ScrollPeer* internal_createScrollPeer( Control* control ) = 0;

	virtual CursorPeer* internal_createCursorPeer( Cursor* cursor ) = 0;

	virtual SystemTrayPeer* internal_createSystemTrayPeer() = 0;

	virtual  MenuManagerPeer* internal_createMenuManagerPeer() = 0;

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer( AbstractApplication* app ) = 0;

	virtual bool internal_createCaret( Control* owningControl, Image* caretImage  ) = 0;

	virtual bool internal_destroyCaret( Control* owningControl ) = 0;

	virtual void internal_setCaretVisible( const bool& caretVisible ) = 0;

	virtual void internal_setCaretPos( Point* point ) = 0;

	virtual void internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true ) = 0;

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds ) = 0;

	virtual void internal_unregisterTimerHandler( EventHandler* handler ) = 0;

	/*
	*this runs an event loop - the imeplementation is entirely system specific and
	*in implemented in subclasses of UIToolkit
	*/
	virtual void internal_runEventLoop() = 0;

	virtual ModalReturnType internal_runModalEventLoopFor( Control* control ) = 0;


	/**
	this will attempt to send a message/event to the underlying windowing system's
	event loop (started due to a call to runEventLoop() or runModalEventLoopFor(...) )
	and get it to quit running. It will not block and will return immediately.
	If an event loop ends, and there are no more event loops running then the
	application may quit cleanly.
	<p>On the Win32 system this is implemented with a PostQuitMessage(0)
	*/
	virtual void internal_quitCurrentEventLoop() = 0;

	/**
	*This method creates a new event from native windowing OS event
	*data. Each UIToolkit implementation must implement this method
	*and since we can't possibly know the event data at this point,
	*we just specify a void*. The concrete implementation will have to
	*typecast this to the specific datatype or structure.
	*/
	virtual Event* internal_createEventFromNativeOSEventData( void* eventData ) = 0;

	/**
	*Override this - this should return whatever the appropriate x/y deltas
	*are for starting a drag drop operation are for the specific windowing system
	*/
	virtual Size internal_getDragDropDelta() = 0;

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory ) = 0;

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory ) = 0;

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection ) = 0;
	/**
	This should display the appropriate context sensitive infor for the control,
	and return true, or it should return false, indicating that the control didn't 
	have any context help to display.
	*/
	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory ) = 0;

	virtual void internal_systemSettingsChanged() = 0;

	virtual void internal_handleKeyboardEvent( KeyboardEvent* event );

	virtual VirtualKeyCode internal_findMnemonic( const String& caption );


	const Image* internal_getStandardStopImage();

	const Image* internal_getStandardWarningImage();

	const Image* internal_getStandardQuestionImage();

	const Image* internal_getStandardInformationImage();

	void internal_registerComponentInfo( const String& componentUUID, ComponentInfo* info );

	void internal_removeComponentInfo( ComponentInfo* info );

	void internal_registerAccelerator( AcceleratorKey* accelerator );

	void internal_removeAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask, Object* src );

	Button* internal_getDefaultButton();

	void internal_setDefaultButton( Button* defaultButton );

	void internal_removeDefaultButton( Button* defaultButton );

	AcceleratorKey* internal_getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask, Object* src );

	void internal_removeAcceleratorKeysForControl( Control* control );

	void internal_removeAcceleratorKeysForMenuItem( MenuItem* menuItem );

	void internal_removeAcceleratorKeysForObject( Object* src );

	bool internal_findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators );

	virtual void internal_idleTime();


	ComponentInfo* internal_getComponentInfo( const String& componentUUID );

	ComponentInfo* internal_getComponentInfo( Class* componentClass );

	UIMetricsManager* internal_getUIMetricsManager() {
		return metricsMgr_;
	}

	UIPolicyManager* internal_getUIPolicyManager() {
		return policyMgr_;
	}

	void internal_addToUpdateList( Component* component );
	void internal_removeFromUpdateList( Component* component );
	void internal_setUpdateTimerSpeed( const unsigned long& milliseconds );

	void onUpdateComponentsTimer( TimerEvent* e );

	void handleTabKeyboardEvent( KeyboardEvent* event );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.10  2006/03/28 04:10:17  ddiego
*tweaked some function names for the update process.
*
*Revision 1.5.2.9  2006/03/28 04:04:36  ddiego
*added a slight adjustment to idle message handling. Component
*updating is now handled there instead of a timer.
*
*Revision 1.5.2.8  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.5.2.7  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.5.2.6  2006/03/06 03:48:30  ddiego
*more docs, plus update add-ins, plus migrated HTML browser code to a new kit called HTMLKit.
*
*Revision 1.5.2.5  2006/03/01 04:34:56  ddiego
*fixed tab display to use themes api.
*
*Revision 1.5.2.4  2006/02/23 05:54:23  ddiego
*some html help integration fixes and new features. context sensitive help is finished now.
*
*Revision 1.5.2.3  2006/02/21 04:32:51  ddiego
*comitting moer changes to theme code, progress bars, sliders and tab pages.
*
*Revision 1.5.2.2  2005/10/07 16:41:21  kiklop74
*Added support for building ApplicationKit with Borland Free Compiler
*
*Revision 1.5.2.1  2005/09/07 04:19:54  ddiego
*filled in initial code for help support.
*
*Revision 1.5  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.10  2005/06/06 02:34:06  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3.2.9  2005/06/02 16:17:34  marcelloptr
*some more documentation
*
*Revision 1.3.2.8  2005/05/15 23:17:38  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.7  2005/04/25 00:11:57  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.3.2.6  2005/04/20 02:26:00  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.5  2005/03/14 04:17:24  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.2.4  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3.2.3  2005/01/26 22:43:18  ddiego
*added some docs on event handler and post event mechanics.
*
*Revision 1.3.2.2  2004/12/19 07:09:18  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.2  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.1  2004/08/18 21:20:24  ddiego
*added initial system tray code for win32
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.37.4.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.37  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.36.2.4  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.36.2.3  2003/10/31 05:06:38  ddiego
*added toolbar impl
*
*Revision 1.36.2.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.36.2.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.36  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.35.2.3  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.35.2.2  2003/07/06 01:20:29  ddiego
*added basic Document/View classes. These are based on the existing MVC
*architecture already present in the framework already, and exapnd on the
*existing functionality. Many of the ideas were influenced by the NeXT/Cocoa's
*Document/View architecture. Some of the new features are:
*  automatic creation and connection of the various parts including the
*  Document, view and Window.
*  Automatic default menu items, to ensure standard UI conformance. The menu
*  items are merged with an existing ones.
*  Automatic clipboard support in the form of cut/copy/paste and connecting this
*  directly to the current document
*  Support for Undo/Redo item as well, including default menu item validation
*  Default support for opening and saving documents, including presenting the
*  correct Dialogs to the User, and properly filling the default data, based
*  on the documents data.
*  Support for multiple document types
*  Support for differnt Document Interface policies. Currently we support
*  SDI (Single Document Interface) and MDI (Multiple Document Interface)
*
*Revision 1.35.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.35  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.34.2.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.34.2.1  2003/03/12 03:11:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.34  2003/02/26 04:30:44  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.33.2.2  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.33.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.33  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.32.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.32  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.31.6.2  2002/07/02 05:35:11  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.31.6.1  2002/06/28 17:45:30  ddiego
*migrated over lucki's changes (from his branch) for drag drop
*compiles OK, made chages to control and UIToolkit as neccessary
*still testing though.
*
*Revision 1.31  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.30.4.1  2002/04/27 15:52:21  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.30  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.29  2002/02/07 04:38:55  ddiego
*fixes to Win32Edit, which include problems with setting text, and a bug that
*caused it to crash in Win 98. All textControls now default to the "EDIT"
*window class unles they are multiline, in which case an attempt is made to
*load the richedit control, and if that fails then the EDIT class is used
*Removed responding to WM_COMMAND messages
*in the default parent in the Win32Toolkit, also to fix the Win32Edit crash in 9.x
*
*Revision 1.28  2002/01/26 15:11:09  ddiego
*Default button now working
*
*Revision 1.27  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_UITOOLKIT_H__


