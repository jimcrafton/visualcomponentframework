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
// Definitions for basic argb32 pixel format utilites and renderers
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_ARGB32_BASIC_INCLUDED
#define AGG_RENDERER_ARGB32_BASIC_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_renderer_u8.h"
#include "thirdparty/common/agg/include/agg_renderer_util.h"
#include "thirdparty/common/agg/include/agg_solid_rgba8.h"
#include "thirdparty/common/agg/include/agg_gradient_rgba8.h"
#include "thirdparty/common/agg/include/agg_gouraud_rgba8.h"
#include "thirdparty/common/agg/include/agg_span_argb32.h"
#include "thirdparty/common/agg/include/agg_util_argb32.h"

namespace agg
{
    typedef renderer_util<util_argb32> renderer_argb32_util;

    typedef span_argb32<solid_rgba8> span_argb32_solid;

    typedef renderer_u8<span_argb32_solid> renderer_argb32_solid;

    template<class GradientF> class span_argb32_gradient : 
    public span_argb32<gradient_rgba8<GradientF> > {};

    template<class GradientF> class renderer_argb32_gradient :
    public renderer_u8<span_argb32_gradient<GradientF> > 
    {
    public:
        renderer_argb32_gradient(rendering_buffer& rbuf) : 
           renderer_u8<span_argb32_gradient<GradientF> >(rbuf) {}
    };
    
    typedef span_argb32<gouraud_rgba8> span_argb32_gouraud;
    typedef renderer_u8<span_argb32_gouraud> renderer_argb32_gouraud;
}

#endif
