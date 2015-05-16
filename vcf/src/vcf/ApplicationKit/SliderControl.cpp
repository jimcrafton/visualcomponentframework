//SliderControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SliderControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"



using namespace VCF;


SliderControl::SliderControl():
	CustomControl(true),
	orientation_(doHorizontal),
	minVal_(0.0),
	maxVal_(100.0),
	position_(0.0),
	tickMarkStyle_(SliderControl::tmsTopLeft|SliderControl::tmsBottomRight),
	tickFrequency_(10),
	pressed_(false),
	stepIncrement_(1.0),
	pageIncrement_(10.0)
{
	setTransparent( false );
}

void SliderControl::setDisplayOrientation( const DisplayOrientation& val )
{
	orientation_ = val;
	repaint();
}

void SliderControl::setMinValue( const double& val )
{
	minVal_ = val;
	repaint();
}

void SliderControl::setMaxValue( const double& val )
{
	maxVal_ = val;
	repaint();
}

void SliderControl::setPosition( const double& val )
{
	position_ = minVal<>( maxVal_, maxVal<>( minVal_, val ) );
	repaint();
	Event e(this,SliderControl::PositionChangedEvent);
	PositionChanged(&e);
}

bool SliderControl::hasTickMarks()
{
	return tickMarkStyle_ == SliderControl::tmsNone ? false : true;
}

void SliderControl::setHasTickMarks( const bool& val )
{
	if ( val ) {
		tickMarkStyle_ = SliderControl::tmsTopLeft | SliderControl::tmsBottomRight;
	}
	else {
		tickMarkStyle_ = SliderControl::tmsNone;
	}
	
	repaint();
}

bool SliderControl::hasNoTickMarks()
{
	return SliderControl::tmsNone == tickMarkStyle_;
}

bool SliderControl::hasTickMarksOnTopLeft()
{
	return (SliderControl::tmsTopLeft & tickMarkStyle_) ? true : false;
}

bool SliderControl::hasTickMarksOnBottomRight()
{
	return (SliderControl::tmsBottomRight & tickMarkStyle_) ? true : false;
}

void SliderControl::setTickMarkStyle( const int32& val )
{
	tickMarkStyle_ = val;
	repaint();
}

void SliderControl::setTickFrequency( const int32& val )
{
	tickFrequency_ = val;
	repaint();
}

double SliderControl::getPreferredWidth()
{
	if ( SliderControl::doVertical == orientation_ ) {
		double h = UIToolkit::getUIMetricValue( UIMetricsManager::mtVerticalScrollbarWidth );

		return h * 2;// UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
	}
	else {
		return 100;
	}

	return 0.0;
}

double SliderControl::getPreferredHeight()
{
	if ( SliderControl::doVertical == orientation_ ) {
		return 100;
	}
	else {
		double h = UIToolkit::getUIMetricValue( UIMetricsManager::mtHorizontalProgressHeight );
		return h;
	}

	return 0.0;
}

void SliderControl::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );

	Rect clientBounds = getClientBounds();


	Rect sliderRect;
	Rect tickMarkRect;
	Rect thumbRect;

	SliderState state;
	state.setTickMarkingOnTopLeft( hasTickMarksOnTopLeft() );
	state.setTickMarkingOnBottomRight( hasTickMarksOnBottomRight() );
	state.setEnabled( isEnabled() );
	state.setFocused( isFocused() );
	state.max_ = maxVal_;
	state.min_ = minVal_;
	state.position_ = position_;
	state.setPressed( pressed_ );
	state.tickMarkFrequency_ = tickFrequency_;
	state.setVertical( (SliderControl::doVertical == orientation_) ? true : false );

	sliderRect = clientBounds;


	Size thumbSize;
	if ( state.isVertical() ) {
		thumbSize = UIToolkit::getUIMetricSize( UIMetricsManager::mtVerticalSliderThumbSize );
	}
	else {
		thumbSize = UIToolkit::getUIMetricSize( UIMetricsManager::mtHorizontalSliderThumbSize );
	}
	

	if ( state.isVertical() ) {
		sliderRect.inflate( -2, -thumbSize.width_/2.0 );
		if ( state.isTickMarkingOnBottomRight() ) {
			sliderRect.right_ -= 5;
		}

		if ( state.isTickMarkingOnTopLeft() ) {
			sliderRect.left_ += 5;
		}
	}
	else {
		sliderRect.inflate( -thumbSize.width_/2.0, -2 );
		if ( state.isTickMarkingOnBottomRight() ) {
			sliderRect.bottom_ -= 5;
		}

		if ( state.isTickMarkingOnTopLeft() ) {
			sliderRect.top_ += 5;
		}
	}

	tickMarkRect = sliderRect;

	ctx->drawThemeTickMarks( &tickMarkRect, state );

	ctx->drawThemeSlider( &sliderRect, state );	
}


