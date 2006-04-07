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


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/01/09 02:22:31  ddiego
*more osx code
*
*Revision 1.5.2.1  2005/11/10 04:43:27  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.5  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.3  2005/06/29 05:15:41  marcelloptr
*fixed some white spaces
*
*Revision 1.3.2.2  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.3.2.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.3  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/18 03:10:30  ddiego
*osx updates - add initial command button support, fixed rpoblem in mouse handling, and added dialog support.
*
*Revision 1.2.2.1  2004/10/10 15:23:12  ddiego
*updated os x code
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/27 04:26:04  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.7  2004/06/07 03:07:07  ddiego
*more osx updates dealing with mouse handling
*
*Revision 1.1.2.6  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


#endif // _VCF_OSXCONTROL_H__


