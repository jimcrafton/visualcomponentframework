#ifndef _VCF_FRAME_H__
#define _VCF_FRAME_H__
//Frame.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */



namespace VCF{


#define FRAME_CLASSID			"ED88C0A2-26AB-11d4-B539-00C04F0196DA"


/**
These are enumerations for the possible frame styles
that can be set on Frame instance.
*/
enum FrameStyleType {
	/**
	The default style, this uses the default frame border
	and is resizeable. The exact "look" of this is dependant
	on the platforms windowing system. In Win32 this
	is a window that has a full size caption bar, with
	title, and frame edge borders that can be sized.
	*/
	fstSizeable = 0,

	/**
	This is a sizeable frame with no border, but can still be resized.
	Again, the exact "look" is depedant on the platforms windowing system.
	*/
	fstNoBorder,

	/**
	This makes the frame fixed, like a dialog. The frame will not be allowed 
	to be resized. While the look is windowing system dependant, on Win32 this 
	would look like a normal dialog, with the border edges on the frame.
	*/
	fstFixed,

	/**
	This makes the frame have no border, and disallows resizing.
	*/
	fstNoBorderFixed,

	/**
	This marks the frame so that is has a toolbar border and caption area
	and is resizeable.
	Again, the precise "look" is windowing system dependant, but for 
	Win32 this would create a window that looks like a toolbar, it would
	have the smaller caption bar and smaller border edges.
	*/
	fstToolbarBorder,

	/**
	This creates a look much like fstToolbarBorder, but the frame is not
	resizeable.
	*/
	fstToolbarBorderFixed
};

static String FrameStyleTypeNames[] = { "fstSizeable",
                                         "fstNoBorder",
										 "fstFixed",
										 "fstNoBorderFixed",
										"fstToolbarBorder",
										"fstToolbarBorderFixed"		 };
										
/**
These are the enumeration of the center directions.
*/
enum FrameCenterDirection {
	/**
	This marks that a frame is centered on another frame (the owner)
	*/
    fcdOnFrame = 0x0000,
    /**
    This marks that the frame is centered on the desktop
    */
    fcdOnShell = 0x0002,
    /**
    A frame could be centered Horizontaly, ...
    */
	fcdHorizontal = 0x0004,
	/**
	A frame could be centered verticaly
	*/
	fcdVertical = 0x0008,
	/**
	A frame could also be centered Horizontaly and Verticaly
	*/
	fcdBoth = fcdHorizontal | fcdVertical
};

/**
\class Frame Frame.h "vcf/ApplicationKit/Frame.h"
A frame is a component that houses other components,
plus has special adornments used for interacting with it.
These can include minimize, maximize, restore, system, and help buttons on the caption bar,
which is also part of the frame.

@delegates
	@del Frame::FrameClose
	@del Frame::FrameActivation
	@del Frame::FrameClosing
*/
class APPLICATIONKIT_API Frame : public VCF::Control, public DelegatedContainer<Frame>  {
public:

	class State : public Object, public Persistable{
	public:
		State();

		enum FrameDisplayState{
			fdsMaximized=0,
			fdsMinimized,
			fdsNormal
		};

		void applyState( Frame* frame );

		void initState( Frame* frame );

		virtual void loadFromStream( InputStream* stream, const MIMEType& type=MIMEType() );

		virtual void saveToStream( OutputStream* stream, const MIMEType& type=MIMEType() );
	protected:
		Rect bounds_;
		bool visible_;
		FrameDisplayState displayState_;
	};



	Frame();

	virtual ~Frame();


	enum FrameEventTypes{
		ACTIVATION_EVENT = CUSTOM_EVENT_TYPES + WINDOW_CONST + 6,
		CLOSE_EVENT = CUSTOM_EVENT_TYPES + WINDOW_CONST + 7,
		CLOSING_EVENT = CUSTOM_EVENT_TYPES + WINDOW_CONST + 8
	};

	/**
	@delegate FrameClose this is fired when the frame is closed, either in response to
	events from the underlying windowing system, or programmatically by calling the
	close() method.
	@event WindowEvent
	@eventtype Frame::CLOSE_EVENT
	@see close()
	*/
	DELEGATE(FrameDelegate,FrameClose)

	/**
	@delegate FrameActivation this is called when the frame becomes activated. Typically
	this is a result of events that the framework processes from the underlying
	windowing system. It is also fired when the activate() method is called.
	@event WindowEvent
	@eventtype Frame::ACTIVATION_EVENT
	@see activate()
	*/
	DELEGATE(WindowDelegate,FrameActivation)

	/**
	@delegate FrameClosing this is fired just before the windowing system attempts to close
	the frame. Depending on how a handler manipulates data on the fired FrameEvent, it
	can prevent the the frame from closing.
	@event FrameEvent
	@eventtype Frame::CLOSING_EVENT
	@see FrameEvent::setOkToClose
	@see allowClose()
	*/
	DELEGATE(FrameDelegate,FrameClosing)


	/**
	Sets the caption for the frame. While the exact effects of calling this method
	depend on windowing system the VCF is running on, in general a caption is
	displayed on the top of the frame, and is generally a non client area. This
	method will change the text that is displayed there.
	@param String the new caption to display in the Frame's caption area.
	*/
    virtual void setCaption( const String& caption );

