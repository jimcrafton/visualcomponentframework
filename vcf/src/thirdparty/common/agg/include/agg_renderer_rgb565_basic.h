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
// Definitions for basic rgb565 pixel format utilites and renderers
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_RGB565_BASIC_INCLUDED
#define AGG_RENDERER_RGB565_BASIC_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_renderer_u8.h"
#include "thirdparty/common/agg/include/agg_renderer_util.h"
#include "thirdparty/common/agg/include/agg_solid_rgba8.h"
#include "thirdparty/common/agg/include/agg_gradient_rgba8.h"
#include "thirdparty/common/agg/include/agg_gouraud_rgba8.h"
#include "thirdparty/common/agg/include/agg_span_rgb565.h"
#include "thirdparty/common/agg/include/agg_util_rgb565.h"

namespace agg
{
    typedef renderer_util<util_rgb565> renderer_rgb565_util;

    typedef span_rgb565<solid_rgba8> span_rgb565_solid;
    typedef renderer_u8<span_rgb565_solid> renderer_rgb565_solid;

    template<class GradientF> class span_rgb565_gradient : 
    public span_rgb565<gradient_rgba8<GradientF> > {};

    template<class GradientF> class renderer_rgb565_gradient :
    public renderer_u8<span_rgb565_gradient<GradientF> > 
    {
    public:
        renderer_rgb565_gradient(rendering_buffer& rbuf) : 
           renderer_u8<span_rgb565_gradient<GradientF> >(rbuf) {}
    };
    
    typedef span_rgb565<gouraud_rgba8> span_rgb565_gouraud;
    typedef renderer_u8<span_rgb565_gouraud> renderer_rgb565_gouraud;
}

#endif
