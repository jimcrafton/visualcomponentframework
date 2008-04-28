#ifndef _VCF_AGGGRAPHICSTOOLKIT_H__
#define _VCF_AGGGRAPHICSTOOLKIT_H__
//AggGraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifdef VCF_WIN32
#include "thirdparty/common/agg/include/agg_font_win32_tt.h"
#endif


#define MENUITEMFONT			0
#define SELECTEDMENUITEMFONT	1
#define SYSTEMFONT				2
#define CONTROLFONT				3
#define MESSAGEFONT				4
#define TOOLTIPFONT				5

#define LABELHEIGHT									0
#define COMBOBOXHEIGHT								1
#define LISTITEMHEIGHT								2
#define BUTTONHEIGHT								3
#define RADIOBOXHEIGHT								4
#define CHECKBOXHEIGHT								5
#define TOOLTIPHEIGHT								6
#define SEPARATORHEIGHT								7
#define HEADERHEIGHT								8
#define TREEITEMHEIGHT								9
#define TEXTCONTROLHEIGHT							10
#define VERTICALPROGRESSWIDTH						11
#define HORIZONTALPROGRESSHEIGHT					12
#define MENUSEPARATORHEIGHT							13
#define MENUBARHEIGHT								14

#define INFORMATIONALCONTROLHEIGHT					15 //STATUS BAR
#define STATUSHEIGHT								INFORMATIONALCONTROLHEIGHT
#define VERTICALSCROLLBARTHUMBWIDTH					16
#define HORIZONTALSCROLLBARTHUMBHEIGHT				17
#define VERTICALSCROLLBARWIDTH						18
#define HORIZONTALSCROLLBARHEIGHT					19
#define MENUINDENT									20
#define WINDOWBORDERDELTA							21
#define CONTAINERBORDERDELTA						22
#define CONTROLVERTICALSPACING						23
#define CONTROLHORIZONTALSPACING					24
#define INFORMATIONCONTROLTOPSPACER					25
#define INFORMATIONCONTROLBOTTOMSPACER				26

#define MENUITEMSIZE								27
#define MENUITEMSEPARATORSIZE						28
#define VERTICALSLIDERTHUMBSIZE						29
#define HORIZONTALSLIDERTHUMBSIZE					30
#define TABSIZE										31
#define RADIOBOXBTNSIZE								32
#define CHECKBOXBTNSIZE								33
#define COMBOBOXDROPBTNSIZE							34
#define DISCLOSUREBUTTONSIZE						35

#define TABPANECONTENTRECT							36



namespace VCF  {



#ifdef VCF_WIN32


class TextMetric {
public:
	TextMetric(): tmHeight(0), tmAveCharWidth(0),
		tmMaxWidth(0), tmAscent(0), tmDescent(0){}

	double tmHeight;
	double tmAveCharWidth;
	double tmMaxWidth;
	double tmAscent;
	double tmDescent;
};


class AGGFontEngine : public agg::font_engine_win32_tt_int32 {
public:
	AGGFontEngine(HDC dc, unsigned max_fonts = 32) : 
            font_engine_win32_tt_int32( dc, max_fonts) {}	

	bool get_metrics( TextMetric* metrics ) const ;
	
};


typedef agg::font_cache_manager<AGGFontEngine> AGGFontManager;

#else
#endif



/**
*Class AggGraphicsToolkit documentation
*/
class AggGraphicsToolkit : public GraphicsToolkit {
public:
	AggGraphicsToolkit();

	virtual ~AggGraphicsToolkit();

	virtual ContextPeer* internal_createContextPeer( const uint32& width, const uint32& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual Font* internal_getDefaultSystemFont() {
		return systemFont_;
	}

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );

	virtual void internal_systemSettingsChanged();
	
	Size DLUToPixel( const Size& dlu, VCF::Font& font );

	Size getTextSize( const String& text, Font* font );
protected:
	void initSystemFont();
	void loadSystemColors();
	Font* systemFont_;

	AGGFontEngine fontEngine_;
	AGGFontManager fontManager_;
private:
};


}; //end of namespace VCF


#endif // _VCF_WIN32GRAPHICSTOOLKIT_H__

/**
$Id: AggGraphicsToolkit.h 2806 2006-06-27 20:22:43Z kdmix $
*/
