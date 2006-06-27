//OSXGraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/OSXGraphicsResourceBundle.h"



using namespace VCF;

OSXGraphicsToolkit::OSXGraphicsToolkit()
{
	loadSystemColors();
}

OSXGraphicsToolkit::~OSXGraphicsToolkit()
{

}

void OSXGraphicsToolkit::loadSystemColors()
{
	RGBColor themeColor;

	Color* sysColor = NULL;

	sysColor = new Color();
	systemColors_[SYSCOLOR_SHADOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SHADOW";
	GetThemeBrushAsColor( kThemeBrushButtonActiveDarkShadow, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_FACE] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_FACE";
	GetThemeBrushAsColor( kThemeBrushButtonFaceActive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_HIGHLIGHT";
	GetThemeBrushAsColor( kThemeBrushButtonActiveLightHighlight, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_CAPTION";
	GetThemeBrushAsColor( kThemeBrushButtonFaceActive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_BORDER";
	GetThemeBrushAsColor( kThemeBrushButtonFrameActive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color( *Color::getColor("gray128") );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_DESKTOP";


	sysColor = new Color();
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_CAPTION_TEXT";
	GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_SELECTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION";
	GetThemeBrushAsColor( kThemeBrushFocusHighlight, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION_TEXT";
	GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_BORDER";
	GetThemeBrushAsColor( kThemeBrushButtonFrameInactive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_CAPTION";
	GetThemeBrushAsColor( kThemeBrushButtonFaceInactive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color( *Color::getColor("lemonchiffon") );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP";


	sysColor = new Color();
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP_TEXT";
	GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_MENU] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU";
	GetThemeBrushAsColor( kThemeBrushMenuBackground, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU_TEXT";
	GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW";
	GetThemeBrushAsColor( kThemeBrushUtilityWindowBackgroundActive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_TEXT";
	GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );


	sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_FRAME";
	GetThemeBrushAsColor( kThemeBrushButtonFrameActive, 32, TRUE, &themeColor );
	sysColor->setRGB16( themeColor.red, themeColor.green, themeColor.blue );

}

void OSXGraphicsToolkit::internal_systemSettingsChanged()
{

}

ContextPeer* OSXGraphicsToolkit::internal_createContextPeer( const uint32& width, const uint32& height )
{
	return new OSXContext( width, height );
}

ContextPeer* OSXGraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	return new OSXContext( contextID );
}

FontPeer* OSXGraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new OSXFont( fontName );
}

FontPeer* OSXGraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	return new OSXFont( fontName, pointSize );
}

Image* OSXGraphicsToolkit::internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	return new OSXImage(width, height);
}

Image* OSXGraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	return new OSXImage( context, rect ) ;
}

PrintSessionPeer* OSXGraphicsToolkit::internal_createPrintSessionPeer()
{
	return NULL;
}

GraphicsResourceBundlePeer* OSXGraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new OSXGraphicsResourceBundle();
}

double OSXGraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	return 72.0;
}


/**
$Id$
*/
