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
// Attribute type gradient
//
//----------------------------------------------------------------------------

#ifndef AGG_GRADIENT_ATTR_INCLUDED
#define AGG_GRADIENT_ATTR_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_affine_span.h"

namespace agg
{
    enum 
    {
        gradient_subpixel_shift = 4,
        gradient_subpixel_size  = 1 << gradient_subpixel_shift,
        gradient_subpixel_mask  = gradient_subpixel_size - 1
    };


    typedef affine_span<gradient_subpixel_shift> gradient_span;
    typedef gradient_span::interpolator          gradient_interpolator;


    //========================================================================
    template<class ColorT, 
             class GradientF, 
             class ProfileT=unsigned char, 
             unsigned ArrayShift=8> 
    struct gradient_attr
    {
        enum
        {
            array_shift = ArrayShift,
            array_size  = 1 << array_shift,
            array_mask  = array_size - 1
        };

        //--------------------------------------------------------------------
        gradient_attr() {}
        gradient_attr(const affine_matrix& mtx,
                      const GradientF& gradient_function,
                      const ColorT*    gradient_array,
                      const ProfileT*  profile,
                      double r1, double r2) :
            m_mtx(&mtx),
            m_gradient_function(&gradient_function),
            m_gradient_array(gradient_array),
            m_profile(profile),
            m_d1(int(r1 * gradient_subpixel_size)),
            m_d2(int(r2 * gradient_subpixel_size)) {}
            
        const affine_matrix* m_mtx;
        const GradientF*     m_gradient_function;
        const ColorT*        m_gradient_array;
        const ProfileT*      m_profile;
        int                  m_d1;
        int                  m_d2;
    };



}












#endif

