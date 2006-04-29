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


#define VCF_CONTROL_CREATE		VCF_MESSAGE + 99



namespace VCFWin32 {

	
struct KeyboardData {
	int repeatCount;
	int scanCode;
	bool isExtendedKey;
	bool altKeyDown;
	unsigned short character;
	int VKeyCode;
	UINT keyMask;
};

#define KB_CONTEXT_CODE			29
#define KB_PREVIOUS_STATE		30
#define KB_IS_EXTENDED_KEY		24

#define SHIFT_KEY_DOWN \
	((GetKeyState( VK_SHIFT) & 15 ) == 1)




class APPLICATIONKIT_API Win32UIUtils {
public:
	static unsigned long translateKeyMask( UINT win32KeyMask );

	static unsigned long translateButtonMask( UINT win32ButtonMask );

	static KeyboardData translateKeyData( HWND wndHandle, LPARAM keyData );

	static DWORD translateStyle( unsigned long style );

	static DWORD translateExStyle( unsigned long style );

	static int getXFromLParam( LPARAM lParam );

	static int getYFromLParam( LPARAM lParam );

	static VCF::ulong32 translateVKCode( UINT vkCode );

	static VCF::uint32 convertCharToVKCode( VCF::VCFChar ch );
};


};





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

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined );

	virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl);

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

	virtual  MenuManagerPeer* internal_createMenuManagerPeer();

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

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection );

	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory );

	virtual void internal_systemSettingsChanged();

	static HINSTANCE getInstanceHandle();


	bool getWhatsThisHelpActive() {
		return whatsThisHelpActive_;
	}

	void setWhatsThisHelpActive( bool val ) {
		whatsThisHelpActive_ = val;
	}
protected:

	void createDummyParentWindow();
	HWND dummyParentWnd_;		
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

	bool whatsThisHelpActive_;
	std::map<UINT,TimerRec*> timerMap_;

	TimerRec* findTimerRec( UINT id );

	static ATOM RegisterWin32ToolKitClass(HINSTANCE hInstance);

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK mouseHookProc( int nCode, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK keyboardHookProc( int nCode, WPARAM wParam, LPARAM lParam );
};

};


#endif // _VCF_WIN32TOOLKIT_H__

/**
$Id$
*/
