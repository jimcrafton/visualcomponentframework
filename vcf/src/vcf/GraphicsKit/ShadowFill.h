
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
			
			agg::conv_transform< agg::path_storage > xfrmedPath(fillPath,mat);

			Rect pathBounds;
			uint32 pid[1] = {0};
			agg::bounding_rect( xfrmedPath, pid, 0, 1,
						&pathBounds.left_, &pathBounds.top_,
						&pathBounds.right_, &pathBounds.bottom_ );

			pathBounds.inflate( 2*radius_, 2*radius_ );

			Image* img = GraphicsToolkit::createImage( pathBounds.getWidth(), pathBounds.getHeight() );

			{

				
				ImageContext ictx = img;
				ictx->setColor( &color_ );
				//ictx->rectangle( 0, 0, img->getWidth(), img->getHeight() );
				//ictx->fillPath();
				
			}
			
			ColorPixels pix = img;
			RedChannel mask(pix);
			mask.fill(0);//clear out alpha
			Image* maskImage = mask.createImage();

			{
				ImageContext ictx = maskImage;
				BasicFill fill;
				fill.setColor( &Color(alpha_,alpha_,alpha_,alpha_) );


				ictx->setCurrentFill( &fill );


				ictx->setRenderArea( Rect(0,0,maskImage->getWidth(), maskImage->getHeight()) );


				Matrix2D m;
				m *= Matrix2D::translation( -(pathBounds.left_  /*+ maskImage->getWidth()/2.0*/ ), 
											-(pathBounds.top_ /*+ maskImage->getHeight()/2.0*/ ) );

				m *= *context_->getCurrentTransform();
				
			
				//m *= Matrix2D::translation( (pathBounds.left_  /*+ maskImage->getWidth()/2.0*/ ), 
				//							(pathBounds.top_ /*+ maskImage->getHeight()/2.0*/ ) );
				
/*
				std::vector<PathPoint> pts;
				path->getPoints( pts, &m );
				std::vector<PathPoint>::iterator pit = pts.begin();
				StringUtils::trace( "xfrmed path: \n" );
				while ( pit != pts.end() ) {
					PathPoint& pt = *pit;
					StringUtils::trace( Format("\tpt: %.2f, %.2f \n") % pt.point_.x_ % pt.point_.y_ );

					pit ++;
				}
*/


				ictx->setCurrentTransform( m );

				ictx->draw( path );


				ictx->setCurrentFill( NULL );				


				//ictx->setColor( &Color(alpha_,alpha_,alpha_,alpha_) );
				//ictx->rectangle( 10, 10, 30, 30 );
				//ictx->fillPath();


				ictx->flushRenderArea();
			}


			

			agg::rendering_buffer maskRb;
			maskRb.attach( (unsigned char*)maskImage->getData(), maskImage->getWidth(), maskImage->getHeight(),
								maskImage->getWidth() );

			agg::pixfmt_gray8 pixf(maskRb);

			//stack_blur_x_gray8(pixf, radius_);
			//stack_blur_y_gray8(pixf, radius_);

			//mask.updateFromImage( maskImage );

			{
#if 0 
				ImageContext ictx = img;

				ictx->bitBlit( 0, 0, maskImage );

#else
				ColorPixels pix = img;
				ColorPixels::Type* bits = pix;
				GrayPixels grPix = maskImage;
				GrayPixels::Type* grBits = grPix;
				

				uint32 sz =  grPix.width() * grPix.height();
				uint32 i = 0;

				for (int y=0;y<pix.height();y++ ) {
					for (int x=0;x<pix.width();x++ ) {
						if ( grPix.at(x,y).value >= 250 ) {
							
						//pix.at(x,y).r = 255;
						//pix.at(x,y).g = 0;
						pix.at(x,y).b = grPix.at(x,y).value;
						}
						else{
							pix.at(x,y).a = 0;
						}
					}

				}

				//while ( i < sz ) {
				//	bits[i].r = grBits[i].value;
				//	bits[i].g = grBits[i].value;
				//	bits[i].b = grBits[i].value;
				//	i++;
				//}
#endif				
			}

			delete maskImage;



			int gcs = context_->saveState();
			
			org = context_->getOrigin();
			Matrix2D m;
			m *= Matrix2D::translation( org.x_, org.y_  );

			context_->setCurrentTransform( m );

			context_->drawImage( pathBounds.left_, pathBounds.top_, img, false );			
			context_->renderImages();

			context_->restoreState( gcs );
/*

			agg::rendering_buffer& renderingBuffer = *context_->getRenderingBuffer();
			agg::rasterizer_scanline_aa<> rasterizer;
			

			
			agg::conv_curve<agg::path_storage> smooth(fillPath);
			
			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath2(smooth,mat);


			
			rasterizer.add_path( xfrmedPath2 );

			

			context_->resetRenderAreaAlpha();

			renderScanlinesSolid( *context_, rasterizer, agg::rgba(color_.getRed(),color_.getGreen(),color_.getBlue(),color_.getAlpha()) );
			*/
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

