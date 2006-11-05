#ifndef _VCF_WIN32CUSTOMCONTROL_H__
#define _VCF_WIN32CUSTOMCONTROL_H__
//Win32CustomControl.h

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

class APPLICATIONKIT_API Win32CustomControl : public Object, public ControlPeer
{
public:
	Win32CustomControl( Control* component );
	virtual ~Win32CustomControl();

	static bool windowClassRegistered_;

	/**
	* returns a ID that identifies this control. On Win32 this corresponds to an HWND.
	*/
	virtual VCF::OSHandleID getHandleID();

	/**
	* returns a text associated with the component. This usually gets used in the Component::getCaption() method.
	*/
	virtual VCF::String getText();

	/**
	* sets the text for the widget
	*/
	virtual void setText( const VCF::String& text );

	/**
	* sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
	*/
	virtual void setBounds( VCF::Rect* rect );

	/**
	* returns the bounds of the component in the coordinate system of the parent.
	*/
	virtual VCF::Rect* getBounds();

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
	* returns a bit-masked uint32 that contains style constants.
	*  These style constants are defined in the VCF, and must
	* be translated to the particular windowing system being used.
	*/
	virtual uint32 getStyleMask();

	/**
	* sets the current style mask.
	*  Should cause a repaint of the component, if neccessary.
	*/
	virtual void setStyleMask( const uint32& styleMask );

	/**
	* returns the component that this Peer is attached to.
	*/
	virtual VCF::Control* getControl();

	/**
	* attahces the Peer to a particular component. This should only be done once.
	*/
	virtual void setControl( VCF::Control* component );

	virtual void setParent( VCF::Control* parent );

	virtual VCF::Control* getParent();

	virtual bool isFocused();

	virtual void setFocus( const bool& focused );

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

private:
	void registerWndClass();

	HWND wndHandle_;
	VCF::Control* component_;
	VCF::Rect bounds_;
	VCF::Point clickPt_;
};

};


#endif // _VCF_WIN32CUSTOMCONTROL_H__

/**
$Id$
*/
