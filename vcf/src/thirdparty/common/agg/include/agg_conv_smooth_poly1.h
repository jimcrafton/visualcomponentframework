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
// Smooth polygon generator
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_SMOOTH_POLY1_INCLUDED
#define AGG_CONV_SMOOTH_POLY1_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gen_smooth_poly1.h"
#include "thirdparty/common/agg/include/agg_conv_generator.h"
#include "thirdparty/common/agg/include/agg_conv_curve.h"


namespace agg
{

    //------------------------------------------------------------------------
    template<class VertexSource> 
    struct conv_smooth_poly1 : public conv_generator<VertexSource, gen_smooth_poly1>
    {
        conv_smooth_poly1(VertexSource& vs) : 
            conv_generator<VertexSource, gen_smooth_poly1>(vs)
        {
        }

        void   smooth_value(double v) { generator().smooth_value(v); }
        double smooth_value() const { return generator().smooth_value(); }
    };



    //------------------------------------------------------------------------
    template<class VertexSource> 
    struct conv_smooth_poly1_curve : 
    public conv_curve<conv_smooth_poly1<VertexSource> >
    {
        conv_smooth_poly1_curve(VertexSource& vs) :
            conv_curve<conv_smooth_poly1<VertexSource> >(m_smooth),
            m_smooth(vs)
        {
        }

        void   smooth_value(double v) { m_smooth.generator().smooth_value(v); }
        double smooth_value() const { return m_smooth.generator().smooth_value(); }

    private:
        conv_smooth_poly1<VertexSource> m_smooth;
    };

}


#endif

