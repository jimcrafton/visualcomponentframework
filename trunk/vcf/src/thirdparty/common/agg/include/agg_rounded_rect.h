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
// Rounded rectangle vertex generator
//
//----------------------------------------------------------------------------

#ifndef AGG_ROUNDED_RECT_INCLUDED
#define AGG_ROUNDED_RECT_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_arc.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"


namespace agg
{
    //------------------------------------------------------------------------
    class rounded_rect
    {
    public:
        rounded_rect() : m_scale(1.0) {}
        rounded_rect(double x1, double y1, double x2, double y2, double r);

        void rect(double x1, double y1, double x2, double y2);
        void radius(double r);
        void radius(double rx, double ry);
        void radius(double rx_bottom, double ry_bottom, double rx_top, double ry_top);
        void radius(double rx1, double ry1, double rx2, double ry2, 
                    double rx3, double ry3, double rx4, double ry4);
        void normalize_radius();

        void approximation_scale(double s) { m_scale = s; }
        double approximation_scale() const { return m_scale;  }

        void rewind(unsigned);
        unsigned vertex(double* x, double* y);

        typedef rounded_rect source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;
        double m_rx1;
        double m_ry1;
        double m_rx2;
        double m_ry2;
        double m_rx3;
        double m_ry3;
        double m_rx4;
        double m_ry4;
        double m_scale;
        unsigned m_status;
        arc      m_arc;
    };

}

#endif

