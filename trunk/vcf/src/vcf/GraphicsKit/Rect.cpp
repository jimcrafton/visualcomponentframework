//Rect.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/GraphicsKit/GraphicsKit.h"

using namespace VCF;


VCF::Rect::Rect( const Rect& rect ):
    Object(rect),
    Persistable( rect )
{
	setRect( rect.left_, rect.top_, rect.right_, rect.bottom_ );
}

void VCF::Rect::normalize()
{
	double tmp;
	if ( left_ > right_ ) {
		tmp = left_;
		left_ = right_;
		right_ = tmp;
	}

	if ( top_ > bottom_ ) {
		tmp = top_;
		top_ = bottom_;
		bottom_ = tmp;
	}
}

bool VCF::Rect::containsPt( Point * point ) const
{
	bool result = false;
	if ( (point->x_ >= left_) && (point->y_ >= top_) &&
	     (point->x_ < right_) && (point->y_ < bottom_) ){
		result = true;
	}
	return result;
}

bool VCF::Rect::containsPtCloseTo( Point * point, const double& tolerance ) const
{
	bool result = false;
	if ( (point->x_ >= left_-tolerance) && (point->y_ >= top_-tolerance) &&
	     (point->x_ <= right_+tolerance) && (point->y_ <= bottom_+tolerance) ){
		result = true;
	}
	return result;
}

bool VCF::Rect::containsPtOpen( Point * point ) const
{
	bool result = false;
	if ( (point->x_ > left_) && (point->y_ > top_) &&
	     (point->x_ < right_) && (point->y_ < bottom_) ){
		result = true;
	}
	return result;
}

bool VCF::Rect::containsPtClose( Point * point ) const
{
	bool result = false;
	if ( (point->x_ >= left_) &&  (point->y_ >= top_) &&
	     (point->x_ <= right_) &&  (point->y_ <= bottom_) ){
		result = true;
	}
	return result;
}

bool VCF::Rect::containsRect( Rect* rect ) const
{
	bool result = false;

	if ( (left_ <= rect->left_) && (top_ <= rect->top_) && (right_ > rect->right_) && (bottom_ > rect->bottom_) ) {
		result = true;
	}

	return result;
}

bool VCF::Rect::containsRectOpen( Rect* rect ) const
{
	bool result = false;

	if ( (left_ < rect->left_) && (top_ < rect->top_) && (right_ > rect->right_) && (bottom_ > rect->bottom_) ) {
		result = true;
	}

	return result;
}

bool VCF::Rect::containsRectClose( Rect* rect ) const
{
	bool result = false;

	if ( (left_ <= rect->left_) && (top_ <= rect->top_) && (right_ >= rect->right_) && (bottom_ >= rect->bottom_) ) {
		result = true;
	}

	return result;
}

String VCF::Rect::toString() const
{
	String result = "";

	char tmp[256];
	memset(tmp, 0, sizeof(tmp) );
	sprintf( tmp, "%.3f,%.3f,%.3f,%.3f", left_, top_, right_, bottom_ );

	result = tmp;

	return result;
}

void VCF::Rect::saveToStream( OutputStream * stream, const MIMEType& type )
{
	stream->write( left_ );
	stream->write( top_ );
	stream->write( right_ );
	stream->write( bottom_ );
}

void VCF::Rect::loadFromStream( InputStream * stream, const MIMEType& type )
{
	stream->read( left_ );
	stream->read( top_ );
	stream->read( right_ );
	stream->read( bottom_ );
}

void VCF::Rect::add( const Rect* rect )
{
	left_   = VCF::minVal<double>( left_, rect->left_ );

	top_    = VCF::minVal<double>( top_, rect->top_ );

	right_  = VCF::maxVal<double>( right_, rect->right_ );

	bottom_ = VCF::maxVal<double>( bottom_, rect->bottom_ );

}

void VCF::Rect::subtract( const Rect* rect )
{
	bool rectWider = false;
	bool rectTaller = false;

	if ( (rect->left_ <= left_) && (rect->right_ >= right_)) {
		// rect is larger than *this, so let's cut the vertical dimension
		rectWider = true;
	}

	if ( (rect->top_ <= top_) && (rect->bottom_ >= bottom_)) {
		// rect is larger than *this, so let's cut the horizontal dimension
		rectTaller = true;
	}

	if ( rectWider && rectTaller ) {
		setRect( 0.0, 0.0, 0.0, 0.0);
		return;
	}

	if ( rectWider ) {
		if ( (top_ < rect->top_) && (bottom_ > rect->bottom_) ) {
			// rect would split *this: let's leave *this unchanged
			return;
		} else {
			if ( top_ < rect->top_ ) {
				// top of rect becomes bottom ot *this
				bottom_ = rect->top_;
			}
			if ( bottom_ > rect->bottom_ ) {
				// bottom of rect becomes top ot *this
				top_ = rect->bottom_;
			}
		}
	}

	if ( rectTaller )
	{
		if ( (left_ < rect->left_) && (right_ > rect->right_) ) {
			// rect would split *this: let's leave *this unchanged
			return;
		} else {
			if ( left_ < rect->left_ ) {
				// left of rect becomes right ot *this
				right_ = rect->left_;
			}
			if ( right_ > rect->right_ ) {
				// right of rect becomes left ot *this
				left_ = rect->right_;
			}
		}
	}
}

Rect VCF::Rect::makeIntersection( const Rect* rect )
{
	Rect result;

	bool horzIntersect = false;
	bool vertIntersect = false;

	if ( ((left_ <= rect->left_) && (right_ >= rect->left_)) ||
				((rect->left_ <= left_ ) && (rect->right_ >= left_)) ) {
		horzIntersect = true;
	}

	if ( ((top_ <= rect->top_) && (bottom_ >= rect->top_)) ||
				((rect->top_ <= top_ ) && (rect->bottom_ >= top_)) ) {
		vertIntersect = true;
	}

	if ( vertIntersect && horzIntersect ) {

		result.left_ = maxVal<double>( left_, rect->left_ );
		result.right_ = minVal<double>( right_, rect->right_ );

		result.top_ = maxVal<double>( top_, rect->top_ );
		result.bottom_ = minVal<double>( bottom_, rect->bottom_ );

	}

	return result;
}

Rect VCF::Rect::makeUnion( const Rect* rect )
{
	Rect result;

	result.left_ = minVal( rect->left_, left_ );
	result.top_ = minVal( rect->top_, top_ );
	result.right_ = maxVal( rect->right_, right_ );
	result.bottom_ = maxVal( rect->bottom_, bottom_ );

	return result;
}


/**
$Id$
*/
