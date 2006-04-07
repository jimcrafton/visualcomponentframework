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
	\class UIMetricsManager UIMetricsManager.h "vcf/ApplicationKit/UIMetricsManager.h"  
	A utility class to retrieve standard ui element metrics. 
	
	The Win32 implementation takes XP theming into account, 
	and derives at least some of it's information from :
	http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnwue/html/ch14e.asp

	
	The Mac OS X implementation is based on the Appearance Manager
	http://developer.apple.com/documentation/Carbon/Reference/Appearance_Manager/index.html
	*/
	class UIMetricsManager : public Object {
	public:

		enum FontType{
			ftMenuItemFont = 0,
			ftSelectedMenuItemFont,
			ftSystemFont,
			ftControlFont,
			ftMessageFont,
			ftToolTipFont
		};

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		enum HeightType {
			/**
			returns the height for any label control. This should
			be used for the actual control height for radio and
			check boxes as well, with the actual height of the
			radio or check box rect being indicated by the htRadioBoxHeight
			or htCheckBoxHeight values
			*/
			htLabelHeight = 0,
			/**
			returns the default height for combo box, or drop down box controls.
			*/
			htComboBoxHeight,

			/**
			returns the default item height for item in a list like control, such as hte
			list box control, or the popup list for a combo box
			*/
			htListItemHeight,

			/**
			returns the default height for a button control, typically used by the
			command button
			*/
			htButtonHeight,

			/**
			returns the default height for a radio box. The radio box is bounded by a
			square, so the height and width for the radio box are indicated by this
			value
			*/
			htRadioBoxHeight,

			/**
			returns the default height for a check box. The check box is bounded by a
			square, so the height and width for the radio box are indicated by this
			value
			*/
			htCheckBoxHeight,
			htToolTipHeight,
			htSeparatorHeight,

			/**
			returns the default height for an informational control such as a status bar or
			a progress bar. This is also referred to as a "placard" in Apple's HIG
			*/
			htInformationalControl,
			htLast
		};


		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		enum SpacingType {
			stWindowBorderDelta = htLast,
			stContainerBorderDelta,
			stControlVerticalSpacing,
			stControlHorizontalSpacing,

			/**
			returns the appropriate value for the space between an informational
			control (like a status label) and the control above it
			*/
			stInformationControlTopSpacer,

			/**
			returns the appropriate value for the space between an informational
			control (like a status label) and the control below it
			*/
			stInformationControlBottomSpacer
		};

		enum MetricType {
			mtLabelHeight = 0,
			mtComboBoxHeight,
			mtListItemHeight,			
			mtButtonHeight,
			mtRadioBoxHeight,
			mtCheckBoxHeight,
			mtToolTipHeight,
			mtSeparatorHeight,
			mtHeaderHeight,			
			mtTreeItemHeight,
			mtTextControlHeight,
			mtVerticalProgressWidth,
			mtHorizontalProgressHeight,
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
			mtInformationControlTopSpacer,
			mtInformationControlBottomSpacer,			
			mtMenuSize,
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
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual double getDefaultHeightFor( const HeightType& type ) = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual double getPreferredSpacingFor( const SpacingType& type ) = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual Size getDefaultSliderThumbDimensions() = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual Size getDefaultMenuItemDimensions( const String& caption ) = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual Size getDefaultVerticalScrollButtonDimensions() = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual Size getDefaultHorizontalScrollButtonDimensions() = 0;

		/**
		These are going away in the next release, please don't use them any more.
		Instead use the getMetricXXX functions.
		@deprecated
		*/
		virtual Size getDefaultTabDimensions( const String& caption ) = 0;


		/**
		
		Returns a double value for a UI metric, such as the standard height of the 
		combox box control. The text is an optional parameter that may be taken
		into consideration when calculating teh retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtRadioBoxBtnSize, then a
		RuntimeException would be thrown.
		*/
		virtual double getValue( const MetricType& type, const String& text="" ) = 0;

		/**
		
		Returns a Size instance for a UI metric, such as the standard dimensions of 
		a tab button. The text is an optional parameter that may be taken
		into consideration when calculating teh retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtMenuIndent, then a
		RuntimeException would be thrown.
		*/
		virtual Size getSize( const MetricType& type, const String& text="" ) = 0;

		/**
		
		Returns a Rect instance for a UI metric, such as the content bounds of 
		a tab pane. The rect is an optional parameter that may be taken
		into consideration when calculating the retrun value by certain 
		metric types.
		
		If the metric type is inappropriate then the function throws an exception.
		For example, if the caller passed in mtMenuIndent, then a
		RuntimeException would be thrown.
		*/
		virtual Rect getRect( const MetricType& type, Rect* rect=NULL ) = 0;

	};
};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.3  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.2.6.2  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.1  2006/03/01 04:34:56  ddiego
*fixed tab display to use themes api.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.6.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.3.6.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.1  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*/


#endif // _VCF_UIMETRICSMANAGER_H__


