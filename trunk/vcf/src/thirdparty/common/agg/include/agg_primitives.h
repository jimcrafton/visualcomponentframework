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
// Basic primitives for fast drawing regular (aliased) figures 
// Supports any 32-bit per pixel buffer.
//
//----------------------------------------------------------------------------

#ifndef AGG_PRIMITIVES_INCLUDED
#define AGG_PRIMITIVES_INCLUDED


#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"
#include "thirdparty/common/agg/include/agg_ellipse_bresenham.h"


namespace agg
{

    template<class Base> class primitives : public Base
    {
    public:
        primitives(rendering_buffer& rbuf) : Base(rbuf) {}

        void line_color(unsigned c) { m_line_color = c; }
        void fill_color(unsigned c) { m_fill_color = c; }

        void pixel(int x, int y)
        {
            Base::pixel(x, y, m_line_color);
        }

        void pixel(int x, int y, unsigned c)
        {
            Base::pixel(x, y, c);
        }

        void rectangle(int x1, int y1, int x2, int y2)
        {
            hor_line(x1,   y1,   x2-1, m_line_color);
            ver_line(x2,   y1,   y2-1, m_line_color);
            hor_line(x1+1, y2,   x2,   m_line_color);
            ver_line(x1,   y1+1, y2,   m_line_color);
        }

        void outlined_rectangle(int x1, int y1, int x2, int y2)
        {
            rectangle(x1, y1, x2, y2);
            solid_rectangle(x1+1, y1+1, x2-1, y2-1, m_fill_color);
        }

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
                    hor_line(x-dx0, y+dy0, x+dx0, m_fill_color);
                    hor_line(x-dx0, y-dy0, x+dx0, m_fill_color);
                }
                dx0 = dx;
                dy0 = dy;
                ++ei;
            }
            while(dy < 0);
            hor_line(x-dx0, y+dy0, x+dx0, m_fill_color);
        }

        void outlined_ellipse(int x, int y, int rx, int ry)
        {
            ellipse_bresenham_interpolator ei(rx, ry);
            int dx = 0;
            int dy = -ry;

            do
            {
                dx += ei.dx();
                dy += ei.dy();

                Base::pixel(x + dx, y + dy, m_line_color);
                Base::pixel(x + dx, y - dy, m_line_color);
                Base::pixel(x - dx, y - dy, m_line_color);
                Base::pixel(x - dx, y + dy, m_line_color);

                if(ei.dy() && dx)
                {
                   hor_line(x-dx+1, y+dy, x+dx-1, m_fill_color);
                   hor_line(x-dx+1, y-dy, x+dx-1, m_fill_color);
                }
                ++ei;
            }
            while(dy < 0);
        }

    protected:
        unsigned m_line_color;
        unsigned m_fill_color;
    };

}


#endif
