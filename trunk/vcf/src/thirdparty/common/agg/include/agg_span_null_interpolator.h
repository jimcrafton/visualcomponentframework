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

#ifndef AGG_SPAN_NULL_INTERPOLATOR_INCLUDED
#define AGG_SPAN_NULL_INTERPOLATOR_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{
    template<class Attribute> class span_null_interpolator
    {
    public:
        typedef Attribute attr_type;

        //--------------------------------------------------------------------
        static void prepare(const attr_type&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}

        class interpolator
        {
        public:
            interpolator(int x, int y, int count, const attr_type& attr) : 
                m_x(x),
                m_y(y),
                m_count(count),
                m_attr(attr) 
            {}

            static void calculate() {}
            static void step() {}

            int              x()         const { return m_x; }
            int              y()         const { return m_y; }
            unsigned         count()     const { return m_count; }
            const attr_type& attribute() const { return m_attr; }

        private:
            int              m_x;
            int              m_y;
            unsigned         m_count;
            const attr_type& m_attr;
        };

        static interpolator begin(int x, int y, unsigned count, const attr_type& attr)
        {
            return interpolator(x, y, count, attr);
        }
    };

}

#endif
