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
// Stroke generator
//
//----------------------------------------------------------------------------
#ifndef AGG_GEN_STROKE_INCLUDED
#define AGG_GEN_STROKE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_vertex_sequence.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"

namespace agg
{

    // Minimal angle to calculate round joins 
    const double gen_stroke_theta = 1e-10;

    //------------------------------------------------------------------------
    // TO DO comments
    //
    class gen_stroke
    {
        enum status_e
        {
            initial,
            cap1,
            cap2,
            outline1,
            outline2,
            out_vertices,
            stop
        };

    public:
        enum line_cap_e
        {
            butt_cap,
            square_cap,
            round_cap
        };

        enum line_join_e
        {
            miter_join,
            round_join,
            bevel_join
        };

        struct coord_type
        {
            double x, y;

            coord_type() {}
            coord_type(double x_, double y_) : x(x_), y(y_) {}
        };


        typedef vertex_sequence<vertex_dist, 6> vertex_storage;
        typedef array<coord_type, 6>            coord_storage;

        gen_stroke();

        void line_cap(line_cap_e lc) { m_line_cap = lc; }
        void line_join(line_join_e lj) { m_line_join = lj; }

        line_cap_e line_cap() const { return m_line_cap; }
        line_join_e line_join() const { return m_line_join; }

        void width(double w) { m_width = w * 0.5; }
        void miter_limit(double ml) { m_miter_limit = ml; }
        void miter_limit_theta(double t);
        void approximation_scale(double as) { m_approx_scale = as; }

        double width() const { return m_width * 2.0; }
        double miter_limit() const { return m_miter_limit; }
        double approximation_scale() const { return m_approx_scale; }

        // Vertex Generator Interface
        void remove_all();
        void add_vertex(double x, double y, unsigned cmd);
        void prepare_src();

        // Vertex Source Interface
        void     rewind(unsigned id);
        unsigned vertex(double* x, double* y);

        typedef gen_stroke source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        void calc_join(const vertex_dist& v0, 
                       const vertex_dist& v1, 
                       const vertex_dist& v2,
                       double len1, double len2);

        void calc_miter(const vertex_dist& v0, 
                        const vertex_dist& v1, 
                        const vertex_dist& v2,
                        double dx1, double dy1, 
                        double dx2, double dy2);

        void calc_arc(double x,   double y, 
                      double dx1, double dy1, 
                      double dx2, double dy2);

        void calc_cap(const vertex_dist& v0, 
                      const vertex_dist& v1, 
                      double len);

        vertex_storage m_src_vertices;
        coord_storage  m_out_vertices;
        double         m_width;
        double         m_miter_limit;
        double         m_approx_scale;
        line_cap_e     m_line_cap;
        line_join_e    m_line_join;
        unsigned       m_closed;
        status_e       m_status;
        status_e       m_prev_status;
        unsigned       m_src_vertex;
        unsigned       m_out_vertex;
    };


}

#endif
