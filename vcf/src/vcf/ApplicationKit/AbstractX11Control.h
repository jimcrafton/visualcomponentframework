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


#endif // _VCF_ABSTRACTX11CONTROL_H__

/**
$Id$
*/
