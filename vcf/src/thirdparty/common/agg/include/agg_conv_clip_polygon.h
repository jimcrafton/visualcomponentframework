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
// Clipped polygon generator
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_CLIP_POLYGON_INCLUDED
#define AGG_CONV_CLIP_POLYGON_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gen_clip_polygon.h"
#include "thirdparty/common/agg/include/agg_conv_generator.h"


namespace agg
{

    //------------------------------------------------------------------------
    template<class VertexSource> 
    struct conv_clip_polygon : public conv_generator<VertexSource, gen_clip_polygon>
    {
        conv_clip_polygon(VertexSource& vs) : 
            conv_generator<VertexSource, gen_clip_polygon>(vs)
        {
        }

        void clip_box(double x1, double y1, double x2, double y2)
        {
            generator().clip_box(x1, y1, x2, y2);
        }

        void x1(double x1_) { generator().x1(x1_); }
        void y1(double y1_) { generator().y1(y1_); }
        void x2(double x2_) { generator().x2(x2_); }
        void y2(double y2_) { generator().y2(y2_); }

        double x1() const { return generator().x1(); }
        double y1() const { return generator().y1(); }
        double x2() const { return generator().x2(); }
        double y2() const { return generator().y2(); }

    };



}

#endif
