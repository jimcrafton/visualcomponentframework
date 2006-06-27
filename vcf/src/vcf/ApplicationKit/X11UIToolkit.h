#ifndef _VCF_X11UITOOLKIT_H__
#define _VCF_X11UITOOLKIT_H__
//X11UIToolkit.h

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


#define VCF_X11_DELETEWND_ATOM			"WM_DELETE_WINDOW"
#define VCF_X11_VCFCREATEWND_ATOM		"VCF_CREATE_WINDOW"
#define VCF_X11_QUITEVENTLOOP_ATOM		"VCF_QUITEVENTLOOP"
#define VCF_X11_PAINTWND_ATOM				"VCF_PAINT_WINDOW"



class AbstractX11Control;


/**
this class is used as a wrapper around an XEvent.
*/
class X11EventMsg {
public:
	X11EventMsg( XEvent* event, Control* control ): x11event_(event), control_(control) {}


	XEvent* x11event_;
	Control* control_;
};


/**
this class is ONLY to be used internally in this X11 implementation of the
UIToolkit. It is for POSTING messages to the toolkit for later processing
*/
class X11ToolkitMsg {
public:
	X11ToolkitMsg(): type_(0), data_(NULL), autoDeleteData_(false) {

	}

	X11ToolkitMsg( int type, void* data=NULL, bool autoDelete=false ) :
		type_(type), data_(data), autoDeleteData_(autoDelete){

	}


	int type_;
	void* data_;
	bool autoDeleteData_;
};



class TimerEntry {
public:
	TimerEntry() :frequency_(0){
		//sets the current time of the TimerEntry
		resetCurrentTime();
	}

	TimerEntry( uint32 frequency ):frequency_(frequency)  {
		//sets the current time of the TimerEntry
		resetCurrentTime();
	}

	TimerEntry( const TimerEntry& rhs ) {
		*this = rhs;
		resetCurrentTime();
	}

	TimerEntry& operator=( const TimerEntry& rhs ) {
		frequency_ = rhs.frequency_;
		current_ = rhs.current_;
	}

	bool operator==( const TimerEntry& rhs ) const {
		return (frequency_ == rhs.frequency_) && (current_.tv_sec == rhs.current_.tv_sec)
					&& (current_.tv_usec == rhs.current_.tv_usec);
	}

	bool operator!=( const TimerEntry& rhs ) const {
		return (frequency_ != rhs.frequency_) || (current_.tv_sec != rhs.current_.tv_sec)
					|| (current_.tv_usec != rhs.current_.tv_usec);
	}

	uint32 getMillisecondsDifference( struct timeval* val ) const {
		double t1, t2;

		t1 =  (double)(current_.tv_sec * 1000.0) +
				(double)current_.tv_usec/(1000.0);

		t2 =  (double)(val->tv_sec * 1000.0) + (double)val->tv_usec/(1000.0); //convert to Milliseconds

		return (uint32)(t2 - t1);
	}

	void resetCurrentTime() {
		struct	timezone timeZone;
		::gettimeofday( &current_, &timeZone );
	}

	uint32 getFrequency() const {
		return frequency_;
	}
protected:

	//time, in milliseconds, before this
	//entry should be fired
	uint32 frequency_;

	//the current time
	struct timeval current_;
};



/**
*/
class X11UIToolkit :  public UIToolkit {
public:

	X11UIToolkit();

	virtual ~X11UIToolkit();

	virtual ApplicationPeer* createApplicationPeer();

	virtual TextPeer* createTextPeer( TextControl* component, const bool& isMultiLineControl, ComponentType componentType=CT_DEFAULT);

	virtual TreePeer* createTreePeer( TreeControl* component, ComponentType componentType=CT_DEFAULT);

	virtual ListviewPeer* createListViewPeer( ListViewControl* component, ComponentType componentType=CT_DEFAULT);

	virtual DialogPeer* createDialogPeer( Control* owner, Dialog* component, ComponentType componentType=CT_DEFAULT );

	virtual DialogPeer* createDialogPeer();

	virtual ControlPeer* createControlPeer( Control* component, ComponentType componentType);

	virtual WindowPeer* createWindowPeer( Control* component, Control* owner, ComponentType componentType);

	virtual MenuItemPeer* createMenuItemPeer( MenuItem* item );

	virtual MenuBarPeer* createMenuBarPeer( MenuBar* menuBar );

	virtual PopupMenuPeer* createPopupMenuPeer( PopupMenu* popupMenu );

	virtual ButtonPeer* createButtonPeer( CommandButton* component, ComponentType componentType);

	virtual HTMLBrowserPeer* createHTMLBrowserPeer( Control* control );

	virtual ContextPeer* createContextPeer( Control* component );

	virtual CommonFileDialogPeer* createCommonFileOpenDialogPeer( Control* owner );

	virtual CommonFileDialogPeer* createCommonFileSaveDialogPeer( Control* owner );

