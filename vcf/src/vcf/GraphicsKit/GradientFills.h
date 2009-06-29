#ifndef _VCF_GRADIENTFILLS_H__
#define _VCF_GRADIENTFILLS_H__
//GradientFills.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef AGG_SPAN_INTERPOLATOR_LINEAR_INCLUDED
#include "thirdparty/common/agg/include/agg_span_interpolator_linear.h"
#endif

#ifndef AGG_SPAN_GRADIENT_INCLUDED
#include "thirdparty/common/agg/include/agg_span_gradient.h"
#endif 

#ifndef AGG_SPAN_ALLOCATOR_INCLUDED
#include "thirdparty/common/agg/include/agg_span_allocator.h"
#endif

#ifndef AGG_SCANLINE_U_INCLUDED
#include "thirdparty/common/agg/include/agg_scanline_u.h"
#endif


namespace VCF  {

/**
This is the base class for gradient fills. Gradient fills
use the AGG gradient span generators to render the gradient.

The main class function is to produce a color profile,
that is then used by the agg gradient functions to determine
what color to use at any given pixel. 

The interface for the class functions identically to that of 
the Photoshop Gradient Editor. You have a series of 2 or more
colors and a series of 1 or more "mid points" where the number
of mid points is equal to 1 less than the number of colors.
Each color is associated with a location value that indicates
it's position within the range of 0.0 to 1.0. Location values
need to be unique per color and the list of colors is sorted
by it's location. Each mid point has a value ranging 0.0 to 1.0.
Mid point values do \em not need to be unique.
*/
class GradientFill : public HeapObject, public Fill {
public:


	struct GradientColor {

		GradientColor(): location(0.0){}

		Color color;
		double location;
	};

	GradientFill():alpha_(1.0),context_(NULL),maxColorProfileSize_(256){

		initColors();

		buildColorProfile();

	}

	virtual ~GradientFill(){}


	virtual void setContext( GraphicsContext* context ) {
		context_ = context;
	}

