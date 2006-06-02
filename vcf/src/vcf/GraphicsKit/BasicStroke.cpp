//BasicStroke.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/AggCommon.h"
#include "thirdparty/common/agg/include/agg_scanline_p.h"
#include "thirdparty/common/agg/include/agg_conv_dash.h"


using namespace VCF;


BasicStroke::BasicStroke():
	width_(0.0),
	color_ (*Color::getColor( VCF::ColorNames::at( VCF::ColorNames::black ) )),
	context_(NULL),		
	antiAlias_(true),
	dashed_(false),
	dashStart_(0.0)
{

}

BasicStroke::~BasicStroke()
{

}


void BasicStroke::setContext( GraphicsContext* context )
{
	context_ = context;
}




void BasicStroke::render( Path * path )
{
	if ( (NULL != context_) && (NULL != path) ){
		context_->setColor( &color_ );


		//JC - we don't need to grab the current transform since it's 
		//applied to the points any how
		//Matrix2D* currentXFrm = context_->getCurrentTransform();
		std::vector<PathPoint> points;
		/**
		JC - changing the Path API a bit here
		*/
		path->getPoints( points, NULL );

		/**
		JC:
		Thanks to Marcello, we have resolved the VC7/7.1 stack corruption
		bug! Apparently, due to some trickery on my part which involved
		const PathPoint& pt = points->nextElement();
		This was causing some weird problems due to referencing a temporary
		copy of the PathPoint. Marcello found this and discovered that if we replaced
		that with the a simply assignment to the variables below, we have no more
		problems! Many, many, many thanks to Marcello for tracking this down and
		fixing it!!!
		*/
		PathPoint pt, p2, c1, c2;	

		std::vector<PathPoint>::iterator pathIt = points.begin();
		
		if ( (NULL != context_->getRenderingBuffer()) && (antiAlias_) ){			
			agg::rendering_buffer& renderingBuffer = *context_->getRenderingBuffer();
			typedef agg::renderer_base<pixfmt> ren_base;
			typedef agg::renderer_scanline_aa_solid<ren_base> renderer_solid;			

			typedef agg::comp_op_adaptor_rgba<color_type, component_order> blender_type;
			typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
			typedef agg::renderer_base<pixfmt_type> comp_renderer_type;


			


			agg::path_storage strokePath;

			agg::rasterizer_scanline_aa<> rasterizer;
			agg::scanline_p8 scanline;

			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						strokePath.move_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						strokePath.line_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {

						strokePath.move_to( pt.point_.x_, pt.point_.y_ );
						
						pathIt++;
						c1 = *pathIt;
						
						pathIt++;
						c2 = *pathIt;
						
						pathIt++;
						p2 = *pathIt;
						
						strokePath.curve4( c1.point_.x_, c1.point_.y_,
										c2.point_.x_, c2.point_.y_,
										p2.point_.x_, p2.point_.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						strokePath.close_polygon();
					}
					break;
				}
				
				pathIt++;
			}

			Matrix2D& currentXFrm = *context_->getCurrentTransform();

			agg::trans_affine mat( currentXFrm[Matrix2D::mei00],
									currentXFrm[Matrix2D::mei01],
									currentXFrm[Matrix2D::mei10],
									currentXFrm[Matrix2D::mei11],
									currentXFrm[Matrix2D::mei20],
									currentXFrm[Matrix2D::mei21] );
			

			//JC
			//I added this to account for anti-aliasing "defects"
			//that occur with thin lines (1-2 pixels wide)
			//See http://antigrain.com/tips/line_alignment/line_alignment.agdoc.html
			//for more information about why this happens, and why this 
			//may not be the optimal solution
			mat*=agg::trans_affine_translation(0.5,0.5);
			

			agg::conv_curve< agg::path_storage > smooth(strokePath);

			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);

			if( dashed_ ) {
				
				agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > dash(xfrmedPath);
				
				for(unsigned int j=0; j<dashGapLen_.size(); ++j) {
					dash.add_dash( dashGapLen_[j].first, dashGapLen_[j].second );
				}

				dash.dash_start(dashStart_);				
				
				agg::conv_stroke< agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > >  stroke(dash);
				
				stroke.width( maxVal<>( 0.5, width_ ) );
				
				rasterizer.add_path( stroke );
			}
			else {

				agg::conv_stroke< agg::conv_transform< agg::conv_curve< agg::path_storage > > >  stroke(xfrmedPath);
				
				stroke.width( maxVal<>( 0.5, width_ ) );
				
				rasterizer.add_path( stroke );
			}			


			
			if ( GraphicsContext::cmSource == context_->getCompositingMode() ) {
				pixfmt pixf(renderingBuffer);
				ren_base renb(pixf);

				renderer_solid renderer( renb );

				renderer.color(agg::rgba(color_.getRed(),color_.getGreen(),color_.getBlue(),color_.getAlpha()));


				agg::render_scanlines(rasterizer, scanline, renderer);
			}
			else {
				pixfmt_type pixf(renderingBuffer);
				pixf.comp_op( context_->getCompositingMode() );
				comp_renderer_type renb(pixf);


				agg::render_scanlines_aa_solid(rasterizer, scanline, renb, agg::rgba(color_.getRed(),color_.getGreen(),color_.getBlue(),color_.getAlpha()));
			}

			
		}
		else {
			context_->setStrokeWidth( width_ );

			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						context_->moveTo( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						context_->lineTo( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {
						pathIt ++;
						
						c1 = *pathIt;
						
						pathIt ++;
						c2 = *pathIt;

						pathIt++;
						p2 = *pathIt;

						context_->curve( pt.point_.x_, pt.point_.y_,
											c1.point_.x_, c1.point_.y_,
											c2.point_.x_, c2.point_.y_,
											p2.point_.x_, p2.point_.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						context_->lineTo( pt.point_.x_, pt.point_.y_ );
					}
					break;
				}
				
				pathIt ++;
			}
			context_->strokePath();			
		}
	}

}

double BasicStroke::getWidth()
{
	return width_;
}

void BasicStroke::setWidth( double width )
{
	width_ = width;
}

Color* BasicStroke::getColor()
{
	return &color_;
}

void BasicStroke::setColor( Color* color )
{
	color_ = *color;
}

void BasicStroke::line( const double& x1, const double& y1,
		                const double& x2, const double& y2 )
{

}


/**
$Id$
*/