	virtual CommonColorDialogPeer* createCommonColorDialogPeer( Control* owner );

	virtual CommonFolderBrowseDialogPeer* createCommonFolderBrowseDialogPeer( Control* owner );

	virtual CommonFontDialogPeer* createCommonFontDialogPeer( Control* owner );

	virtual DragDropPeer* createDragDropPeer();

	virtual DataObjectPeer* createDataObjectPeer();

	virtual DropTargetPeer* createDropTargetPeer();

	virtual DesktopPeer* createDesktopPeer( Desktop* desktop );

	virtual ScrollPeer* createScrollPeer( Control* control );

	virtual CursorPeer* createCursorPeer( Cursor* cursor );

	virtual ClipboardPeer* createClipboardPeer();

	virtual bool createCaret( Control* owningControl, Image* caretImage  );

	virtual bool destroyCaret( Control* owningControl );

	virtual void setCaretVisible( const bool& caretVisible );

	virtual void setCaretPos( Point* point );

	virtual void postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler );

	virtual void registerTimerHandler( Object* source, EventHandler* handler, const uint32& timeoutInMilliSeconds );

	virtual void unregisterTimerHandler( EventHandler* handler );

	virtual void runEventLoop();

	virtual ModalReturnType runModalEventLoopFor( Control* control );

	/**
	*@param void* in this implementation, the eventData represents a
	*pointer to an X11 XEvent structure.
	*/
	virtual VCF::Event* createEventFromNativeOSEventData( void* eventData );

	virtual Size getDragDropDelta();

	xLib::Window getDefaultParentWnd() {
		return defaultParentWnd_;
	}

	String getX11ErrorMessage( XID id );

	VirtualKeyCode translateKeyCode( KeySym code );

	uint32 translateKeyMask( uint32 xKeyState );

	uint32 translateButtonMask( uint32 xButtonState );

	Atom getQuitEventLoopMsg() {
		return quitEventLoopMsg_;
	}

	Atom getDeleteWindowMsg() {
		return deleteWindowMsg_;
	}

	Atom getVCFCreateWindowMsg() {
		return vcfCreateWindowMsg_;
	}

	Atom getVCFPaintWindowMsg() {
		return vcfPaintWindowMsg_;
	}

	void postToolkitMessage( int type, void* data=NULL );

	void postToolkitMessage( X11ToolkitMsg* msg );

	void postQuitMessage( int exitValue );

	void repaintControl( AbstractX11Control* control, Rect& bounds );

	void addTimer( const TimerEntry& entry );

	void removeTimer( const TimerEntry& entry );

	void xGrabPointer( AbstractX11Control* control );

	void xUnGrabPointer( AbstractX11Control* control );

	void sendPaintEvent( AbstractX11Control* control );

	void removeControlFromPaintEventQueue( AbstractX11Control* control );
protected:

	//common typedefs
	typedef std::map<AbstractX11Control*,AbstractX11Control*> PaintUpdateMap;

	void createDefaultParentWnd();

	Atom quitEventLoopMsg_;
	Atom deleteWindowMsg_;
	Atom vcfCreateWindowMsg_;
	Atom vcfPaintWindowMsg_;
	Display* x11Display_;
	xLib::Window defaultParentWnd_;
	bool consoleQuitHandlerCalled_;

	std::deque<X11ToolkitMsg*> toolkitMessages_;
	std::vector<TimerEntry> timerList_;


	//use a map - we only want the key - but this makes it easy to
	//not fool around with multiple entries
	PaintUpdateMap paintEventQueue_;

	void timersAvailable( std::vector<TimerEntry>& availableTimers );

	void fireTimers( std::vector<TimerEntry>& availableTimers );

	/**
	internal method for handling messages sent to
	the toolkit
	@return bool if this returns false, then a quit message has been received, otherwise
	it will return true
	*/
	bool handleToolkitMessages();

	/**
	internal method for handling paint events
	*/
	void handlePaintEvents();
	/**
	this method is to trap a Ctrl+C from the console, since this is a common way to
	run a program in X. It will use the signal(SIGINT, handler); call to do this
	*/
	static void  consoleQuitHandler( int sig );

	/**
	this method is a NON blocking call similar to XPending().
	@return bool returns true if there are 1 or more events in the queue, in which case
	you should use XNextEvent() to remove the next XEvent from the queue. If it returns
	false it means there are no events in the current queue.
	*/
	bool xPending();

	/**
	this method will be used to handle any X11 protocol error from the XServer.
	the current implementation will throw an exception, which will provide a more
	text string of the error and may be caught in a try/catch statement if appropriate
	*/
	static int x11ErrorHandler( Display* display, XErrorEvent* xError );

	static String x11GetRequestCodeString( int requestCode );
};


}; //end of namespace VCF


#endif // _VCF_X11UITOOLKIT_H__

/**
$Id$
*/
