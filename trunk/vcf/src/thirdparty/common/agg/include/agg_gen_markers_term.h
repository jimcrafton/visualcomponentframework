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
// Terminal markers generator (arrowhead/arrowtail)
//
//----------------------------------------------------------------------------
#ifndef AGG_GEN_MARKERS_TERM_INCLUDED
#define AGG_GEN_MARKERS_TERM_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_vertex_sequence.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"

namespace agg
{
    //------------------------------------------------------------------------
    class gen_markers_term
    {
    public:
        void remove_all();
        void add_vertex(double x, double y, unsigned cmd);
        void prepare_src() {}

        void rewind(unsigned id);
        unsigned vertex(double* x, double* y);

        typedef gen_markers_term source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        struct coord_type
        {
            double x, y;

            coord_type() {}
            coord_type(double x_, double y_) : x(x_), y(y_) {}
        };

        typedef array<coord_type, 6> coord_storage;

        coord_storage m_markers;
        unsigned      m_curr_id;
        unsigned      m_curr_idx;
    };


}

#endif
