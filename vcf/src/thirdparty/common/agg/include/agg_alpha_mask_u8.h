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
// scanline_u8 class
//
//----------------------------------------------------------------------------
#ifndef AGG_ALPHA_MASK_U8_INCLUDED
#define AGG_ALPHA_MASK_U8_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"

namespace agg
{
    struct one_component_mask_u8
    {
        static int8u calculate(const int8u* p) { return *p; }
    };
    

    template<unsigned R, unsigned G, unsigned B>
    struct rgb_to_gray_mask_u8
    {
        static int8u calculate(const int8u* p) 
        { 
            return (p[R]*77 + p[G]*150 + p[B]*29) >> 8; 
        }
    };

    //------------------------------------------------------------------------
    template<unsigned Step=1, unsigned Offset=0, class MaskF=one_component_mask_u8>
    class alpha_mask_u8
    {
    public:
        alpha_mask_u8() : m_rbuf(0) {}
        alpha_mask_u8(rendering_buffer& rbuf) : m_rbuf(&rbuf) {}

        void attach(rendering_buffer& rbuf) { m_rbuf = &rbuf; }

        MaskF& mask_function() { return m_mask_function; }
        const MaskF& mask_function() const { return m_mask_function; }
         
        //--------------------------------------------------------------------
        void combine_span(int x, int y, unsigned char* dst, int num_pix) const
        {
            rect cb = m_rbuf->clip_box();

            int count = num_pix;
            unsigned char* covers = dst;

            if(y < cb.y1 || y > cb.y2)
            {
                memset(dst, 0, num_pix);
                return;
            }

            if(x < cb.x1)
            {
                count -= cb.x1 - x;
                if(count <= 0) 
                {
                    memset(dst, 0, num_pix);
                    return;
                }
                memset(covers, 0, cb.x1 - x);
                covers += cb.x1 - x;
                x = cb.x1;
            }

            if(x + count > cb.x2)
            {
                int rest = x + count - cb.x2 - 1;
                count -= rest;
                if(count <= 0) 
                {
                    memset(dst, 0, num_pix);
                    return;
                }
                memset(covers + count, 0, rest);
            }

            const unsigned char* mask = m_rbuf->row(y) + x * Step + Offset;
            do
            {
                *covers++ = ((*covers) * m_mask_function.calculate(mask)) >> 8;
                mask += Step;
            }
            while(--count);
        }

    private:
        rendering_buffer* m_rbuf;
        MaskF             m_mask_function;
    };
    

    typedef alpha_mask_u8<1, 0> alpha_mask_gray8;

    typedef alpha_mask_u8<3, 0> alpha_mask_rgb24r;
    typedef alpha_mask_u8<3, 1> alpha_mask_rgb24g;
    typedef alpha_mask_u8<3, 2> alpha_mask_rgb24b;

    typedef alpha_mask_u8<3, 2> alpha_mask_bgr24r;
    typedef alpha_mask_u8<3, 1> alpha_mask_bgr24g;
    typedef alpha_mask_u8<3, 0> alpha_mask_bgr24b;

    typedef alpha_mask_u8<4, 0> alpha_mask_rgba32r;
    typedef alpha_mask_u8<4, 1> alpha_mask_rgba32g;
    typedef alpha_mask_u8<4, 2> alpha_mask_rgba32b;
    typedef alpha_mask_u8<4, 3> alpha_mask_rgba32a;

    typedef alpha_mask_u8<4, 1> alpha_mask_argb32r;
    typedef alpha_mask_u8<4, 2> alpha_mask_argb32g;
    typedef alpha_mask_u8<4, 3> alpha_mask_argb32b;
    typedef alpha_mask_u8<4, 0> alpha_mask_argb32a;

    typedef alpha_mask_u8<4, 2> alpha_mask_bgra32r;
    typedef alpha_mask_u8<4, 1> alpha_mask_bgra32g;
    typedef alpha_mask_u8<4, 0> alpha_mask_bgra32b;
    typedef alpha_mask_u8<4, 3> alpha_mask_bgra32a;

    typedef alpha_mask_u8<4, 3> alpha_mask_abgr32r;
    typedef alpha_mask_u8<4, 2> alpha_mask_abgr32g;
    typedef alpha_mask_u8<4, 1> alpha_mask_abgr32b;
    typedef alpha_mask_u8<4, 0> alpha_mask_abgr32a;

    typedef alpha_mask_u8<3, 0, rgb_to_gray_mask_u8<0, 1, 2> > alpha_mask_rgb24gray;
    typedef alpha_mask_u8<3, 0, rgb_to_gray_mask_u8<2, 1, 0> > alpha_mask_bgr24gray;
    typedef alpha_mask_u8<4, 0, rgb_to_gray_mask_u8<0, 1, 2> > alpha_mask_rgba32gray;
    typedef alpha_mask_u8<4, 1, rgb_to_gray_mask_u8<0, 1, 2> > alpha_mask_argb32gray;
    typedef alpha_mask_u8<4, 0, rgb_to_gray_mask_u8<2, 1, 0> > alpha_mask_bgra32gray;
    typedef alpha_mask_u8<4, 1, rgb_to_gray_mask_u8<2, 1, 0> > alpha_mask_abgr32gray;

}



#endif
