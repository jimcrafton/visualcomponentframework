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
// Class scanline_bin - binary scanline.
//
//----------------------------------------------------------------------------
#ifndef AGG_SCANLINE_BIN_INCLUDED
#define AGG_SCANLINE_BIN_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    //========================================================================
    // 
    // This is binary scaline container which supports the interface 
    // used in the rasterizer::render(). See description of agg_scanline_u8 
    // for details.
    // 
    // Rendering:
    //-------------------------------------------------------------------------
    //  
    //  int y = sl.y();
    //  
    // ************************************
    // ...Perform vertical clipping here...
    // ************************************
    //
    //  unsigned num_spans = sl.num_spans();
    //  const agg::scanline_bin::span* cur_span = sl.spans();
    //
    //  do
    //  {
    //      x = cur_span->x;
    //      len = cur_span->len;
    // 
    //      **************************************
    //      ...Perform horizontal clipping here...
    //      **************************************
    //      
    //      hor_line(x, y, len)
    //      ++cur_span;
    //  }
    //  while(--num_spans);
    // 
    //------------------------------------------------------------------------
    class scanline_bin
    {
    public:
        enum 
        {
            aa_shift = 8
        };
        typedef bool alpha_mask_type;
        typedef bool cover_type;


        struct span
        {
            int      x;
            unsigned len;
        };

        ~scanline_bin()
        {
            delete [] m_spans;
        }

        scanline_bin() :
            m_max_len(0),
            m_dx(0),
            m_dy(0),
            m_last_x(0x7FFF),
            m_last_y(0x7FFF),
            m_spans(0),
            m_span_ptr(0),
            m_num_spans(0)
        {
        }

        void reset(int min_x, int max_x, int dx, int dy);
        void reset_spans();
        void add_cell(int x, int y, unsigned cover);
        void add_span(int x, int y, unsigned len, unsigned cover);
        void alpha_mask() {}

        int is_ready(int y) const
        {
            return m_num_spans && (y ^ m_last_y);
        }

        int         y()         const { return m_last_y + m_dy; }
        unsigned    num_spans() const { return m_num_spans; }
        const span* spans()     const { return m_spans + 1; }

    private:
        scanline_bin(const scanline_bin&);
        const scanline_bin operator = (const scanline_bin&);

        unsigned  m_max_len;
        int       m_dx;
        int       m_dy;
        int       m_last_x;
        int       m_last_y;
        span*     m_spans;
        span*     m_span_ptr;
        unsigned  m_num_spans;
    };


    //------------------------------------------------------------------------
    inline void scanline_bin::reset(int min_x, int max_x, int dx=0, int dy=0)
    {
        unsigned max_len = max_x - min_x + 3;
        if(max_len > m_max_len)
        {
            delete [] m_spans;
            m_spans   = new span [max_len];
            m_max_len = max_len;
        }
        m_dx        = dx;
        m_dy        = dy;
        m_last_x    = 0x7FFF;
        m_last_y    = 0x7FFF;
        m_span_ptr  = m_spans;
        m_num_spans = 0;
    }


    //------------------------------------------------------------------------
    void scanline_bin::reset_spans()
    {
        m_last_x    = 0x7FFF;
        m_last_y    = 0x7FFF;
        m_span_ptr  = m_spans;
        m_num_spans = 0;
    }


    //------------------------------------------------------------------------
    void scanline_bin::add_cell(int x, int y, unsigned)
    {
        x += m_dx;
        if(x == m_last_x+1)
        {
            m_span_ptr->len++;
        }
        else
        {
            ++m_span_ptr;
            ++m_num_spans;
            m_span_ptr->x = x;
            m_span_ptr->len = 1;
        }
        m_last_x = x;
        m_last_y = y;
    }


    //------------------------------------------------------------------------
    void scanline_bin::add_span(int x, int y, unsigned len, unsigned)
    {
        x += m_dx;
        if(x == m_last_x+1)
        {
            m_span_ptr->len += len;
        }
        else
        {
            ++m_span_ptr;
            ++m_num_spans;
            m_span_ptr->x = x;
            m_span_ptr->len = len;
        }
        m_last_x = x + len - 1;
        m_last_y = y;
    }

}


#endif
