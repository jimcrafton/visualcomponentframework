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

class ListviewPeer;
class ComboBoxPeer;
class TextPeer;
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
class HTMLBrowserPeer;
class AcceleratorKey;
class Button;
class Toolbar;
class TimerEvent;

class SystemTrayPeer;





/**
The UIToolkit is used to create instances of various peer's needed by the VCF,
as well as providing certain low level services, such as modal and non-modal
event loops, and getting at UI metrics. Each system the VCF is ported to has
a concrete implementation of the UIToolkit. The UIToolkit is a singleton, and
there should only be one instance for a given process running the VCF libraries.

To work with the toolkit you retreive it's instance via a static function,
UIToolkit::getDefaultUIToolkit(). If no toolkit is found (which is an extremely bad thing!)
a NoToolKitFoundException is thrown. A quick example:
<pre>
try {
	UIToolkit* toolkit = UIToolkit::getDefaultUIToolkit();
}
catch ( NoToolKitFoundException & e ) {
	//we are screwed!!!
	System::print( e.getMessage() );
}
</pre>
The UIToolkit is a singleton, meaning there is only ever one single instance of it.
Developers porting the VCF to another platform will have to create a derived class
from UIToolkit and implement various functions.
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
	static ContextPeer* createContextPeer( const long& contextID );

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
    static TextPeer* createTextPeer( TextControl* component, const bool& isMultiLineControl);

	/**
	This creates a peer that implements the HTMLBrowserPeer interface. The HTMLBrowserPeer
	allows you to view HTML.
	*/
	static HTMLBrowserPeer* createHTMLBrowserPeer( Control* control );

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

	static bool createCaret( Control* owningControl, Image* caretImage  );

	static bool destroyCaret( Control* owningControl );

	static void setCaretVisible( const bool& caretVisible );

	static void setCaretPos( Point* point );

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

	static void removeAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	static Button* getDefaultButton();

	static void setDefaultButton( Button* defaultButton );

	static void removeDefaultButton( Button* defaultButton );

	static AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	static void removeAcceleratorKeysForControl( Control* control );

	static void handleKeyboardEvent( KeyboardEvent* event );

	static VirtualKeyCode findMnemonic( const String& caption );

	static ComponentInfo* getComponentInfo( const String& componentUUID );

	static ComponentInfo* getComponentInfo( Class* componentClass );

	static UIMetricsManager* getUIMetricsManager();

	static UIPolicyManager* getUIPolicyManager();

	/**
	public so platform implementers can get at it easily
	*/
	static UIToolkit* internal_getDefaultUIToolkit();

	static void addToUpdateTimer( Component* component );
	static void removeFromUpdateTimer( Component* component );
	static void setUpdateTimerSpeed( const unsigned long& milliseconds );
protected:
	static UIToolkit* toolKitInstance;

	std::map<String,ComponentInfo*> componentInfoMap_;
	std::map<ulong32,AcceleratorKey*> acceleratorMap_;
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

	virtual ContextPeer* internal_createContextPeer( const long& contextID );

	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height );

    virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component) = 0;

    virtual TreePeer* internal_createTreePeer( TreeControl* component) = 0;

    virtual TextPeer* internal_createTextPeer( TextControl* component, const bool& isMultiLineControl) = 0;

	virtual HTMLBrowserPeer* internal_createHTMLBrowserPeer( Control* control ) = 0;

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

	virtual void internal_handleKeyboardEvent( KeyboardEvent* event );

	virtual VirtualKeyCode internal_findMnemonic( const String& caption );


	const Image* internal_getStandardStopImage();

	const Image* internal_getStandardWarningImage();

	const Image* internal_getStandardQuestionImage();

	const Image* internal_getStandardInformationImage();

	void internal_registerComponentInfo( const String& componentUUID, ComponentInfo* info );

	void internal_removeComponentInfo( ComponentInfo* info );

	void internal_registerAccelerator( AcceleratorKey* accelerator );

	void internal_removeAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	Button* internal_getDefaultButton();

	void internal_setDefaultButton( Button* defaultButton );

	void internal_removeDefaultButton( Button* defaultButton );

	AcceleratorKey* internal_getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	void internal_removeAcceleratorKeysForControl( Control* control );



	ComponentInfo* internal_getComponentInfo( const String& componentUUID );

	ComponentInfo* internal_getComponentInfo( Class* componentClass );

	UIMetricsManager* internal_getUIMetricsManager() {
		return metricsMgr_;
	}

	UIPolicyManager* internal_getUIPolicyManager() {
		return policyMgr_;
	}

	void internal_addToUpdateTimer( Component* component );
	void internal_removeFromUpdateTimer( Component* component );
	void internal_setUpdateTimerSpeed( const unsigned long& milliseconds );

	void onUpdateComponentsTimer( TimerEvent* e );
};

};


/**
*CVS Log info
*$Log$
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


