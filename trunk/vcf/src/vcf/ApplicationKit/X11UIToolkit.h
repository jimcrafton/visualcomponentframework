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

	TimerEntry( ulong32 frequency ):frequency_(frequency)  {
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

	ulong32 getMillisecondsDifference( struct timeval* val ) const {
		double t1, t2;

		t1 =  (double)(current_.tv_sec * 1000.0) +
				(double)current_.tv_usec/(1000.0);

		t2 =  (double)(val->tv_sec * 1000.0) + (double)val->tv_usec/(1000.0); //convert to Milliseconds

		return (ulong32)(t2 - t1);
	}

	void resetCurrentTime() {
		struct	timezone timeZone;
		::gettimeofday( &current_, &timeZone );
	}

	ulong32 getFrequency() const {
		return frequency_;
	}
protected:

	//time, in milliseconds, before this
	//entry should be fired
	ulong32 frequency_;

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

	virtual void registerTimerHandler( Object* source, EventHandler* handler, const ulong32& timeoutInMilliSeconds );

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

	ulong32 translateKeyMask( ulong32 xKeyState );

	ulong32 translateButtonMask( ulong32 xButtonState );

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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:11:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.15  2003/02/03 05:22:47  ddiego
*added support for command types to the PuchButton class
*added support for clicks in the PuchButton class to auto close a dialog
*if it is parented to one, similar to the CommandButton. This is part of the
*gradual phase out of the CommandButton class
*Add supprt for drawing a focus rect in the PushButton class
*plugged in tabbing bahaviour to the X11UIToolkit. It seems as though
*"Shift" + "Tab" is not being picked up properly
*Finished implementing the X11Dialog::showMessage(String,String) method
*and also add some finishing touches to teh X11Dialog so it displays correctly
*Add some finishing touches to the X11UIToolkit::runModalEventLoop() as well
*
*Revision 1.1.2.14  2003/02/02 04:56:02  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.1.2.13  2003/01/19 20:18:21  ddiego
*changes to try and optimize painting. didn't work for this go around :(
*
*Revision 1.1.2.12  2003/01/19 03:11:32  ddiego
*misc coding fixes, added x11 error handler
*
*Revision 1.1.2.11  2003/01/13 04:57:03  ddiego
*added a fix for the X11COntext::gettextWidth and Height, now returns correct values
*static makefile for the various kits is now ready to use for all
*AbstractX11Controll::keepMouseEvents is now working correctly
*
*Revision 1.1.2.10  2003/01/11 23:17:24  ddiego
*added extra functionality to the static makefile in vcf/build/make
*added some bug fixes to X11
*
*Revision 1.1.2.9  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.1.2.8  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.1.2.7  2003/01/02 04:07:18  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.1.2.6  2003/01/01 05:06:06  ddiego
*changes start propagating VCF::Event instances back into the main Control
*event loop from native X11 events.
*
*Revision 1.1.2.5  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.1.2.4  2002/12/27 06:44:45  ddiego
*added initial control peer for X11 controls
*
*Revision 1.1.2.3  2002/12/26 04:32:11  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
*Revision 1.1.2.2  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*/


#endif // _VCF_X11UITOOLKIT_H__


