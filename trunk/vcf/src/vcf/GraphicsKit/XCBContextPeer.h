#ifndef _VCF_XCBCONTEXTPEER_H__
#define _VCF_XCBCONTEXTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

class XCBContextPeer : public ContextPeer {
public:
	XCBContextPeer();

	XCBContextPeer( const unsigned long& width, const unsigned long& height );

	XCBContextPeer( OSHandleID contextID );

	void init();

	void checkHandle();

	void releaseHandle();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual OSHandleID getContextID();

	virtual void setContextID( OSHandleID contextID );

	virtual bool prepareForDrawing( long drawingOperation );

	virtual void finishedDrawing( long drawingOperation );

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );

	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

	virtual void rectangle( const double & x1, const double & y1,
								const double & x2, const double & y2 );

	virtual void roundRect( const double & x1, const double & y1,
								const double & x2, const double & y2,
								const double & xc, const double & yc );

	virtual void ellipse( const double & x1, const double & y1,
							const double & x2, const double & y2 );

	virtual void arc( const double & x1, const double & y1,
						const double & x2, const double & y2,
						const double & x3, const double & y3,
						const double & x4, const double & y4 );

	virtual void polyline( const std::vector<Point>& pts );

	virtual void curve( const double & x1, const double & y1, const double & x2, const double & y2,
						const double & x3, const double & y3, const double & x4, const double & y4 );

	virtual void moveTo( const double & x, const double & y );

	virtual void lineTo( const double & x, const double & y );


	virtual void setOrigin( const double& x, const double& y );

	virtual Point getOrigin();

	virtual void copyContext( const Rect& sourceRect,
							  const Rect& destRect,
							  ContextPeer* sourceContext );

	virtual bool isMemoryContext();

	virtual bool isXORModeOn();

	virtual void setXORModeOn( const bool& XORModeOn );

	virtual bool isAntiAliasingOn();

	virtual void setAntiAliasingOn( bool antiAliasingOn );

	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode );

	virtual void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image );

	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL );

	virtual void drawThemeButtonFocusRect( Rect* rect );

	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );

	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	virtual void drawThemeTab( Rect* rect, TabState& state );

	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabContent( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );

	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );

	virtual void drawThemeSlider( Rect* rect, SliderState& state );

	virtual void drawThemeProgress( Rect* rect, ProgressState& state );

	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle );

	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state );

	virtual void drawThemeText( Rect* rect, TextState& state );

protected:
	GraphicsContext* context_;
    XCBGCONTEXT      xcbContext_;
	XCBImage        *image;

};

}; //end of namespace VCF

#endif // _VCF_XCBCONTEXTPEER_H__

/**
$Id$
*/

