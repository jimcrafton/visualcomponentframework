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
// class affine_span
//
//----------------------------------------------------------------------------

#ifndef AGG_AFFINE_SPAN_INCLUDED
#define AGG_AFFINE_SPAN_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_affine_matrix.h"
#include "thirdparty/common/agg/include/agg_dda_line.h"

namespace agg
{


    //========================================================================
    template<unsigned SubpixelShift> class affine_span
    {
    public:
        enum
        {
            subpixel_shift = SubpixelShift,
            subpixel_size  = 1 << subpixel_shift
        };

        //====================================================================
        class interpolator
        {
        public:
            //----------------------------------------------------------------
            interpolator(const affine_span& span) :
                m_li_x(span.m_fg_x1, span.m_fg_x2, span.m_count), 
                m_li_y(span.m_fg_y1, span.m_fg_y2, span.m_count)
            {
            }
            
            //----------------------------------------------------------------
            void operator++()
            {
                ++m_li_x;
                ++m_li_y;
            }

            //----------------------------------------------------------------
            int x() const { return m_li_x.y(); }
            int y() const { return m_li_y.y(); }

        private:
            dda2_line_interpolator m_li_x;
            dda2_line_interpolator m_li_y;
        };

        friend class interpolator;

        //--------------------------------------------------------------------
        affine_span(int x, int y, 
                    unsigned count, 
                    const affine_matrix& amtx) :
            m_count(count)
        {
            double dbl_x;
            double dbl_y;

            dbl_x = x;
            dbl_y = y;
            amtx.transform(&dbl_x, &dbl_y);
            m_fg_x1 = int(dbl_x * subpixel_size);
            m_fg_y1 = int(dbl_y * subpixel_size);

            dbl_x = x + m_count;
            dbl_y = y;
            amtx.transform(&dbl_x, &dbl_y);
            m_fg_x2 = int(dbl_x * subpixel_size);
            m_fg_y2 = int(dbl_y * subpixel_size);
        }

    private:
        unsigned m_count;
        int      m_fg_x1;
        int      m_fg_y1;
        int      m_fg_x2;
        int      m_fg_y2;
    };


}



#endif


