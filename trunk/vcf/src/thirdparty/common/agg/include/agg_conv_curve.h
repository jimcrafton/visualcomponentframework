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
// classes conv_curve
//
//----------------------------------------------------------------------------

#ifndef AGG_CONV_CURVE_INCLUDED
#define AGG_CONV_CURVE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_curves.h"

namespace agg
{


    //------------------------------------------------------------------------
    // Curve converter class. Any path storage can have Bezier curves defined 
    // by their control points. There're two types of curves supported: curve3 
    // and curve4. Curve3 is a conic Bezier curve with 2 endpoints and 1 control
    // point. Curve4 has 2 control points (4 points in total) and can be used
    // to interpolate more complicated curves. Curve4, unlike curve3 can be used 
    // to approximate arcs, both curcular and elliptical. Curves are approximated 
    // with straight lines and one of the approaches is just to store the whole 
    // sequence of vertices that approximate our curve. It takes additional 
    // memory, and at the same time the consecutive vertices can be calculated 
    // on demand. 
    //
    // Initially, path storages are not suppose to keep all the vertices of the
    // curves (although, nothig prevents us from doing so). Instead, path_storage
    // keeps only vertices, needed to calculate a curve on demand. Those vertices
    // are marked with special commands. So, if the path_storage contains curves 
    // (which are not real curves yet), and we render this storage directly, 
    // all we will see is only 2 or 3 straight line segments (for curve3 and 
    // curve4 respectively). If we need to see real curves drawn we need to 
    // include this class into the conversion pipeline. 
    //
    // Class conv_curve recognizes commands path_cmd_curve3 and path_cmd_curve4 
    // and converts these vertices into a move_to() sequence. Template version 
    // of the class can use custom curve interpolators, by default classes curve3 
    // and curve4 are used. All you need implement your own interpolators is 
    // to support methods init(), rewind() and vertex().
    //------------------------------------------------------------------------
    template<class VertexSource> class conv_curve
    {
    public:
        conv_curve(VertexSource& source) :
          m_source(&source), m_last_x(0.0), m_last_y(0.0) { }

        void approximation_scale(double s) 
        { 
            m_curve3.approximation_scale(s); 
            m_curve4.approximation_scale(s); 
        }

        double approximation_scale() const 
        { 
            return m_curve3.approximation_scale();  
        }

        void     rewind(unsigned id); 
        unsigned vertex(double* x, double* y);

        typedef conv_curve<VertexSource> source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }

    private:
        VertexSource* m_source;
        double        m_last_x;
        double        m_last_y;
        unsigned      m_path_flags;
        curve3        m_curve3;
        curve4        m_curve4;
    };



    //------------------------------------------------------------------------
    template<class VertexSource>
    void conv_curve<VertexSource>::rewind(unsigned id)
    {
        m_source->rewind(id);
        m_last_x = 0.0;
        m_last_y = 0.0;
        m_path_flags = 0;
        m_curve3.reset();
        m_curve4.reset();
    }



    //------------------------------------------------------------------------
    template<class VertexSource>
    unsigned conv_curve<VertexSource>::vertex(double* x, double* y)
    {
        if(!is_stop(m_curve3.vertex(x, y)))
        {
            m_last_x = *x;
            m_last_y = *y;
            return path_cmd_line_to | m_path_flags;
        }

        if(!is_stop(m_curve4.vertex(x, y)))
        {
            m_last_x = *x;
            m_last_y = *y;
            return path_cmd_line_to | m_path_flags;
        }

        double ct2_x;
        double ct2_y;
        double end_x;
        double end_y;

        unsigned cmd = m_source->vertex(x, y);
        m_path_flags |= path_flags(cmd);
        switch(path_cmd(cmd))
        {
        case path_cmd_move_to:
            m_path_flags = 0;
        case path_cmd_line_to:
            m_last_x = *x;
            m_last_y = *y;
        default:
            break; 
        
        case path_cmd_curve3:
            m_path_flags |= path_flags(m_source->vertex(&end_x, &end_y));

            m_curve3.init(m_last_x, m_last_y, 
                          *x,       *y, 
                          end_x,     end_y);

            m_curve3.vertex(x, y);    // First call returns path_cmd_move_to
            m_curve3.vertex(x, y);    // This is the first vertex of the curve
            cmd = path_cmd_line_to | m_path_flags;
            break;

        case path_cmd_curve4:
            m_path_flags |= path_flags(m_source->vertex(&ct2_x, &ct2_y));
            m_path_flags |= path_flags(m_source->vertex(&end_x, &end_y));

            m_curve4.init(m_last_x, m_last_y, 
                          *x,       *y, 
                          ct2_x,    ct2_y, 
                          end_x,    end_y);

            m_curve4.vertex(x, y);    // First call returns path_cmd_move_to
            m_curve4.vertex(x, y);    // This is the first vertex of the curve
            cmd = path_cmd_line_to | m_path_flags;
            break;
        }
        return cmd;
    }



}



#endif
