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
// scanline_u8 class
//
//----------------------------------------------------------------------------
#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_scanline_u8.h"



namespace agg
{

    //------------------------------------------------------------------------
    scanline_u8::~scanline_u8()
    {
        delete [] m_counts;
        delete [] m_start_ptrs;
        delete [] m_covers;
    }


    //------------------------------------------------------------------------
    scanline_u8::scanline_u8()
        : m_min_x(0),
          m_max_len(0),
          m_dx(0),
          m_dy(0),
          m_last_x(0x7FFF),
          m_last_y(0x7FFF),
          m_covers(0),
          m_start_ptrs(0),
          m_counts(0),
          m_num_spans(0),
          m_cur_start_ptr(0),
          m_cur_count(0)
    {
    }


    //------------------------------------------------------------------------
    void scanline_u8::reset(int min_x, int max_x, int dx, int dy)
    {
        unsigned max_len = max_x - min_x + 2;
        if(max_len > m_max_len)
        {
            delete [] m_counts;
            delete [] m_start_ptrs;
            delete [] m_covers;
            m_covers     = new unsigned char  [max_len];
            m_start_ptrs = new unsigned char* [max_len];
            m_counts     = new int16u[max_len];
            m_max_len    = max_len;
        }
        m_dx            = dx;
        m_dy            = dy;
        m_last_x        = 0x7FFF;
        m_last_y        = 0x7FFF;
        m_min_x         = min_x;
        m_cur_count     = m_counts;
        m_cur_start_ptr = m_start_ptrs;
        m_num_spans     = 0;
    }


    //------------------------------------------------------------------------
    void scanline_u8::add_span(int x, int y, unsigned num, unsigned cover)
    {
        x -= m_min_x;

        memset(m_covers + x, cover, num);
        if(x == m_last_x+1)
        {
            (*m_cur_count) += (int16u)num;
        }
        else
        {
            *++m_cur_count = (int16u)num;
            *++m_cur_start_ptr = m_covers + x;
            m_num_spans++;
        }
        m_last_x = x + num - 1;
        m_last_y = y;
    }


}

