//EtchedBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


EtchedBorder::EtchedBorder():
	sidesToPaint_(GraphicsContext::etAllSides),
	style_(GraphicsContext::etEtched)
{

}

EtchedBorder::EtchedBorder( int32 sidesToPaint, int32 style ):
	sidesToPaint_(sidesToPaint),
	style_(style)
{

}

EtchedBorder::EtchedBorder( Component* owner ):
	Border(owner),		
	sidesToPaint_(GraphicsContext::etAllSides),
	style_(GraphicsContext::etEtched)
{

}

void EtchedBorder::paint( Control* control, GraphicsContext* context )
{
	if ( NULL == control ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "can't paint a border on a NULL Control." ) );
	}
	paint( &control->getClientBounds(false), context );
}

void EtchedBorder::paint( Rect* bounds, GraphicsContext* context )
{
	DrawUIState state;
	state.setActive( true );
	context->drawThemeEdge( bounds, state, sidesToPaint_, style_ );
}

Rect EtchedBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;

	double left, top, right, bottom;

	left = top = right = bottom = 0;


	if ( (sidesToPaint_ & GraphicsContext::etLeftSide  ) != 0 ) left   = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etTopSide   ) != 0 ) top    = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etRightSide ) != 0 ) right  = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etBottomSide) != 0 ) bottom = -2.0;

	result.inflate( left, top, right, bottom );

	return result;
}


/**
$Id$
*/
