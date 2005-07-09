#ifndef _VCF_ABSTRACTX11CONTROL_H__
#define _VCF_ABSTRACTX11CONTROL_H__
//AbstractX11Control.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
This class serves as a common implementation
for various methods of the ControlPeer interface.
Usually a class like X11Control, X11Window, etc will share
most of the same functionality, and only differ by a few overridden methods
*/
class AbstractX11Control : public ControlPeer {
public:

	AbstractX11Control();

	virtual ~AbstractX11Control();

	virtual long getHandleID() {
		return (long)wndHandle_;
	}

	/**
	* returns a text associated with the component. This usually gets used in the Control::getCaption() method.
	*/
	virtual String getText();

	/**
	* sets the text for the widget
	*/
	virtual void setText( const String& text );

	/**
	* sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
	*/
	virtual void setBounds( Rect* rect );

	/**
	*advanced function for changing the size of multiple child windows
	*/
	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

	/**
	* returns the bounds of the component in the coordinate system of the parent.
	*/
	virtual Rect* getBounds();

	/**
	* shows or hides the component.
	* This does NOT close the component (if invoked on a frame based component ).
	*/
	virtual void setVisible( const bool& visible );

	/**
	* returns wether or not the component is currently visible.
	*/
	virtual bool getVisible();

	/**
	* returns a bit-masked unsigned long that contains style constants.
	*  These style constants are defined in the VCF, and must
	* be translated to the particular windowing system being used.
	*/
	virtual unsigned long getStyleMask();

	/**
	* sets the current style mask.
	*  Should cause a repaint of the component, if neccessary.
	*/
	virtual void setStyleMask( const unsigned long& styleMask );

	/**
	* returns the component that this Peer is attached to.
	*/
	virtual Control* getControl();

	/**
	* attahces the Peer to a particular component. This should only be done once.
	*/
	virtual void setControl( Control* component );

	virtual void setCursor( Cursor* cursor );

	virtual void setParent( Control* parent );

	virtual Control* getParent();

	virtual bool isFocused();

	virtual void setFocus( const bool& focused );

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect=NULL );

	/**
	*this keeps the mouse events being sent to this control, even is the
	*mouse leaves the physical bounds of the control
	*/
	virtual void keepMouseEvents();

	/**
	*releases mouse events - goes back to normal event handling
	*/
	virtual void releaseMouseEvents();

	void addUpdateRect( const Rect& updateRect );

	virtual void handlePaintEvent();

	virtual void handleEvent( XEvent* x11Event );

	static void handleXEvent( xLib::Window wndHandle, XEvent* x11Event );

	static AbstractX11Control* getX11ControlFromXWindow( xLib::Window wndHandle );
protected:
	typedef std::map<xLib::Window,AbstractX11Control*> XwndControlMap;

	static void registerX11Control( AbstractX11Control* x11Control );
	static void unRegisterX11Control( AbstractX11Control* x11Control );

	static XwndControlMap xwndControlMap;

	AbstractX11Control* parent_;
	std::vector<Rect> updateRects_;

	xLib::Window wndHandle_;
	Control* control_;
	Rect bounds_;
	bool visible_;
	bool enabled_;
	ulong32 currentKeyState_;
	ulong32 currentButtonState_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/29 05:00:03  marcelloptr
*some white spaces
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/12 03:10:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.5  2003/01/08 00:19:46  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.1.2.4  2003/01/03 05:43:02  ddiego
*added some tune ups to the event loop method in the X11UIToolkit
*added code for closing a window and destroying child peers
*trying to track down why a core dump happens in the ApplicationKit::terminate
*method - seems to be due to bad pointers? Very very annoying....
*
*Revision 1.1.2.3  2003/01/01 05:06:06  ddiego
*changes start propagating VCF::Event instances back into the main Control
*event loop from native X11 events.
*
*Revision 1.1.2.2  2002/12/31 07:02:16  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.1.2.1  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Auto generated header for class AbstractX11Control
*/


#endif // _VCF_ABSTRACTX11CONTROL_H__