void SliderControl::mouseDown( MouseEvent* e )
{
	CustomControl::mouseDown( e );

	if ( !isEnabled() ) {
		return;
	}


	if ( e->hasLeftButton() ) {
		pressed_ = true;
		keepMouseEvents();
		dragPosStart_ = *e->getPoint();
		movePosition( e );
	}
}

void SliderControl::mouseMove( MouseEvent* e )
{
	CustomControl::mouseMove( e );

	if ( !isEnabled() ) {
		return;
	}


	if ( e->hasLeftButton() ) {
		movePosition( e );
	}
}

void SliderControl::mouseUp( MouseEvent* e )
{
	CustomControl::mouseUp( e );
	if ( !isEnabled() ) {
		return;
	}

	releaseMouseEvents();
	pressed_ = false;
	if ( e->hasLeftButton() ) {
		movePosition( e );
	}
}

void SliderControl::movePosition( MouseEvent* e )
{
	double delta = 0;
	double range = maxVal_ - minVal_;

	Size thumbSize;
	if ( SliderControl::doVertical == orientation_ ) {
		thumbSize = UIToolkit::getUIMetricSize( UIMetricsManager::mtVerticalSliderThumbSize );
	}
	else {
		thumbSize = UIToolkit::getUIMetricSize( UIMetricsManager::mtHorizontalSliderThumbSize );
	}


	double newPos = 0.0;

	if ( SliderControl::doVertical == orientation_ ) {
		double h = getHeight()-thumbSize.width_;
		delta = -1 * (e->getPoint()->y_ - dragPosStart_.y_ );// - thumbSize.width_/4)/h;

		newPos = ((h- ((dragPosStart_.y_ - delta) - thumbSize.width_/2))/h) * range;
	}
	else {

		double w = getWidth()-thumbSize.width_;
		delta = ((e->getPoint()->x_ - dragPosStart_.x_)- thumbSize.width_/2)/w;// - thumbSize.width_/4)/w;

		newPos = ((dragPosStart_.x_/w + delta)) * range;
	}

//	StringUtils::trace( Format("newPos: %0.1f\n") % newPos );
	newPos += minVal_;

	if ( tickFrequency_ > 0.0 ) {
		double tickRange = range/tickFrequency_;
		double rem = fmod(newPos,tickRange);
		if ( rem > (tickRange/2.0) ) {
			newPos = (newPos - rem) + tickRange;
		}
		else {
			newPos = newPos - rem;
		}


	}

	setPosition( newPos  );
}

void SliderControl::setStepIncrement( const double& val )
{
	stepIncrement_ = val;
}

void SliderControl::setPageIncrement( const double& val )
{
	pageIncrement_ = val;
}

void SliderControl::keyDown( KeyboardEvent* e )
{
	CustomControl::keyDown(e);

	switch ( e->virtualKeyCode ) {
		case vkPgUp : {
			setPosition( getPosition() + pageIncrement_ );
		}
		break;

		case vkPgDown : {
			setPosition( getPosition() - pageIncrement_ );
		}
		break;

		case vkRightArrow : case vkUpArrow : {
			setPosition( getPosition() + stepIncrement_ );
		}
		break;

		case vkLeftArrow : case vkDownArrow : {
			setPosition( getPosition() - stepIncrement_ );
		}
		break;
	}
}

void SliderControl::keyUp( KeyboardEvent* e )
{
	CustomControl::keyUp(e);
}


bool SliderControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_WIDTH ) {
		if ( SliderControl::doVertical == orientation_ ) {
			if ( getWidth() == UIToolkit::getUIMetricValue( UIMetricsManager::mtVerticalProgressWidth ) ) {
				strValue = CC_VSLIDERWIDTH;
				return true;
			}
		}
	}
	else if ( lcPropName == CONTROL_HEIGHT ) {
		if ( SliderControl::doVertical != orientation_ ) {
			if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtHorizontalProgressHeight ) ) {
				strValue = CC_HSLIDERHEIGHT;
				return true;
			}
		}
	}

	return Control::generatePropertyValue( fullPropertyName, property, value, strValue );
}

/**
$Id$
*/
