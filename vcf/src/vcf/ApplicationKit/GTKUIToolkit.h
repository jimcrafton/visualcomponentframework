#ifndef _VCF_GTKUITOOLKIT_H__
#define _VCF_GTKUITOOLKIT_H__
//GTKUIToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include <deque>





namespace VCF {




class AbstractX11Control;


/**
this class is used as a wrapper around an XEvent.
*/
class GTKEventMsg {
public:
	GTKEventMsg( GdkEvent* event, Control* control ): gdkEvent_(event), control_(control) {}


	GdkEvent* gdkEvent_;
	Control* control_;
};



class TimeOutHandler {
public:
	TimeOutHandler():source_(NULL), handler_(NULL), timerID_(0) {

	}

	Object* source_;
	EventHandler* handler_;
	guint timerID_;
};

/**
*/
class GTKUIToolkit :  public UIToolkit {
public:

	GTKUIToolkit();

	virtual ~GTKUIToolkit();

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

	virtual void internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds );

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

	GtkWidget* getDefaultParent() {
		return defaultParent_;
	}
	static void  internal_gdkEventHandler( GdkEvent* gdkEvent, gpointer data);

	static gboolean internal_gdkIdleHandler(gpointer data);

protected:
	VirtualKeyCode translateKeyCode( guint code );
	ulong32 translateKeyMask( GdkModifierType keyState );
	ulong32 translateButtonMask( GdkModifierType buttonState );

	bool handleGdkEvent( GdkEvent* gdkEvent );
	void createDefaultParentWnd();
	GtkWidget* defaultParent_;
	static gboolean gtkTimeOutHandler(gpointer data);

	std::map<EventHandler*,TimeOutHandler> timeoutHandlers_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.2.2  2003/11/01 20:39:35  ddiego
*added gtk toolbar - no implementation yet
*
*Revision 1.3.2.1  2003/08/25 03:13:44  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.3  2003/08/09 02:56:44  ddiego
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
*Revision 1.2.2.2  2003/07/14 22:52:40  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*Revision 1.2.2.1  2003/07/09 03:53:18  ddiego
*some fixes to gtk port
*
*Revision 1.2  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.3  2003/04/23 03:43:37  ddiego
*further gtk dev got basic eventing code in place
*
*Revision 1.1.2.2  2003/04/19 03:31:15  ddiego
*basic code in place for gtk port for ApplicationKit - needs to be tested in
*linux
*
*Revision 1.1.2.1  2003/04/17 04:29:49  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


#endif // _VCF_GTKUITOOLKIT_H__


