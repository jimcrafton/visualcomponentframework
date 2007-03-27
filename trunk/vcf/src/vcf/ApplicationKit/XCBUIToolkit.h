#ifndef _VCF_XCBUITOOLKIT_H__
#define _VCF_XCBUITOOLKIT_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class XCBWindowPeer;

typedef void* XCBVoidCookie;

class XCBUIToolkit : public UIToolkit
{
public:
	XCBUIToolkit();

	struct XCBCookieInfo
	{
		xcb_void_cookie_t cookie;
		String        extraInfo;
	};
	void internal_addVoidCookie( const xcb_void_cookie_t &cookie, const String &extraInfo );

protected:
	virtual ControlPeer* internal_createControlPeer( Control* component, ComponentType componentType=CT_DEFAULT );

	virtual ContextPeer* internal_createContextPeer( Control* component );

	virtual ListviewPeer* internal_createListViewPeer( ListViewControl* component );

	virtual TreePeer* internal_createTreePeer( TreeControl* component );

	virtual TextPeer* internal_createTextPeer( const bool& autoWordWrap, const bool& multiLined );

	virtual TextEditPeer* internal_createTextEditPeer( TextControl* component, const bool& isMultiLineControl );

	virtual ButtonPeer* internal_createButtonPeer( CommandButton* component );

	virtual DialogPeer* internal_createDialogPeer( Control* owner, Dialog* component );

	virtual DialogPeer* internal_createDialogPeer();

	virtual WindowPeer* internal_createWindowPeer( Control* component, Control* owner );

	virtual ToolbarPeer* internal_createToolbarPeer( Toolbar* toolbar );

	virtual MenuItemPeer* internal_createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* internal_createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* internal_createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ClipboardPeer* internal_createClipboardPeer();

	virtual DragDropPeer* internal_createDragDropPeer();

	virtual DataObjectPeer* internal_createDataObjectPeer();

	virtual DropTargetPeer* internal_createDropTargetPeer();

	virtual ApplicationPeer* internal_createApplicationPeer();

	virtual CommonFileDialogPeer* internal_createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* internal_createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* internal_createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* internal_createCommonColorDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* internal_createCommonFontDialogPeer( Control* owner );

	virtual CommonPrintDialogPeer* internal_createCommonPrintDialogPeer( Control* owner );

    virtual PopupWindowPeer* internal_createPopupWindowPeer( Frame* frame, Window* owner );

	virtual TransparentWindowPeer* internal_createTransparentWindowPeer( Frame* frame );

	virtual UIShellPeer* internal_createUIShellPeer( UIShell* shell );

	virtual ScrollPeer* internal_createScrollPeer( Control* control );

	virtual CursorPeer* internal_createCursorPeer( Cursor* cursor );

	virtual SystemTrayPeer* internal_createSystemTrayPeer();

	virtual  MenuManagerPeer* internal_createMenuManagerPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer( AbstractApplication* app );

	virtual bool internal_createCaret( Control* owningControl, Image* caretImage );

	virtual bool internal_destroyCaret( Control* owningControl );

	virtual void internal_setCaretVisible( const bool& caretVisible );

	virtual void internal_setCaretPos( Point* point );

	virtual void internal_postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler=true );

	virtual void internal_registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds );

	virtual void internal_unregisterTimerHandler( EventHandler* handler );

	virtual void internal_runEventLoop();

	virtual UIToolkit::ModalReturnType internal_runModalEventLoopFor( Control* control );

	virtual void internal_quitCurrentEventLoop();

	virtual Event* internal_createEventFromNativeOSEventData( void* eventData );

	virtual Size internal_getDragDropDelta();

	virtual void internal_displayHelpContents( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpIndex( const String& helpBookName, const String& helpDirectory );

	virtual void internal_displayHelpSection( const String& helpBookName, const String& helpDirectory, const String& helpSection );

	virtual bool internal_displayContextHelpForControl( Control* control, const String& helpBookName, const String& helpDirectory );

	virtual void internal_systemSettingsChanged();

private:
	static void consoleQuitHandler( int sig );

    /**
     * returns whether event loop should exit.
    */
	bool handleError( const xcb_generic_error_t& err );
	void handleClientMessage( xcb_connection_t* connection, const xcb_client_message_event_t& event );
	void handleConfigureNotify( xcb_connection_t* connection, const xcb_configure_notify_event_t& event );
	void handleExpose( const xcb_expose_event_t& event );
	void handleDestroyNotify( xcb_connection_t* connection, const xcb_destroy_notify_event_t& event );
	void handleDefault( const xcb_generic_event_t& event );

	/**
	 * returns whether event loop should exit.
	*/
	bool handlePollForEventError();
	void handleExposes(xcb_connection_t* connection);

private:
	typedef std::map<uint32, xcb_expose_event_t> ExposeEventXIDMap;
	ExposeEventXIDMap exposeEvents_;

	bool consoleQuitHandlerCalled_;


	typedef std::vector<XCBCookieInfo> XCBCookieInfoVector;
	XCBCookieInfoVector cookieInfos_;

};


} //end of namespace VCF


#endif // _VCF_XCBUITOOLKIT_H__

/**
$Id$
*/

