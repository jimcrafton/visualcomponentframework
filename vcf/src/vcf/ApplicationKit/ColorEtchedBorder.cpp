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
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/01 16:57:37  dougtinkham
*implemented painting
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/05/17 20:37:21  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:46  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.1  2002/10/01 20:34:59  ddiego
*borders
*
*/


