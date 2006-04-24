#ifndef _VCF_PROGRESSCONTROL_H__
#define _VCF_PROGRESSCONTROL_H__
//ProgressControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {



#define PROGRESSCONTROL_CLASSID		"afb8b792-f354-4234-884d-ecccd277f9e8"

static String ProgressAlignmentNames[] = { "ProgressControl::paVertical",
                                         "ProgressControl::paHorizontal" };

/**
\class ProgressControl ProgressControl.h "vcf/ApplicationKit/ProgressControl.h"
The ProgressControl is a class that displays a vertical or horizontal
progress bar showing the position of within a given range of a task.
*/
class APPLICATIONKIT_API ProgressControl : public CustomControl {
public:
	enum ProgressAlignment {
		paVertical = 0,
		paHorizontal
	};	


	ProgressControl();

	virtual ~ProgressControl();

	virtual void setName( const String& name );

	ProgressAlignment getDisplayAlignment() {
		return displayAlignment_;
	}

	void setDisplayAlignment( const ProgressAlignment& val );

	double getMinValue() {
		return minVal_;
	}

	void setMinValue( const double& val );

	double getMaxValue() {
		return maxVal_;
	}

	void setMaxValue( const double& val );

	double getPosition() {
		return position_;
	}

	void setPosition( const double& val );

	bool getDisplayProgressText() {
		return displayProgressText_;
	}

	void setDisplayProgressText( const bool& val );

	bool getUseProgressFormatString() {
		return useProgressFormatString_;
	}

	void setUseProgressFormatString( const bool& val );

	String getProgressFormatString() {
		return progressFormatString_;
	}

	void setProgressFormatString( const String& val );


	virtual double getPreferredWidth();

	virtual double getPreferredHeight();

	virtual void paint( GraphicsContext* ctx );

	void stepIt();

	double getStepItIncrement() {
		return stepItIncrement_;
	}

	void setStepItIncrement( const double& val );

	Color* getProgressBarColor() {
		return progressBarColor_;
	}
	void setProgressBarColor( Color* val );

	Color* getProgressTextColor() {
		return progressTextColor_;
	}
	void setProgressTextColor( Color* val );
protected:
	ProgressAlignment displayAlignment_;
	double minVal_;
	double maxVal_;
	double position_;
	bool displayProgressText_;
	bool useProgressFormatString_;
	String progressFormatString_;
	double stepItIncrement_;
	Color* progressBarColor_;
	Color* progressTextColor_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/02/28 04:51:56  ddiego
*fixed issue in handling componenent state and events when in design mode
*
*Revision 1.2.4.1  2005/02/27 01:45:33  ddiego
*fixed bug in testing whether a path should be loaded as a bundle.
*added some additional rtti info for certain classes in app kit.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*/


#endif // _VCF_PROGRESSCONTROL_H__


