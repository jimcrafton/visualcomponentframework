#ifndef _VCF_WIZARD_H__
#define _VCF_WIZARD_H__
//Wizard.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

	/**
	*Wizard documentation
	this interface is used to disaplay a UI
	in the wizard dialog
	the layout of the dialog is like so
	<pre>
	+-------------------------------------------------+
	|	TITLE                                  +----+ |
	|                                          |    | <----Image here
	|		Description                        +----+ |
	+-------------------------------------------------+
	|                                                 |
	|                                                 |
	|                                                 |
	|                                                 |
	|                                                 |
	|                 Wizard UI                       |
	|                                                 |
	|                                                 |
	|                                                 |
	+-------------------------------------------------+
	|                                                 |
	|            <<Back    Next>>    Finish    Cancel |
	|                                                 |
	+-------------------------------------------------+
	</pre>
	*/
	class Wizard : public Interface {
	public:
		virtual ~Wizard(){}

		/**
		*returns the name of the Wizard in human readable format
		*/
		virtual String getName() = 0;

		virtual unsigned long getNumberOfSteps() = 0;

		/**
		*Returns a string used in the Title area
		*/
		virtual String getStepTitle( const unsigned long& step ) = 0;

		/**
		*Returns a string used in the Description area
		*/
		virtual String getStepDescription( const unsigned long& step ) = 0;

		/**
		*returns a new Image object for the Image area - callers
		*responsibility to clean this up. The Image returned MUST
		have dimensions equal to or less than those specified in the
		dimensions parameter
		@param Size dimensions the maximum dimensions of the image
		*/
		virtual Image* getStepImage( const unsigned long& step, const Size& dimensions ) = 0;

		/**
		*returns a page to display
		*/
		virtual Control* getStepPage( const unsigned long& step ) = 0;

		virtual Size getStepPreferredDimensions( const unsigned long& step ) = 0;

		virtual void finish() = 0;

	};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:35  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.6.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.3.6.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:33  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.1  2002/10/06 05:35:38  ddiego
*adding more implementation for the addNewClass method, added the default
*dialog for this, plus the default dialog for class templates with no wizard.
*Broke up the ClassWizard and ProjectWizard and created a commend abstract
*base class that has been moved into the ApplicationKit proper.
*Added a new MessageDialog class for presenting a uniform UI for message
*boxes or alerts, which includes verifying that the ui is proeprly made up
*
*/


#endif // _VCF_WIZARD_H__


