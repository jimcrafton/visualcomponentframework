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
// class util_rgb555
//
//----------------------------------------------------------------------------

#ifndef AGG_UTIL_RGB555_INCLUDED
#define AGG_UTIL_RGB555_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{

    inline int16u rgb555(unsigned r, unsigned g, unsigned b)
    {
        return ((r & 0xF8) << 7) | ((g & 0xF8) << 2) | (b >> 3);
    }

    //========================================================================
    class util_rgb555
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void  render_span(unsigned char* ptr, int x, unsigned count, rgba8 c)
        {
            int16u* p = ((int16u*)ptr) + x;
            int16u  rgb = rgb555(c.r, c.g, c.b);
            do
            {
                *p++ = rgb;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void  pixel(unsigned char* ptr, int x, rgba8 c)
        {
            ptr += x + x;
            *(int16u*)ptr = rgb555(c.r, c.g, c.b);
        }

        //--------------------------------------------------------------------
        static rgba8 pixel(unsigned char* ptr, int x)
        {
            register unsigned rgb = ((int16u*)ptr)[x];
            return rgba8((rgb >> 7) & 0xF8, 
                         (rgb >> 2) & 0xF8, 
                         (rgb << 3) & 0xF8);
        }

        //--------------------------------------------------------------------
        static void copy(unsigned char* dst, 
                         const unsigned char* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + (xdst << 1), src + (xsrc << 1), len << 1);
        }
    };

}


#endif
