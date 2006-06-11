#ifndef _VCF_OSXCONTEXT_H__
#define _VCF_OSXCONTEXT_H__
//OSXContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class GraphicsContext;


class OSXContext  : public ContextPeer, public Object {
public:

	
	enum LastPrimitive{
		lpNone, 
		lpMove, 
		lpLine
	};


	OSXContext();
	/**
	*Creates a new HDC from scratch
	*/
	OSXContext( const unsigned long& width, const unsigned long& height );

	OSXContext( OSHandleID contextID );

	virtual ~OSXContext();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual OSHandleID getContextID();

	virtual void setContextID( OSHandleID handle );

	virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

    virtual void rectangle(const double & x1, const double & y1, const double & x2, const double & y2);

	virtual void roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc);

    virtual void ellipse(const double & x1, const double & y1, const double & x2, const double & y2 );

	virtual void arc(const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
						 const double & y3, const double & x4, const double & y4);

    virtual void polyline(const std::vector<Point>& pts);

    virtual void curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4);

    virtual void lineTo(const double & x, const double & y);

    virtual void moveTo(const double & x, const double & y);

	void init();

	virtual void setOrigin( const double& x, const double& y );

	virtual Point getOrigin();

	virtual void copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext );

	virtual bool isMemoryContext();

	virtual bool prepareForDrawing( long drawingOperation );

	virtual void finishedDrawing( long drawingOperation );

	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode );
	
	virtual void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image );

	virtual void checkHandle();

	virtual void releaseHandle();

	virtual bool isXORModeOn();

	virtual void setXORModeOn( const bool& XORModeOn );

	virtual bool isAntiAliasingOn() {
		return antialiasingOn_;
	}
	
	virtual void setAntiAliasingOn( bool antiAliasingOn );
	
	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );
	
	
	
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
	
	virtual void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );
	
	void setCGContext( CGContextRef cgRef, GrafPtr port, const Rect& ownerRect  );
	void setPortFromImage( GrafPtr port, uint32 width, uint32 height );
	
	
	CGContextRef getCGContext() {
		return contextID_;
	}
	
	GrafPtr getGrafPtr() {
		return grafPort_;
	}
protected:
	CGContextRef contextID_;
    GrafPtr grafPort_;
	unsigned char* inMemoryImage_;
    ulong32 imgWidth_;
    ulong32 imgHeight_;
	GraphicsContext* context_;
	long currentDrawingOperation_;
	ATSUTextLayout textLayout_;
	VCF::Point origin_;
    bool xorModeOn_;
    Rect ownerRect_;
	LastPrimitive lastPrimitive_;
	VCF::Point lastPrimitiveP1_;
	VCF::Point lastPrimitiveV1_;
	bool antialiasingOn_;




	void atsuDrawTextInBox(	const VCF::Rect& rect, const long& drawOptions );

	double getLayoutWidth( ATSUTextLayout layout );

	void setLayoutWidth( ATSUTextLayout layout, double width );
	VCF::Size getLayoutDimensions( const String& text );
	
	void endLastPrimitive();
	void finishLastPrimitive(const double & x, const double & y);
};

}; //end of namespace VCF


#endif // _VCF_OSXCONTEXT_H__

/**
$Id$
*/
