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

#ifndef AGG_SPAN_SOLID_GRAY8_INCLUDED
#define AGG_SPAN_SOLID_GRAY8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_gray8.h"

namespace agg
{
    class span_solid_gray8
    {
    public:
        typedef gray8 attr_type;

        //--------------------------------------------------------------------
        static void prepare(const gray8&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}

        class interpolator
        {
        public:
            interpolator(const gray8& gray) : m_gray(gray) {}

            static void calculate() {}
            static void step() {}

            int v() const { return m_gray.v; }
            int a() const { return m_gray.a; }

        private:
            gray8 m_gray;
        };

        static interpolator begin(int, int, unsigned, const attr_type& attr)
        {
            return interpolator(attr);
        }
    };


/*
    class span_solid_gray8
    {
    public:
        typedef gray8 attr_type;

        //--------------------------------------------------------------------
               void prepare(const attr_type& gray) { m_gray = gray; }
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}

        static void calculate() {}
               void operator++ () {}

        int v() const { return m_gray.v; }
        int a() const { return m_gray.a; }

    private:
        attr_type m_gray;
    };
*/
}

#endif
