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
		x = pt.point_.x_;
		pt.point_.x_ = x * (transform[Matrix2D::mei00]) +
							pt.point_.y_ * (transform[Matrix2D::mei10]) +
								(transform[Matrix2D::mei20]);

		pt.point_.y_ = x * (transform[Matrix2D::mei01]) +
							pt.point_.y_ * (transform[Matrix2D::mei11]) +
								(transform[Matrix2D::mei21]);


		it ++;
	}
}


bool BezierCurve::contains( const Rect& rect )
{
	bool result = false;

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

	return rasterizer.hit_test( bottomRight.x_, bottomRight.y_ ) && rasterizer.hit_test( topLeft.x_, topLeft.y_ );
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


	return rasterizer.hit_test( pt.x_, pt.y_ );
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


	return rasterizer.hit_test( pt.x_, pt.y_ );
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


	if ( rasterizer.hit_test( rect.left_, rect.top_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( rect.right_, rect.top_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( rect.right_, rect.bottom_ ) ) {
		return true;
	}

	if ( rasterizer.hit_test( rect.left_, rect.bottom_ ) ) {
		return true;
	}

	return false;
}

Rect BezierCurve::getBounds()
{
	Rect result;
	ulong32 count = points_.size();

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

		for (ulong32 i=2;i<count;i++){//we start on 2 since the first segment
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

			destPt.point_.x_ = srcPt.point_.x_ * (m[Matrix2D::mei00]) +
								srcPt.point_.y_ * (m[Matrix2D::mei10]) +
								(m[Matrix2D::mei20]);

			destPt.point_.y_ = srcPt.point_.x_ * (m[Matrix2D::mei01]) +
								srcPt.point_.y_ * (m[Matrix2D::mei11]) +
								(m[Matrix2D::mei21]);

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
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.3  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.2.4.1  2004/02/21 03:27:09  ddiego
*updates for OSX porting
*
*Revision 1.2  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.1  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*/


