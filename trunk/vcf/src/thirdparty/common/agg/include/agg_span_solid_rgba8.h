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
// span_solid_rgba8
//
//----------------------------------------------------------------------------

#ifndef AGG_SPAN_SOLID_RGBA8_INCLUDED
#define AGG_SPAN_SOLID_RGBA8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{
    class span_solid_rgba8
    {
    public:
        typedef rgba8 attr_type;

        //--------------------------------------------------------------------
        static void prepare(const rgba8&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}

        class interpolator
        {
        public:
            interpolator(const rgba8& rgba) : m_rgba(rgba) {}

            static void calculate() {}
            static void step() {}

            int r() const { return m_rgba.r; }
            int g() const { return m_rgba.g; }
            int b() const { return m_rgba.b; }
            int a() const { return m_rgba.a; }

        private:
            rgba8 m_rgba;
        };

        static interpolator begin(int, int, unsigned, const attr_type& attr)
        {
            return interpolator(attr);
        }
    };

}

#endif