    virtual void render( Path* path ) {
		std::vector<PathPoint> points;
		path->getPoints( points, NULL );

		std::vector<Point> pts;
		std::vector<PathPoint>::iterator pathIt = points.begin();	

		if ( NULL != context_->getRenderingBuffer() ) {
			
			Point org = context_->getOrigin();

			agg::rendering_buffer& renderingBuffer = *context_->getRenderingBuffer();

			agg::path_storage fillPath;

			while ( pathIt != points.end() ) {
				PathPoint& pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						fillPath.move_to( pt.point_.x_ + org.x_, pt.point_.y_ + org.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						fillPath.line_to( pt.point_.x_ + org.x_, pt.point_.y_ + org.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {
						fillPath.move_to( pt.point_.x_ + org.x_, pt.point_.y_ + org.y_ );

						pathIt++;
						PathPoint& c1 = *pathIt;

						pathIt++;
						PathPoint& c2 = *pathIt;

						pathIt++;
						PathPoint& p2 = *pathIt;
						
						fillPath.curve4( c1.point_.x_ + org.x_, c1.point_.y_ + org.y_,
										c2.point_.x_ + org.x_, c2.point_.y_ + org.y_,
										p2.point_.x_ + org.x_, p2.point_.y_ + org.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						fillPath.close_polygon();
					}
					break;
				}
				
				pathIt ++;
			}

			agg::trans_affine mat = *context_->getCurrentTransform();
			agg::conv_curve<agg::path_storage> smooth(fillPath);
			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);


			agg::rasterizer_scanline_aa<> rasterizer;
			rasterizer.add_path(xfrmedPath);			

			context_->resetRenderAreaAlpha();

			renderGradient( renderingBuffer, rasterizer );
		}

	}

	void setAlpha( const double& val ) {
		alpha_ = val;
		buildColorProfile();
	}

	double getAlpha() const {
		return alpha_;
	}

	GradientColor& addColor( const Color& color, double location, double midPoint=0.5 ) {
		GradientColor c;
		c.color = color;
		c.location = location;

		colors_.push_back( c );
		midPoints_.push_back(midPoint);		

		buildColorProfile();

		return colors_[ colors_.size()-1 ];
	}


	void setColor( const size_t& index, const GradientColor& val ) {
		colors_[ index ] = val;
		buildColorProfile();
	}

	void setColorValue( const size_t& index, const Color& val ) {
		colors_[ index ].color = val;
		buildColorProfile();
	}

	void setColorLocation( const size_t& index, const double& val ) {
		colors_[ index ].location = val;
		buildColorProfile();
	}

	GradientColor getColor( const size_t index ) const {
		return colors_[ index ];
	}

	Color getColorValue( const size_t index ) const {
		return colors_[ index ].color;
	}

	double getColorLocation( const size_t index ) const {
		return colors_[ index ].location;
	}
	
	size_t getColorCount() const {
		return colors_.size();
	}
	
	void setMidPoint( const size_t& index, double val ) {
		midPoints_[index] = val;
		buildColorProfile();
	}

	double getMidPoint( const size_t& index ) const {
		return midPoints_[index];
	}

	size_t getMidPointCount() const {
		return midPoints_.size();
	}

	void sortColors() {
		std::sort( colors_.begin(), colors_.end(), ColorSorter() );
	}

	void setGradientMatrix( const Matrix2D& val ) {
		gradientMatrix_ = val;
		buildColorProfile();
	}

	Matrix2D getGradientMatrix() const {
		return gradientMatrix_;
	}

	Matrix2D& getGradientMatrix() {
		return gradientMatrix_;
	}

	void setMaxColorProfileSize( const size_t& val ) {
		maxColorProfileSize_ = val;
		buildColorProfile();
	}

	size_t getMaxColorProfileSize() const {
		return maxColorProfileSize_;
	}

	void resetColors() {
		initColors();
		buildColorProfile();
	}
protected:

	typedef agg::span_interpolator_linear<> InterpolatorType;
	typedef color_type ColorT;
	
	typedef std::vector<ColorT> ColorProfileVector;
	typedef std::vector<agg::gray8> GrayscaleColorProfileVector;
	
	double alpha_;
	GraphicsContext* context_;	

	std::vector<GradientColor> colors_;
	std::vector<double> midPoints_;
	ColorProfileVector colorProfile_;
	size_t maxColorProfileSize_;

	Matrix2D gradientMatrix_;


	class ColorSorter {
	public:
		bool operator() ( const GradientColor& x, const GradientColor& y ) const {
			return x.location < y.location;
		}
	};	

	virtual void renderGradient( agg::rendering_buffer& renderingBuffer, agg::rasterizer_scanline_aa<>& rasterizer ) = 0;

	void initColors() {
		colors_.clear();
		midPoints_.clear();

		colors_.resize(2);
		midPoints_.resize(colors_.size()-1);

		colors_[0].color = Color(0,0,0,1.0);
		colors_[0].location = 0.0;

		colors_[1].color = Color(1,1,1,1.0);
		colors_[1].location = 1.0;

		
		midPoints_[0] = 0.5;

		buildColorProfile();
	}

	
	void convertColorProfileToGrayscale( GrayscaleColorProfileVector& grayColors ) {
		grayColors.resize( colorProfile_.size() );

		for ( uint32 i=0;i<colorProfile_.size();i++ ) {
			grayColors[i] = agg::gray8(colorProfile_[i]);
		}
	}

	void buildColorProfile() {

		VCF_ASSERT( colors_.size() > 1 );
		VCF_ASSERT( midPoints_.size() == (colors_.size() - 1) );

		if ( colors_.size() <= 1 ) {
			throw RuntimeException("Less than 2 colors in gradient");
		}

		if ( midPoints_.size() != (colors_.size() - 1) ) {
			throw RuntimeException("Wrong number of midpoints");
		}

		sortColors();


		colorProfile_.clear();
		colorProfile_.resize(maxColorProfileSize_);


		uint32 colorIdx = 0;

		double r1,g1,b1,a1;
		double r2,g2,b2,a2;

		colors_[colorIdx].color.getRGBA(r1,g1,b1,a1);		

		colors_[colorIdx+1].color.getRGBA(r2,g2,b2,a2);
		double location = 0;
		double nextLocation = colors_[colorIdx+1].location;

		uint32 midPtIdx = 0;
		double midpoint = midPoints_[midPtIdx];

		for ( uint32 i=0;i<maxColorProfileSize_;i++ ) {
			GradientColor& currentCol = colors_[colorIdx];
			currentCol.color.getRGBA(r1,g1,b1,a1);			
			
			if ( colorIdx+1 < colors_.size() ) {
				colors_[colorIdx+1].color.getRGBA(r2,g2,b2,a2);
			}


			location = (double)i / (double)maxColorProfileSize_;

			double blendVal = 0;

			if ( location > currentCol.location && location < nextLocation ) {				
				double range = nextLocation - currentCol.location;
				double scaledLocation = (location - currentCol.location)  / range;
				midpoint = midPoints_[midPtIdx];

				if ( scaledLocation < midpoint ) {
					blendVal = (scaledLocation / midpoint) * 0.5;
				}
				else {
					blendVal = 0.5;

					blendVal += ((scaledLocation - midpoint) / (1.0-midpoint)) * 0.5;
				}
			}
			else if ( location <= currentCol.location ) {
				blendVal = 0;
			}
			else if ( location > nextLocation ) {
				midPtIdx = minVal<>( midPtIdx+1, midPoints_.size()-1 );
				colorIdx ++;			

				blendVal = 0.0;

				colors_[colorIdx].color.getRGBA(r1,g1,b1,a1);

				if ( colorIdx+1 < colors_.size() ) {
					nextLocation = colors_[colorIdx+1].location;
					colors_[colorIdx+1].color.getRGBA(r2,g2,b2,a2);
				}
				else {
					nextLocation = 1.0;
				}
			}

			ColorT c1 = ColorT( r1*255, g1*255, b1*255, a1*255 );
			ColorT c2 = ColorT( r2*255, g2*255, b2*255, a2*255 );

			blendVal = minVal<>( 1.0, maxVal<>( 0.0, blendVal ) );

			ColorT c = c1.gradient( c2, blendVal);

			c.a = (((double)c.a/255.0) * alpha_) * 255;
			colorProfile_[i] = c;
		}
	}	

};



class RadialGradientFill : public GradientFill {
public:

