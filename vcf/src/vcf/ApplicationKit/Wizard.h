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
	\class Wizard Wizard.h "vcf/ApplicationKit/Wizard.h"  
	A Wizard is used to disaplay a UI in a wizard dialog.
	The layout of the dialog looks like this:
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

		virtual uint32 getNumberOfSteps() = 0;

		/**
		*Returns a string used in the Title area
		*/
		virtual String getStepTitle( const uint32& step ) = 0;

		/**
		*Returns a string used in the Description area
		*/
		virtual String getStepDescription( const uint32& step ) = 0;

		/**
		*returns a new Image object for the Image area - callers
		*responsibility to clean this up. The Image returned MUST
		have dimensions equal to or less than those specified in the
		dimensions parameter
		@param Size dimensions the maximum dimensions of the image
		*/
		virtual Image* getStepImage( const uint32& step, const Size& dimensions ) = 0;

		/**
		*returns a page to display
		*/
		virtual Control* getStepPage( const uint32& step ) = 0;

		virtual Size getStepPreferredDimensions( const uint32& step ) = 0;

		virtual void finish() = 0;

	};

};


#endif // _VCF_WIZARD_H__

/**
$Id$
*/
