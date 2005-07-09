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

	virtual void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );
	
	virtual void setBorder( Border* border );	

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


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.2  2005/06/29 05:15:41  marcelloptr
*fixed some white spaces
*
*Revision 1.3.2.1  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/10/28 03:34:16  ddiego
*more dialog updates for osx
*
*Revision 1.2.2.4  2004/10/25 03:23:57  ddiego
*and even more dialog updates. Introduced smore docs to the dialog class and added a new showXXX function.
*
*Revision 1.2.2.3  2004/10/23 18:10:43  ddiego
*mac osx updates, some more fixes for dialog code and for command button peer functionality
*
*Revision 1.2.2.2  2004/10/18 03:10:30  ddiego
*osx updates - add initial command button support, fixed rpoblem in mouse handling, and added dialog support.
*
*Revision 1.2.2.1  2004/10/10 15:23:12  ddiego
*updated os x code
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.8.2.2  2004/07/09 02:01:28  ddiego
*more osx updates
*
*Revision 1.1.2.8.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.8  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.7  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.6  2004/05/16 02:39:01  ddiego
*OSX code updates
*
*Revision 1.1.2.5  2004/05/07 23:22:45  ddiego
*more osx changes
*
*Revision 1.1.2.4  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/25 05:17:55  ddiego
*updates to ApplicationKit to support posting events and timer and idle time handlers for the OSX UI Toolkit.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXWINDOW_H__


