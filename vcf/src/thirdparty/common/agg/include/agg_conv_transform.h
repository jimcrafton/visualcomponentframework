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
// class conv_transform
//
//----------------------------------------------------------------------------
#ifndef AGG_CONV_TRANSFORM_INCLUDED
#define AGG_CONV_TRANSFORM_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_affine_matrix.h"
#include "thirdparty/common/agg/include/agg_vertex_iterator.h"

namespace agg
{

    //------------------------------------------------------------------------
    template<class VertexSource, class Transformer=affine_matrix> class conv_transform
    {
    public:
        conv_transform(VertexSource& source, const Transformer& tr) :
          m_source(&source), m_trans(&tr) { }

        void rewind(unsigned id) 
        { 
            m_source->rewind(id); 
        }

        unsigned vertex(double* x, double* y)
        {
            unsigned cmd = m_source->vertex(x, y);
            if(!is_stop(cmd))
            {
                m_trans->transform(x, y);
            }
            return cmd;
        }

        void transformer(const Transformer& tr)
        {
            m_trans = &tr;
        }

        typedef conv_transform<VertexSource, Transformer> source_type;
        typedef vertex_iterator<source_type> iterator;
        iterator begin(unsigned id) { return iterator(*this, id); }
        iterator end() { return iterator(path_cmd_stop); }


    private:
        VertexSource*      m_source;
        const Transformer* m_trans;
    };


}

#endif
