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
// class renderer
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_U8_INCLUDED
#define AGG_RENDERER_U8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"
#include "thirdparty/common/agg/include/agg_scanline_u8.h"

namespace agg
{



    //------------------------------------------------------------------------
    template<class Span> class renderer_u8
    {
    public:
        typedef typename Span::attr_type attr_type;

        //--------------------------------------------------------------------
        renderer_u8(rendering_buffer& rbuf) :
            m_rbuf(&rbuf)
        {
        }
        
        //--------------------------------------------------------------------
        void attribute(const attr_type& attr) 
        { 
            m_attr = attr;
        }
        
        //--------------------------------------------------------------------
        const attr_type& attribute() const 
        { 
            return m_attr;
        }

        //--------------------------------------------------------------------
        void prepare()
        {
            m_span.prepare(m_attr);
        }
        
        //--------------------------------------------------------------------
        void pixel(int x, int y, const attr_type& attr, int alpha)
        {
            if(m_rbuf->inbox(x, y)) m_span.pixel(m_rbuf->row(y), x, attr, alpha);
        }

        //--------------------------------------------------------------------
        void render(const scanline_u8& sl)
        {
            rect cb = m_rbuf->clip_box();
            int y = sl.y();

            m_span.prepare_y(y);

            if(y < cb.y1 || y > cb.y2)
            {
                return;
            }

            unsigned num_spans = sl.num_spans();
            int base_x = sl.base_x();
            unsigned char* row = m_rbuf->row(y);
            scanline_u8::const_iterator span(sl);

            do
            {
                int x = span.next() + base_x;
                const int8u* covers = span.covers();
                int num_pix = span.num_pix();

                m_span.prepare_x(x, num_pix);

                if(x < cb.x1)
                {
                    num_pix -= cb.x1 - x;
                    if(num_pix <= 0) continue;
                    covers += cb.x1 - x;
                    x = cb.x1;
                }
                if(x + num_pix > cb.x2)
                {
                    num_pix -= x + num_pix - cb.x2 - 1;
                    if(num_pix <= 0) continue;
                }

                m_span.render(row, x, y, num_pix, covers, m_attr);
            }
            while(--num_spans);
        }
        

        //--------------------------------------------------------------------
        rendering_buffer& rbuf() { return *m_rbuf; }
          
    private:
        rendering_buffer* m_rbuf;
        attr_type         m_attr;
        Span              m_span;
    };


}


#endif

