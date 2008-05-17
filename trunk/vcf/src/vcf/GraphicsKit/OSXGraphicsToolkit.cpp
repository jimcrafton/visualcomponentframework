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



namespace  VCF { 



//UIMetricsManager implementation for OSX
class OSXUIMetricsManager : public UIMetricsManager {
public:
	OSXUIMetricsManager(){}

	virtual ~OSXUIMetricsManager(){}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result("Arial", 13);

		result.setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_CAPTION_TEXT ) );
		
		Str255 fontName;
		SInt16 fontSize = 0;
		Style fontStyle = 0;
		OSStatus err = noErr;
		
		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
				}				
			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );					
				}
			}
			break;

			case UIMetricsManager::ftSystemFont : {
				err = GetThemeFont( kThemeSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
			
			case UIMetricsManager::ftControlFont :   {
				err = GetThemeFont( kThemeLabelFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
			

			case UIMetricsManager::ftMessageFont : {
				err = GetThemeFont( kThemeEmphasizedSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftToolTipFont : {
				err = GetThemeFont( kThemeSmallSystemFont, smSystemScript, fontName, &fontSize, &fontStyle );	
				if ( err != noErr ) {
					CFTextString name(fontName);
					result.setName( name );
					result.setPointSize( fontSize );
					result.setBold ( (fontStyle & bold) ? true : false );
					result.setItalic ( (fontStyle & italic) ? true : false );
					result.setUnderlined ( (fontStyle & underline) ? true : false );
				}
			}
			break;
		}

		return result;
	}
/*
	virtual double getDefaultHeightFor( const UIMetricsManager::HeightType& type )  {
		double result = 0.0;
		switch ( type ) {
			case UIMetricsManager::htLabelHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htComboBoxHeight : {
				result = 20;
			}
			break;

			case UIMetricsManager::htListItemHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htButtonHeight : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricPushButtonHeight, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case UIMetricsManager::htRadioBoxHeight : case UIMetricsManager::htCheckBoxHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htToolTipHeight : {
				result = 18;
			}
			break;

			case UIMetricsManager::htSeparatorHeight : {
				result = 2.0;
			}
			break;

			case UIMetricsManager::htInformationalControl : {
				result = 15;
			}
			break;
		}
		return result;

	}

	virtual double getPreferredSpacingFor( const UIMetricsManager::SpacingType& type )  {
		double result = 0.0;

		//values largely derived from the Apple HIG at
		//http://developer.apple.com/documentation/UserExperience/Conceptual/OSXHIGuidelines/index.html
		//http://developer.apple.com/documentation/UserExperience/Conceptual/OSXHIGuidelines/XHIGLayout/chapter_19_section_2.html#//apple_ref/doc/uid/TP30000360-BEIBEAFJ
		switch ( type ) {
			case UIMetricsManager::stWindowBorderDelta : {
				result = 20.0;
			}
			break;

			case UIMetricsManager::stContainerBorderDelta : {
				result = 22;
			}
			break;

			case UIMetricsManager::stControlVerticalSpacing : {
				result = 12;
			}
			break;

			case UIMetricsManager::stControlHorizontalSpacing : {
				result = 12;
			}
			break;

			case UIMetricsManager::stInformationControlTopSpacer : {
				result = 2.0;
			}
			break;

			case UIMetricsManager::stInformationControlBottomSpacer : {
				result = 8.0;
			}
			break;
		}

		return result;
	}

	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;
		SInt32 val = 0;
		GetThemeMetric( kThemeMetricScrollBarWidth, &val );		

		result.width_ = val;
		result.height_ = val;

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;


		return result;
	}

	virtual Size getDefaultVerticalScrollButtonDimensions()  {
		Size result;
		SInt32 val = 0;
		GetThemeMetric( kThemeMetricScrollBarWidth, &val );		

		result.width_ = val;
		result.height_ = val;

		return result;
	}

	virtual Size getDefaultHorizontalScrollButtonDimensions()  {
		Size result;

		result.width_ = 22;
		result.height_ = 22;

		return result;
	}

	virtual Size getDefaultTabDimensions( const String& caption )  {
		Size result;

		return result;
	}
	*/
	virtual double getValue( const MetricType& type, const String& text, Font* font ) {
		double result = 0;

		switch ( type ) {
			case mtLabelHeight : {
				result = 18;
			}
			break;

			case mtComboBoxHeight : {
				result = 20;
			}
			break;

			case mtListItemHeight : {
				result = 19.0;
			}
			break;

			case mtButtonHeight : {			
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricPushButtonHeight, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtRadioBoxHeight : {			
				result = 18;
			}
			break;

			case mtCheckBoxHeight : {				
				result = 18;
			}
			break;

			case mtToolTipHeight : {
				result = 18;
			}
			break;

			case mtSeparatorHeight : {
				result = 2.0;
			}
			break;

			case mtHeaderHeight : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricListHeaderHeight, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtTreeItemHeight : {//???? is this even right?
				result = 19.0;
			}
			break;

			case mtTextControlHeight : {
				result = 22.0;
			}
			break;

			case mtVerticalProgressWidth : {
				result = 16.0;
			}
			break;

			case mtHorizontalProgressHeight : {
				result = 16.0;
			}
			break;

			case mtInformationalControlHeight : {
				
			}
			break;

			case mtVerticalScrollbarThumbWidth : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricScrollBarWidth, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtHorizontalScrollbarThumbHeight : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricScrollBarWidth, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtVerticalScrollbarWidth : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricScrollBarWidth, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtHorizontalScrollbarHeight : {
				SInt32 val = 0;
				if ( noErr == GetThemeMetric( kThemeMetricScrollBarWidth, &val ) ) {
					result = val;
				}
				else {
					result = 20;
				}
			}
			break;

			case mtMenuIndent : {

			}
			break;

			case mtWindowBorderDelta : {
				result = 20.0;
			}
			break;

			case mtContainerBorderDelta : {
				result = 22;
			}
			break;

			case mtControlVerticalSpacing : {
				result = 12;
			}
			break;

			case mtControlHorizontalSpacing : {
				result = 12;
			}
			break;

			case mtInformationControlTopSpacer : {
				result = 2.0;
			}
			break;

			case mtInformationControlBottomSpacer : {
				result = 8.0;
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}
		
		return result;
	}
	
	virtual VCF::Size getSize( const MetricType& type, const String& text, Font* font ) {
		Size result;
		
		switch ( type ) {
		/*
			case mtMenuSize : {
				
			}
			break;
*/
			case mtVerticalSliderThumbSize : {
				
			}
			break;

			case mtHorizontalSliderThumbSize : {
				
			}
			break;

			case mtTabSize : {
				
			}
			break;

			case mtRadioBoxBtnSize : {
				
			}
			break;

			case mtCheckBoxBtnSize : {
				
			}
			break;

			case mtComboBoxDropBtnSize : {
			
			}
			break;

			case mtDisclosureButtonSize : {
				
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;

	}
	
	virtual VCF::Rect getRect( const MetricType& type, VCF::Rect* rect, Font* font ) {
		return VCF::Rect();
	}
};

};


using namespace VCF;





OSXGraphicsToolkit::OSXGraphicsToolkit()
{
	loadSystemColors();
	this->metricsMgr_ = new OSXUIMetricsManager();
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
