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

	DELEGATE(EventDelegate,PositionChanged)

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

	bool hasTickMarks();

	void setHasTickMarks( const bool& val );


	int32 getTickMarkStyle() {
		return tickMarkStyle_;
	}

	bool hasNoTickMarks();
	bool hasTickMarksOnTopLeft();
	bool hasTickMarksOnBottomRight();

	void setTickMarkStyle( const int32& val );

	int32 getTickFrequency() {
		return tickFrequency_;
	}

	void setTickFrequency( const int32& val );

	double getStepIncrement() {
		return stepIncrement_;
	}

	void setStepIncrement( const double& val );

	double getPageIncrement() {
		return pageIncrement_;
	}

	void setPageIncrement( const double& val );

	virtual bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue );

protected:

	DisplayOrientation orientation_;
	double minVal_;
	double maxVal_;
	double position_;
	int32 tickMarkStyle_;
	int32 tickFrequency_;
	Point dragPosStart_;
	bool pressed_;
	double stepIncrement_;
	double pageIncrement_;

	void movePosition( MouseEvent* e );
};


};


#endif // _VCF_SLIDERCONTROL_H__

/**
$Id$
*/
