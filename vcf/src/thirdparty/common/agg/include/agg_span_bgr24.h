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
//
// classes span_bgr24
//
//----------------------------------------------------------------------------

#ifndef AGG_SPAN_BGR24_INCLUDED
#define AGG_SPAN_BGR24_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{
    //========================================================================
    template<class BaseRenderer> class span_bgr24 : public BaseRenderer
    {
    public:
        static void pixel(unsigned char* p, int x, 
                          const typename BaseRenderer::attr_type& attr, 
                          int alpha)
        {
            p += x+x+x;

            //*p++ = attr.b;
            //*p++ = attr.g;
            //*p++ = attr.r;

            int b = p[0];
            int g = p[1];
            int r = p[2];
            alpha *= attr.a;
            *p++ = (((attr.b - b) * alpha) + (b << 16)) >> 16;
            *p++ = (((attr.g - g) * alpha) + (g << 16)) >> 16;
            *p++ = (((attr.r - r) * alpha) + (r << 16)) >> 16;
        }

        void render(unsigned char* ptr, 
                    int x, int y,
                    unsigned count, 
                    const unsigned char* covers,
                    const typename BaseRenderer::attr_type& attr)
        {
            typename BaseRenderer::interpolator span = begin(x, y, count, attr);
            unsigned char* p = ptr + x + x + x;
            do 
            {
                span.calculate();
                int alpha = (*covers++) * span.a();

                if(alpha == 255*255)
                {
                    *p++ = span.b();
                    *p++ = span.g();
                    *p++ = span.r();
                }
                else
                {
                    int b = p[0];
                    int g = p[1];
                    int r = p[2];
                    *p++ = (((span.b() - b) * alpha) + (b << 16)) >> 16;
                    *p++ = (((span.g() - g) * alpha) + (g << 16)) >> 16;
                    *p++ = (((span.r() - r) * alpha) + (r << 16)) >> 16;
                }
                span.step();
            }
            while(--count);
        }
    };

}


#endif
