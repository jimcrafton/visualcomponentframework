#ifndef _VCF_AGGGRAPHICSPEERS_H__
#define _VCF_AGGGRAPHICSPEERS_H__

//AggGraphicsPeers.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_GRAYSCALEIMAGE_H__
#include "vcf/GraphicsKit/GrayScaleImage.h"
#endif 



#include "thirdparty/common/agg/include/agg_renderer_scanline.h"
#include "thirdparty/common/agg/include/agg_font_cache_manager.h"


namespace VCF {

class GRAPHICSKIT_API AggFont : public FontPeer  {
public:

	enum {
		fItalic = 0x01,
		fBold = 0x02,
		fStrikeout = 0x04,
		fUnderlined = 0x08,
		fFixedPitch = 0x10,
		fTrueType = 0x20,
	};

	AggFont( const String& fontName );

	AggFont( const String& fontName, const double& pointSize );

	virtual ~AggFont();

	void init();

	virtual OSHandleID getFontHandleID() ;

	virtual String getName() {
		return name_;
	}

	virtual void setName( const String& name ) {
		name_ = name;
	}

	virtual bool isTrueType()  {
		return characteristics_ & fTrueType ? true : false;
	}

	virtual double getPointSize() {
		return pointSize_;
	}

	virtual void setPointSize( const double val ) {
		pointSize_ = val;
	}

	virtual double getPixelSize() ;

	virtual void setPixelSize( const double pixelSize );

    virtual void setBold( const bool& val ) {
		characteristics_ = val ? characteristics_ | fBold : characteristics_ & ~fBold;
	}

    virtual bool getBold() {
		return characteristics_ & fBold ? true : false;
	}

    virtual bool getItalic() {
		return characteristics_ & fItalic ? true : false;
	}

    virtual void setItalic( const bool& val ) {
		characteristics_ = val ? characteristics_ | fItalic : characteristics_ & ~fItalic;
	}

    virtual bool getUnderlined() {
		return characteristics_ & fUnderlined ? true : false;
	}

    virtual void setUnderlined( const bool& val ) {
		characteristics_ = val ? characteristics_ | fUnderlined : characteristics_ & ~fUnderlined;
	}

    virtual bool getStrikeOut() {
		return characteristics_ & fStrikeout ? true : false;
	}

    virtual void setStrikeOut( const bool& val ) {
		characteristics_ = val ? characteristics_ | fStrikeout : characteristics_ & ~fStrikeout;
	}

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name );

	virtual double getAscent() {
		return ascent_;
	}

	virtual double getDescent() {
		return descent_;
	}

	virtual bool isFixedPitch() {
		return characteristics_ & fFixedPitch ? true : false;
	}

	virtual Size getTextSize( const String& text );

	virtual void updateLocaleSettings();

	virtual GlyphCollection* getGlyphCollection( const String& text )  ;

	virtual bool isEqual( Object* object );

	void setFont( Font* font ) {
		font_ = font;
	}
protected:
	String name_;
	double pointSize_;
	double ascent_;
	double descent_;
	uint32 characteristics_;

	Font* font_;
};

















class GRAPHICSKIT_API AggRGBAImage : public AbstractImage
{
public:
	AggRGBAImage();

	AggRGBAImage( const String& fileName );

	AggRGBAImage( const uint32& width, const uint32& height );

	AggRGBAImage( GraphicsContext* context, Rect* rect );	

	virtual ~AggRGBAImage();	

	virtual void setSize( const uint32 & width, const uint32 & height );	

	virtual void beginDrawing();

	virtual void finishedDrawing();
	
protected:	
	
};


class GRAPHICSKIT_API AggGrayScaleImage : public GrayScaleImage {
public:
	AggGrayScaleImage();

	AggGrayScaleImage( const String& fileName );

	AggGrayScaleImage( const uint32& width, const uint32& height );

	AggGrayScaleImage( GraphicsContext* context, Rect* rect );

	virtual ~AggGrayScaleImage();

	virtual void setSize( const uint32 & width, const uint32 & height );	

	virtual void beginDrawing();

	virtual void finishedDrawing();

	
};








class GRAPHICSKIT_API AggGraphicsResourceBundle : public Win32ResourceBundle, public GraphicsResourceBundlePeer {
public:
	AggGraphicsResourceBundle();

	virtual ~AggGraphicsResourceBundle();

	virtual Image* getImage( const String& resourceName );	
protected:
	
	
};









struct FontStruct {
#ifdef VCF_WIN32
	FontStruct(): engine(GetDC(GetDesktopWindow())), mgr(engine){}
#endif

	AGGFontEngine engine;
	AGGFontManager mgr;
	bool fontLoaded;
	agg::glyph_rendering glyphRendering;
	double currentPointSize;
	agg::rgba color;
};

struct CachedGlyph {
	const agg::glyph_cache* glyph;
	double kernX;
	double kernY;
};




class AggContextPeer : public ContextPeer {
public:

	AggContextPeer();

	AggContextPeer( const uint32& width, const uint32& height );

	AggContextPeer( OSHandleID contextID );

	virtual ~AggContextPeer();

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

	void closePath();

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
//	void internal_setImage(xcb_image_t *image);

	void internal_setGamma( double gamma );
protected:
	struct GlyphInfo {
		double x;
		double y;
		const agg::glyph_cache* glyph;
		bool visible;
	};


	GraphicsContext *context_;
//	xcb_image_t        *image_;

//    XCBSurface* drawingSurface_;

    agg::rendering_buffer renderBuffer_;
    agg::scanline_u8 scanline_;

    Rect currentClipRect_;
    agg::path_storage currentPath_;
    FontStruct* fonts_;
	std::vector<CachedGlyph*> cachedFontGlyphs_;
	String prevFontHash_;


	Point origin_;

    void resetPath();
	void renderScanlinesSolid( agg::rasterizer_scanline_aa<>& rasterizer, const agg::rgba& color  );
	void clearGlyphs();

	const agg::glyph_cache* glyph( int character, double& x, double& y );
	Size getTextSize( const String& text );
	void renderLine( const std::vector<GlyphInfo>& glyphs, size_t lastGlyphPos, const Size& currentLineSz,
						const Rect& bounds, const int32& drawOptions );
};








}; //end of namespace VCF


#endif //_VCF_AGGGRAPHICSPEERS_H__

