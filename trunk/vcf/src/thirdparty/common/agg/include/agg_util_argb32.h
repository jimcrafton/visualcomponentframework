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
// class util_argb32
//
//----------------------------------------------------------------------------

#ifndef AGG_UTIL_ARGB32_INCLUDED
#define AGG_UTIL_ARGB32_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{
    //========================================================================
    class util_argb32
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void  render_span(unsigned char* ptr, int x, unsigned count, rgba8 c)
        {
            unsigned char* p = ptr + (x << 2);
            unsigned char  r = c.r;
            unsigned char  g = c.g;
            unsigned char  b = c.b;
            unsigned char  a = c.a;
            do
            {
                *p++ = a;
                *p++ = r;
                *p++ = g;
                *p++ = b;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void  pixel(unsigned char* ptr, int x, rgba8 c)
        {
            ptr += x << 2;
            *ptr++ = c.a;
            *ptr++ = c.r;
            *ptr++ = c.g;
            *ptr   = c.b;
        }

        //--------------------------------------------------------------------
        static rgba8 pixel(unsigned char* ptr, int x)
        {
            ptr += x << 2;
            return rgba8(unsigned(ptr[1]), 
                         unsigned(ptr[2]), 
                         unsigned(ptr[3]),
                         unsigned(ptr[0]));
        }

        //--------------------------------------------------------------------
        static void copy(unsigned char* dst, 
                         const unsigned char* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + (xdst << 2), src + (xsrc << 2), len << 2);
        }
    };


}


#endif
