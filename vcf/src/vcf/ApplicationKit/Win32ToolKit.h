#ifndef _VCF_WIN32TOOLKIT_H__
#define _VCF_WIN32TOOLKIT_H__
//Win32ToolKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Win32MSG {
public:
	Win32MSG( const MSG& msg, Control* control=NULL ) :msg_(msg), control_(control) {

	}


	Win32MSG( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Control* control=NULL):
		control_(control) {

		memset( &msg_, 0, sizeof(MSG) );

		msg_.hwnd = hwnd;
		msg_.message = message;
		msg_.wParam = wParam;
		msg_.lParam = lParam;
	}

	Win32MSG( const Win32MSG& msg ):msg_(msg.msg_), control_(msg.control_) {

	}

	Win32MSG& operator=( const Win32MSG& msg ) {
		msg_ = msg.msg_;
		control_ = msg.control_;
		return *this;
	}

	MSG msg_;
	Control* control_;
};


class APPLICATIONKIT_API Win32ToolKit : public UIToolkit
{
public:
	Win32ToolKit();
	virtual ~Win32ToolKit();

	virtual ApplicationPeer* internal_createApplicationPeer();

	virtual TextPeer* internal_createTextPeer( TextControl* component, const bool& isMultiLineControl);

	virtual TreePeer* internal_createTreePeer( TreeControl* component);

	virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component);

	virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component );

	virtual DialogPeer* internal_createDialogPeer();

	virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType);

	virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner);

	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar );

	HWND getDummyParent();

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ButtonPeer* internal_createButtonPeer( CommandButton* component);

	virtual HTMLBrowserPeer* internal_createHTMLBrowserPeer( Control* control );

	virtual ContextPeer* internal_createContextPeer( Control* component );

	virtual CommonFileDialogPeer* internal_createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* internal_createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* internal_createCommonColorDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* internal_createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* internal_createCommonFontDialogPeer( Control* owner );

	virtual CommonPrintDialogPeer* internal_createCommonPrintDialogPeer( Control* owner );

	virtual DragDropPeer* internal_createDragDropPeer();

	virtual DataObjectPeer* internal_createDataObjectPeer();

	virtual DropTargetPeer* internal_createDropTargetPeer();

	virtual DesktopPeer* internal_createDesktopPeer( Desktop* desktop );

	virtual ScrollPeer* internal_createScrollPeer( Control* control );

	virtual CursorPeer* internal_createCursorPeer( Cursor* cursor );

	virtual ClipboardPeer* internal_createClipboardPeer();

	virtual SystemTrayPeer* internal_createSystemTrayPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer( AbstractApplication* app );

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
	*pointer to a Win32MSG structure.
	*/
	virtual Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();

	static HINSTANCE getInstanceHandle();
protected:

	void createDummyParentWindow();
	HWND dummyParentWnd_;
	Library browserLib_;
	bool browserLibAvailable_;
	int runEventCount_;

	class TimerRec {
	public:
		TimerRec( Object* source, EventHandler* handler ) {
			source_ = source;
			handler_ = handler;
		}

		Object* source_;
		EventHandler* handler_;
	};

	std::map<UINT,TimerRec*> timerMap_;

	TimerRec* findTimerRec( UINT id );

	static ATOM RegisterWin32ToolKitClass(HINSTANCE hInstance);

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 07:09:19  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2.2.1  2004/08/18 21:20:24  ddiego
*added initial system tray code for win32
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.32.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.32  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.31.2.2  2003/10/31 05:06:23  ddiego
*added toolbar impl
*
*Revision 1.31.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.31  2003/08/09 02:56:44  ddiego
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
*Revision 1.30.2.2  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.30.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.30  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.29.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.29.2.1  2003/03/12 03:11:36  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.29  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.28.8.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.28  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.27.6.1  2002/06/28 17:45:29  ddiego
*migrated over lucki's changes (from his branch) for drag drop
*compiles OK, made chages to control and UIToolkit as neccessary
*still testing though.
*
*Revision 1.27  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.26.4.1  2002/04/27 15:52:20  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.26  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.25  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32TOOLKIT_H__


