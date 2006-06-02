#ifndef _VCF_WIN32CONTEXT_H__
#define _VCF_WIN32CONTEXT_H__
//Win32Context.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32Context.h: interface for the Win32Context class.


#include <deque>


namespace VCF
{


class GRAPHICSKIT_API Win32Image;
/**
*A Context provides the lowest level graphics interface to the
*native systems 2D drawing operations. Based loosely on PostScript,
*a Context takes a series of of drawing operations, or commands
*(lineTo, moveTo, etc), and then executes them by either filling or
*strokeing the path(s) that result from the commands. Thus calling
*ellipse() will not draw anything till the strokePath() or fillPath()
*methods have been called. All path commands should add their information
*to a stack of some sort that is then looped through and executed
*using the appropriate native graphics calls. At each path command
*a test should be made as to whether the buffer should be cleared.
*The buffer should be cleared only after the stroke of fill methods
*have been  called. For example:
*
*<p><pre>
*	ellipse(23,23,45,67) //added to buffer
*	moveTo(89,100) //add to buffer
*	lineTo(300,40) //add to buffer
*	strokePath()
*	fillPath()
*	rectangle(200,300,400,400)//buffer cleared, then add to buffer
*</pre></p>
*/
class GRAPHICSKIT_API Win32Context  : public Object, public ContextPeer {
public:
	Win32Context();

	/**
	* creates a new HDC from scratch
	*/
	Win32Context( const unsigned long& width, const unsigned long& height );

	Win32Context( OSHandleID contextID );

	virtual ~Win32Context();

public:
	/**
	*
	*
	*/
	virtual void setContext( GraphicsContext* context );

	/**
	*
	*
	*/
	virtual GraphicsContext* getContext();

	/**
	*
	*
	*/
	virtual OSHandleID getContextID();

	/**
	*
	*
	*/
	virtual void setContextID( OSHandleID handle );

	/**
	*
	*
	*/
	void init();

	/**
	*
	*
	*/
	virtual void setOrigin( const double& x, const double& y );

	/**
	*
	*
	*/
	virtual Point getOrigin();

	/**
	*
	*
	*/
	virtual bool isAntiAliasingOn(){
		return false;
	}

	/**
	*
	*
	*/
	virtual void setAntiAliasingOn( bool antiAliasingOn ) {} //no-op for now


	/**
	*
	*
	*/
	virtual bool prepareForDrawing( long drawingOperation );

	/**
	*
	*
	*/
	virtual void finishedDrawing( long drawingOperation );

	/**
	*
	*
	*/
	virtual bool isMemoryContext();

	/**
	*
	*
	*/
	virtual void copyContext( const Rect& sourceRect, const Rect& destRect,
	                          ContextPeer* sourceContext );


	/**
	*
	*
	*/
	virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	/**
	*
	*/
	virtual double getTextWidth( const String& text );

	/**
	*
	*/
	virtual double getTextHeight( const String& text );


	/**
	*
	*/
	virtual void lineTo( const double & x, const double & y );

	/**
	*
	*/
	virtual void moveTo( const double & x, const double & y );

	/**
	*
	*/
	virtual void rectangle( const double & x1, const double & y1, const double & x2, const double & y2 );

	/**
	*
	*/
	virtual void roundRect( const double & x1, const double & y1, const double & x2, const double & y2,
	                        const double & xc, const double & yc );


	/**
	*
	*/
	virtual void ellipse( const double & x1, const double & y1, const double & x2, const double & y2 );

	/**
	*
	*/
	virtual void arc( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                  const double & y3, const double & x4, const double & y4 );

/*
	virtual void pie( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                  const double & y3, const double & x4, const double & y4 );

	virtual void chord( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                    const double & y3, const double & x4, const double & y4 );
*/

	/**
	*
	*/
	virtual void polyline( const std::vector<Point>& pts );

	/**
	*
	*/
	virtual void curve( const double & x1, const double & y1, const double & x2, const double & y2,
	                    const double & x3, const double & y3, const double & x4, const double & y4 );

	/**
	*
	*
	*/
	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode );

