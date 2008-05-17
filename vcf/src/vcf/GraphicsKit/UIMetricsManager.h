#ifndef _VCF_UIMETRICSMANAGER_H__
#define _VCF_UIMETRICSMANAGER_H__
//UIMetricsManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//UIMetricsManager




namespace VCF {
	/**
	\class UIMetricsManager UIMetricsManager.h "vcf/GraphicsKit/UIMetricsManager.h"  
	A utility class to retrieve standard ui element metrics. 
	
	The Win32 implementation takes XP theming into account, 
	and derives at least some of it's information from :
	http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnwue/html/ch14e.asp

	
	The Mac OS X implementation is based on the Appearance Manager
	http://developer.apple.com/documentation/Carbon/Reference/Appearance_Manager/index.html
	*/
	class UIMetricsManager {
	public:

		enum FontType{
			ftMenuItemFont = 0,
			ftSelectedMenuItemFont,
			ftSystemFont,
			ftControlFont,
			ftMessageFont,
			ftToolTipFont
		};

		enum MetricType {
			/**
			returns the height for any label control. This should
			be used for the actual control height for radio and
			check boxes as well, with the actual height of the
			radio or check box rect being indicated by the htRadioBoxHeight
			or htCheckBoxHeight values
			*/			
			mtLabelHeight = 0,

			/**
			returns the default height for combo box, or drop down box controls.
			*/
			mtComboBoxHeight,
			/**
			returns the default item height for item in a list like control, such as hte
			list box control, or the popup list for a combo box
			*/
			mtListItemHeight,	
			/**
			returns the default height for a button control, typically used by the
			command button
			*/
			mtButtonHeight,
			/**
			returns the default height for a radio box. The radio box is bounded by a
			square, so the height and width for the radio box are indicated by this
			value
			*/
			mtRadioBoxHeight,
			/**
			returns the default height for a check box. The check box is bounded by a
			square, so the height and width for the radio box are indicated by this
			value
			*/
			mtCheckBoxHeight,
			mtToolTipHeight,
			mtSeparatorHeight,
			mtHeaderHeight,			
			mtTreeItemHeight,
			mtTextControlHeight,
			mtVerticalProgressWidth,
			mtHorizontalProgressHeight,
			mtMenuSeparatorHeight,
			mtMenuBarHeight,

			/**
			returns the default height for an informational control such as a status bar or
			a progress bar. This is also referred to as a "placard" in Apple's HIG
			*/
			mtInformationalControlHeight, //status bar
			mtStatusHeight = mtInformationalControlHeight,
			mtVerticalScrollbarThumbWidth,
			mtHorizontalScrollbarThumbHeight,
			mtVerticalScrollbarWidth,
			mtHorizontalScrollbarHeight,
			mtMenuIndent,			
			mtWindowBorderDelta,
			mtContainerBorderDelta,
			mtControlVerticalSpacing,
			mtControlHorizontalSpacing,
			/**
			returns the appropriate value for the space between an informational
			control (like a status label) and the control above it
			*/
			mtInformationControlTopSpacer,
			/**
			returns the appropriate value for the space between an informational
			control (like a status label) and the control below it
			*/
			mtInformationControlBottomSpacer,			
			mtMenuItemSize,
			mtMenuItemSeparatorSize,
			mtVerticalSliderThumbSize,
			mtHorizontalSliderThumbSize,						
			mtTabSize,
			mtRadioBoxBtnSize,
			mtCheckBoxBtnSize,
			mtComboBoxDropBtnSize,
			mtDisclosureButtonSize,
			mtTabPaneContentRect


		};

		UIMetricsManager(){};

		virtual ~UIMetricsManager(){};

		virtual Font getDefaultFontFor( const FontType& type ) = 0;
		
		/**

		Returns a double value for a UI metric, such as the standard height of the 
		combox box control. The text is an optional parameter that may be taken
		into consideration when calculating teh retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtRadioBoxBtnSize, then a
		RuntimeException would be thrown.
		*/
		virtual double getValue( const MetricType& type, const String& text, Font* alternateFont ) = 0;

		/**
		
		Returns a Size instance for a UI metric, such as the standard dimensions of 
		a tab button. The text is an optional parameter that may be taken
		into consideration when calculating teh retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtMenuIndent, then a
		RuntimeException would be thrown.
		*/
		virtual Size getSize( const MetricType& type, const String& text, Font* alternateFont ) = 0;

		/**
		
		Returns a Rect instance for a UI metric, such as the content bounds of 
		a tab pane. The rect is an optional parameter that may be taken
		into consideration when calculating the retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtMenuIndent, then a
		RuntimeException would be thrown.
		*/
		virtual Rect getRect( const MetricType& type, Rect* rect, Font* alternateFont ) = 0;

	};
};


#endif // _VCF_UIMETRICSMANAGER_H__

/**
$Id$
*/
