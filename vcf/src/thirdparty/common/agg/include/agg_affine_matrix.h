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
// Affine transformation classes.
//
//----------------------------------------------------------------------------
#ifndef AGG_AFFINE_MATRIX_INCLUDED
#define AGG_AFFINE_MATRIX_INCLUDED

#include <math.h>
#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    //========================================================================
    //
    // Introduction to Affine Transformations and Matrices
    //
    // Affine transformation are linear transformations in Cartesian coordinates
    // (strictly speaking not only in Cartesian, but for the beginning we will 
    // think so). They are rotation, scaling, translation and skewing.  
    // After any affine transformation a line segment remains a line segment 
    // and it will never become a curve. 
    //
    // There will be no math about matrix calculations, since it has been 
    // described many times. Ask yourself a very simple question:
    // "why do we need to understand and use some matrix stuff instead of just 
    // rotating, scaling and so on". The answers are:
    //
    // 1. Any combination of transformations can be done by only 4 multiplications
    //    and 4 additions in floating point.
    // 
    // 2. One matrix transformation is equivalent to the number of consecutive
    //    discrete transformations, i.e. the matrix "accumulates" all transformations 
    //    in the order of their settings. Suppose we have 4 transformations: 
    //       - rotate by 30 degrees,
    //       - scale X to 2.0, 
    //       - scale Y to 1.5, 
    //       - move to (100, 100). 
    //    The result will depend on the order of these transformations, 
    //    and the advantage of matrix is that the sequence of discret calls:
    //    rotate(30), scaleX(2.0), scaleY(1.5), move(100,100) 
    //    will have exactly the same result as the following matrix transformations:
    //   
    //    matrix m;
    //    m *= rotate_matrix(30); 
    //    m *= scaleX_matrix(2.0);
    //    m *= scaleY_matrix(1.5);
    //    m *= move_matrix(100,100);
    //
    //    m.transform_my_point_at_last(x, y);
    //
    // What is the good of it? In real life we will set-up the matrix only once
    // and then transform many points, let alone the convenience to set any 
    // combination of transformations.
    //
    // So, how to use it? Very easy - literally as it's shown above. Not quite,
    // let us write a correct example:
    //
    // agg::affine_matrix m;
    // m *= agg::rotation_matrix(30.0 * 3.1415926 / 180.0);
    // m *= agg::scaling_matrix(2.0, 1.5);
    // m *= agg::translation_matrix(100.0, 100.0);
    // m.transform(&x, &y);
    //
    // The affine matrix is all you need to perform any linear transformation,
    // but all transformations have origin point (0,0). It means that we need to 
    // use 2 translations if we want to rotate someting around (100,100):
    // 
    // m *= agg::translation_matrix(-100.0, -100.0);         // move to (0,0)
    // m *= agg::rotation_matrix(30.0 * 3.1415926 / 180.0);  // rotate
    // m *= agg::translation_matrix(100.0, 100.0);           // move back to (100,100)
    // 
    class affine_matrix
    {
    public:
        //========================================== Construction
        // Construct a matrix of identity - it does not transform anything
        affine_matrix() :
          m0(1.0), m1(0.0), m2(0.0), m3(1.0), m4(0.0), m5(0.0)
        {}

        // Copy-constructor
        affine_matrix(const affine_matrix& m) :
          m0(m.m0), m1(m.m1), m2(m.m2), m3(m.m3), m4(m.m4), m5(m.m5)
        {}

        // Construct a custom matrix. Usually used in derived classes
        affine_matrix(double v0, double v1, double v2, double v3, double v4, double v5) :
          m0(v0), m1(v1), m2(v2), m3(v3), m4(v4), m5(v5)
        {}

        //========================================== Operations
        // Reset - actually load identity matrix
        const affine_matrix& reset();

        // Multiply matrix to another one
        const affine_matrix& multiply(const affine_matrix& m);

        // Invert matrix. Do not try to invert degenerate matrices, 
        // there's no check for validity. If you set scale to 0 and 
        // then try to invert matrix, expect unpredictable result.
        const affine_matrix& invert();

        // Mirroring around X
        const affine_matrix& flip_x();

        // Mirroring around Y
        const affine_matrix& flip_y();

        //=========================================== Load/Store
        // Store matrix to an array [6] of double
        void store_to(double* m) const
        {
            *m++ = m0; *m++ = m1; *m++ = m2; *m++ = m3; *m++ = m4; *m++ = m5;
        }

        // Load matrix from an array [6] of double
        const affine_matrix& load_from(const double* m)
        {
            m0 = *m++; m1 = *m++; m2 = *m++; m3 = *m++; m4 = *m++;  m5 = *m++;
            return *this;
        }

        //=========================================== Operators
        // Assignment
        const affine_matrix& operator = (const affine_matrix& m)
        {
            m0 = m.m0; m1 = m.m1; m2 = m.m2; m3 = m.m3; m4 = m.m4; m5 = m.m5;
            return *this;
        }

        // Load matrix from an array [6] of double
        const affine_matrix& operator = (const double* m)
        {
            return load_from(m);
        }

        // Multiply current matrix to another one
        const affine_matrix& operator *= (const affine_matrix& m)
        {
            return multiply(m);
        }

        // Calculate and return the inverse matrix
        affine_matrix operator ~ () const
        {
            affine_matrix ret = *this;
            return ret.invert();
        }

        //============================================ Transformations
        // Direct transformation x and y
        void transform(double* x, double* y) const;

        // Get current scale
        double scale() const;

        // Inverse transformation x and y. Works slower than direct transformation,
        // so if the performance is critical it's better to invert() the matrix
        // and then use transform()
        void inverse_transform(double* x, double* y) const;

        //============================================ Auxiliary
        // Calculate the determinant of matrix
        double determinant() const
        {
            return 1.0 / (m0 * m3 - m1 * m2);
        }

    private:
        double m0;
        double m1;
        double m2;
        double m3;
        double m4;
        double m5;
    };


    //------------------------------------------------------------------------
    inline void affine_matrix::transform(double* x, double* y) const
    {
        register double tx = *x;
        *x = tx * m0 + *y * m2 + m4;
        *y = tx * m1 + *y * m3 + m5;
    }

    //------------------------------------------------------------------------
    inline void affine_matrix::inverse_transform(double* x, double* y) const
    {
        register double d = determinant();
        register double a = (*x - m4) * d;
        register double b = (*y - m5) * d;
        *x = a * m3 - b * m2;
        *y = b * m0 - a * m1;
    }

    //------------------------------------------------------------------------
    inline double affine_matrix::scale() const
    {
        double x = 0.707106781 * m0 + 0.707106781 * m2;
        double y = 0.707106781 * m1 + 0.707106781 * m3;
        return sqrt(x*x + y*y);
    }

    //========================================================================
    // Rotation matrix. sin() and cos() are calculated twice for the same angle.
    // There's no harm because the performance of sin()/cos() is very good on all
    // modern processors. Besides, this operation is not going to be invoked too 
    // often.
    class rotation_matrix : public affine_matrix
    {
    public:
        rotation_matrix(double a) : 
          affine_matrix(cos(a), sin(a), -sin(a), cos(a), 0.0, 0.0)
        {}
    };

    //========================================================================
    // Scaling matrix. sx, sy - scale coefficients by X and Y respectively
    class scaling_matrix : public affine_matrix
    {
    public:
        scaling_matrix(double sx, double sy) : 
          affine_matrix(sx, 0.0, 0.0, sy, 0.0, 0.0)
        {}

        scaling_matrix(double s) : 
          affine_matrix(s, 0.0, 0.0, s, 0.0, 0.0)
        {}
    };

    //========================================================================
    // Translation matrix
    class translation_matrix : public affine_matrix
    {
    public:
        translation_matrix(double tx, double ty) : 
          affine_matrix(1.0, 0.0, 0.0, 1.0, tx, ty)
        {}
    };

    //========================================================================
    // Sckewing (shear) matrix
    class skewing_matrix : public affine_matrix
    {
    public:
        skewing_matrix(double sx, double sy) : 
          affine_matrix(1.0, tan(sy), tan(sx), 1.0, 0.0, 0.0)
        {}
    };



}


#endif

