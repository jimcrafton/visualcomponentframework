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

#include "thirdparty/common/agg/include/agg_gen_clip_polygon.h"

namespace agg
{

    //------------------------------------------------------------------------
    gen_clip_polygon::gen_clip_polygon() : 
        m_vertex(0)
    {
        m_clip_box[0] = 0.0;
        m_clip_box[1] = 0.0;
        m_clip_box[2] = 1.0;
        m_clip_box[3] = 1.0;
    }


    //------------------------------------------------------------------------
    void gen_clip_polygon::remove_all()
    {
        m_storage.remove_all();
    }


    //------------------------------------------------------------------------
    void gen_clip_polygon::add_vertex(double x, double y, unsigned cmd)
    {
        if(is_move_to(cmd))
        {
            m_storage.modify_last(coord_type(x, y));
        }
        else
        {
            m_storage.add(coord_type(x, y));
        }
    }


    //------------------------------------------------------------------------
    void gen_clip_polygon::rewind(unsigned id)
    {
        m_vertex = 0;
    }

    //------------------------------------------------------------------------
    unsigned gen_clip_polygon::vertex(double* x, double* y)
    {
        if(m_vertex >= m_storage.size()) return path_cmd_stop;
        *x = m_storage[m_vertex].x;
        *y = m_storage[m_vertex].y;
        ++m_vertex;
        return ((m_vertex == 1) ? path_cmd_move_to : path_cmd_line_to) | path_flags_close;
    }



    //------------------------------------------------------------------------
    inline bool x1_test(const double* cb, const double* p) { return p[0] >= cb[0]; }
    inline bool y1_test(const double* cb, const double* p) { return p[1] >= cb[1]; }
    inline bool x2_test(const double* cb, const double* p) { return p[0] <= cb[2]; }
    inline bool y2_test(const double* cb, const double* p) { return p[1] <= cb[3]; }

    //------------------------------------------------------------------------
    inline void x1_clip(const double* cb, const double* p1, const double* p2, double* pout) 
    {
       pout[0] =  cb[0];
       pout[1] = (cb[0] - p1[0]) * (p2[1] - p1[1]) / (p2[0] - p1[0]) + p1[1];
    }

    //------------------------------------------------------------------------
    inline void y1_clip(const double* cb, const double* p1, const double* p2, double* pout) 
    {
       pout[0] = (cb[1] - p1[1]) * (p2[0] - p1[0]) / (p2[1] - p1[1]) + p1[0];
       pout[1] =  cb[1];
    }

    //------------------------------------------------------------------------
    inline void x2_clip(const double* cb, const double* p1, const double* p2, double* pout) 
    {
       pout[0] =  cb[2];
       pout[1] = (cb[2] - p1[0]) * (p2[1] - p1[1]) / (p2[0] - p1[0]) + p1[1];
    }

    //------------------------------------------------------------------------
    inline void y2_clip(const double* cb, const double* p1, const double* p2, double* pout) 
    {
       pout[0] = (cb[3] - p1[1]) * (p2[0] - p1[0]) / (p2[1] - p1[1]) + p1[0];
       pout[1] =  cb[3];
    }


    typedef array<double, 6> coord_array;

    //------------------------------------------------------------------------
    template<class Test, class Clip> 
    bool clip(const double* cb, coord_array& in, coord_array& out, Test tf, Clip cf)
    {
        unsigned i;
        double p[2], s[2], temp[2];

        if(in.size() < 6) return false;

        out.remove_all();
        s[0]=in[in.size() - 2];
        s[1]=in[in.size() - 1];

        for(i = 0; i < in.size(); i += 2) 
        {
            p[0] = in[i];
            p[1] = in[i + 1];

            if(tf(cb, p)) 
            {
                if(tf(cb, s)) 
                {
                    out.add(p[0]);
                    out.add(p[1]);
                } 
                else 
                {
                    cf(cb, s, p, temp);
                    out.add(temp[0]);
                    out.add(temp[1]);
                    out.add(p[0]);
                    out.add(p[1]);
                }
            } 
            else 
            {
                if(tf(cb, s)) 
                {
                    cf(cb, s, p, temp);
                    out.add(temp[0]);
                    out.add(temp[1]);
                }
            }
            s[0] = p[0];
            s[1] = p[1];
        }
        return true;
    }



    //------------------------------------------------------------------------
    void gen_clip_polygon::prepare_src()
    {
        coord_array array1;
        coord_array array2;

        unsigned i;
        for(i = 0; i < m_storage.size(); i++)
        {
            array1.add(m_storage[i].x);
            array1.add(m_storage[i].y);
        }
        m_storage.remove_all();

        bool flag = true;

                 flag = clip(m_clip_box, array1, array2, x1_test, x1_clip);
        if(flag) flag = clip(m_clip_box, array2, array1, x2_test, x2_clip);
        if(flag) flag = clip(m_clip_box, array1, array2, y1_test, y1_clip);
        if(flag) flag = clip(m_clip_box, array2, array1, y2_test, y2_clip);

        if(flag)
        {
            for(i = 0; i < array1.size(); i += 2)
            {
                m_storage.add(coord_type(array1[i], array1[i + 1]));
            }
        }
    }


}

