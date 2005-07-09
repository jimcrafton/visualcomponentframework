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
	hasTickMarks_(true),
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
	PositionChanged.fireEvent(&e);
}

void SliderControl::setHasTickMarks( const bool& val )
{
	hasTickMarks_ = val;
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

void SliderControl::setTickMarkStyle( const long& val )
{
	tickMarkStyle_ = val;
	repaint();
}

void SliderControl::setTickFrequency( const long& val )
{
	tickFrequency_ = val;
	repaint();
}

double SliderControl::getPreferredWidth()
{
	if ( SliderControl::doVertical == orientation_ ) {
		Size thumbSize = UIToolkit::getUIMetricsManager()->getDefaultSliderThumbDimensions();

		return thumbSize.height_ * 2;// UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
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
		Size thumbSize = UIToolkit::getUIMetricsManager()->getDefaultSliderThumbDimensions();
		return thumbSize.height_ * 2;
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


	Size thumbSize = UIToolkit::getUIMetricsManager()->getDefaultSliderThumbDimensions();

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
/*
	thumbRect = sliderRect;
	if ( info.vertical ) {
		thumbRect.top_ = thumbRect.bottom_ - thumbSize.width_;

		thumbRect.offset( 0, (int)(thumbSize.width_/2)-(int)((position_/(maxVal_-minVal_))*sliderRect.getHeight()) );
	}
	else {
		thumbRect.right_ = thumbRect.left_ + thumbSize.width_;

		thumbRect.offset( (int)(((position_-minVal_)/(maxVal_-minVal_))*sliderRect.getWidth()) - (int)(thumbSize.width_/2), 0 );
	}	
*/

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

	Size thumbSize = UIToolkit::getUIMetricsManager()->getDefaultSliderThumbDimensions();


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

	StringUtils::traceWithArgs( Format("newPos: %0.1f\n") % newPos );
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

	switch ( e->getVirtualCode() ) {
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


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/03/15 01:51:50  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.3  2003/10/28 04:06:12  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.1.2.2  2003/10/27 04:20:39  ddiego
*more tweaks to the Slider control
*
*/


