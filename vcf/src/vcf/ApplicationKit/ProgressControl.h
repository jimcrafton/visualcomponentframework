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


/**
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

	ProgressAlignment getDisplayAlignment() {
		return displayAlignment_;
	}

	void setDisplayAlignment( ProgressAlignment val );

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


