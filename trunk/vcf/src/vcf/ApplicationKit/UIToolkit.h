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

class UIShellPeer;
class UIShell;

class ComponentInfo;
class ScrollPeer;
class AcceleratorKey;
class Button;
class Toolbar;
class TimerEvent;

class SystemTrayPeer;

class MenuManagerPeer;

class PopupWindowPeer;
class TransparentWindowPeer;





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
class APPLICATIONKIT_API UIToolkit : public ObjectWithCallbacks {
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
	static ContextPeer* createContextPeer( const uint32& width, const uint32& height );

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

	static PopupWindowPeer* createPopupWindowPeer( Frame* frame, Window* owner );

	static TransparentWindowPeer* createTransparentWindowPeer( Frame* frame );


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
	

	static UIShellPeer* createUIShellPeer( UIShell* shell );

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

	static void registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds );

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

	static void removeAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src );

	static Button* getDefaultButton();

	static void setDefaultButton( Button* defaultButton );

	static void removeDefaultButton( Button* defaultButton );

	static AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src );

	/**
	Finds all the matching accelerators and store them in a list.
	A matching accelerator is defined as an accelerator that has the same key code, 
	modifier mask, and event handler. This let the synchronize the state of all
	the matching accelerators when one of them has its changed enabled/disabled state.
	*/
	static bool findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators );

	static void getAcceleratorKeysForControl( Control* control, std::vector<AcceleratorKey*>& matchingAccelerators );

	static void getAcceleratorKeysForMenuItem( MenuItem* item, std::vector<AcceleratorKey*>& matchingAccelerators );

	static void getAcceleratorKeysForObject( Object* src, std::vector<AcceleratorKey*>& matchingAccelerators );

	static void removeAcceleratorKeysForControl( Control* control );

	static void removeAcceleratorKeysForMenuItem( MenuItem* item );

	static void removeAcceleratorKeysForObject( Object* src );

	static void handleKeyboardEvent( KeyboardEvent* event );

	static VirtualKeyCode findMnemonic( const String& caption );

	static ComponentInfo* getComponentInfo( const String& componentUUID );

	static ComponentInfo* getComponentInfo( Class* componentClass );

	static UIMetricsManager* getUIMetricsManager();

	static double getUIMetricValue( const UIMetricsManager::MetricType& type, const String& text="", Font* alternateFont=NULL );

	static Size getUIMetricSize( const UIMetricsManager::MetricType& type, const String& text="", Font* alternateFont=NULL );

	static Rect getUIMetricRect( const UIMetricsManager::MetricType& type, Rect* rect=NULL, Font* alternateFont=NULL );

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
	static void setUpdateTimerSpeed( const uint32& milliseconds );

	static void systemSettingsChanged();
protected:
	static UIToolkit* toolKitInstance;

	std::map<String,ComponentInfo*> componentInfoMap_;
	std::multimap<uint32,AcceleratorKey*> acceleratorMap_;
	std::vector<Control*> visitedContainers_;
	Clipboard* systemClipboard_;
    GraphicsToolkit * graphicsToolKit_;
	Image* stopImage_;
	Image* warningImage_;
	Image* informationImage_;
	Image* questionImage_;
	KeyboardHandler* acceleratorMnemonicHandler_;
	KeyboardHandler* defaultButtonHandler_;
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

	virtual ContextPeer* internal_createContextPeer( const uint32& width, const uint32& height );

    virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component) = 0;

    virtual TreePeer* internal_createTreePeer( TreeControl* component) = 0;

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined ) = 0;

    virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl ) = 0;

    virtual ButtonPeer* internal_createButtonPeer( CommandButton* component) = 0;

    virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component) = 0;

	virtual DialogPeer* internal_createDialogPeer() = 0;

    virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner) = 0;

	virtual PopupWindowPeer* internal_createPopupWindowPeer( Frame* frame, Window* owner ) = 0;

	virtual TransparentWindowPeer* internal_createTransparentWindowPeer( Frame* frame ) = 0;


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

	virtual UIShellPeer* internal_createUIShellPeer( UIShell* shell ) = 0;

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

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds ) = 0;

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

	void internal_removeAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src );

	Button* internal_getDefaultButton();

	void internal_setDefaultButton( Button* defaultButton );

	void internal_removeDefaultButton( Button* defaultButton );

	AcceleratorKey* internal_getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src );

	void internal_removeAcceleratorKeysForControl( Control* control );

	void internal_removeAcceleratorKeysForMenuItem( MenuItem* menuItem );

	void internal_removeAcceleratorKeysForObject( Object* src );

	bool internal_findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators );

	void internal_getAcceleratorKeysForControl( Control* control, std::vector<AcceleratorKey*>& matchingAccelerators );

	void internal_getAcceleratorKeysForMenuItem( MenuItem* item, std::vector<AcceleratorKey*>& matchingAccelerators );

	void internal_getAcceleratorKeysForObject( Object* src, std::vector<AcceleratorKey*>& matchingAccelerators );

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
	void internal_setUpdateTimerSpeed( const uint32& milliseconds );

	void onUpdateComponentsTimer( TimerEvent* e );

	void handleTabKeyboardEvent( KeyboardEvent* event );

	static String getControlConstants( const String& name );
};

};


#endif // _VCF_UITOOLKIT_H__

/**
$Id$
*/
