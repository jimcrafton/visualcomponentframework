//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.0 
// Copyright (C) 2002 Maxim Shemanarev (McSeem)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------

#ifndef AGG_PIXFMT_RGB24_INCLUDED
#define AGG_PIXFMT_RGB24_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{
    struct order_rgb24 { enum { R=0, G=1, B=2 }; };
    struct order_bgr24 { enum { B=0, G=1, R=2 }; };

    //========================================================================
    template<class Order> class pixel_formats_rgb24
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, const color_type& c)
        {
            p += x + x + x;
            p[Order::R] = c.r;
            p[Order::G] = c.g;
            p[Order::B] = c.b;
        }

        //--------------------------------------------------------------------
        static color_type pixel(int8u* p, int x)
        {
            p += x + x + x;
            return color_type(p[Order::R], p[Order::G], p[Order::B]);
        }

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, 
                          const color_type& c, 
                          int alpha)
        {
            p += x + x + x;
            alpha *= c.a;

            if(alpha == 255*255)
            {
                p[Order::R] = c.r;
                p[Order::G] = c.g;
                p[Order::B] = c.b;
            }
            else
            {
                int r = p[Order::R];
                int g = p[Order::G];
                int b = p[Order::B];
                p[Order::R] = (((c.r - r) * alpha) + (r << 16)) >> 16;
                p[Order::G] = (((c.g - g) * alpha) + (g << 16)) >> 16;
                p[Order::B] = (((c.b - b) * alpha) + (b << 16)) >> 16;
            }
        }

        //--------------------------------------------------------------------
        static void hline(int8u* p, int x, 
                          unsigned count, 
                          const color_type& c)
        {
            p += x + x + x;
            do
            {
                p[Order::R] = c.r; 
                p[Order::G] = c.g; 
                p[Order::B] = c.b;
                p += 3;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void vline(int8u* p, int x, 
                          int stride, 
                          unsigned count, 
                          const color_type& c)
        {
            p += x + x + x;
            do
            {
                p[Order::R] = c.r; 
                p[Order::G] = c.g; 
                p[Order::B] = c.b;
                p += stride;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void copy(int8u* dst, 
                         const int8u* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + xdst * 3, src + xsrc * 3, len * 3);
        }


        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  SpanInterpolator& span)
        {
            int8u* p = ptr + x + x + x;
            int alpha = span.a();
            if(alpha)
            {
                if(alpha == 255)
                {
                    do 
                    {
                        span.calculate();
                        p[Order::R] = span.r();
                        p[Order::G] = span.g();
                        p[Order::B] = span.b();
                        span.step();
                        p += 3;
                    }
                    while(--count);
                }
                else
                {
                    do 
                    {
                        span.calculate();
                        int r = p[Order::R];
                        int g = p[Order::G];
                        int b = p[Order::B];
                        p[Order::R] = (((span.r() - r) * alpha) + (r << 8)) >> 8;
                        p[Order::G] = (((span.g() - g) * alpha) + (g << 8)) >> 8;
                        p[Order::B] = (((span.b() - b) * alpha) + (b << 8)) >> 8;
                        span.step();
                        p += 3;
                    }
                    while(--count);
                }
            }
        }


        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& span)
        {
            int8u* p = ptr + x + x + x;
            do 
            {
                span.calculate();
                int alpha = (*covers++) * span.a();

                if(alpha)
                {
                    if(alpha == 255*255)
                    {
                        p[Order::R] = span.r();
                        p[Order::G] = span.g();
                        p[Order::B] = span.b();
                    }
                    else
                    {
                        int r = p[Order::R];
                        int g = p[Order::G];
                        int b = p[Order::B];
                        p[Order::R] = (((span.r() - r) * alpha) + (r << 16)) >> 16;
                        p[Order::G] = (((span.g() - g) * alpha) + (g << 16)) >> 16;
                        p[Order::B] = (((span.b() - b) * alpha) + (b << 16)) >> 16;
                    }
                }
                span.step();
                p += 3;
            }
            while(--count);
        }
    };

    typedef pixel_formats_rgb24<order_rgb24> pixfmt_rgb24;
    typedef pixel_formats_rgb24<order_bgr24> pixfmt_bgr24;

}

#endif

