//OSXGraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"



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
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );


    sysColor = new Color();
	systemColors_[SYSCOLOR_FACE] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_FACE";

    GetThemeBrushAsColor( kThemeBrushButtonFaceActive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_HIGHLIGHT";

    GetThemeBrushAsColor( kThemeBrushButtonActiveLightHighlight, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_CAPTION";

    GetThemeBrushAsColor( kThemeBrushButtonFaceActive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_BORDER";

    GetThemeBrushAsColor( kThemeBrushButtonFrameActive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color( *Color::getColor("gray128") );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_DESKTOP";


    sysColor = new Color();
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_CAPTION_TEXT";

    GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_SELECTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION";

    GetThemeBrushAsColor( kThemeBrushFocusHighlight, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION_TEXT";

    GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_BORDER";

    GetThemeBrushAsColor( kThemeBrushButtonFrameInactive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_CAPTION";

    GetThemeBrushAsColor( kThemeBrushButtonFaceInactive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );


    sysColor = new Color( *Color::getColor("lemonchiffon") );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP";


    sysColor = new Color();
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP_TEXT";

    GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );


    sysColor = new Color();
	systemColors_[SYSCOLOR_MENU] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU";

    GetThemeBrushAsColor( kThemeBrushMenuBackground, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU_TEXT";

    GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW";

    GetThemeBrushAsColor( kThemeBrushUtilityWindowBackgroundActive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_TEXT";

    GetThemeBrushAsColor( kThemeTextColorBlack, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

    sysColor = new Color();
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_FRAME";

    GetThemeBrushAsColor( kThemeBrushButtonFrameActive, 32, TRUE, &themeColor );
    sysColor->setRGB( ((double)themeColor.red)/65535.0,
                        ((double)themeColor.green)/65535.0,
                        ((double)themeColor.blue)/65535.0 );

}

ContextPeer* OSXGraphicsToolkit::internal_createContextPeer( const unsigned long& width, const unsigned long& height )
{
	return new OSXContext( width, height );
}

ContextPeer* OSXGraphicsToolkit::internal_createContextPeer( const unsigned long& contextID )
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

Image* OSXGraphicsToolkit::internal_createImage( const unsigned long& width, const unsigned long& height )
{
	return new OSXImage(width, height);
}

Image* OSXGraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect )
{
	return new OSXImage( context, rect ) ;
}


/**
*CVS Log info
*$Log$
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


