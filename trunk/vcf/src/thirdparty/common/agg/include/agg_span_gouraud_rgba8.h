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

#ifndef AGG_SPAN_GOURAUD_RGBA8_INCLUDED
#define AGG_SPAN_GOURAUD_RGBA8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"
#include "thirdparty/common/agg/include/agg_gouraud_attr.h"
#include "thirdparty/common/agg/include/agg_dda_line.h"
#include "thirdparty/common/agg/include/agg_math.h"

namespace agg
{

    //========================================================================
    class span_gouraud_rgba8
    {
    public:
        typedef gouraud_attr<rgba8> attr_type;
        typedef attr_type::gouraud_coord coord_type;

        class interpolator
        {
        public:
            interpolator(const rgba8& c1, 
                         const rgba8& c2, 
                         unsigned count) :
                m_r(c1.r, c2.r, count),
                m_g(c1.g, c2.g, count),
                m_b(c1.b, c2.b, count),
                m_a(c1.a, c2.a, count)
            {
            }

            static void calculate() {}

            void step()
            {
                ++m_r; ++m_g; ++m_b; ++m_a;
            }

            int r() const { return m_r.y(); }
            int g() const { return m_g.y(); }
            int b() const { return m_b.y(); }
            int a() const { return m_a.y(); }

        private:
            dda_line_interpolator<16> m_r;
            dda_line_interpolator<16> m_g;
            dda_line_interpolator<16> m_b;
            dda_line_interpolator<16> m_a;
        };

        struct rgba_calc
        {
            void init(const coord_type& c1, const coord_type& c2)
            {
                m_x1 = c1.x;
                m_y1 = c1.y;
                m_dx = 1.0 / (c2.x - c1.x);
                m_dy = 1.0 / (c2.y - c1.y);
                m_r1 = c1.color.r;
                m_g1 = c1.color.g;
                m_b1 = c1.color.b;
                m_a1 = c1.color.a;
                m_dr = c2.color.r - m_r1;
                m_dg = c2.color.g - m_g1;
                m_db = c2.color.b - m_b1;
                m_da = c2.color.a - m_a1;
            }

            rgba8 calc(int y) const
            {
                double k = 0.0;
                if(y > m_y1) k = (y - m_y1) * m_dy;
                rgba8 rgba;
                rgba.r = m_r1 + int(m_dr * k);
                rgba.g = m_g1 + int(m_dg * k);
                rgba.b = m_b1 + int(m_db * k);
                rgba.a = m_a1 + int(m_da * k);
                return rgba;
            }

            double m_x1;
            double m_y1;
            double m_dx;
            double m_dy;
            int    m_r1;
            int    m_g1;
            int    m_b1;
            int    m_a1;
            int    m_dr;
            int    m_dg;
            int    m_db;
            int    m_da;
        };


    protected:
        bool       m_swap;
        int        m_y2;
        int        m_span_x;
        int        m_span_count;
        rgba_calc  m_rgba1;
        rgba_calc  m_rgba2;
        rgba_calc  m_rgba3;

    public:
        void prepare(const attr_type& attr) 
        {
            coord_type coord[3];

            coord[0] = attr.m_coord[0];
            coord[1] = attr.m_coord[1];
            coord[2] = attr.m_coord[2];

            if(attr.m_coord[0].y > attr.m_coord[2].y)
            {
                coord[0] = attr.m_coord[2]; 
                coord[2] = attr.m_coord[0];
            }

            attr_type::gouraud_coord tmp;
            if(coord[0].y > coord[1].y)
            {
                tmp      = coord[1];
                coord[1] = coord[0];
                coord[0] = tmp;
            }

            if(coord[1].y > coord[2].y)
            {
                tmp      = coord[2];
                coord[2] = coord[1];
                coord[1] = tmp;
            }
            
            m_y2 = int(coord[1].y);

            m_swap = calc_point_location(coord[0].x, coord[0].y, 
                                         coord[2].x, coord[2].y,
                                         coord[1].x, coord[1].y) < 0.0;

            m_rgba1.init(coord[0], coord[2]);
            m_rgba2.init(coord[0], coord[1]);
            m_rgba3.init(coord[1], coord[2]);
        }


        void prepare_y(int y) 
        {
        }

        void prepare_x(int x, unsigned count) 
        {
            m_span_x = x;
            m_span_count = count;
        }


        interpolator begin(int x, int y, unsigned, const attr_type&)
        {

            rgba8 c1(m_rgba1.calc(y));
            rgba8 c2;

            if(y < m_y2)
            {
                c2 = m_rgba2.calc(y+1);
            }
            else
            {
                c2 = m_rgba3.calc(y);
            }

            const rgba8* pc1 = &c1;
            const rgba8* pc2 = &c2;
            if(m_swap)
            {
                pc1 = &c2;
                pc2 = &c1;
            }

            interpolator span(*pc1, *pc2, m_span_count);
            while(m_span_x < x)
            {
                ++m_span_x;
                span.step();
            }
            return span;
        }

    };


}

#endif
