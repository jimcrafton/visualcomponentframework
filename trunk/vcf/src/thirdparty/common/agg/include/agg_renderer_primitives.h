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
// class renderer_primitives
//
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_PRIMITIVES_INCLUDED
#define AGG_RENDERER_PRIMITIVES_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_renderer_base.h"
#include "thirdparty/common/agg/include/agg_dda_line.h"
#include "thirdparty/common/agg/include/agg_ellipse_bresenham.h"

namespace agg
{
    //------------------------------------------------------------------------
    template<class PixelRenderer> 
    class renderer_primitives : public renderer_base<PixelRenderer>
    {
    public:
        typedef renderer_base<PixelRenderer> base_type;

        //--------------------------------------------------------------------
        renderer_primitives(rendering_buffer& rbuf) :
            base_type(rbuf),
            m_fill_color(),
            m_line_color(),
            m_curr_x(0),
            m_curr_y(0)
        {
        }

        //--------------------------------------------------------------------
        static int coord(double c) 
        { 
            return int(c * line_bresenham_interpolator::subpixel_size); 
        }

        //--------------------------------------------------------------------
        void fill_color(const color_type& c) { m_fill_color = c; }
        void line_color(const color_type& c) { m_line_color = c; }
        const color_type& fill_color() const { return m_fill_color; }
        const color_type& line_color() const { return m_line_color; }

        //--------------------------------------------------------------------
        void rectangle(int x1, int y1, int x2, int y2)
        {
            hline(x1,   y1,   x2-1, m_line_color);
            vline(x2,   y1,   y2-1, m_line_color);
            hline(x1+1, y2,   x2,   m_line_color);
            vline(x1,   y1+1, y2,   m_line_color);
        }

        //--------------------------------------------------------------------
        void solid_rectangle(int x1, int y1, int x2, int y2)
        {
            bar(x1, y1, x2, y2, m_fill_color);
        }

        //--------------------------------------------------------------------
        void outlined_rectangle(int x1, int y1, int x2, int y2) 
        {
            rectangle(x1, y1, x2, y2);
            bar(x1+1, y1+1, x2-1, y2-1, m_fill_color);
        }

        //--------------------------------------------------------------------
        void ellipse(int x, int y, int rx, int ry)
        {
            ellipse_bresenham_interpolator ei(rx, ry);
            int dx = 0;
            int dy = -ry;
            do
            {
                dx += ei.dx();
                dy += ei.dy();
                pixel(x + dx, y + dy, m_line_color);
                pixel(x + dx, y - dy, m_line_color);
                pixel(x - dx, y - dy, m_line_color);
                pixel(x - dx, y + dy, m_line_color);
                ++ei;
            }
            while(dy < 0);
        }

        //--------------------------------------------------------------------
        void solid_ellipse(int x, int y, int rx, int ry)
        {
            ellipse_bresenham_interpolator ei(rx, ry);
            int dx = 0;
            int dy = -ry;
            int dy0 = dy;
            int dx0 = dx;

            do
            {
                dx += ei.dx();
                dy += ei.dy();

                if(dy != dy0)
                {
                    hline(x-dx0, y+dy0, x+dx0, m_fill_color);
                    hline(x-dx0, y-dy0, x+dx0, m_fill_color);
                }
                dx0 = dx;
                dy0 = dy;
                ++ei;
            }
            while(dy < 0);
            hline(x-dx0, y+dy0, x+dx0, m_fill_color);
        }

        //--------------------------------------------------------------------
        void outlined_ellipse(int x, int y, int rx, int ry)
        {
            ellipse_bresenham_interpolator ei(rx, ry);
            int dx = 0;
            int dy = -ry;

            do
            {
                dx += ei.dx();
                dy += ei.dy();

                pixel(x + dx, y + dy, m_line_color);
                pixel(x + dx, y - dy, m_line_color);
                pixel(x - dx, y - dy, m_line_color);
                pixel(x - dx, y + dy, m_line_color);

                if(ei.dy() && dx)
                {
                   hline(x-dx+1, y+dy, x+dx-1, m_fill_color);
                   hline(x-dx+1, y-dy, x+dx-1, m_fill_color);
                }
                ++ei;
            }
            while(dy < 0);
        }

        //--------------------------------------------------------------------
        void line(int x1, int y1, int x2, int y2, bool last=false)
        {
            line_bresenham_interpolator li(x1, y1, x2, y2);

            unsigned len = li.len();
            if(len == 0)
            {
                if(last)
                {
                    pixel(li.line_lr(x1), li.line_lr(y1), m_line_color);
                }
                return;
            }

            if(last) ++len;

            if(li.is_ver())
            {
                do
                {
                    pixel(li.x2(), li.y1(), m_line_color);
                    li.vstep();
                }
                while(--len);
            }
            else
            {
                do
                {
                    pixel(li.x1(), li.y2(), m_line_color);
                    li.hstep();
                }
                while(--len);
            }
        }

        //--------------------------------------------------------------------
        void move_to(int x, int y)
        {
            m_curr_x = x;
            m_curr_y = y;
        }

        //--------------------------------------------------------------------
        void line_to(int x, int y, bool last=false)
        {
            line(m_curr_x, m_curr_y, x, y, last);
            m_curr_x = x;
            m_curr_y = y;
        }

    protected:
        color_type m_fill_color;
        color_type m_line_color;
        int m_curr_x;
        int m_curr_y;
    };

}

#endif
