//BasicFill.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/AggCommon.h"
#include "thirdparty/common/agg/include/agg_scanline_p.h"

using namespace VCF;

BasicFill::BasicFill():
	context_(NULL),
	antiAlias_(true)
{

}

BasicFill::~BasicFill()
{

}



void BasicFill::render( Path* path )
{
	if ( (NULL != context_) && (NULL != path) ){
		context_->setColor( &color_ );


		

		//JC - we don't need to grab the current transform since it's 
		//applied to the points any how
		//Matrix2D* currentXFrm = context_->getCurrentTransform();
		std::vector<PathPoint> points;
		path->getPoints( points, NULL );

		std::vector<Point> pts;

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

		if ( (NULL != context_->getRenderingBuffer()) && antiAlias_ ){

			agg::rendering_buffer& renderingBuffer = *context_->getRenderingBuffer();
			agg::path_storage fillPath;
			agg::rasterizer_scanline_aa<> rasterizer;


			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						fillPath.move_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						fillPath.line_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {

						fillPath.move_to( pt.point_.x_, pt.point_.y_ );

						pathIt++;
						c1 = *pathIt;

						pathIt++;
						c2 = *pathIt;

						pathIt++;
						p2 = *pathIt;
						
						fillPath.curve4( c1.point_.x_, c1.point_.y_,
										c2.point_.x_, c2.point_.y_,
										p2.point_.x_, p2.point_.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						fillPath.line_to( pt.point_.x_, pt.point_.y_ );
						fillPath.close_polygon();
					}
					break;
				
					case PathPoint::ptUnknown:
						VCF_ASSERT(false);
					break;
				}
				
				pathIt ++;
			}

			Matrix2D& currentXFrm = *context_->getCurrentTransform();

			agg::trans_affine mat( currentXFrm[Matrix2D::mei00],
									currentXFrm[Matrix2D::mei01],
									currentXFrm[Matrix2D::mei10],
									currentXFrm[Matrix2D::mei11],
									currentXFrm[Matrix2D::mei20],
									currentXFrm[Matrix2D::mei21] );

			Point org = context_->getOrigin();
			mat *= agg::trans_affine_translation( org.x_, org.y_  );


			agg::conv_curve<agg::path_storage> smooth(fillPath);
			
			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);


			
			rasterizer.add_path( xfrmedPath );

			

			context_->resetRenderAreaAlpha();

			renderScanlinesSolid( *context_, rasterizer, agg::rgba(color_.getRed(),color_.getGreen(),color_.getBlue(),color_.getAlpha()) );
		}
		else {
			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						if ( !pts.empty() ) {
							context_->polyline( pts );
						}
						pts.clear();
						pts.push_back( pt.point_ );
					}
					break;

					case PathPoint::ptLineTo: {
						//context_->lineTo( pt.point_.x_, pt.point_.y_ );
						pts.push_back( pt.point_ );
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
						pts.push_back( pt.point_ );
						context_->polyline( pts );

						pts.clear();
					}
					break;
				}
				
				pathIt ++;
			}

			if ( !pts.empty() ) {
				context_->polyline( pts );
				pts.clear();
			}

			context_->fillPath();			
		}
	}
}


/**
$Id$
*/
