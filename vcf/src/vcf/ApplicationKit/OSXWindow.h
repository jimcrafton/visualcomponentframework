#ifndef _VCF_OSXWINDOW_H__
#define _VCF_OSXWINDOW_H__
//OSXWindow.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/WindowPeer.h"

namespace VCF {


class OSXWindow : public Object, public ControlPeer, public WindowPeer {
public:

	enum WindowState{
		wsNone = 0,
		wsMaximized,
		wsMinimized,
		wsNormal
	};

	OSXWindow();

	OSXWindow( Control* control, Control* owner );

	virtual ~OSXWindow();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)windowRef_;
	}

	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setBounds( Rect* rect );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

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
	

	Rect internal_getBounds() {
		return bounds_;
	}

	void internal_setBounds( const Rect& bounds ) {
		bounds_ = bounds;
	}


	//Window peer methods
	virtual Rect getClientBounds();

	virtual void  setClientBounds( Rect* bounds );

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual bool isMaximized();

	virtual void setMaximized( const bool maximised );

	virtual bool isMinimized();

	virtual void setMinimized( const bool& minimized );

	virtual void restore();

	virtual void setIconImage( Image* icon );
	
	virtual bool isActiveWindow();

	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );

	bool isComposited();
	
	static OSXWindow* getWindowFromWindowRef( WindowRef window );
	
	ControlRef getRootControl();
	
	unsigned long getCurrentMouseBtn() {
		return currentMouseBtn_;
	}
	
	virtual WindowAttributes getCreationWinAttrs();
	
	virtual WindowClass getCreationWinClass();
protected:
	static EventHandlerUPP getEventHandlerUPP();

	WindowRef windowRef_;
	Control* control_;
	Rect bounds_;
	EventHandlerRef handlerRef_;
	EventHandlerRef contentViewHandlerRef_;	
	//RgnHandle mouseTrackRgn_;
	MouseTrackingRef mouseTrackRef_;	
	unsigned long currentMouseBtn_;
	bool internalClose_;	

	RgnHandle determineUnobscuredClientRgn();
	
	static OSStatus handleOSXEvents(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData);
	
   	Control* getControlForMouseEvent( EventRef event );
	
	static OSStatus wndContentViewHandler(EventHandlerCallRef nextHandler, EventRef theEvent, void* userData);
	
	OSStatus handleContentViewDraw( EventHandlerCallRef nextHandler, EventRef theEvent );
	
	void copyControlsFromWndRef( WindowRef oldWndRef );
};


}; //end of namespace VCF


#endif // _VCF_OSXWINDOW_H__

/**
$Id$
*/
