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
// Definitions for basic gray8 pixel format utilites and renderers
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_GRAY8_BASIC_INCLUDED
#define AGG_RENDERER_GRAY8_BASIC_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_renderer_u8.h"
#include "thirdparty/common/agg/include/agg_renderer_util.h"
#include "thirdparty/common/agg/include/agg_solid_gray8.h"
#include "thirdparty/common/agg/include/agg_gradient_gray8.h"
#include "thirdparty/common/agg/include/agg_gouraud_gray8.h"
#include "thirdparty/common/agg/include/agg_span_gray8.h"
#include "thirdparty/common/agg/include/agg_util_gray8.h"

namespace agg
{
    typedef renderer_util<util_gray8> renderer_gray8_util;

    typedef span_gray8<solid_gray8> span_gray8_solid;
    typedef renderer_u8<span_gray8_solid> renderer_gray8_solid;

    template<class GradientF> class span_gray8_gradient : 
    public span_gray8<gradient_gray8<GradientF> > {};

    template<class GradientF> class renderer_gray8_gradient :
    public renderer_u8<span_gray8_gradient<GradientF> > 
    {
    public:
        renderer_gray8_gradient(rendering_buffer& rbuf) : 
           renderer_u8<span_gray8_gradient<GradientF> >(rbuf) {}
    };
    
    typedef span_gray8<gouraud_gray8> span_gray8_gouraud;
    typedef renderer_u8<span_gray8_gouraud> renderer_gray8_gouraud;
}


#endif


