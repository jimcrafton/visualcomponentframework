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
// classe util_gray8
//
//----------------------------------------------------------------------------

#ifndef AGG_UTIL_GRAY8_INCLUDED
#define AGG_UTIL_GRAY8_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gray8.h"

namespace agg
{

    //========================================================================
    class util_gray8
    {
    public:
        typedef gray8 color_type;

        //--------------------------------------------------------------------
        static void render_span(unsigned char* ptr, int x, unsigned count, gray8 c)
        {
            memset(ptr + x, c.v, count);
        }

        //--------------------------------------------------------------------
        static void  pixel(unsigned char* ptr, int x, gray8 c)
        {
            ptr[x] = c.v;
        }

        //--------------------------------------------------------------------
        static gray8 pixel(unsigned char* ptr, int x)
        {
            return gray8(unsigned(ptr[x]));
        }

        //--------------------------------------------------------------------
        static void copy(unsigned char* dst, 
                         const unsigned char* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + xdst, src + xsrc, len);
        }
    };


}


#endif

