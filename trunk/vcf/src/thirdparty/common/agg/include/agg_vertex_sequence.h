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
// vertex_sequence container and vertex_dist struct
//
//----------------------------------------------------------------------------
#ifndef AGG_VERTEX_SEQUENCE_INCLUDED
#define AGG_VERTEX_SEQUENCE_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_array.h"
#include "thirdparty/common/agg/include/agg_math.h"

namespace agg
{

    //------------------------------------------------------------------------
    // Modified agg::array. The data is interpreted as a sequence of vertices.
    // It means that the type T must expose:
    //
    // bool operator() (const T& val)
    // 
    // that is called every time new vertex is being added. The main purpose
    // of this operator is the possibility to calculate some values during 
    // adding and to return true if the vertex fits some criteria or false if
    // it doesn't. In the last case the new vertex is not added. 
    // 
    // The simple example is filtering coinciding vertices with calculation 
    // of the distance between the current and previous ones:
    //
    //    struct vertex_dist
    //    {
    //        double   x;
    //        double   y;
    //        double   dist;
    //
    //        vertex_dist() {}
    //        vertex_dist(double x_, double y_) :
    //            x(x_),
    //            y(y_),
    //            dist(0.0)
    //        {
    //        }
    //
    //        bool operator () (const vertex_dist& val)
    //        {
    //            return (dist = calc_distance(x, y, val.x, val.y)) > EPSILON;
    //        }
    //    };
    //
    // Function close() calls this operator and removes the last vertex if 
    // necessary.
    //------------------------------------------------------------------------
    template<class T, unsigned S=6> 
    class vertex_sequence : public array<T, S>
    {
    public:
        void add(const T& val);
        void modify_last(const T& val);
        void close(bool remove_flag);
    };



    //------------------------------------------------------------------------
    template<class T, unsigned S> 
    void vertex_sequence<T, S>::add(const T& val)
    {
        array<T,S>::add(val);
        if(size() > 1)
        {
            if(!(*this)[size() - 2]((*this)[size() - 1])) remove_last();
        }
    }


    //------------------------------------------------------------------------
    template<class T, unsigned S> 
    void vertex_sequence<T, S>::modify_last(const T& val)
    {
        array<T,S>::remove_last();
        add(val);
    }



    //------------------------------------------------------------------------
    template<class T, unsigned S> 
    void vertex_sequence<T, S>::close(bool remove_flag)
    {
        if(size() > 1)
        {
            T* ptr = &(*this)[size() - 1];
            if(!(*ptr)((*this)[0]))
            {
                if(remove_flag) remove_last();
            }
        }
    }




    // Coinciding points maximal distance (Epsilon)
    const double vertex_dist_epsilon = 1e-30;

    //------------------------------------------------------------------------
    // Vertex (x, y) with the distance to the next one. The last vertex has 
    // the distance between the last and the first points
    struct vertex_dist
    {
        double   x;
        double   y;
        double   dist;

        vertex_dist() {}
        vertex_dist(double x_, double y_) :
            x(x_),
            y(y_),
            dist(0.0)
        {
        }

        bool operator () (const vertex_dist& val)
        {
            bool ret = (dist = calc_distance(x, y, val.x, val.y)) > vertex_dist_epsilon;
            if(!ret) dist = 1.0 / vertex_dist_epsilon;
            return ret;
        }
    };




}

#endif
