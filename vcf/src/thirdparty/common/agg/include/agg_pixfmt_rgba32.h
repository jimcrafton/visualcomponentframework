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

#ifndef AGG_PIXFMT_RGBA32_INCLUDED
#define AGG_PIXFMT_RGBA32_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{
    struct order_rgba32 { enum { R=0, G=1, B=2, A=3 }; };
    struct order_argb32 { enum { A=0, R=1, G=2, B=3 }; };
    struct order_abgr32 { enum { A=0, B=1, G=2, R=3 }; };
    struct order_bgra32 { enum { B=0, G=1, R=2, A=3 }; };

    //========================================================================
    template<class Order> class pixel_formats_rgba32
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, const color_type& c)
        {
            p += x << 2;
            p[Order::R] = c.r;
            p[Order::G] = c.g;
            p[Order::B] = c.b;
            p[Order::A] = c.a;
        }

        //--------------------------------------------------------------------
        static color_type pixel(int8u* p, int x)
        {
            p += x << 2;
            return color_type(p[Order::R], p[Order::G], p[Order::B], p[Order::A]);
        }

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, 
                          const color_type& c, 
                          int alpha)
        {
            p += x << 2;
            alpha *= c.a;

            if(alpha == 255*255)
            {
                p[Order::R] = c.r;
                p[Order::G] = c.g;
                p[Order::B] = c.b;
                p[Order::A] = c.a;
            }
            else
            {
                int r = p[Order::R];
                int g = p[Order::G];
                int b = p[Order::B];
                int a = p[Order::A];
                p[Order::R] = (((c.r - r) * alpha) + (r << 16)) >> 16;
                p[Order::G] = (((c.g - g) * alpha) + (g << 16)) >> 16;
                p[Order::B] = (((c.b - b) * alpha) + (b << 16)) >> 16;
                p[Order::A] = (((c.a - a) * alpha) + (a << 16)) >> 16;
            }
        }

        //--------------------------------------------------------------------
        static void hline(int8u* p, int x, 
                          unsigned count, 
                          const color_type& c)
        {
            int32u v;
            int8u* p8 = (int8u*)&v;
            p8[Order::R] = c.r;
            p8[Order::G] = c.g;
            p8[Order::B] = c.b;
            p8[Order::A] = c.a;
            int32u* p32 = ((int32u*)p) + x;
            do
            {
                *p32++ = v;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void vline(int8u* p, int x, 
                          int stride, 
                          unsigned count, 
                          const color_type& c)
        {
            int32u v;
            int8u* p8 = (int8u*)&v;
            p8[Order::R] = c.r;
            p8[Order::G] = c.g;
            p8[Order::B] = c.b;
            p8[Order::A] = c.a;
            p += x << 2;
            do
            {
                *(int32u*)p = v; 
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
            memmove(dst + xdst * 4, src + xsrc * 4, len * 4);
        }


        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  SpanInterpolator& span)
        {
            int8u* p = ptr + (x << 2);
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
                        p[Order::A] = span.a();
                        span.step();
                        p += 4;
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
                        int a = p[Order::A];
                        p[Order::R] = (((span.r() - r) * alpha) + (r << 8)) >> 8;
                        p[Order::G] = (((span.g() - g) * alpha) + (g << 8)) >> 8;
                        p[Order::B] = (((span.b() - b) * alpha) + (b << 8)) >> 8;
                        p[Order::A] = (((span.a() - a) * alpha) + (a << 8)) >> 8;
                        span.step();
                        p += 4;
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
            int8u* p = ptr + (x << 2);
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
                        p[Order::A] = span.a();
                    }
                    else
                    {
                        int r = p[Order::R];
                        int g = p[Order::G];
                        int b = p[Order::B];
                        int a = p[Order::A];
                        p[Order::R] = (((span.r() - r) * alpha) + (r << 16)) >> 16;
                        p[Order::G] = (((span.g() - g) * alpha) + (g << 16)) >> 16;
                        p[Order::B] = (((span.b() - b) * alpha) + (b << 16)) >> 16;
                        p[Order::A] = (((span.a() - a) * alpha) + (a << 16)) >> 16;
                    }
                }
                span.step();
                p += 4;
            }
            while(--count);
        }
    };

    typedef pixel_formats_rgba32<order_rgba32> pixfmt_rgba32;
    typedef pixel_formats_rgba32<order_argb32> pixfmt_argb32;
    typedef pixel_formats_rgba32<order_abgr32> pixfmt_abgr32;
    typedef pixel_formats_rgba32<order_bgra32> pixfmt_bgra32;
}

#endif

