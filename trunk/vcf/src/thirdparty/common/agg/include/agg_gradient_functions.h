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
// gradient functions
//
//----------------------------------------------------------------------------

#ifndef AGG_GRADIENT_FUNCTIONS_INCLUDED
#define AGG_GRADIENT_FUNCTIONS_INCLUDED

#include <math.h>
#include <stdlib.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_math.h"

namespace agg
{


    //------------------------------------------------------------------------
    class gradient_circle
    {
    public:
        static int calculate(int x, int y, int)
        {
            return int(fast_sqrt(x*x + y*y));
        }
    };


    //------------------------------------------------------------------------
    class gradient_x
    {
    public:
        static int calculate(int x, int, int) { return x; }
    };


    //------------------------------------------------------------------------
    class gradient_y
    {
    public:
        static int calculate(int, int y, int) { return y; }
    };


    //------------------------------------------------------------------------
    class gradient_diamond
    {
    public:
        static int calculate(int x, int y, int) 
        { 
            int ax = abs(x);
            int ay = abs(y);
            return ax > ay ? ax : ay; 
        }
    };


    //------------------------------------------------------------------------
    class gradient_xy
    {
    public:
        static int calculate(int x, int y, int d) 
        { 
            return abs(x) * abs(y) / d; 
        }
    };


    //------------------------------------------------------------------------
    class gradient_sqrt_xy
    {
    public:
        static int calculate(int x, int y, int) 
        { 
            return fast_sqrt(abs(x) * abs(y)); 
        }
    };


    //------------------------------------------------------------------------
    class gradient_conic
    {
    public:
        static int calculate(int x, int y, int d) 
        { 
            return int(fabs(atan2(double(y), double(x))) * double(d) / pi);
        }
    };



}





#endif


