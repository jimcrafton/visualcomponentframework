#ifndef _VCF_XCBGRAPHICSTOOLKIT_H__
#define _VCF_XCBGRAPHICSTOOLKIT_H__


/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


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

class XCBFontPeer;

struct XCBFontEngine;

/**
*Class XCBGraphicsToolkit documentation
*/
class XCBGraphicsToolkit : public GraphicsToolkit {
public:

	XCBGraphicsToolkit();
	virtual ~XCBGraphicsToolkit();

	static XCBConnection* getConnection();
	static XCBSCREEN*     getScreen();
	static FcPattern* getFontPatternForFont( XCBFontPeer* fontPeer );
	static String getFontFileNameForFont( XCBFontPeer* fontPeer );
	static void updateFontAttributes( XCBFontPeer* fontPeer );

	static Font getDefaultFontFor( const int& type );

	static double getValue( const int& type, const String& text, Font* alternateFont );

	static Size getSize( const int& type, const String& text, Font* alternateFont );

	static Rect getRect( const int& type, Rect* rect, Font* alternateFont );

	static Size DLUToPixel( const Size& dlu, VCF::Font& font );
protected:
	virtual ContextPeer* internal_createContextPeer( const uint32& width, const uint32& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );

	virtual void internal_systemSettingsChanged();

private:
	XCBConnection *connection_;
	XCBSCREEN     *screen_;
	std::map<String,FcPattern*> fontPatternCache_;
	XCBFontEngine* fontEngine_;
	void loadSystemColors();
	Size getTextSize( const String& text, Font* font );
};

}; //end of namespace VCF

#endif // _VCF_XCBGRAPHICSTOOLKIT_H__

/**
$Id$
*/

