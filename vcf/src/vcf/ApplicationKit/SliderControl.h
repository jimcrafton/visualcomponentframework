#ifndef _VCF_SLIDERCONTROL_H__
#define _VCF_SLIDERCONTROL_H__
//SliderControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define SLIDERCONTROL_CLASSID		"e5b77d23-4a5f-42e5-adba-e2bde202206e"

	
static String DisplayOrientationNames[] = { "SliderControl::doHorizontal",
                                         "SliderControl::doVertical" };


static String TickMarkStyleNames[] = { "SliderControl::tmsNone",
                                         "SliderControl::tmsTopLeft",
										"SliderControl::tmsBottomRight" };
/**
\class SliderControl SliderControl.h "vcf/ApplicationKit/SliderControl.h"
The SliderControl, sometimes referred to as a "trackbar" provides
a UI that consists of a thumb button that slides, vertically or
horizontally, along a "track". Sliding this causes the position 
value to change. The position is bounded by a minimum and maximum
value.
*/
class APPLICATIONKIT_API SliderControl : public CustomControl {
public:

	enum DisplayOrientation {
		doHorizontal = 0,
		doVertical
	};

	enum TickMarkStyle {
		tmsNone = 0,
		tmsTopLeft = 0x01,
		tmsBottomRight = 0x02
	};

	enum {
		PositionChangedEvent = 546600
	};

	SliderControl();

	DELEGATE(PositionChanged)

	virtual double getPreferredWidth();

	virtual double getPreferredHeight();

	virtual void paint( GraphicsContext* ctx );

	virtual void mouseDown( MouseEvent* e );

	virtual void mouseMove( MouseEvent* e );

	virtual void mouseUp( MouseEvent* e );

	virtual void keyDown( KeyboardEvent* e );

	virtual void keyUp( KeyboardEvent* e );



	DisplayOrientation getDisplayOrientation() {
		return orientation_;
	}

	void setDisplayOrientation( const DisplayOrientation& val );

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

	bool hasTickMarks() {
		return hasTickMarks_;
	}
	void setHasTickMarks( const bool& val );


	long getTickMarkStyle() {
		return tickMarkStyle_;
	}

	bool hasNoTickMarks();
	bool hasTickMarksOnTopLeft();
	bool hasTickMarksOnBottomRight();

	void setTickMarkStyle( const long& val );

	long getTickFrequency() {
		return tickFrequency_;
	}

	void setTickFrequency( const long& val );

	double getStepIncrement() {
		return stepIncrement_;
	}

	void setStepIncrement( const double& val );

	double getPageIncrement() {
		return pageIncrement_;
	}

	void setPageIncrement( const double& val );


protected:

	DisplayOrientation orientation_;
	double minVal_;
	double maxVal_;
	double position_;
	bool hasTickMarks_;
	long tickMarkStyle_;
	long tickFrequency_;
	Point dragPosStart_;
	bool pressed_;
	double stepIncrement_;
	double pageIncrement_;

	void movePosition( MouseEvent* e );
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/02/28 04:51:56  ddiego
*fixed issue in handling componenent state and events when in design mode
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
*Revision 1.1.2.3  2003/10/28 04:06:10  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.1.2.2  2003/10/27 04:20:35  ddiego
*more tweaks to the Slider control
*
*Revision 1.1.2.1  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*/


#endif // _VCF_SLIDERCONTROL_H__


