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
// Affine transformation operations
//
//----------------------------------------------------------------------------
#include "thirdparty/common/agg/include/agg_affine_matrix.h"



namespace agg
{

    //------------------------------------------------------------------------
    const affine_matrix& affine_matrix::multiply(const affine_matrix& m)
    {
        double t0 = m0 * m.m0 + m1 * m.m2;
        double t2 = m2 * m.m0 + m3 * m.m2;
        double t4 = m4 * m.m0 + m5 * m.m2 + m.m4;
        m1 = m0 * m.m1 + m1 * m.m3;
        m3 = m2 * m.m1 + m3 * m.m3;
        m5 = m4 * m.m1 + m5 * m.m3 + m.m5;
        m0 = t0;
        m2 = t2;
        m4 = t4;
        return *this;
    }


    //------------------------------------------------------------------------
    const affine_matrix& affine_matrix::invert()
    {
        double d  = determinant();

        double t0 =  m3 * d;
               m3 =  m0 * d;
               m1 = -m1 * d;
               m2 = -m2 * d;

        double t4 = -m4 * t0 - m5 * m2;
               m5 = -m4 * m1 - m5 * m3;

        m0 = t0;
        m4 = t4;
        return *this;
    }


   //------------------------------------------------------------------------
    const affine_matrix& affine_matrix::flip_x()
    {
        m0 = -m0;
        m1 = -m1;
        m4 = -m4;
        return *this;
    }

    //------------------------------------------------------------------------
    const affine_matrix& affine_matrix::flip_y()
    {
        m2 = -m2;
        m3 = -m3;
        m5 = -m5;
        return *this;
    }

    //------------------------------------------------------------------------
    const affine_matrix& affine_matrix::reset()
    {
        m0 = m3 = 1.0; 
        m1 = m2 = m4 = m5 = 0.0;
        return *this;
    }


}

