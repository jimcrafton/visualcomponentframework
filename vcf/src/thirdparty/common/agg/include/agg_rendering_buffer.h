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

#ifndef AGG_RENDERING_BUFFER_INCLUDED
#define AGG_RENDERING_BUFFER_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_matrix.h"


namespace agg
{

    //========================================================================
    // Rendering buffer wrapper. This class does not know anything about 
    // memory organizations, all it does it keeps an array of pointers 
    // to each pixel row. The general rules of rendering are as follows.
    // 
    // 1. Allocate or create somehow a rendering buffer itself. Since 
    //    the library does not depend on any particular platform or
    //    architecture it was decided that it's your responsibility 
    //    to create and destroy rendering buffers properly. You can use
    //    any available mechanism to create it - you can use a system API 
    //    function, simple memory allocation, or even statically defined array. 
    //    You also should know the memory organization (or possible variants)
    //    in your system. For example, there's an R,G,B or B,G,R organizations 
    //    with one byte per component (three byter per pixel) is used very often. 
    //    So, if you intend to use class render_bgr24, for example, you should 
    //    allocate at least width*height*3 bytes of memory.
    //
    // 2. Create a rendering_buffer object and then call method attach(). It requires
    //    a pointer to the buffer itself, width and height of the buffer in 
    //    pixels, and the length of the row in bytes. All these values must 
    //    properly correspond to the memory organization. The argument stride
    //    is used because in reality the row length in bytes does not obligatory 
    //    correspond with the width of the image in pixels, i.e. it cannot be 
    //    simply calculated as width_in_pixels * bytes_per_pixel. For example, 
    //    it must be aligned to 4 bytes in Windows bitmaps. Besides, the value
    //    of stride can be negative - it depends on the order of displaying
    //    the rendering buffer - from top to bottom or from bottom to top. 
    //    In other words, if stride > 0 the pointers to each row will start 
    //    from the beginning of the buffer and increase. If it < 0, the pointers 
    //    start from the end of the buffer and decrease. It gives you an 
    //    additional degree of freedom.
    //    Method attach() can be called more than once. The execution time of it
    //    is very little, still it allocates memory of heigh * sizeof(char*) bytes
    //    and has a loop while(height--) {...}, so it's unreasonable to call it
    //    every time before drawing any single pixel :-)
    //
    // 3. Create an object (or a number of objects) of a rendering class, such as
    //    renderer_bgr24_solid, renderer_bgr24_image and so on. These classes
    //    require a pointer to the renderer_buffer object, but they do not perform
    //    any considerable operations except storing this pointer. So, rendering
    //    objects can be created on demand almost any time. These objects know 
    //    about concrete memory organization (this knowledge is hardcoded), so 
    //    actually, the memory you allocated or created in clause 1 should 
    //    actually be in correspondence to the needs of the rendering class.
    //  
    // 4. Rener your image using rendering classes, for example, rasterizer
    //  
    // 5. Display the result, or store it, or whatever. It's also your 
    //    responsibility and depends on the platform.
    //------------------------------------------------------------------------
    class rendering_buffer : public matrix<int8u>
    {
    public:
        //--------------------------------------------------------------------
        void attach(int8u* buf, unsigned width, unsigned height, int stride)
        {
            matrix<int8u>::attach(buf, width, height, stride);
            m_clip_box = rect(0, 0, int(width) - 1, int(height) - 1);
        }

        //--------------------------------------------------------------------
        bool clip_box(rect cb)
        {
            cb.normalize();
            if(cb.clip(rect(0, 0, width() - 1, height() - 1)))
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

        //--------------------------------------------------------------------
        const rect& clip_box() const { return m_clip_box;    }
        int         xmin()     const { return m_clip_box.x1; }
        int         ymin()     const { return m_clip_box.y1; }
        int         xmax()     const { return m_clip_box.x2; }
        int         ymax()     const { return m_clip_box.y2; }

        //--------------------------------------------------------------------
        bool inbox(int x, int y) const
        {
            return x >= m_clip_box.x1 && y >= m_clip_box.y1 &&
                   x <= m_clip_box.x2 && y <= m_clip_box.y2;
        }
        
    private:
        rect m_clip_box;
    };

}


#endif