	virtual void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image );


	/* utility functions */

	/**
	*
	*
	*/
	void copyToImage( Win32Image* image );

	/**
	* make sure we always have the HDC ( device context handle ) we need.
	* Normally the paint function already receives the correct handle
	* so this is a no-op (does nothing).
	* In the case of a control we may need to get a different HDC, for example when
	* painting under a mouse move event or getting other informations depending
	* on the device context.
	* @see releaseHandle()
	*/
	virtual void checkHandle(){};

	/**
	* Does the opposite operation of checkHandle(), i.e. restores
	* the previous HDC if it has been changed by checkHandle().
	* Normally the paint function already receives the correct handle
	* in checkHandle() so this one too is a no-op.
	* @see checkHandle()
	*/
	virtual void releaseHandle();


	/**
	*
	*
	*/
	virtual void setTextAlignment( const bool& alignTobaseline );

	/**
	*
	*
	*/
	virtual bool isTextAlignedToBaseline();

	/**
	*
	*
	*/
	virtual void setClippingPath( Path* clippingPath );

	/**
	*
	*
	*/
	virtual void setClippingRect( Rect* clipRect );


	/**
	*
	*/
	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );

	/**
	*
	*/
	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	/**
	*
	*/
	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL );

	/**
	*
	*/
	virtual void drawThemeButtonFocusRect( Rect* rect );

	/**
	*
	*/
	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	/**
	*
	*/
	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );

	/**
	*
	*/
	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	/**
	*
	*/
	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	/**
	* Draws a button that is used to open up more details, for example
	* the button that opens up a tree node to reveal it's children, that is compliant
	* with the native windowing systems default look and feel.
	* On Win32 this is usually represented by the "+" and "-" look as found on
	* the tree controls, while on OSX it is the little triangles
	*/
	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	/**
	* Draws a tab, the part of the TabbedPages control that acts like a
	* little button to activate a page, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeTab( Rect* rect, TabState& state );

	/**
	Draws a tab page - the page on which other controls for the page are
	parented to, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabContent( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );

	/**
	* Draws a tick mark, like that used for a slider control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );

	/**
	* Draws a slider control, like that used for a slider control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeSlider( Rect* rect, SliderState& state );

	/**
	* Draws a progress bar control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeProgress( Rect* rect, ProgressState& state );

	/**
	*
	*
	*/
	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	/**
	* draws a header control that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	/**
	* draws edges, useful for separators, that is compliant
	* with the native windowing systems default look and feel.
	* use a mask or 1 or more values of type ContextPeer::EdgeType
	* to indicate which sides of the rect to draw an edge on
	*/
	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle );

	/**
	* Draws a size gripper for resizing a control/window that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	/**
	* Draws a them compliant background
	*/
	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	/**
	* Draws the background appropriate for a menu item that is compliant
	* with the native windowing systems default look and feel.
	* This is typically called first by a menu item to give it a standard
	* look and feel in it's background before drawing any thing else
	*/
	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state );

	/**
	*
	*
	*/
	virtual void drawThemeText( Rect* rect, TextState& state );


protected:

	void drawImageAGG(  const double& x, const double& y, Rect* imageBounds, Image* image );

	void drawGrayScaleImage( const double& x, const double& y, Rect* imageBounds, Image* image );
	/**
	*
	*
	*/
	void prepareDCWithContextFont( HFONT& fontHandle );

	/**
	*
	*
	*/
	HDC getDC();

	/**
	* Utility function to draw a transparent bitmap
	*/
	static void drawTransparentBitmap( HDC hdc, HBITMAP hBitmap, long xStart,
	                                   long yStart, COLORREF cTransparentColor );

	


private:

protected:
	HRGN clipRGN_;

	bool pathStarted_;

	Point oldOrigin_;
	Point origin_;
	bool inFillPath_;
	HDC dc_;
	HBITMAP memBitmap_;
	HBITMAP originalBitmap_;

	HBRUSH currentHBrush_;
	HPEN currentHPen_;
	HFONT currentHFont_;

	int currentDCState_;

	bool isMemoryCtx_;
	GraphicsContext* context_;

	bool alignToBaseline_;
};

};


#endif // _VCF_WIN32CONTEXT_H__

/**
$Id$
*/
