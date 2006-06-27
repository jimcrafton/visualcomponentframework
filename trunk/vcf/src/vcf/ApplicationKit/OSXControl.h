#ifndef _VCF_OSXCONTROL_H__
#define _VCF_OSXCONTROL_H__
//OSXControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {


class OSXControl : public ObjectWithEvents, public ControlPeer {
public:
	enum MouseState{
		msNoState=0,
		msDown,
		msUp,
		msEntered,
		msExited
	};
	
	OSXControl( Control* control );

	virtual ~OSXControl();

	virtual OSHandleID getHandleID();

	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual String getText() {
		return String();
	}

	virtual void setText( const String& text ){};

	virtual void setBounds( Rect* rect );

	virtual bool beginSetBounds( const uint32& numberOfChildren );

	virtual void endSetBounds();

	virtual Rect getBounds();

	virtual void setVisible( const bool& visible );

	virtual bool getVisible();

	virtual Control* getControl();

	virtual void setControl( Control* component );

	virtual void setCursor( Cursor* cursor );

	virtual void setParent( Control* parent );

	virtual Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect, const bool& immediately );
	
	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );
	
	virtual void setBorder( Border* border );
	
	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );
	
	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );
	
	static OSXControl* getControlFromControlRef( ControlRef control );
protected:
	ControlRef hiView_;
	Control* control_;
	EventHandlerRef handlerRef_;
	MouseState mouseState_;
	::Point lastMousePt_;
	
	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );

	OSStatus handleControlTrack( EventRef theEvent );
	
	OSStatus handleWrappedControlTrack( EventRef theEvent );
	
	OSStatus handleWrappedControlTrackDone( EventRef theEvent );
	
	OSStatus handleWrappedControlHitTest( EventRef theEvent );
	
	OSStatus installStdControlHandler();

	static EventHandlerUPP getEventHandlerUPP();
	static OSStatus handleOSXEvents(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData);
};


}; //end of namespace VCF


#endif // _VCF_OSXCONTROL_H__

/**
$Id$
*/
