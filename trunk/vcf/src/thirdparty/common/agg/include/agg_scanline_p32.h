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
// Class scanline_p32 - a general purpose scanline container.
//
//----------------------------------------------------------------------------
#ifndef AGG_SCANLINE_P32_INCLUDED
#define AGG_SCANLINE_P32_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    //========================================================================
    // 
    // This is a general purpose scaline container which supports the interface 
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
    //  const agg::scanline_p32<8>::span* cur_span = sl.spans();
    //
    //  do
    //  {
    //      **************************************
    //      ...Perform horizontal clipping here...
    //      **************************************
    //
    //      unsigned span_len = cur_span->len;
    //      int x;
    //      if(cur_span->pix_covers)
    //      {
    //          // pixel-by-pixel
    //          const unsigned* covers = cur_span->pix_covers;
    //          x = cur_span->x;
    //          do
    //          {
    //              //... draw one pixel with coordinates (x,y) and 
    //              //    alpha-value "*covers"
    //              ++x;
    //              ++covers;
    //          }
    //          while(--span_len);
    //      }
    //      else
    //      {
    //          //... draw a solid span. The variables:
    //          // cur_span->x             - X
    //          // y,                      - Y
    //          // span_len                - length
    //          // cur_span->span_cover    - alpha-value
    //      }
    //      ++cur_span;
    //  }
    //  while(--num_spans);
    // 
    //------------------------------------------------------------------------
    template<unsigned AA_Shift=8> class scanline_p32
    {
    public:
        enum { aa_shift = AA_Shift };

        typedef int alpha_mask_type;
        typedef unsigned cover_type;

        struct span
        {
            const unsigned* pix_covers;
            unsigned        span_cover;
            int             x;
            unsigned        len;
        };

        ~scanline_p32()
        {
            delete [] m_spans;
            delete [] m_covers;
        }

        scanline_p32() :
            m_max_len(0),
            m_dx(0),
            m_dy(0),
            m_last_x(0x7FFF),
            m_last_y(0x7FFF),
            m_covers(0),
            m_cover_ptr(0),
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
        scanline_p32(const scanline_p32<AA_Shift>&);
        const scanline_p32<AA_Shift> operator = (const scanline_p32<AA_Shift>&);

        unsigned  m_max_len;
        int       m_dx;
        int       m_dy;
        int       m_last_x;
        int       m_last_y;
        unsigned* m_covers;
        unsigned* m_cover_ptr;
        span*     m_spans;
        span*     m_span_ptr;
        unsigned  m_num_spans;
    };


    //------------------------------------------------------------------------
    template<unsigned AA_Shift> 
    void scanline_p32<AA_Shift>::reset(int min_x, int max_x, int dx=0, int dy=0)
    {
        unsigned max_len = max_x - min_x + 3;
        if(max_len > m_max_len)
        {
            delete [] m_spans;
            delete [] m_covers;
            m_covers  = new unsigned [max_len];
            m_spans   = new span [max_len];
            m_max_len = max_len;
        }
        m_dx        = dx;
        m_dy        = dy;
        m_last_x    = 0x7FFF;
        m_last_y    = 0x7FFF;
        m_cover_ptr = m_covers;
        m_span_ptr  = m_spans;
        m_num_spans = 0;
        m_span_ptr->pix_covers = 0;
    }


    //------------------------------------------------------------------------
    template<unsigned AA_Shift> 
    void scanline_p32<AA_Shift>::reset_spans()
    {
        m_last_x    = 0x7FFF;
        m_last_y    = 0x7FFF;
        m_cover_ptr = m_covers;
        m_span_ptr  = m_spans;
        m_num_spans = 0;
        m_span_ptr->pix_covers = 0;
    }


    //------------------------------------------------------------------------
    template<unsigned AA_Shift> 
    void scanline_p32<AA_Shift>::add_cell(int x, int y, unsigned cover)
    {
        x += m_dx;
        *m_cover_ptr = cover;
        if(x == m_last_x+1 && m_span_ptr->pix_covers)
        {
            m_span_ptr->len++;
        }
        else
        {
            ++m_span_ptr;
            ++m_num_spans;
            m_span_ptr->pix_covers = m_cover_ptr;
            m_span_ptr->span_cover = 0;
            m_span_ptr->x = x;
            m_span_ptr->len = 1;
        }
        m_last_x = x;
        m_last_y = y;
        ++m_cover_ptr;
    }


    //------------------------------------------------------------------------
    template<unsigned AA_Shift> 
    void scanline_p32<AA_Shift>::add_span(int x, int y, unsigned len, unsigned cover)
    {
        x += m_dx;
        ++m_span_ptr;
        ++m_num_spans;
        m_span_ptr->pix_covers = 0;
        m_span_ptr->span_cover = cover;
        m_span_ptr->x = x;
        m_span_ptr->len = len;
        m_last_x = x + len - 1;
        m_last_y = y;
    }

}


#endif
