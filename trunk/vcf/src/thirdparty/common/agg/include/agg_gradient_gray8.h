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

#ifndef AGG_GRADIENT_GRAY8_INCLUDED
#define AGG_GRADIENT_GRAY8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gray8.h"
#include "thirdparty/common/agg/include/agg_gradient_attr.h"

namespace agg
{

    //========================================================================
    template<class GradientF> class gradient_gray8
    {
    public:
        typedef gradient_attr<gray8, GradientF, unsigned char, 8> attr_type;

        class interpolator
        {
        public:
            interpolator(int x, int y, unsigned count, const attr_type& attr) :
                m_dd(attr.m_d2 - attr.m_d1),
                m_d1(attr.m_d1),
                m_span(gradient_span(x, y, count, *attr.m_mtx)),
                m_gradient_function(attr.m_gradient_function),
                m_profile(attr.m_profile),
                m_gradient_array(attr.m_gradient_array)
            {
            }
        
            void calculate()
            {
                int d = m_gradient_function->calculate(m_span.x(), m_span.y(), m_dd);
                d = ((d - m_d1) << attr_type::array_shift) / m_dd;
                if(d < 0) d = 0;
                if(d > attr_type::array_mask) d = attr_type::array_mask;
                m_gray = m_gradient_array + m_profile[d];
            }

            int v() const { return m_gray->v; }
            int a() const { return m_gray->a; }

            void step()
            {
                ++m_span;
            }

        private:
            int                   m_dd;
            int                   m_d1;
            gradient_interpolator m_span;
            const GradientF*      m_gradient_function;
            const unsigned char*  m_profile;
            const gray8*          m_gradient_array;
            const gray8*          m_gray;
        };

    public:
        static void prepare(const attr_type&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}

        interpolator begin(int x, int y, unsigned count, const attr_type& attr)
        {
            return interpolator(x, y, count, attr);
        }
    };


}

#endif
