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
// class renderer_base
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_BASE_INCLUDED
#define AGG_RENDERER_BASE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"

namespace agg
{

    //------------------------------------------------------------------------
    template<class PixelRenderer> class renderer_base
    {
    public:
        typedef typename PixelRenderer::color_type color_type;

        //--------------------------------------------------------------------
        renderer_base(rendering_buffer& rbuf) :
            m_rbuf(&rbuf)
        {
        }
          
        //--------------------------------------------------------------------
        void clear(const color_type& c)
        {
            unsigned y;
            if(m_rbuf->width())
            {
                for(y = 0; y < m_rbuf->height(); y++)
                {
                    m_ren.hline(m_rbuf->row(y), 
                                0,  
                                m_rbuf->width(), 
                                c);
                }
            }
        }
          
        //--------------------------------------------------------------------
        void pixel(int x, int y, const color_type& c)
        {
            if(m_rbuf->inbox(x, y))
            {
                m_ren.pixel(m_rbuf->row(y), x, c);
            }
        }

        //--------------------------------------------------------------------
        void pixel(int x, int y, const color_type& c, int alpha)
        {
            if(m_rbuf->inbox(x, y))
            {
                m_ren.pixel(m_rbuf->row(y), x, c, alpha);
            }
        }

        //--------------------------------------------------------------------
        color_type pixel(int x, int y)
        {
            return m_rbuf->inbox(x, y) ? 
                   m_ren.pixel(m_rbuf->row(y), x) :
                   color_type(0,0,0,0);
        }

        //--------------------------------------------------------------------
        void hline(int x1, int y, int x2, const color_type& c)
        {
            if(x1 > x2) { int t = x2; x2 = x1; x1 = t; }
            if(x1 > m_rbuf->xmax()) return;
            if(x2 < m_rbuf->xmin()) return;
            if(y  > m_rbuf->ymax()) return;
            if(y  < m_rbuf->ymin()) return;

            if(x1 < m_rbuf->xmin()) x1 = m_rbuf->xmin();
            if(x2 > m_rbuf->xmax()) x2 = m_rbuf->xmax();
            m_ren.hline(m_rbuf->row(y), x1, x2 - x1 + 1, c);
        }

        //--------------------------------------------------------------------
        void vline(int x, int y1, int y2, const color_type& c)
        {
            if(y1 > y2) { int t = y2; y2 = y1; y1 = t; }
            if(x  > m_rbuf->xmax()) return;
            if(x  < m_rbuf->xmin()) return;
            if(y1 > m_rbuf->ymax()) return;
            if(y2 < m_rbuf->ymin()) return;

            if(y1 < m_rbuf->ymin()) y1 = m_rbuf->ymin();
            if(y2 > m_rbuf->ymax()) y2 = m_rbuf->ymax();

            m_ren.vline(m_rbuf->row(y1), 
                        x, 
                        m_rbuf->stride(), 
                        y2 - y1 + 1, 
                        c);
        }
        
        //--------------------------------------------------------------------
        void bar(int x1, int y1, int x2, int y2, const color_type& c)
        {
            rect rc(x1, y1, x2, y2);
            rc.normalize();
            if(rc.clip(m_rbuf->clip_box()))
            {
                int y;
                for(y = rc.y1; y <= rc.y2; y++)
                {
                    m_ren.hline(m_rbuf->row(y),
                                rc.x1,
                                unsigned(rc.x2 - rc.x1 + 1), 
                                c);
                }
            }
        }


        //--------------------------------------------------------------------
        void copy_from(const rendering_buffer& from, 
                       const rect* rc=0, 
                       int x_to=0, 
                       int y_to=0)
        {
            rect tmp_rect(0, 0, from.width(), from.height());
            if(rc == 0)
            {
                rc = &tmp_rect;
            }

            rect rc2(*rc);
            rc2.normalize();
            if(rc2.clip(rect(0, 0, from.width() - 1, from.height() - 1)))
            {
                rect rc3(x_to + rc2.x1 - rc->x1, 
                         y_to + rc2.y1 - rc->y1, 
                         x_to + rc2.x2 - rc->x1, 
                         y_to + rc2.y2 - rc->y1);
                rc3.normalize();

                if(rc3.clip(m_rbuf->clip_box()))
                {
                    while(rc3.y1 <= rc3.y2)
                    {
                        m_ren.copy(m_rbuf->row(rc3.y1),
                                   from.row(rc2.y1),
                                   rc3.x1, rc2.x1,
                                   rc3.x2 - rc3.x1 + 1);
                        ++rc2.y1;
                        ++rc3.y1;
                    }
                }
            }
        }
        
        //--------------------------------------------------------------------
        rendering_buffer& rbuf() { return *m_rbuf; }
        PixelRenderer&    ren()  { return m_ren; }
          
        //--------------------------------------------------------------------
        const rendering_buffer& rbuf() const { return *m_rbuf; }
        const PixelRenderer&    ren()  const { return m_ren;   }

    private:
        rendering_buffer* m_rbuf;
        PixelRenderer     m_ren;
    };


}

#endif
