#ifndef _VCF_GTKCONTEXT_H__
#define _VCF_GTKCONTEXT_H__ 
//GTKContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class GTKImage;

/**
 
*/
class GRAPHICSKIT_API GTKContext : public Object, public ContextPeer
{
public:

	GTKContext();

	GTKContext( const unsigned long& width, const unsigned long& height );

	GTKContext( OSHandleID contextID );

	virtual ~GTKContext();

	void init();

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

	virtual void textAt( const Rect& bounds,
	                     const String & text,
	                     const long& drawOptions = 0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

	virtual void rectangle( const double & x1,
	                        const double & y1,
	                        const double & x2,
	                        const double & y2 );

	virtual void roundRect( const double & x1,
	                        const double & y1,
	                        const double & x2,
	                        const double & y2,
	                        const double & xc,
	                        const double & yc );

	virtual void ellipse( const double & x1,
	                      const double & y1,
	                      const double & x2,
	                      const double & y2 );

	virtual void arc( const double & x1,
	                  const double & y1,
	                  const double & x2,
	                  const double & y2,
	                  const double & x3,
	                  const double & y3,
	                  const double & x4,
	                  const double & y4 );


	virtual void polyline( const std::vector<Point>& pts );

	virtual void curve( const double & x1,
	                    const double & y1,
	                    const double & x2,
	                    const double & y2,
	                    const double & x3,
	                    const double & y3,
	                    const double & x4,
	                    const double & y4 );

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

	virtual void drawImage( const double& x,
	                        const double& y,
	                        Rect* imageBounds,
	                        Image* image );

	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL );

	virtual void drawThemeButtonFocusRect( Rect* rect );

	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );

	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	virtual void drawThemeDisclosureButton( Rect* rect,
	                                        DisclosureButtonState& state );

	virtual void drawThemeTab( Rect* rect, TabState& state );

	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabContent( Rect* rect, DrawUIState& state );

	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );

	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );

	virtual void drawThemeSlider( Rect* rect, SliderState& state );

	virtual void drawThemeProgress( Rect* rect, ProgressState& state );

	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	virtual void drawThemeEdge( Rect* rect, DrawUIState& state,
	                            const long& edgeSides,
	                            const long& edgeStyle );

	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state );

	virtual void drawThemeText( Rect* rect, TextState& state );

	virtual void checkHandle();

	virtual void releaseHandle();

	/*
	virtual void drawSelectionRect( Rect* rect );

	virtual void drawButtonRect( Rect* rect, const bool& isPressed );

	virtual void drawCheckboxRect( Rect* rect, const bool& isPressed );

	virtual void drawRadioButtonRect( Rect* rect, const bool& isPressed );

	virtual void drawVerticalScrollButtonRect( Rect* rect,
	                                           const bool& topButton,
	                                           const bool& isPressed );

	virtual void drawDisclosureButton( Rect* rect, const long& state );

	virtual void drawHorizontalScrollButtonRect( Rect* rect,
	                                             const bool& leftButton,
	                                             const bool& isPressed );

	virtual void drawTab( Rect* rect, const bool& selected, const String& caption );

	virtual void drawTabPage( Rect* rect );

	virtual void drawTickMarks( Rect* rect, const SliderInfo& sliderInfo );

	virtual void drawSliderThumb( Rect* rect, const SliderInfo& sliderInfo );

	virtual void drawSlider( Rect* rect, const SliderInfo& sliderInfo );

	virtual void drawHeader( Rect* rect );

	virtual void drawEdge( Rect* rect,
	                       const long& edgeSides,
	                       const long& edgeStyle );

	virtual void drawSizeGripper( Rect* rect );

	virtual void drawControlBackground( Rect* rect );

	virtual void drawWindowBackground( Rect* rect );

	virtual void drawMenuItemBackground( Rect* rect, const bool& selected );
	*/
	
	GdkDrawable* getDrawable()
	{
		return drawable_;
	}

	GdkGC* getGC()
	{
		return gdkGC_;
	}

	void setParentImage( GTKImage* image )
	{
		parentImage_ = image;
	}
	
protected:
	GdkDrawable* drawable_;
	GdkGC* gdkGC_;
	PangoContext* pangoCtx_;
	PangoLayout* pangoLayout_;

	unsigned long pixmapWidth_;
	unsigned long pixmapHeight_;

	//std::vector<PointOperation*> pathOperations_;
	//std::vector<TextOperation*> textOperations_;

	Point currentMoveTo_;
	Point oldOrigin_;
	Point origin_;

	bool inFillPath_;
	bool isMemoryCtx_;
	//bool pathStarted_;
	bool isXORModeOn_;
	bool alignToBaseline_;

	GraphicsContext* context_;

	GTKImage* parentImage_;

	GtkStyle* getGTKStyle( GtkWidget* widget );
	GtkStateType getGTKState( GtkWidget* widget );

	//void clearBuffer();
	//void clearPathBuffer();
	//void clearTextBuffer();
	//void testBuffer();

	//void execPathOperations();
};

}


#endif // _VCF_GTKCONTEXT_H__

/**
$Id$
*/
