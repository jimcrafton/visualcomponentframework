
#ifndef _VCF_SHADOWFILL_H__
#define _VCF_SHADOWFILL_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.

Algorithm copyright 2006 Mario Klingemann 
(for more information see http://incubator.quasimondo.com/processing/fast_blur_deluxe.php).

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

You may only use this algorithm, specifically the code in the functions 
stack_blur_x_gray8() and stack_blur_y_gray8() in the context of developing 
the VCF framework, or developing your own software that itself uses the 
VCF framework. If you would like to use the code independantly from the 
VCF, then please contact Mario Klingemann for more information at 
"mario at quasimondo dot com".
*/



#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef AGG_PIXFMT_GRAY_INCLUDED
#include "thirdparty/common/agg/include/agg_pixfmt_gray.h"
#endif


struct color_sum_gray8
{
   int v;
   void clear() { v = 0; }
};


template<class PixFmt>
void stack_blur_x_gray8(PixFmt& img, int radius)
{
   if(radius < 1) return;

   int w = img.width();
   int h = img.height();
   int wm = w-1;
   int hm = h-1;
   int wh = w*h;
   int div = radius + radius + 1;

   agg::pod_vector<agg::gray8> buf(w);

   int x, y, i;
   agg::pod_vector<int> vmin(w);

   int divsum = (div+1) >> 1;
   divsum *= divsum;

   agg::pod_vector<int> dv(256 * divsum);
   for(i = 0; i < 256 * divsum; i++)
   {
       dv[i] = i / divsum;
   }

   int  stackpointer;
   int  stackstart;
   int  rbs;
   int  r1 = radius + 1;

   color_sum_gray8 sum, insum, outsum;
   agg::pod_vector<color_sum_gray8> stack(div);
   color_sum_gray8* sir;

   agg::gray8 p;

   for(y = 0; y < h; y++)
   {
       sum.clear();
       insum.clear();
       outsum.clear();

       for(i = -radius; i <= radius; i++)
       {
           int ix = i;
           if(ix < 0)  ix = 0;
           if(ix > wm) ix = wm;
           p = img.pixel(ix, y);

           sir = &stack[i + radius];
           sir->v = p.v;
           
           rbs = r1 - abs(i);

           sum.v += sir->v * rbs;

           if(i > 0)
           {
               insum.v += sir->v;
           }
           else
           {
               outsum.v += sir->v;
           }
       }

       stackpointer = radius;

       for(x = 0; x < w; x++)
       {
           buf[x].v = dv[sum.v];

           sum.v -= outsum.v;

           stackstart = stackpointer - radius + div;
           sir = &stack[stackstart % div];

           outsum.v -= sir->v;

           if(y==0)
           {
               vmin[x] = x + radius + 1;
               if(vmin[x] > wm) vmin[x] = wm;
           }

           p = img.pixel(vmin[x], y);

           sir->v = p.v;

           insum.v += sir->v;

           sum.v += insum.v;

           ++stackpointer;
           if(stackpointer >= div) stackpointer = 0;
           sir = &stack[stackpointer];

           outsum.v += sir->v;
           insum.v -= sir->v;

       }
       img.copy_color_hspan(0, y, w, &buf[0]);
   }
}



template<class PixFmt>
void stack_blur_y_gray8(PixFmt& img, int radius)
{
   if(radius < 1) return;

   int w = img.width();
   int h = img.height();
   int wm = w-1;
   int hm = h-1;
   int wh = w*h;
   int div = radius + radius + 1;

   agg::pod_vector<agg::gray8> buf(h);

   int x, y, i;
   agg::pod_vector<int> vmin(h);

   int divsum = (div+1) >> 1;
   divsum *= divsum;

   agg::pod_vector<int> dv(256 * divsum);
   for(i = 0; i < 256 * divsum; i++)
   {
       dv[i] = i / divsum;
   }

   int  stackpointer;
   int  stackstart;
   int  rbs;
   int  r1 = radius + 1;

   color_sum_gray8 sum, insum, outsum;
   agg::pod_vector<color_sum_gray8> stack(div);
   color_sum_gray8* sir;

   agg::gray8 p;

   for(x = 0; x < w; x++)
   {
       sum.clear();
       insum.clear();
       outsum.clear();

       for(i = -radius; i <= radius; i++)
       {
           int iy = i;
           if(iy < 0)  iy = 0;
           if(iy > wm) iy = wm;
           p = img.pixel(x, iy);

           sir = &stack[i + radius];
           sir->v = p.v;

           rbs = r1 - abs(i);

           sum.v += sir->v * rbs;

           if(i > 0)
           {
              insum.v += sir->v;
           }
           else
           {
               outsum.v += sir->v;
           }
       }

       stackpointer = radius;

       for(y = 0; y < h; y++)
       {
           buf[y].v = dv[sum.v];

           sum.v -= outsum.v;

           stackstart = stackpointer - radius + div;
           sir = &stack[stackstart % div];

           outsum.v -= sir->v;

           if(x == 0)
           {
               vmin[y] = y + radius + 1;
               if(vmin[y] > hm) vmin[y] = hm;
           }

           p = img.pixel(x, vmin[y]);

           sir->v = p.v;

           insum.v += sir->v;

           sum.v += insum.v;

           ++stackpointer;
           if(stackpointer >= div) stackpointer = 0;
           sir = &stack[stackpointer];

           outsum.v += sir->v;

           insum.v -= sir->v;

       }
       img.copy_color_vspan(x, 0, h, &buf[0]);
	}
}


namespace VCF  {

class ShadowFill : public Object, public Fill {
public:


	

	ShadowFill():alpha_(1.0),radius_(6), context_(NULL){

	}

	virtual ~ShadowFill(){}


	virtual void setContext( GraphicsContext* context ) {
		context_ = context;
	}

    virtual void render( Path* path ) {
		std::vector<PathPoint> points;
		path->getPoints( points, NULL );

		std::vector<Point> pts;
		std::vector<PathPoint>::iterator pathIt = points.begin();	

		if ( NULL != context_->getRenderingBuffer() ) {

			agg::path_storage fillPath;

			while ( pathIt != points.end() ) {
				PathPoint& pt = *pathIt;

				
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
						PathPoint& c1 = *pathIt;

						
						pathIt++;
						PathPoint& c2 = *pathIt;

						pathIt++;
						PathPoint& p2 = *pathIt;
						
						
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
				}
				
				pathIt ++;
			}

			context_->resetRenderAreaAlpha();

			agg::trans_affine mat = *context_->getCurrentTransform();
			Point org = context_->getOrigin();
			mat *= agg::trans_affine_translation( org.x_, org.y_  );
			
			agg::conv_curve<agg::path_storage> smooth(fillPath);

			agg::conv_transform< agg::conv_curve< agg::path_storage > > 
				xfrmedPath(smooth,mat);


			Rect pathBounds;
			uint32 pid[1] = {0};
			agg::bounding_rect( xfrmedPath, pid, 0, 1,
						&pathBounds.left_, &pathBounds.top_,
						&pathBounds.right_, &pathBounds.bottom_ );

			pathBounds.inflate( 2*radius_, 2*radius_ );

			Image* img = GraphicsToolkit::createImage( pathBounds.getWidth(), pathBounds.getHeight() );
			
			{	
				ImageContext imgCtx = img;

				imgCtx->setColor( &getColor() );
				imgCtx->rectangle( 0, 0, img->getWidth(), img->getHeight() );
				imgCtx->fillPath();
			}

			ColorPixels pix = img;
			AlphaChannel mask(pix);
			mask.fill(0);//clear out alpha
			Image* maskImage = mask.createImage();

			{
				ImageContext maskCtx = maskImage;
				
				maskCtx->setAntiAliasingOn(true);
				agg::trans_affine m;
				m *= agg::trans_affine_translation( -pathBounds.left_,//  + maskImage->getWidth()/2.0, 
											-pathBounds.top_ ); //+ maskImage->getHeight()/2.0 );
				
				m *= mat;


				agg::conv_transform< agg::conv_transform< agg::conv_curve< agg::path_storage > > >
					xpath2( xfrmedPath, m );

				agg::rasterizer_scanline_aa<> rasterizer;

				rasterizer.clip_box( 0, 0, img->getWidth(), img->getHeight() ); 
				rasterizer.add_path( xpath2 );

				renderScanlinesSolidGreyscale( *maskCtx, rasterizer, agg::rgba(alpha_,alpha_,alpha_,alpha_) );				

				agg::pixfmt_gray8 pixf(*maskCtx->getRenderingBuffer());

				stack_blur_x_gray8(pixf, radius_);
				stack_blur_y_gray8(pixf, radius_);
			}			

			mask.updateFromImage( maskImage );
				

			delete maskImage;



			int gcs = context_->saveState();
			
			org = context_->getOrigin();
			Matrix2D m;
			m *= Matrix2D::translation( org.x_, org.y_  );

			context_->setCurrentTransform( m );

			context_->drawImage( pathBounds.left_, pathBounds.top_, img, false );			
			context_->renderImages();

			context_->restoreState( gcs );
		}
	}

	void setAlpha( const double& val ) {
		alpha_ = val;
	}

	double getAlpha() const {
		return alpha_;
	}

	Color getColor() const {
		return color_;
	}

	void setColor( const Color& c ) {
		color_ = c;
	}

	int getRadius() const {
		return radius_;
	}

	void setRadius( int val ) {
		radius_ = val;
	}
protected:	
	double alpha_;
	GraphicsContext* context_;
	Color color_;
	int radius_;
};


};



#endif //_VCF_SHADOWFILL_H__

