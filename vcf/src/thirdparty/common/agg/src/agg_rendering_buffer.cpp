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
// class rendering_buffer
//
//----------------------------------------------------------------------------
#include <string.h>
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"


namespace agg
{

    //========================================================================

    //------------------------------------------------------------------------
    rendering_buffer::~rendering_buffer()
    {
        delete [] m_rows;
    }


    //------------------------------------------------------------------------
    rendering_buffer::rendering_buffer() :
        m_buf(0),
        m_rows(0),
        m_width(0),
        m_height(0),
        m_row_bytes(0),
        m_max_height(0)
    {
    }


    //------------------------------------------------------------------------
    void rendering_buffer::attach(unsigned char* buf,
                                  unsigned width, 
                                  unsigned height,
                                  int      row_bytes)
    {
        m_buf = buf;
        m_width = width;
        m_height = height;
        m_row_bytes = row_bytes;
        if(height > m_max_height)
        {
            delete [] m_rows;
            m_rows = new unsigned char* [m_max_height = height];
        }

        unsigned char* row_ptr = m_buf;

        if(row_bytes < 0)
        {
            row_ptr = m_buf - int(height - 1) * row_bytes;
        }

        unsigned char** rows = m_rows;

        while(height--)
        {
            *rows++ = row_ptr;
            row_ptr += row_bytes;
        }

        m_clip_box.x1 = 0;
        m_clip_box.y1 = 0;
        m_clip_box.x2 = int(m_width)  - 1;
        m_clip_box.y2 = int(m_height) - 1;
    }


    //------------------------------------------------------------------------
    bool rendering_buffer::clip_box(rect cb)
    {
        cb.normalize();
        if(cb.clip(rect(0, 0, m_width - 1, m_height - 1)))
        {
            m_clip_box = cb;
            return true;
        }
        m_clip_box.x1 = 1;
        m_clip_box.y1 = 1;
        m_clip_box.x2 = 0;
        m_clip_box.y2 = 0;
        return false;
    }


    //------------------------------------------------------------------------
    void rendering_buffer::copy_from(const rendering_buffer& rbuf)
    {
        unsigned h = height();
        if(rbuf.height() < h) h = rbuf.height();
        
        unsigned l = row_bytes_abs();
        if(rbuf.row_bytes_abs() < l) l = rbuf.row_bytes_abs();
        
        unsigned y;
        for (y = 0; y < h; y++)
        {
            memcpy(row(y), rbuf.row(y), l);
        }
    }

    
    
}





