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
			htInformationalControl
		};


		enum SpacingType {
			stWindowBorderDelta = 0,
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

		UIMetricsManager(){};

		virtual ~UIMetricsManager(){};

		virtual Font getDefaultFontFor( const FontType& type ) = 0;

		virtual double getDefaultHeightFor( const HeightType& type ) = 0;

		virtual double getPreferredSpacingFor( const SpacingType& type ) = 0;

		virtual Size getDefaultSliderThumbDimensions() = 0;

		virtual Size getDefaultMenuItemDimensions( const String& caption ) = 0;

		virtual Size getDefaultVerticalScrollButtonDimensions() = 0;

		virtual Size getDefaultHorizontalScrollButtonDimensions() = 0;

		virtual Size getDefaultTabDimensions( const String& caption ) = 0;
	};


};


/**
*CVS Log info
*$Log$
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


