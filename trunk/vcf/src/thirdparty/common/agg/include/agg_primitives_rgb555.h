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
// Supports rgb555 pixel format.
//
//----------------------------------------------------------------------------

#ifndef AGG_PRIMITIVES_RGB555_INCLUDED
#define AGG_PRIMITIVES_RGB555_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_primitives.h"
#include "thirdparty/common/agg/include/agg_primitives16.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"


namespace agg
{

    template<class Base> class primitives_rgb555_base : public Base
    {
    public:
        typedef Base base_type;

        primitives_rgb555_base(rendering_buffer& rbuf) : base_type(rbuf) {}

        static int16u rgb555(unsigned r, unsigned g, unsigned b)
        {
            return ((r & 0xF8) << 7) | ((g & 0xF8) << 2) | (b >> 3);
        }

        void line_color(const rgba8& c) 
        {
            base_type::line_color(rgb555(c.r, c.g, c.b));
        }

        void fill_color(const rgba8& c)
        { 
            base_type::fill_color(rgb555(c.r, c.g, c.b));
        }

        void pixel(int x, int y, int r, int g, int b)
        {
            base_type::pixel(x, y, rgb555(r, g, b));
        }
    };

    typedef primitives_rgb555_base<primitives<primitives16> > primitives_rgb555;

}


#endif

