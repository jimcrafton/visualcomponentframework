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
// class bspline
//
//----------------------------------------------------------------------------

#ifndef AGG_BSPLINE_INCLUDED
#define AGG_BSPLINE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{
    //------------------------------------------------------------------------
    // A very simple class of Bi-cubic Spline interpolation.
    // First call init(num, x[], y[]) where num - number of source points, 
    // x, y - arrays of Y and Y values respectively. Here Y must be a function 
    // of X. It means that all the X-coordinates must be arranged in the ascending
    // order. 
    // Then call get(x) that calculates a value Y for the respective X. 
    // The class supports extrapolation, i.e. you can call get(x) where x is
    // outside the given with init() X-range. Extrapolation is a simple linear 
    // function.
    //------------------------------------------------------------------------
    class bspline 
    {
    public:
        ~bspline();
        bspline();

        void   init(int num, double* x, double* y);
        double get(double x) const;
    
    private:
        bspline(const bspline&);
        const bspline& operator = (const bspline&);

        static void bsearch(int n, double *x, double x0, int *i, int *j);

        int    m_num;
        double *m_x;
        double *m_y;
        double *m_am;
    };


}

#endif
