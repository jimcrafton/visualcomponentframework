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
// class renderer_scanline
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_SCANLINE_INCLUDED
#define AGG_RENDERER_SCANLINE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_renderer_base.h"

namespace agg
{

    //========================================================================
    template<class SpanInterpolator, class PixelRenderer> 
    class renderer_scanline : public renderer_base<PixelRenderer>
    {
    public:
        typedef renderer_base<PixelRenderer> base_type;
        typedef typename SpanInterpolator::attr_type attr_type;

        //--------------------------------------------------------------------
        renderer_scanline(rendering_buffer& rbuf) :
            base_type(rbuf)
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
        template<class Scanline> void render(const Scanline& sl)
        {
            rect cb = rbuf().clip_box();
            int y = sl.y();

            m_span.prepare_y(y);

            if(y < cb.y1 || y > cb.y2)
            {
                return;
            }

            unsigned num_spans = sl.num_spans();
            int base_x = sl.base_x();
            int8u* row = rbuf().row(y);
            typename Scanline::const_iterator span(sl);

            do
            {
                int x = span.next() + base_x;
                const typename Scanline::cover_type* covers = span.covers();
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
                typename SpanInterpolator::interpolator si = m_span.begin(x, y, num_pix, m_attr);
                ren().span(row, x, y, unsigned(num_pix), covers, si);
            }
            while(--num_spans);
        }
        
    private:
        attr_type         m_attr;
        SpanInterpolator  m_span;
    };




    //========================================================================
    template<class SpanInterpolator, class PixelRenderer> 
    class renderer_scanline_bin : public renderer_base<PixelRenderer>
    {
    public:
        typedef renderer_base<PixelRenderer> base_type;
        typedef typename SpanInterpolator::attr_type attr_type;

        //--------------------------------------------------------------------
        renderer_scanline_bin(rendering_buffer& rbuf) :
            base_type(rbuf)
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
        template<class Scanline> void render(const Scanline& sl)
        {
            rect cb = rbuf().clip_box();
            int y = sl.y();

            m_span.prepare_y(y);

            if(y < cb.y1 || y > cb.y2)
            {
                return;
            }

            unsigned num_spans = sl.num_spans();
            int8u* row = rbuf().row(y);
            const typename Scanline::span* cur_span = sl.spans();

            do
            {
                int x = cur_span->x;
                int num_pix = cur_span->len;

                m_span.prepare_x(x, num_pix);

                if(x < cb.x1)
                {
                    num_pix -= cb.x1 - x;
                    if(num_pix <= 0) continue;
                    x = cb.x1;
                }
                if(x + num_pix > cb.x2)
                {
                    num_pix -= x + num_pix - cb.x2 - 1;
                    if(num_pix <= 0) continue;
                }
                typename SpanInterpolator::interpolator si = m_span.begin(x, y, num_pix, m_attr);
                ren().span(row, x, y, unsigned(num_pix), si);
                ++cur_span;
            }
            while(--num_spans);
        }
        
    private:
        attr_type         m_attr;
        SpanInterpolator  m_span;
    };





    //========================================================================
    template<class PixelRenderer> 
    class renderer_scanline_bin_solid : public renderer_base<PixelRenderer>
    {
    public:
        typedef renderer_base<PixelRenderer> base_type;
        typedef typename PixelRenderer::color_type attr_type;

        //--------------------------------------------------------------------
        renderer_scanline_bin_solid(rendering_buffer& rbuf) :
            base_type(rbuf)
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
        void prepare() {}
        
        //--------------------------------------------------------------------
        template<class Scanline> void render(const Scanline& sl)
        {
            unsigned num_spans = sl.num_spans();
            int y = sl.y();
            const typename Scanline::span* cur_span = sl.spans();

            do
            {
                hline(cur_span->x, y, cur_span->x + cur_span->len - 1, m_attr);
                ++cur_span;
            }
            while(--num_spans);
        }
        
    private:
        attr_type m_attr;
    };

}

#endif
