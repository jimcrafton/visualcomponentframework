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

ContextPeer* OSXGraphicsToolkit::internal_createContextPeer( const unsigned long& width, const unsigned long& height )
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

Image* OSXGraphicsToolkit::internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType )
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
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/02/22 01:26:22  ddiego
*mac osx updates.
*
*Revision 1.5.2.1  2005/11/10 02:02:39  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.5  2005/07/09 23:06:00  ddiego
*added missing gtk files
*
*Revision 1.4  2005/01/08 20:52:48  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.3  2005/06/23 01:26:56  ddiego
*build updates
*
*Revision 1.3.2.2  2005/06/09 06:13:10  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.3.2.1  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/10 15:24:00  ddiego
*updated os x code in graphics stuff.
*
*Revision 1.2.2.1  2004/09/22 13:22:01  ddiego
*removed mgc code for drawing vector shapes. Unneccessary since agg does this just fine.
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.7  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.6  2004/05/31 13:20:59  ddiego
*more osx updates
*
*Revision 1.1.2.5  2004/05/06 03:01:29  ddiego
*checking in OSX updates
*
*Revision 1.1.2.4  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*/


