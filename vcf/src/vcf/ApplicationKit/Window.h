#ifndef _VCF_WINDOW_H__
#define _VCF_WINDOW_H__
//Window.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */





namespace VCF {

class WindowPeer;


#define WINDOW_CLASSID				"ED88C0A1-26AB-11d4-B539-00C04F0196DA"


/**
\class Window Window.h "vcf/ApplicationKit/Window.h"  
A frame with min. max, restore, and system buttons.
Has a caption of the standard height.

@delegates
	@del Window::WindowRestore
	@del Window::WindowMaximize
	@del Window::WindowMinimize
*/
class APPLICATIONKIT_API Window : public Frame {
public:


	Window();

	Window( Control* control );

	enum WindowEvents{
		weRestore
	};

	virtual ~Window();

	/**
	@delegate WindowRestore this is fired when the window is restored back to it's
	original position. This event is generated by the underlying windowing system.
	@event WindowEvent
	@eventtype WINDOW_EVENT_RESTORE
	*/
	DELEGATE(WindowDelegate,WindowRestore)

	/**
	@delegate WindowMaximize this is fired when the window is maximized.
	This event is generated by the underlying windowing system.
	@event WindowEvent
	@eventtype WINDOW_EVENT_MAXIMIZE
	*/
	DELEGATE(WindowDelegate,WindowMaximize)

	/**
	@delegate WindowMinimize this is fired when the window is minimized.
	This event is generated by the underlying windowing system.
	@event WindowEvent
	@eventtype WINDOW_EVENT_MINIMIZE
	*/
	DELEGATE(WindowDelegate,WindowMinimize)


	virtual void setCaption( const String& caption );

	virtual void paint(GraphicsContext * context);

	/**
	*overridden to take into account client bounds
	**/
	virtual void resizeChildren( Control* control ) ;

	/**
	returns the client bounds of a window. This excludes the areas such as
	the nonclient border, the caption bar, etc.
	*/
	virtual Rect getClientBounds(const bool& includeBorder=true);


	virtual void  setClientBounds( Rect* bounds );

	/**
	Returns the menu bar for the window. While this is partially dependent on how
	the underlying windowing system implements menu bars, in general (at least
	on Win32 and most X11 window managers) the menu bar is attached to the window,
	and displayed directly under the caption bar. It is not considered part of the
	client region. By default, a newly created window has no menu bar.
	@return MenuBar the menu bar of the window, may be NULL.
	*/
	MenuBar* getMenuBar();


	/**
	Sets the menu bar for the window. Note, that this <i>currently</i> does
	not add the menuBar as a component of the window.
	*/
	void setMenuBar( MenuBar* menuBar );

	virtual void beforeDestroy( ComponentEvent* event );

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual double getPreferredWidth();

	virtual double getPreferredHeight();

	/**
	indicates whether or not the window is maximized.
	@return bool true if the window is minimized, otherwise
	it is false.
	*/
	bool isMaximized();

	/**
	Sets whether or not the window is maximized.
	*/
	void setMaximized( const bool& maximized );

	/**
	returns whether or not teh window is minimized
	@return bool true if the window is minimized, otherwise false.
	*/
	bool isMinimized();

	/**
	Sets whether or not the window is minimized.
	*/
	void setMinimized( const bool& minimized );

	/**
	restores the window to it's original position prior to being
	minimized or maximized.
	*/
	void restore();

	virtual bool allowsActivation() {
		return true;
	}

	virtual void setIconImage( Image* icon );

	virtual Image* getIconImage();
	
	virtual bool isActiveFrame();

	virtual void setBorderPath( Path* path );

	void handleEvent( Event* event );
protected:
	void postClose( Event* event );
	void onClose( FrameEvent* e );
    WindowPeer * windowPeer_;
	MenuBar* menuBar_;



	virtual void destroy();
};

};


#endif // _VCF_WINDOW_H__

/**
$Id$
*/
