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
// Basic primitives for fast drawing regular (aliased) figures 
// Supports 32-bit B-G-R-A pixel format.
//
//----------------------------------------------------------------------------

#ifndef AGG_PRIMITIVES_BRGA32_INCLUDED
#define AGG_PRIMITIVES_BRGA32_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_primitives.h"
#include "thirdparty/common/agg/include/agg_primitives32.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{

    template<class Base> class primitives_bgra32_base : public Base
    {
    public:
        typedef Base base_type;
        
        primitives_bgra32_base(rendering_buffer& rbuf) : base_type(rbuf) {}

        static int32u bgra32(unsigned r, unsigned g, unsigned b, unsigned a)
        {
            int32u c;
            unsigned char* p = (unsigned char*)(&c);
            *p++ = b; 
            *p++ = g; 
            *p++ = r; 
            *p   = a;
            return c;
        }

        void line_color(const rgba8& c) 
        {
            base_type::line_color(bgra32(c.r, c.g, c.b, c.a));
        }

        void fill_color(const rgba8& c)
        { 
            base_type::fill_color(bgra32(c.r, c.g, c.b, c.a));
        }

        void pixel(int x, int y, int r, int g, int b)
        {
            base_type::pixel(x, y, bgra32(r, g, b, 255));
        }
    };

    typedef primitives_bgra32_base<primitives<primitives32> > primitives_bgra32;

}


#endif

