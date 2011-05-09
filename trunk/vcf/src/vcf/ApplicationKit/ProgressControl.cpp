//ProgressControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ProgressControl.h"
#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


ProgressControl::ProgressControl():
	CustomControl(false),
	displayAlignment_(paHorizontal),
	minVal_(0.0),
	maxVal_(100.0),
	position_(0.0),
	displayProgressText_(false),
	useProgressFormatString_(false),
	stepItIncrement_(1.0)
{
	progressBarColor_ = new Color();

	*progressBarColor_ = *GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION);

	progressTextColor_ = new Color();

	*progressTextColor_ = *GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION_TEXT);
}

ProgressControl::~ProgressControl()
{
	delete progressBarColor_;
	delete progressTextColor_;
}


void ProgressControl::setDisplayAlignment( const ProgressAlignment& val )
{
	displayAlignment_ = val;
	repaint();
}

void ProgressControl::setMinValue( const double& val )
{
	minVal_ = val;
	repaint();
}

void ProgressControl::setMaxValue( const double& val )
{
	maxVal_ = val;
	repaint();
}

void ProgressControl::setPosition( const double& val )
{
	double minv = minVal( minVal_, maxVal_ );
	double maxv = maxVal( minVal_, maxVal_ );

	position_ = minVal<>( maxv, maxVal<>( minv, val ) );
	repaint();
}

void ProgressControl::setName( const String& name )
{
	CustomControl::setName( name );
	if ( isDesigning() ) {
		if ( progressFormatString_.empty() ) {
			setProgressFormatString( name + " %0.3f" );
		}
	}
}

void ProgressControl::setDisplayProgressText( const bool& val )
{
	displayProgressText_ = val;
	repaint();
}

void ProgressControl::setUseProgressFormatString( const bool& val )
{
	useProgressFormatString_ = val;
	repaint();
}

void ProgressControl::setProgressFormatString( const String& val )
{
	progressFormatString_ = val;
	repaint();
}

void ProgressControl::setStepItIncrement( const double& val )
{
	stepItIncrement_ = val;
	repaint();
}

void ProgressControl::setProgressBarColor( Color* val )
{
	if ( NULL == val ) {
		return;
	}

	*progressBarColor_ = *val;
	repaint();
}

void ProgressControl::setProgressTextColor( Color* val )
{
	if ( NULL == val ) {
		return;
	}

	*progressTextColor_ = *val;
	repaint();
}

void ProgressControl::stepIt()
{
	setPosition( position_ + stepItIncrement_ );
}

double ProgressControl::getPreferredWidth()
{
	if ( paVertical == displayAlignment_ ) {
		return UIToolkit::getUIMetricValue( UIMetricsManager::mtVerticalProgressWidth );
	}
	else {
		return 100;
	}

	return 0.0;
}

double ProgressControl::getPreferredHeight()
{
	if ( paVertical == displayAlignment_ ) {
		return 100;
	}
	else {
		return UIToolkit::getUIMetricValue( UIMetricsManager::mtHorizontalProgressHeight );
	}

	return 0.0;
}

void ProgressControl::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );

	Rect clientBounds = getClientBounds();

	ProgressState state;
	state.min_ = minVal_;
	state.max_ = maxVal_;
	state.position_ = position_;
	state.setActive( isActive() );
	state.setEnabled( isEnabled() );
	state.setFocused( isFocused() && state.isActive() );
	if ( displayProgressText_ ) {
		String text;
		if ( useProgressFormatString_ && (!progressFormatString_.empty()) ) {
			text = Format(progressFormatString_) % position_;
		}
		else {
			text = Format("%0.1f %%") % position_;
		}
		state.progressCaption_ = text; 
	}
	state.setVertical( (paVertical == displayAlignment_) ? true : false );
	ctx->drawThemeProgress( &clientBounds, 	state );
}

bool ProgressControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( paHorizontal == displayAlignment_ ) {
			if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtHorizontalProgressHeight ) ) {
				strValue = CC_HPROGRESSHEIGHT;
				return true;
			}
		}		
	}
	else if ( lcPropName == CONTROL_WIDTH ) {
		if ( paVertical == displayAlignment_ ) {
			if ( getWidth() == UIToolkit::getUIMetricValue( UIMetricsManager::mtVerticalProgressWidth ) ) {
				strValue = CC_VPROGRESSWIDTH;
				return true;
			}
		}		
	}

	return CustomControl::generatePropertyValue( fullPropertyName, property, value, strValue );
}


/**
$Id$
*/
