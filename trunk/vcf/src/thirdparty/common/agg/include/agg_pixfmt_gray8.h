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

#ifndef AGG_PIXFMT_GRAY8_INCLUDED
#define AGG_PIXFMT_GRAY8_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gray8.h"

namespace agg
{

    //========================================================================
    class pixfmt_gray8
    {
    public:
        typedef gray8 color_type;

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, const color_type& c)
        {
            p[x] = c.v;
        }

        //--------------------------------------------------------------------
        static color_type pixel(int8u* p, int x)
        {
            return color_type(p[x]);
        }

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, 
                          const color_type& c, 
                          int alpha)
        {
            int v = p[x];
            alpha *= c.a;
            p[x] = (((c.v - v) * alpha) + (v << 16)) >> 16;
        }

        //--------------------------------------------------------------------
        static void hline(int8u* p, int x, 
                          unsigned count, 
                          const color_type& c)
        {
            p += x;
            do
            {
                *p++ = c.v; 
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void vline(int8u* p, int x, 
                          int stride, 
                          unsigned count, 
                          const color_type& c)
        {
            p += x;
            do
            {
                *p = c.v; 
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
            memmove(dst + xdst, src + xsrc, len);
        }


        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  SpanInterpolator& span)
        {
            int8u* p = ptr + x;
            do 
            {
                span.calculate();
                *p++ = span.v();
                span.step();
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& span)
        {
            int8u* p = ptr + x;
            do 
            {
                span.calculate();
                int alpha = (*covers++) * span.a();

                if(alpha)
                {
                    if(alpha == 255*255)
                    {
                        *p++ = span.v();
                    }
                    else
                    {
                        int v = *p;
                        *p++ = (((span.v() - v) * alpha) + (v << 16)) >> 16;
                    }
                }
                span.step();
            }
            while(--count);
        }
    };

}

#endif

