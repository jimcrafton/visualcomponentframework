#ifndef _VCF_XCBCONTEXTPEER_H__
#define _VCF_XCBCONTEXTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "thirdparty/common/agg/include/agg_renderer_scanline.h"
#include "thirdparty/common/agg/include/agg_font_cache_manager.h"

namespace VCF  {

	
	
	
/**
This represents the struct that we need to build a VCF graphics context 
peer. We will need the xcb image, almost certainly the window/drawable,
and probably the GC. We also define a specific type of pixel format for 
this surface - all we care about is the RGB components, we don't need the
alpha channel for this level.
*/
struct XCBSurface {
    XCBGCONTEXT* context;
    XCBDRAWABLE* drawable;
    XCBImage* drawableImage;

	typedef agg::pixfmt_argb32 PixFmt;
	typedef agg::pixfmt_argb32_pre PixFmtPre;
	typedef agg::rgba8 ColorType;
	typedef agg::order_argb ComponentOrder;
};


struct FontStruct;
struct CachedGlyph;
	
class XCBContextPeer : public ContextPeer {
public:
	


	XCBContextPeer();

	XCBContextPeer( const uint32& width, const uint32& height );

    /**
    In this case the OSHandleID will be a vaild pointer to a XCBSurface
    struct. The XCBSurface pointer will have valid values set for all it's
    members.
    */
	XCBContextPeer( OSHandleID contextID );

	virtual ~XCBContextPeer();

	void init();

	void checkHandle();

	void releaseHandle();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual OSHandleID getContextID();

	virtual void setContextID( OSHandleID contextID );

	virtual bool prepareForDrawing( int32 drawingOperation );

	virtual void finishedDrawing( int32 drawingOperation );

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );

	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void textAt( const Rect& bounds, const String & text, const int32& drawOptions=0 );

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

	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const int32& edgeSides, const int32& edgeStyle );

	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	virtual void drawThemeMenuItemText( Rect* rect, MenuState& state );

	virtual void drawThemeText( Rect* rect, TextState& state );

	////////////////////////////////////
	void internal_setImage(XCBImage *image);
protected:
	GraphicsContext *context_;
	XCBImage        *image_;

    XCBSurface* drawingSurface_;


    agg::rendering_buffer renderBuffer_;
    agg::scanline_u8 scanline_;

    Rect currentClipRect_;
    agg::path_storage currentPath_;
    FontStruct* fonts_;
	std::vector<CachedGlyph*> cachedFontGlyphs_;
	String prevFontHash_;
    
    void resetPath();
	void renderScanlinesSolid( agg::rasterizer_scanline_aa<>& rasterizer, const agg::rgba& color  );
	void clearGlyphs();

	const agg::glyph_cache* glyph( int character, double& x, double& y );
};

}; //end of namespace VCF

#endif // _VCF_XCBCONTEXTPEER_H__

/**
$Id$
*/