	RadialGradientFill():startRadius_(0), endRadius_(100){}

	virtual ~RadialGradientFill(){}


	void setStartRadius( const double& val ) {
		startRadius_ = val;
	}

	void setEndRadius( const double& val ) {
		endRadius_ = val;
	}


	double getStartRadius() const {
		return startRadius_;
	}

	double getEndRadius() const {
		return endRadius_;
	}
protected:
	virtual void renderGradient( agg::rendering_buffer& renderingBuffer, agg::rasterizer_scanline_aa<>& rasterizer )	{		
		Point org = context_->getOrigin();

		agg::trans_affine mat;
		mat *= gradientMatrix_;
		mat *= agg::trans_affine_translation( org.x_, org.y_  );

		mat.invert();
		InterpolatorType inter(mat);
		agg::gradient_radial func;

		if ( context_->getMemoryCtxImageType() == Image::itColor ) {
			typedef agg::span_gradient<ColorT, 
                                   InterpolatorType,
                                   agg::gradient_radial,
                                   ColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
			GradientSpanAlloc span_alloc;		

			
			GradientSpanGen span_gen(inter, func, colorProfile_, startRadius_, endRadius_);

			renderScanlines( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
		else {
			typedef agg::span_gradient<agg::gray8, 
                                   InterpolatorType,
                                   agg::gradient_radial,
                                   GrayscaleColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
			GradientSpanAlloc span_alloc;		

			GrayscaleColorProfileVector grayColors;
			convertColorProfileToGrayscale( grayColors );
			
			GradientSpanGen span_gen(inter, func, grayColors, startRadius_, endRadius_);

			renderScanlinesGreyscale( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}

		
	}

	double startRadius_;
	double endRadius_;

};





class HorizontalGradientFill : public GradientFill {
public:

	HorizontalGradientFill():start_(0), end_(100){}

	virtual ~HorizontalGradientFill(){}


	void setStart( const double& val ) {
		start_ = val;
	}

	void setEnd( const double& val ) {
		end_ = val;
	}


	double getStart() const {
		return start_;
	}

	double getEnd() const {
		return end_;
	}
protected:
	virtual void renderGradient( agg::rendering_buffer& renderingBuffer, agg::rasterizer_scanline_aa<>& rasterizer )	{
		
		Point org = context_->getOrigin();		
		agg::trans_affine mat;		
		mat *= gradientMatrix_;
		mat *= agg::trans_affine_translation( org.x_, org.y_  );
		mat.invert();		
		
		InterpolatorType      inter(mat);
		agg::gradient_x func;
		

		if ( context_->getMemoryCtxImageType() == Image::itColor ) {
			typedef agg::span_gradient<ColorT, 
                                   InterpolatorType,
                                   agg::gradient_x,
                                   ColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
			GradientSpanAlloc    span_alloc;
			GradientSpanGen      span_gen(inter, func, colorProfile_, start_, end_);

			renderScanlines( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
		else {
			typedef agg::span_gradient<agg::gray8, 
                                   InterpolatorType,
                                   agg::gradient_x,
                                   GrayscaleColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
			
			GrayscaleColorProfileVector grayColors;
			convertColorProfileToGrayscale( grayColors );

			GradientSpanAlloc    span_alloc;			
			GradientSpanGen      span_gen(inter, func, grayColors, start_, end_);

			renderScanlinesGreyscale( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
	}

	double start_;
	double end_;

};





class VerticalGradientFill : public GradientFill {
public:

	VerticalGradientFill():start_(0), end_(100){}

	virtual ~VerticalGradientFill(){}


	void setStart( const double& val ) {
		start_ = val;
	}

	void setEnd( const double& val ) {
		end_ = val;
	}


	double getStart() const {
		return start_;
	}

	double getEnd() const {
		return end_;
	}
	

protected:
	virtual void renderGradient( agg::rendering_buffer& renderingBuffer, agg::rasterizer_scanline_aa<>& rasterizer )	{		
		Point org = context_->getOrigin();

		agg::trans_affine mat;		
		mat *= gradientMatrix_;
		mat *= agg::trans_affine_translation( org.x_, org.y_  );
		mat.invert();

		InterpolatorType      inter(mat);
		agg::gradient_y func;

		if ( context_->getMemoryCtxImageType() == Image::itColor ) {
			typedef agg::span_gradient<ColorT, 
									   InterpolatorType,
									   agg::gradient_y,
									   ColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;

			GradientSpanAlloc    span_alloc;			
			GradientSpanGen      span_gen(inter, func, colorProfile_, start_, end_);

			renderScanlines( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
		else {
			typedef agg::span_gradient<agg::gray8, 
									   InterpolatorType,
									   agg::gradient_y,
									   GrayscaleColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;

			GrayscaleColorProfileVector grayColors;
			convertColorProfileToGrayscale( grayColors );

			GradientSpanAlloc    span_alloc;			
			GradientSpanGen      span_gen(inter, func, grayColors, start_, end_);

			renderScanlinesGreyscale( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
		
	}

	double start_;
	double end_;

};





class ConicGradientFill : public GradientFill {
public:

	ConicGradientFill():start_(0), end_(100){}

	virtual ~ConicGradientFill(){}


	void setStart( const double& val ) {
		start_ = val;
	}

	void setEnd( const double& val ) {
		end_ = val;
	}


	double getStart() const {
		return start_;
	}

	double getEnd() const {
		return end_;
	}
protected:
	virtual void renderGradient( agg::rendering_buffer& renderingBuffer, agg::rasterizer_scanline_aa<>& rasterizer )	{
		Point org = context_->getOrigin();			
		agg::trans_affine mat;
		mat *= gradientMatrix_;
		mat *= agg::trans_affine_translation( org.x_, org.y_  );
		
		mat.invert();


		InterpolatorType inter(mat);
		agg::gradient_conic conic;

		if ( context_->getMemoryCtxImageType() == Image::itColor ) {
			typedef agg::span_gradient<ColorT, 
                                   InterpolatorType,
                                   agg::gradient_conic,
                                   ColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;
			GradientSpanAlloc    span_alloc;
			GradientSpanGen      span_gen(inter, conic, colorProfile_, 0, 100);

			renderScanlines( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
		else {
			typedef agg::span_gradient<agg::gray8, 
                                   InterpolatorType,
                                   agg::gradient_conic,
                                   GrayscaleColorProfileVector > GradientSpanGen;

			typedef agg::span_allocator<GradientSpanGen::color_type> GradientSpanAlloc;

			GrayscaleColorProfileVector grayColors;
			convertColorProfileToGrayscale( grayColors );

			GradientSpanAlloc    span_alloc;
			GradientSpanGen      span_gen(inter, conic, grayColors, 0, 100);
			renderScanlinesGreyscale( *context_, renderingBuffer, rasterizer, span_alloc, span_gen ); 
		}
	}

	double start_;
	double end_;

};







};


#endif //_VCF_GRADIENTFILLS_H__


