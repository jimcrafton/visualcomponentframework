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
// class span_rgb555
//
//----------------------------------------------------------------------------

#ifndef AGG_SPAN_RGB555_INCLUDED
#define AGG_SPAN_RGB555_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    //========================================================================
    template<class BaseRenderer> class span_rgb555 : public BaseRenderer
    {
    public:
        void render(unsigned char* ptr, 
                    int x, int y,
                    unsigned count, 
                    const unsigned char* covers, 
                    const typename BaseRenderer::attr_type& attr)
        {
            typename BaseRenderer::interpolator span = begin(x, y, count, attr);
            int16u* p = ((int16u*)ptr) + x;
            do
            {
                span.calculate();
                int16 rgb = *p;
                int alpha = (*covers++) * span.a();

                int r = (rgb >> 7) & 0xF8;
                int g = (rgb >> 2) & 0xF8;
                int b = (rgb << 3) & 0xF8;

                *p++ = (((((span.r() - r) * alpha) + (r << 16)) >> 9) & 0x7C00) |
                       (((((span.g() - g) * alpha) + (g << 16)) >> 14) & 0x3E0) |
                        ((((span.b() - b) * alpha) + (b << 16)) >> 19);
                span.step();
            }
            while(--count);
        }
    };
}


#endif
