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
#ifndef AGG_GEN_CLIP_POLYGON_INCLUDED
#define AGG_GEN_CLIP_POLYGON_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_vertex_sequence.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"

namespace agg
{


    //------------------------------------------------------------------------
    class gen_clip_polygon
    {
        struct coord_type
        {
            double x, y;

            coord_type() {}
            coord_type(double x_, double y_) : x(x_), y(y_) {}
        };

        typedef array<coord_type, 6> coord_storage;

    public:
        gen_clip_polygon();

        void clip_box(double x1, double y1, double x2, double y2)
        {
            m_clip_box[0] = x1;
            m_clip_box[1] = y1;
            m_clip_box[2] = x2;
            m_clip_box[3] = y2;
        }

        void x1(double x1_) { m_clip_box[0] = x1_; }
        void y1(double y1_) { m_clip_box[1] = y1_; }
        void x2(double x2_) { m_clip_box[2] = x2_; }
        void y2(double y2_) { m_clip_box[3] = y2_; }

        double x1() const { return m_clip_box[0]; }
        double y1() const { return m_clip_box[1]; }
        double x2() const { return m_clip_box[2]; }
        double y2() const { return m_clip_box[3]; }

        // Vertex Generator Interface
        void remove_all();
        void add_vertex(double x, double y, unsigned cmd);
        void prepare_src();

        // Vertex Source Interface
        void     rewind(unsigned id);
        unsigned vertex(double* x, double* y);

        typedef gen_clip_polygon source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        coord_storage  m_storage;
        unsigned       m_vertex;
        double         m_clip_box[4];
    };


}

#endif

