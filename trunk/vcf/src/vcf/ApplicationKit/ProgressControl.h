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


#endif // _VCF_PROGRESSCONTROL_H__

/**
$Id$
*/
