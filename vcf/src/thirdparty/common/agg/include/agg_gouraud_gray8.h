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
// Base class for gradient renderers
//
//----------------------------------------------------------------------------

#ifndef AGG_GOURAUD_GRAY8_INCLUDED
#define AGG_GOURAUD_GRAY8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gray8.h"
#include "thirdparty/common/agg/include/agg_gouraud_attr.h"
#include "thirdparty/common/agg/include/agg_dda_line.h"
#include "thirdparty/common/agg/include/agg_math.h"

namespace agg
{

    //========================================================================
    class gouraud_gray8
    {
    public:
        typedef gouraud_attr<gray8> attr_type;
        typedef attr_type::gouraud_coord coord_type;

        class interpolator
        {
        public:
            interpolator(const gray8& c1, 
                         const gray8& c2, 
                         unsigned count) :
                m_v(c1.v, c2.v, count),
                m_a(c1.a, c2.a, count)
            {
            }

            static void calculate() {}

            void step()
            {
                ++m_v; ++m_a;
            }

            int v() const { return m_v.y(); }
            int a() const { return m_a.y(); }

        private:
            dda_line_interpolator<16> m_v;
            dda_line_interpolator<16> m_a;
        };

        struct gray_calc
        {
            void init(const coord_type& c1, const coord_type& c2)
            {
                m_x1 = c1.x;
                m_y1 = c1.y;
                m_dx = 1.0 / (c2.x - c1.x);
                m_dy = 1.0 / (c2.y - c1.y);
                m_v1 = c1.color.v;
                m_a1 = c1.color.a;
                m_dv = c2.color.v - m_v1;
                m_da = c2.color.a - m_a1;
            }

            gray8 calc(int y) const
            {
                double k = 0.0;
                if(y > m_y1) k = (y - m_y1) * m_dy;
                gray8 gray;
                gray.v = m_v1 + int(m_dv * k);
                gray.a = m_a1 + int(m_da * k);
                return gray;
            }

            double m_x1;
            double m_y1;
            double m_dx;
            double m_dy;
            int    m_v1;
            int    m_a1;
            int    m_dv;
            int    m_da;
        };


    protected:
        bool       m_swap;
        int        m_y2;
        int        m_span_x;
        int        m_span_count;
        gray_calc  m_gray1;
        gray_calc  m_gray2;
        gray_calc  m_gray3;

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

            m_gray1.init(coord[0], coord[2]);
            m_gray2.init(coord[0], coord[1]);
            m_gray3.init(coord[1], coord[2]);
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

            gray8 c1(m_gray1.calc(y));
            gray8 c2;

            if(y < m_y2)
            {
                c2 = m_gray2.calc(y+1);
            }
            else
            {
                c2 = m_gray3.calc(y);
            }

            const gray8* pc1 = &c1;
            const gray8* pc2 = &c2;
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
