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
// classes span_gray8
//
//----------------------------------------------------------------------------

#ifndef AGG_SPAN_GRAY8_INCLUDED
#define AGG_SPAN_GRAY8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{
    //========================================================================
    template<class BaseRenderer> class span_gray8 : public BaseRenderer
    {
    public:
        static void pixel(unsigned char* p, int x, 
                          const typename BaseRenderer::attr_type& attr, 
                          int alpha)
        {
            p += x;
            *p = (((attr.v - int(*p)) * alpha * attr.a) + (int(*p) << 16)) >> 16;
        }

        void render(unsigned char* ptr, 
                    int x, int y,
                    unsigned count, 
                    const unsigned char* covers,
                    const typename BaseRenderer::attr_type& attr)
        {
            typename BaseRenderer::interpolator span = begin(x, y, count, attr);
            unsigned char* p = ptr + x;
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
                        *p++ = (((span.v() - int(*p)) * alpha) + (int(*p) << 16)) >> 16;
                    }
                }
                else
                {
                    ++p;
                }
                span.step();
            }
            while(--count);
        }
    };

}


#endif
