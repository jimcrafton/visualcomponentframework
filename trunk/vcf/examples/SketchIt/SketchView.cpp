#include "ApplicationKit.h"
#include "ModelViewKit.h"
#include "SketchView.h"
#include "SketchDocument.h"
#include "SketchTools.h"



#include "graphics/AggCommon.h"


#include "../../thirdparty/common/agg/include/agg_image_transform.h"
#include "../../thirdparty/common/agg/include/agg_span_null_interpolator.h"
#include "../../thirdparty/common/agg/include/agg_pixfmt_rgba32_image.h"
#include "../../thirdparty/common/agg/include/agg_renderer_scanline.h"

//#include "../../thirdparty/common/agg/include/agg_span_bgra32_image.h"


using namespace VCF;


SketchView::SketchView()
{

}

SketchView::~SketchView()
{

}


class ColorAlpha {
public:
	int alphaValue_;

	int calculate(int alpha, int c, int, int, int) const { 
		return alphaValue_; 
	}
};

void SketchView::paintView( GraphicsContext* ctx )
{
	ctx->setColor( Color::getColor( "white" ) );
	
	Rect* clientBounds = getViewControl()->getClientBounds();
	ctx->rectangle( clientBounds );
	ctx->fillPath();


	SketchDocument* doc = (SketchDocument*)getViewModel();

	BasicStroke bs;
	BasicFill bf;
	ctx->setCurrentStroke( &bs );
	
	Rect viewBounds = ctx->getViewableBounds();
	

	Enumerator<Shape*>* shapes = doc->getShapes();
	while ( shapes->hasMoreElements() ) {
		Shape* shape = shapes->nextElement();
			
		bs.setColor( &shape->strokeColor_ );		
		bs.setOpacity( shape->opacity_ );
		bs.setWidth( shape->width_ );
		
		if ( shape->fill_ ) {
			bf.setColor( shape->fillColor_ );
			bf.setOpacity( shape->opacity_ );
			ctx->setCurrentFill( &bf );
		}
		else {
			ctx->setCurrentFill( NULL );
		}
		
		ctx->draw( &shape->polygon_ );
		
		if ( NULL != shape->image_ ) {
			Rect bounds = shape->polygon_.getBounds();
			
			//ctx->drawImage( bounds.left_, bounds.top_, shape->image_ );
			
			if ( this->getViewControl()->isUsingRenderBuffer() ) {
				
				agg::rendering_buffer* renderingBuffer = ctx->getRenderingBuffer();
				
				shape->image_->getImageBits()->attachRenderBuffer( shape->image_->getWidth(), shape->image_->getHeight() );
				
				
				
				typedef agg::image_transform_attr<agg::null_distortions, 
					ColorAlpha,//agg::null_color_alpha, 
					agg::null_gradient_alpha> attr_type;
				
				typedef agg::span_null_interpolator<attr_type> span_interpolator;
				
				typedef agg::pixfmt_bgra32_image_bilinear<attr_type> span_renderer;
				
				typedef agg::renderer_scanline<span_interpolator, span_renderer> renderer_image;
				
				
				
				agg::null_distortions    distortions; 
				ColorAlpha   color_alpha;
				color_alpha.alphaValue_ = 255.0 * (bounds.left_ / clientBounds->getWidth() );
				agg::null_gradient_alpha gradient_alpha;
				
				renderer_image           imgRenderer(*renderingBuffer);
				
				typedef agg::renderer_scanline<agg::span_solid_rgba8, pixfmt> renderer_solid;
				
				renderer_solid renderer( *renderingBuffer );
				
				agg::rasterizer_scanline_aa<agg::scanline_u8, agg::gamma8> rasterizer;
				
				agg::affine_matrix src_mtx; 
				//src_mtx *= agg::translation_matrix( 0,0);//bounds.left_, bounds.top_ );
				
				//src_mtx *= agg::rotation_matrix(32.0 * agg::pi / 180.0);
				
				src_mtx *= agg::translation_matrix( -bounds.left_, -bounds.top_ );
				
				
				agg::rendering_buffer* imgRenderingBuffer = shape->image_->getImageBits()->renderBuffer_;
				
				attr_type attr( *imgRenderingBuffer, src_mtx, distortions, color_alpha, gradient_alpha);
				
				imgRenderer.attribute (attr);
				
				agg::path_storage strokePath;
				strokePath.move_to( bounds.left_, bounds.top_ );
				strokePath.line_to( bounds.left_ + bounds.getWidth(), bounds.top_ );
				strokePath.line_to( bounds.left_ + bounds.getWidth(), bounds.top_ + bounds.getHeight() );
				strokePath.line_to( bounds.left_, bounds.top_ + bounds.getHeight() );
				strokePath.close_polygon();
				rasterizer.add_path( strokePath );
				
				rasterizer.render (imgRenderer);
				
			}
		}		
	}

	ctx->setCurrentStroke( NULL );
	ctx->setCurrentFill( NULL );

	Tool* tool = ToolManager::getToolManager()->getCurrentTool();

	if ( NULL != tool ) {
		tool->paintState( ctx );
	}
	
}

