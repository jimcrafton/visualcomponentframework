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
// bounding_rect function template
//
//----------------------------------------------------------------------------
#ifndef AGG_BOUNDING_RECT_INCLUDED
#define AGG_BOUNDING_RECT_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    template<class VertexSource, class GetId> 
    void bounding_rect(VertexSource& vs, GetId& gi, 
                       unsigned start, unsigned num, 
                       double* x1, double* y1, double* x2, double* y2)
    {
        unsigned i;
        double x;
        double y;
        bool first = true;

        *x1 = *y1 = *x2 = *y2 = 0.0;

        for(i = 0; i < num; i++)
        {
            vs.rewind(gi[start + i]);
            while(!is_stop(vs.vertex(&x, &y)))
            {
                if(first)
                {
                    *x1 = *x2 = x;
                    *y1 = *y2 = y;
                    first = false;
                }
                else
                {
                    if(x < *x1) *x1 = x;
                    if(y < *y1) *y1 = y;
                    if(x > *x2) *x2 = x;
                    if(y > *y2) *y2 = y;
                }
            }
        }
    }

}

#endif
