//TitledBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;

TitledBorder::TitledBorder():
	sidesToPaint_(GraphicsContext::etAllSides)
{
	font_ = UIToolkit::getUIMetricsManager()->getDefaultFontFor(UIMetricsManager::ftControlFont);
}

TitledBorder::TitledBorder(const String& title):
	caption_(title),
	sidesToPaint_(GraphicsContext::etAllSides)
{
	font_ = UIToolkit::getUIMetricsManager()->getDefaultFontFor(UIMetricsManager::ftControlFont);
}

TitledBorder::TitledBorder(const String& title, long sidesToPaint):
	caption_(title),
	sidesToPaint_(sidesToPaint)
{
	font_ = UIToolkit::getUIMetricsManager()->getDefaultFontFor(UIMetricsManager::ftControlFont);
}

TitledBorder::TitledBorder(const String& title, long sidesToPaint, const Font& font):
	caption_(title),
	sidesToPaint_(sidesToPaint),
	font_(font)
{
	
}

TitledBorder::TitledBorder( Component* owner ):
	Border(owner),
	sidesToPaint_(GraphicsContext::etAllSides)
{
	font_ = UIToolkit::getUIMetricsManager()->getDefaultFontFor(UIMetricsManager::ftControlFont);
}



void TitledBorder::paint( Control* control, GraphicsContext* context )
{
	if ( NULL == control ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "can't paint a border on a NULL Control." ) );
	}
	context->setColor( control->getColor() );
	paint( &control->getClientBounds(false), context );
}

void TitledBorder::paint( Rect* bounds, GraphicsContext* context )
{
	Rect edgeRect = *bounds;


	Rect textRect;
	Font* oldFont = context->getCurrentFont();
	context->setCurrentFont( &font_ );

	double textHeight = context->getTextHeight( "EM" );
	double textWidth = maxVal<double>( context->getTextWidth( "EM" ), context->getTextWidth( caption_ ) );

	edgeRect.top_ += textHeight/2.0;



	double y = edgeRect.top_ - textHeight/2.0;
	double x = edgeRect.left_ + 10;
	textRect.setRect( x, y, x + textWidth, y + textHeight );

	context->rectangle( &Rect(bounds->left_, bounds->top_, bounds->right_, bounds->top_ + textHeight + 1 ) );
	context->fillPath();

	DrawUIState state;
	state.setActive( true );
	
	context->drawThemeEdge( &edgeRect, state, sidesToPaint_, GraphicsContext::etEtched );

	textRect.inflate( 5, 0 );
	context->rectangle( &textRect );
	textRect.inflate( -5, 0 );
	context->fillPath();

	String text = caption_;
	text = System::getCurrentThreadLocale()->translate( text );

	context->textBoundedBy( &textRect, text, false );

	context->setCurrentFont( oldFont );
}

Rect TitledBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;
	
	if ( NULL != control ) {
		GraphicsContext* context = control->getContext();	
		result.inflate( -2.0, 0.0 );	
		result.bottom_ -= 2.0;

		Font oldFont = *context->getCurrentFont();
		context->setCurrentFont( &font_ );

		result.top_ += context->getTextHeight( "EM" );
		context->setCurrentFont( &oldFont );
	}
	else {
		result.inflate( -2.0, -2.0 );	
	}
	return result;
}


/**
$Id$
*/
