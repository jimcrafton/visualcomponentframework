#ifndef _VCF_ELLIPSE_H__
#define _VCF_ELLIPSE_H__
//Ellipse.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef AGG_ELLIPSE_INCLUDED
#include "thirdparty/common/agg/include/agg_ellipse.h"
#endif 

#ifndef AGG_BOUNDING_RECT_INCLUDED
#include "thirdparty/common/agg/include/agg_bounding_rect.h"
#endif




namespace VCF{

class GRAPHICSKIT_API Ellipse : public VCF::HeapObject, public VCF::Path {
public:
	Ellipse(){}

	Ellipse( const Rect& r ){
		ellipse(r);
	}

	Ellipse( const double& x1, const double& y1, const double& x2, const double& y2 ){
		ellipse(Rect(x1,y1,x2,y2));
	}

	Ellipse( const Point& tl, const Point& br ){
		ellipse(Rect(tl.x_,tl.y_,br.x_,br.y_));
	}

	virtual ~Ellipse(){}


	virtual void applyTransform( const Matrix2D& transform ) {
		agg::trans_affine mat = transform;
		agg::path_storage tmp = ellipsePath_;
		agg::conv_transform< agg::path_storage > xfrmdPath(tmp,mat);

		
		

		ellipsePath_.remove_all();
		ellipsePath_.concat_path(xfrmdPath);
	}

	virtual bool contains( const Rect& rect, Matrix2D* transform=NULL) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}

		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_transform< agg::path_storage > xfrmedPath(ellipsePath_,mat);
		agg::conv_curve< agg::conv_transform< agg::path_storage > > smooth(xfrmedPath);
		rasterizer.add_path( smooth );

		Point topLeft = rect.getTopLeft();
		Point bottomRight = rect.getTopLeft();

		ellipsePath_.rewind(0);

		return rasterizer.hit_test( (unsigned int)bottomRight.x_, (unsigned int)bottomRight.y_ ) && rasterizer.hit_test( (unsigned int)topLeft.x_, (unsigned int)topLeft.y_ );
	}

    virtual bool contains( const Point& pt, Matrix2D* transform=NULL ) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}

		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_transform< agg::path_storage > xfrmedPath(ellipsePath_,mat);
		agg::conv_curve< agg::conv_transform< agg::path_storage > > smooth(xfrmedPath);
		rasterizer.add_path( smooth );

		ellipsePath_.rewind(0);

		return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
	}

    virtual bool intersects( const Point& pt, Matrix2D* transform=NULL ) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}

		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_transform< agg::path_storage > xfrmedPath(ellipsePath_,mat);
		agg::conv_curve< agg::conv_transform< agg::path_storage > > smooth(xfrmedPath);
		agg::conv_stroke< agg::conv_curve< agg::conv_transform< agg::path_storage > > >  stroke(smooth);
		stroke.width( 2 );

		ellipsePath_.rewind(0);

		rasterizer.add_path( stroke );
		return rasterizer.hit_test( (unsigned int)pt.x_, (unsigned int)pt.y_ );
	}

    virtual bool intersects( const Rect& rect, Matrix2D* transform=NULL ) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}

		agg::rasterizer_scanline_aa<> rasterizer;
		agg::conv_transform< agg::path_storage > xfrmedPath(ellipsePath_,mat);
		agg::conv_curve< agg::conv_transform< agg::path_storage > > smooth(xfrmedPath);
		agg::conv_stroke< agg::conv_curve< agg::conv_transform< agg::path_storage > > >  stroke(smooth);
		rasterizer.add_path( smooth );
		
		ellipsePath_.rewind(0);

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

	virtual Rect getBounds() {
		Rect result;

		uint32 pid[1] = {0};

		agg::bounding_rect( ellipsePath_, pid, 0, 1,
						&result.left_, &result.top_,
						&result.right_, &result.bottom_ );

		ellipsePath_.rewind(0);
		return result;
	}

	virtual WindingRule getWindingRule() {
		return wrNonZero;
	}

	virtual void setWindingRule( WindingRule rule ) {

	}

	virtual bool getPoints( std::vector<PathPoint>& points, Matrix2D* transform ) {
		agg::trans_affine mat;
		if ( NULL != transform ) {
			mat = *transform;
		}
		agg::conv_transform< agg::path_storage > xfrmdPath(ellipsePath_,mat);
		
		for ( size_t i=0;i<ellipsePath_.total_vertices();i++ ) {
			PathPoint pt;
			unsigned vertCmd = xfrmdPath.vertex(&pt.point_.x_, &pt.point_.y_);
			switch ( vertCmd ) {
				case agg::path_cmd_move_to : {
					pt.type_ = PathPoint::ptMoveTo;
					points.push_back( pt );
				}
				break;

				case agg::path_cmd_line_to : {
					pt.type_ = PathPoint::ptLineTo;
					points.push_back( pt );
				}
				break;

				default : {
					if ( vertCmd & agg::path_flags_close ) {
						pt.type_ = PathPoint::ptClose;
						points.push_back( pt );
					}
				}
				break;
			}

			
		}

		ellipsePath_.rewind(0);

		return !points.empty();
	}

	virtual void flattenPoints( std::vector<Point>& flattenedPoints ) {		
		for ( size_t i=0;i<ellipsePath_.total_vertices();i++ ) {
			Point pt;
			unsigned vertCmd = ellipsePath_.vertex(&pt.x_, &pt.y_);
			switch ( vertCmd ) {
				case agg::path_cmd_move_to : {
					flattenedPoints.push_back( pt );
				}
				break;

				case agg::path_cmd_line_to : {
					flattenedPoints.push_back( pt );
				}
				break;

				default : {
					if ( vertCmd & agg::path_flags_close ) {
						flattenedPoints.push_back( pt );
					}
				}
				break;
			}			
		}

		ellipsePath_.rewind(0);
	}


	void ellipse( const Rect& bounds ) {

		agg::ellipse ellipseShape( bounds.left_ + bounds.getWidth()/2.0, 
									bounds.top_ + bounds.getHeight()/2.0,
									bounds.getWidth()/2.0, 
									bounds.getHeight()/2.0, 100 );

		ellipsePath_.rewind(0);
		ellipsePath_.remove_all();
		ellipsePath_.concat_path( ellipseShape );
	}
protected:
	agg::path_storage ellipsePath_;
};

};


#endif // _VCF_ELLIPSE_H__

/**
$Id$
*/
