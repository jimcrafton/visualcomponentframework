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
#ifndef AGG_GEN_SMOOTH_POLY1_INCLUDED
#define AGG_GEN_SMOOTH_POLY1_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_vertex_sequence.h"


namespace agg
{

    //------------------------------------------------------------------------
    // TO DO comments
    //
    class gen_smooth_poly1
    {
        enum status_e
        {
            initial,
            polygon,
            ctrl_b,
            ctrl_e,
            ctrl1,
            ctrl2,
            stop
        };

    public:
        typedef vertex_sequence<vertex_dist, 6> vertex_storage;

        gen_smooth_poly1();

        void   smooth_value(double v) { m_smooth_value = v * 0.5; }
        double smooth_value() const { return m_smooth_value * 2.0; }

        void remove_all();
        void add_vertex(double x, double y, unsigned cmd);
        void prepare_src();

        // Vertex Source Interface
        void     rewind(unsigned id);
        unsigned vertex(double* x, double* y);

    private:
        void calculate(const vertex_dist& v0, 
                       const vertex_dist& v1, 
                       const vertex_dist& v2,
                       const vertex_dist& v3);

        vertex_storage m_src_vertices;
        double         m_smooth_value;
        unsigned       m_closed;
        status_e       m_status;
        unsigned       m_src_vertex;
        double         m_ctrl1_x;
        double         m_ctrl1_y;
        double         m_ctrl2_x;
        double         m_ctrl2_y;
    };

}


#endif