	/**
	The current text of the Frame's caption.
	*/
    virtual String getCaption();

	/**
	Sets the client bounds only.
	*/
	virtual void  setClientBounds( Rect* bounds ) = 0;

	virtual void paint( GraphicsContext * context );

	/**
	Shows the frame.
	Generally the same as calling Control::setVisible(true)
	It also activates it.
	@see Control::setVisible
	*/
	virtual void show();

	/**
	Hides the frame. Dependending on the underlying windowing system, the frame may
	be minimized.
	*/
	virtual void hide();

	/**
	Closes the Frame. Must be implemented by classes that derive from Frame.
	*/
	virtual void close() = 0;

	/**
	Is this frame the top most frame amongst the application's current collection of
	frame windows.
	@return bool returns true if the frame is topmost, otherwise it returns false.
	*/
	virtual bool isFrameTopmost();

	/**
	Makes this frame a topmost floating window. This is typically used for frames that want
	to behave like toolbars.
	*/
	virtual void setFrameTopmost( const bool& isTopmost );

	/**
	returns the current frame style. This determines whether the frame is allowed to
	be resizeable through user interaction, or wether it's got a fixed size. This can 
	also determine the border style of the frame.
	@see FrameStyleType
	*/
	virtual FrameStyleType getFrameStyle(){
		return 	frameStyle_;
	};

	/**
	Sets the frame style
	@ see FrameStyleType
	*/
	virtual void setFrameStyle( const FrameStyleType& frameStyle ) = 0;

	/**
	By default a frame may have it's parent set to another control 
	without becoming a child control itself.
	@return bool returns true if the frame is to be allowed to
	act as a child control when it's setParent() method is called.
	*/
	bool allowFrameAsChildControl() {
		return allowFrameAsChildControl_;
	}

	void setAllowFrameAsChildControl( const bool& val ) {
		allowFrameAsChildControl_ = val;
	}


	/**
	Indicates whether or not this frame is active.
	@return bool returns true if the frame is active otherwise it returns false.
	*/
	bool isActive();

	/**
	Activates this frame.
	This base implementation activates the window 
	only if is not already the active one.
	*/
	virtual void activate();

	/**
	Indicates to the framework whether or not this frame should allow activation.
	Som frames do <i>not</i> support becoming activated, for example the tooltip frame,
	or the frame that houses the dropdown list for the ComboBoxControl. Must be implemented
	by derived classes.
	*/
	virtual bool allowsActivation() = 0;

	/**
	modifies the border of the frame to follow the 
	series of points contained in the path. 
	*/
	virtual void setBorderPath( Path* path ){};

	/**
	Sets the icon image. The behaviour of this is partially windowing system dependent,
	and some systems (Mac OSX, for example, or some X11 window managers) may choose to
	ignore this. However, typically the icon is displayed in the top left corner of the
	frame, in the non client area that houses the caption.

	*/
	virtual void setIconImage( Image* icon ) = 0;

	/**
	Returns the current image for the frames icon.
	*/
	virtual Image* getIconImage() = 0;
	
	virtual bool isActiveFrame() = 0;

	

	/**
	A static method uses to determine the current active frame.
	@return Frame the currently active frame. This may be NULL.
	*/
	static Frame* getActiveFrame();

	/**
	*don't call - for internal use only
	*/
	void setIsActive( const bool& active );	

	virtual void afterCreate( ComponentEvent* event );

	/**
	This method is called by the framework to determine whetehr or not the frame should
	actually be closed. This method is the first step in determining if a frame can
	be closed. If it returns true, then the FrameClosing is called. Note that the
	frame can still be prevented from closing depending on how the event handlers
	attached to the FrameClosing delegate are implemented. If this method returns
	false then the frame is not closed, and the FrameClosing event is not fired.
	*/
	virtual bool allowClose();

	/**
	* sets if we want to use the control's color to draw the control's background;
	* otherwise the theme background is drawn.
	*@param const bool&, true if we use the control's color, false if 
	* we draw the theme background.
	*/
	void setUseColorForBackground( const bool& val ) {
		useColorForBackground_ = val;
		repaint();
	}
	
	/**
	* gets if we use the control's color to draw the control's background
	*@return bool, true if we use the control's color, false if it uses the theme background.
	*/
	bool getUseColorForBackground() {
		return useColorForBackground_;
	}

	/**
	*don't call - for internal use only
	*/
	static void internal_setActiveFrame( Frame* activeFrame );

	/**
	*/
	static Dialog* createDialog( Class* dialogClazz, ResourceBundle* resBundle=NULL );

	/**
	*/
	static Window* createWindow( Class* windowClazz, ResourceBundle* resBundle=NULL );
	
	/**
	 * The generic center function. Centers the frame on owner by default or on screen
	 * when there is no owner.
	 */
	void center(uint32 direction = fcdBoth);
	
	/**
	 * Center the frame on the shell/desktop
	 */
	void centerOnShell(uint32 direction = fcdBoth) { 
		center(direction | fcdOnShell); 
	}

	
protected:
	static Frame* currentActiveFrame;
	String caption_;
	FrameStyleType frameStyle_;
	bool isTopmostFrame_;
	bool useColorForBackground_;
	bool allowFrameAsChildControl_;


	virtual void destroy();

};

}


#endif // _VCF_FRAME_H__

/**
$Id$
*/
