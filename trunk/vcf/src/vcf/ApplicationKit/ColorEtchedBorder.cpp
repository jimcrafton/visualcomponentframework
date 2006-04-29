//ColorEtchedBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ColorEtchedBorder.h"

using namespace VCF;


ColorEtchedBorder::ColorEtchedBorder()
{

}

ColorEtchedBorder::ColorEtchedBorder( Component* owner ):
	EtchedBorder(owner)
{

}

void ColorEtchedBorder::paint( Control* control, GraphicsContext* context )
{
	paint( &control->getClientBounds(false), context );
}

void ColorEtchedBorder::paint( Rect* bounds, GraphicsContext* context )
{
	// colors initially set for etEtched style.
	Color leftOut = shadow_;
	Color topOut = shadow_;
	Color rightIn = shadow_;
	Color bottomIn = shadow_;

	Color leftIn = highlight_;
	Color topIn = highlight_;
	Color rightOut = highlight_;
	Color bottomOut = highlight_;

	if ( style_ == GraphicsContext::etRaised ) {
		leftOut = highlight_;
		topOut = highlight_;
		bottomOut = shadow_;
		rightOut = shadow_;
	}
	if ( style_ == GraphicsContext::etSunken ) {
		leftIn = shadow_;
		topIn = shadow_;
		rightIn = highlight_;
		bottomIn = highlight_;
	}
	if ( style_ == GraphicsContext::etRecessed ) {
		leftIn = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		rightIn = leftIn;
		topIn = leftIn;
		bottomIn = leftIn;
	}

	
	if ( NULL != bounds ){
		if ( sidesToPaint_ != GraphicsContext::etNoSides ) {
			
			bool left, right, top, bottom = false;

			if ( (sidesToPaint_ & GraphicsContext::etLeftSide) != 0 ){
				left = true;
				//outside
				context->moveTo( bounds->left_, bounds->top_ );
				context->lineTo( bounds->left_, bounds->bottom_ );
				context->setColor( &leftOut );
				context->strokePath();
				//inside
				context->moveTo( bounds->left_ + 1, bounds->top_ );
				context->lineTo( bounds->left_ + 1, bounds->bottom_ );
				context->setColor( &leftIn );
				context->strokePath();
			}
			if ( (sidesToPaint_ & GraphicsContext::etTopSide) != 0 ){
				top = true;
				//outside
				context->moveTo( bounds->left_, bounds->top_ );
				context->lineTo( bounds->right_, bounds->top_ );
				context->setColor( &topOut );
				context->strokePath();
				//inside
				context->moveTo( bounds->left_ , bounds->top_ + 1 );
				context->lineTo( bounds->right_, bounds->top_ + 1 );
				context->setColor( &topIn );
				context->strokePath();
			}
			if ( (sidesToPaint_ & GraphicsContext::etRightSide) != 0 ){
				right = true;
				//outside
				context->moveTo( bounds->right_ - 1, bounds->top_ );
				context->lineTo( bounds->right_ - 1, bounds->bottom_ );
				context->setColor( &rightOut );
				context->strokePath();
				//inside
				context->moveTo( bounds->right_ - 2, bounds->top_ );
				context->lineTo( bounds->right_ - 2, bounds->bottom_ );
				context->setColor( &rightIn );
				context->strokePath();
			}			
			if ( (sidesToPaint_ & GraphicsContext::etBottomSide) != 0 ){
				bottom = true;
				//outside
				context->moveTo( bounds->left_, bounds->bottom_ - 1 );
				context->lineTo( bounds->right_, bounds->bottom_ - 1 );
				context->setColor( &bottomOut );
				context->strokePath();
				//inside
				context->moveTo( bounds->left_ , bounds->bottom_ - 2 );
				context->lineTo( bounds->right_, bounds->bottom_ - 2 );
				context->setColor( &bottomIn );
				context->strokePath();
			}
			
			//now, check for 2 pixels that may need repainted.
			//needs tweeked for etRaised, etSunken
			if ( left && top ) {
				context->moveTo( bounds->left_ , bounds->top_ + 1 );
				context->lineTo( bounds->left_ , bounds->top_ + 2 );
				context->setColor( &leftOut );
				context->strokePath();
			}
			if ( right && bottom ) {
				context->moveTo( bounds->right_ - 1 , bounds->bottom_ - 2 );
				context->lineTo( bounds->right_ - 1 , bounds->bottom_ - 3 );
				context->setColor( &rightOut );
				context->strokePath();
			}
		}
	}
}

Rect ColorEtchedBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;

	double left, top, right, bottom = 0;

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
