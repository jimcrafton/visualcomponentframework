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
// gouraud attribute type 
//
//----------------------------------------------------------------------------

#ifndef AGG_GOURAUD_ATTR_INCLUDED
#define AGG_GOURAUD_ATTR_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"

namespace agg
{

    //========================================================================
    template<class ColorT> struct gouraud_attr
    {
        struct gouraud_coord
        {
            double x;
            double y;
            ColorT color;
        };

        gouraud_attr() {}
        gouraud_attr(ColorT c1, ColorT c2, ColorT c3)
        {
            m_coord[0].color = c1;
            m_coord[1].color = c2;
            m_coord[2].color = c3;
        }
        gouraud_attr(double x1, double y1, 
                     double x2, double y2,
                     double x3, double y3,
                     ColorT c1, ColorT c2, ColorT c3)
        {
            m_coord[0].x = x1; 
            m_coord[0].y = y1;
            m_coord[1].x = x2; 
            m_coord[1].y = y2;
            m_coord[2].x = x3; 
            m_coord[2].y = y3;
            m_coord[0].color = c1;
            m_coord[1].color = c2;
            m_coord[2].color = c3;
        }

        void color(ColorT c1, ColorT c2, ColorT c3)
        {
            m_coord[0].color = c1;
            m_coord[1].color = c2;
            m_coord[2].color = c3;
        }

        void triangle(double x1, double y1, 
                      double x2, double y2,
                      double x3, double y3)
        {
            m_coord[0].x = x1; 
            m_coord[0].y = y1;
            m_coord[1].x = x2; 
            m_coord[1].y = y2;
            m_coord[2].x = x3; 
            m_coord[2].y = y3;
        }

        gouraud_coord m_coord[3];
    };

}

#endif

