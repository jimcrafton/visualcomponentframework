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
// class renderer_util that exposes simple uptility functions: 
//       clear, rectangle, pixel, copy_from
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_UTIL_INCLUDED
#define AGG_RENDERER_UTIL_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"


namespace agg
{

    //------------------------------------------------------------------------
    template<class Util> class renderer_util
    {
    public:
        typedef typename Util::color_type color_type;

        //--------------------------------------------------------------------
        renderer_util(rendering_buffer& rbuf) :
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
                    m_util.render_span(m_rbuf->row(y), 
                                       0,  
                                       m_rbuf->width(), 
                                       c);
                }
            }
        }
          
        //--------------------------------------------------------------------
        void pixel(int x, int y, const color_type& c)
        {
            m_util.pixel(m_rbuf->row(y), x, c);
        }
        
        //--------------------------------------------------------------------
        color_type pixel(int x, int y)
        {
            return m_util.pixel(m_rbuf->row(y), x);
        }
        
        //--------------------------------------------------------------------
        void rectangle(rect rc, const color_type& c)
        {
            rc.normalize();
            if(rc.clip(m_rbuf->clip_box()))
            {
                int y;
                for(y = rc.y1; y <= rc.y2; y++)
                {
                    m_util.render_span(m_rbuf->row(y),
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
                        m_util.copy(m_rbuf->row(rc3.y1),
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
          
    private:
        rendering_buffer* m_rbuf;
        Util              m_util;
    };



}

#endif
