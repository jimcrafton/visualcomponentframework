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
// conv_marker
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_MARKER_INCLUDED
#define AGG_CONV_MARKER_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_affine_matrix.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"

namespace agg
{
    //------------------------------------------------------------------------
    template<class MarkerLocator, class MarkerShapes>
    class conv_marker
    {
    public:
        conv_marker(MarkerLocator& ml, MarkerShapes& ms);

        affine_matrix& transform() { return m_transform; }
        const affine_matrix& transform() const { return m_transform; }

        void rewind(unsigned id);
        unsigned vertex(double* x, double* y);

        typedef conv_marker<MarkerLocator, MarkerShapes> source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        enum status_e 
        {
            initial,
            markers,
            polygon,
            stop
        };

        MarkerLocator* m_marker_locator;
        MarkerShapes*  m_marker_shapes;
        affine_matrix  m_transform;
        affine_matrix  m_mtx;
        status_e       m_status;
        unsigned       m_marker;
        unsigned       m_num_markers;
    };


    //------------------------------------------------------------------------
    template<class MarkerLocator, class MarkerShapes> 
    conv_marker<MarkerLocator, MarkerShapes>::conv_marker(MarkerLocator& ml, MarkerShapes& ms) :
        m_marker_locator(&ml),
        m_marker_shapes(&ms),
        m_status(initial),
        m_marker(0),
        m_num_markers(1)
    {
    }


    //------------------------------------------------------------------------
    template<class MarkerLocator, class MarkerShapes> 
    void conv_marker<MarkerLocator, MarkerShapes>::rewind(unsigned)
    {
        m_status = initial;
        m_marker = 0;
        m_num_markers = 1;
    }


    //------------------------------------------------------------------------
    template<class MarkerLocator, class MarkerShapes> 
    unsigned conv_marker<MarkerLocator, MarkerShapes>::vertex(double* x, double* y)
    {
        unsigned cmd = path_cmd_move_to;
        double x1, y1, x2, y2;

        while(!is_stop(cmd))
        {
            switch(m_status)
            {
            case initial:
                if(m_num_markers == 0)
                {
                   cmd = path_cmd_stop;
                   break;
                }
                m_marker_locator->rewind(m_marker);
                ++m_marker;
                m_num_markers = 0;
                m_status = markers;

            case markers:
                if(is_stop(m_marker_locator->vertex(&x1, &y1)))
                {
                    m_status = initial;
                    break;
                }
                if(is_stop(m_marker_locator->vertex(&x2, &y2)))
                {
                    m_status = initial;
                    break;
                }
                ++m_num_markers;
                m_mtx = m_transform;
                m_mtx *= rotation_matrix(atan2(y2 - y1, x2 - x1));
                m_mtx *= translation_matrix(x1, y1);
                m_marker_shapes->rewind(m_marker - 1);
                m_status = polygon;

            case polygon:
                cmd = m_marker_shapes->vertex(x, y);
                if(is_stop(cmd))
                {
                    cmd = path_cmd_move_to;
                    m_status = markers;
                    break;
                }
                m_mtx.transform(x, y);
                return cmd;

            case stop:
                cmd = path_cmd_stop;
                break;
            }
        }
        return cmd;
    }

}


#endif

