//ProgressControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ProgressControl.h"
#include "vcf/ApplicationKit/EtchedBorder.h"


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
	EtchedBorder* border = new EtchedBorder();
	border->setStyle( GraphicsContext::etSunken );
	setBorder( border );

	progressBarColor_ = new Color();

	*progressBarColor_ = *GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION);

	progressTextColor_ = new Color();

	*progressTextColor_ = *GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION_TEXT);
}

ProgressControl::~ProgressControl()
{
	progressBarColor_->free();
	progressTextColor_->free();
}


void ProgressControl::setDisplayAlignment( ProgressAlignment val )
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
	position_ = minVal<>( maxVal_, maxVal<>( minVal_, val ) );
	repaint();
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
		return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
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
		return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight );
	}

	return 0.0;
}

void ProgressControl::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );

	Rect clientBounds = getClientBounds();
	clientBounds.inflate( -2, -2 );
	Rect progressRect = clientBounds;

	if ( paVertical == displayAlignment_ ) {
		double s = minVal<>( minVal_, maxVal_ );
		double e = maxVal<>( minVal_, maxVal_ );

		progressRect.top_ = progressRect.bottom_ - ((position_/fabs(e-s)) * clientBounds.getHeight());
	}
	else {
		double s = minVal<>( minVal_, maxVal_ );
		double e = maxVal<>( minVal_, maxVal_ );

		progressRect.right_ = progressRect.left_ + ((position_/(e-s)) * clientBounds.getWidth());
	}



	ctx->setColor( progressBarColor_ );
	ctx->rectangle( progressRect );
	ctx->fillPath();

	//draw text
	if ( displayProgressText_ ) {
		Rect textBounds;
		String text;
		if ( useProgressFormatString_ && (!progressFormatString_.empty()) ) {
			text = StringUtils::format( progressFormatString_, position_ );
		}
		else {
			text = StringUtils::format( "%0.1f %%", position_ );
		}


		if ( paVertical == displayAlignment_ ) {
			textBounds.left_ = progressRect.left_;
			textBounds.right_ = progressRect.right_;

			double h = minVal<>( ctx->getTextHeight( "EM" ), clientBounds.getHeight()-2 );
			textBounds.top_ = clientBounds.top_ +
								(clientBounds.getHeight()/2.0 - h/2.0);

			textBounds.bottom_ = textBounds.top_ + h;

			textBounds.inflate( 0, 2 );
		}
		else {
			textBounds.top_ = progressRect.top_;
			textBounds.bottom_ = progressRect.bottom_;

			double w = minVal<>( ctx->getTextWidth( text ), clientBounds.getWidth()-2 );

			textBounds.left_ = clientBounds.left_ +
								(clientBounds.getWidth()/2.0 - w/2.0);

			textBounds.right_ = textBounds.left_ + w;
		}

		long drawOptions = GraphicsContext::tdoNone;
		drawOptions |= GraphicsContext::tdoCenterHorzAlign;
		drawOptions |= GraphicsContext::tdoCenterVertAlign;

		Color oldColor = *ctx->getCurrentFont()->getColor();

		ctx->getCurrentFont()->setColor( progressTextColor_ );

		ctx->textBoundedBy( &textBounds, text, drawOptions );

		ctx->getCurrentFont()->setColor(&oldColor);

	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/30 19:19:29  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
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
*Revision 1.1.2.1  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*/


