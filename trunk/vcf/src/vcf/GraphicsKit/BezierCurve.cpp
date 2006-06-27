//BezierCurve.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/BezierCurve.h"
#include "vcf/GraphicsKit/AggCommon.h"

using namespace VCF;


BezierCurve::BezierCurve()
{
	currentMoveToIndex_ = -1;
}

BezierCurve::~BezierCurve()
{
	clear();
}

void BezierCurve::applyTransform( const Matrix2D& transform )
{
	std::vector<PathPoint>::iterator it = points_.begin();
	double x = 0.0;
	while ( it != points_.end() ) {
		PathPoint& pt = *it;

		transform.apply( &pt.point_ );

		it ++;
	}
}


bool BezierCurve::contains( const Rect& rect )
{
	agg::rasterizer_scanline_aa<> rasterizer;
	agg::path_storage path;

	std::vector<PathPoint>::iterator it = points_.begin();

	while ( it != points_.end() ) {
		PathPoint& pt = *it;

		switch ( pt.type_ ){
			case PathPoint::ptMoveTo: {
				path.move_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptLineTo: {
				path.line_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptQuadTo: {
				if ( (points_.end() - it) < 4 ) {
					return false;
				}
				path.move_to( pt.point_.x_, pt.point_.y_ );
				it ++;

				PathPoint& c1 = *it;
				it++;
				PathPoint& c2 = *it;
				it++;
				PathPoint& p2 = *it;
				path.curve4( c1.point_.x_, c1.point_.y_,
								c2.point_.x_, c2.point_.y_,
								p2.point_.x_, p2.point_.y_ );
			}
			break;

			case PathPoint::ptCubicTo: {

			}
			break;

			case PathPoint::ptClose: {
				path.close_polygon();
			}
			break;
		}

		it ++;
	}
	agg::conv_curve<agg::path_storage> smooth(path);
	//agg::conv_stroke<agg::conv_curve<agg::path_storage> >  stroke(smooth);

	rasterizer.add_path( smooth );

	Point topLeft = rect.getTopLeft();
	Point bottomRight = rect.getTopLeft();

	return rasterizer.hit_test( (unsigned int)bottomRight.x_, (unsigned int)bottomRight.y_ ) && rasterizer.hit_test( (unsigned int)topLeft.x_, (unsigned int)topLeft.y_ );
}

bool BezierCurve::contains( const Point& pt )
{
	agg::rasterizer_scanline_aa<> rasterizer;
	agg::path_storage path;

	std::vector<PathPoint>::iterator it = points_.begin();

	while ( it != points_.end() ) {
		PathPoint& pt = *it;

		switch ( pt.type_ ){
			case PathPoint::ptMoveTo: {
				path.move_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptLineTo: {
				path.line_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptQuadTo: {
				if ( (points_.end() - it) < 4 ) {
					return false;
				}
				path.move_to( pt.point_.x_, pt.point_.y_ );
				it ++;

				PathPoint& c1 = *it;
				it++;
				PathPoint& c2 = *it;
				it++;
				PathPoint& p2 = *it;
				path.curve4( c1.point_.x_, c1.point_.y_,
								c2.point_.x_, c2.point_.y_,
								p2.point_.x_, p2.point_.y_ );
			}
			break;

			case PathPoint::ptCubicTo: {

			}
			break;

			case PathPoint::ptClose: {
				path.close_polygon();
			}
			break;
		}

		it ++;
	}

	agg::conv_curve<agg::path_storage> smooth(path);
	//agg::conv_stroke<agg::conv_curve<agg::path_storage> >  stroke(smooth);

	rasterizer.add_path( smooth );


	return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
}

bool BezierCurve::intersects( const Point& pt )
{
	agg::rasterizer_scanline_aa<> rasterizer;
	agg::path_storage path;

	std::vector<PathPoint>::iterator it = points_.begin();

	while ( it != points_.end() ) {
		PathPoint& pt = *it;

		switch ( pt.type_ ){
			case PathPoint::ptMoveTo: {
				path.move_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptLineTo: {
				path.line_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptQuadTo: {
				if ( (points_.end() - it) < 4 ) {
					return false;
				}
				path.move_to( pt.point_.x_, pt.point_.y_ );
				it ++;

				PathPoint& c1 = *it;
				it++;
				PathPoint& c2 = *it;
				it++;
				PathPoint& p2 = *it;
				path.curve4( c1.point_.x_, c1.point_.y_,
								c2.point_.x_, c2.point_.y_,
								p2.point_.x_, p2.point_.y_ );
			}
			break;

			case PathPoint::ptCubicTo: {

			}
			break;

			case PathPoint::ptClose: {
				path.close_polygon();
			}
			break;
		}

		it ++;
	}
	agg::conv_curve<agg::path_storage> smooth(path);
	agg::conv_stroke<agg::conv_curve<agg::path_storage> >  stroke(smooth);
	stroke.width( 2 );

	rasterizer.add_path( stroke );


	return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
}

bool BezierCurve::intersects( const Rect& rect)
{
	agg::rasterizer_scanline_aa<> rasterizer;
	agg::path_storage path;

	std::vector<PathPoint>::iterator it = points_.begin();

	while ( it != points_.end() ) {
		PathPoint& pt = *it;

		switch ( pt.type_ ){
			case PathPoint::ptMoveTo: {
				path.move_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptLineTo: {
				path.line_to( pt.point_.x_, pt.point_.y_ );
			}
			break;

			case PathPoint::ptQuadTo: {
				if ( (points_.end() - it) < 4 ) {
					return false;
				}
				path.move_to( pt.point_.x_, pt.point_.y_ );
				it ++;

				PathPoint& c1 = *it;
				it++;
				PathPoint& c2 = *it;
				it++;
				PathPoint& p2 = *it;
				path.curve4( c1.point_.x_, c1.point_.y_,
								c2.point_.x_, c2.point_.y_,
								p2.point_.x_, p2.point_.y_ );
			}
			break;

			case PathPoint::ptCubicTo: {

			}
			break;

			case PathPoint::ptClose: {
				path.close_polygon();
			}
			break;
		}

		it ++;
	}

	agg::conv_curve<agg::path_storage> smooth(path);
	rasterizer.add_path( smooth );


	if ( rasterizer.hit_test( (unsigned int)rect.left_, (unsigned int)rect.top_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( (unsigned int)rect.right_, (unsigned int)rect.top_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( (unsigned int)rect.right_, (unsigned int)rect.bottom_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( (unsigned int)rect.left_, (unsigned int)rect.bottom_ ) ) {
		return true;
	}

	return false;
}

Rect BezierCurve::getBounds()
{
	Rect result;
	uint32 count = points_.size();

	if ( count < 2 ){
		result.setRect( points_[0].point_.x_,
			              points_[0].point_.y_,
						  points_[0].point_.x_,
						  points_[0].point_.y_ );

	}
	else {
		if ( points_[1].point_.x_ > points_[0].point_.x_ ) {
			result.left_ = points_[0].point_.x_;
		}
		else {
			result.left_ = points_[1].point_.x_;
		}

		if ( points_[1].point_.y_ > points_[0].point_.y_ ) {
			result.top_ = points_[0].point_.y_;
		}
		else {
			result.top_ = points_[1].point_.y_;
		}

		if ( points_[0].point_.x_ < points_[1].point_.x_ ) {
			result.right_ = points_[1].point_.x_;
		}
		else {
			result.right_ = points_[0].point_.x_;
		}

		if ( points_[0].point_.y_ < points_[1].point_.y_ ) {
			result.bottom_ = points_[1].point_.y_;
		}
		else {
			result.bottom_ = points_[0].point_.y_;
		}

		for (uint32 i=2;i<count;i++){//we start on 2 since the first segment
                                  //is already assigned
			if ( result.left_ > points_[i].point_.x_ ){
				result.left_ = points_[i].point_.x_;
			}

			if ( result.top_ > points_[i].point_.y_ ){
				result.top_ = points_[i].point_.y_;
			}

			if ( result.right_ < points_[i].point_.x_ ){
				result.right_ = points_[i].point_.x_;
			}

			if ( result.bottom_ < points_[i].point_.y_ ){
				result.bottom_ = points_[i].point_.y_;
			}
		}
	}

	return result;
}

bool BezierCurve::getPoints( std::vector<PathPoint>& points, Matrix2D* transform )
{
	if ( NULL != transform ) {
		points = points_;

		std::vector<PathPoint>::iterator it1 = points_.begin();
		std::vector<PathPoint>::iterator it2 = points.begin();

		Matrix2D& m = *transform;

		while ( it1 != points_.end() ) {
			PathPoint& srcPt = *it1;
			PathPoint& destPt = *it2;

			destPt.point_ = srcPt.point_;
			m.apply( &destPt.point_ );

			it2 ++;
			it1 ++;
		}		
	}
	else {
		points = points_;
	}

	return !points.empty();
}

void BezierCurve::flattenPoints( std::vector<Point>& flattenedPoints )
{

}


void BezierCurve::lineTo( const double& x, const double& y )
{
	points_.push_back( PathPoint( x, y, PathPoint::ptLineTo ) );
}

void BezierCurve::moveTo( const double& x, const double& y )
{
	points_.push_back( PathPoint( x, y, PathPoint::ptMoveTo ) );
	currentMoveToIndex_ = points_.size() - 1;
}

void BezierCurve::rectangle( const Rect& rectangle )
{
	points_.push_back( PathPoint( rectangle.left_, rectangle.top_, PathPoint::ptMoveTo ) );
	points_.push_back( PathPoint( rectangle.right_, rectangle.top_, PathPoint::ptLineTo ) );
	points_.push_back( PathPoint( rectangle.right_, rectangle.bottom_, PathPoint::ptLineTo ) );
	points_.push_back( PathPoint( rectangle.left_, rectangle.bottom_, PathPoint::ptLineTo ) );
	points_.push_back( PathPoint( rectangle.left_, rectangle.top_, PathPoint::ptClose ) );
}

void BezierCurve::polyTo( std::vector<Point>& points )
{
	std::vector<Point>::iterator it = points.begin();
	while ( it != points.end() ) {
		Point& pt = *it;
		points_.push_back( PathPoint( pt.x_, pt.y_, PathPoint::ptLineTo ) );
		it ++;
	}
}

void BezierCurve::polyline( std::vector<Point>& points )
{
	std::vector<Point>::iterator it = points.begin();
	Point& pt = *it;
	points_.push_back( PathPoint( pt.x_, pt.y_, PathPoint::ptMoveTo ) );
	it ++;
	while ( it != points.end() ) {
		Point& pt = *it;
		points_.push_back( PathPoint( pt.x_, pt.y_, PathPoint::ptLineTo ) );
		it ++;
	}
}

void BezierCurve::curveTo( const double& cx1, const double& cy1,
					const double& cx2, const double& cy2,
					const double& x, const double& y)
{
	PathPoint& moveToPt = points_.back();

	points_.push_back( PathPoint( moveToPt.point_.x_, moveToPt.point_.y_, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( cx1, cy1, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( cx2, cy2, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( x, y, PathPoint::ptQuadTo ) );
}

void BezierCurve::curve( const double& x1, const double& y1,
					const double& cx1, const double& cy1,
					const double& cx2, const double& cy2,
					const double& x2, const double& y2)
{
	points_.push_back( PathPoint( x1, y1, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( cx1, cy1, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( cx2, cy2, PathPoint::ptQuadTo ) );
	points_.push_back( PathPoint( x2, y2, PathPoint::ptQuadTo ) );
}

void BezierCurve::close()
{
	if ( currentMoveToIndex_ >= 0 ) {
		PathPoint& moveToPt = points_[currentMoveToIndex_];
		points_.push_back( PathPoint( moveToPt.point_, PathPoint::ptClose ) );
	}
}

void BezierCurve::clear()
{
	points_.clear();
}


/**
$Id$
*/
