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
// classes span_bgra32_image*
//
//----------------------------------------------------------------------------

#ifndef AGG_PIXFMT_RGBA32_IMAGE_INCLUDED
#define AGG_PIXFMT_RGBA32_IMAGE_INCLUDED

#include "thirdparty/common/agg/include/agg_image_transform.h"
#include "thirdparty/common/agg/include/agg_span_null_interpolator.h"
#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"

namespace agg
{

    //========================================================================
    template<class Order, class Attribute> 
    class pixel_formats_rgba32_image_nn : public pixel_formats_rgba32<Order>
    {
    public:
        typedef Attribute attr_type;

        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int y,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& si)
        {
            const attr_type& attr = si.attribute();
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg[4];

            const unsigned char *fg_ptr;
            const typename Attribute::distortions_type* distortions = attr.m_distortions;
            const typename Attribute::color_alpha_type* color_alpha = attr.m_color_alpha;
            typename Attribute::gradient_alpha_type gradient_alpha(*attr.m_gradient_alpha, x, y, count);
            const rendering_buffer* src = attr.m_src;

            int maxx = attr.m_src->width() - 1;
            int maxy = attr.m_src->height() - 1;

            do
            {
                int x = span.x();
                int y = span.y();

                distortions->calculate(&x, &y);

                x >>= image_subpixel_shift;
                y >>= image_subpixel_shift;

                if(x >= 0    && y >= 0 &&
                   x <= maxx && y <= maxy) 
                {
                    fg_ptr = src->row(y) + (x << 2);
                    fg[0] = *fg_ptr++;
                    fg[1] = *fg_ptr++;
                    fg[2] = *fg_ptr++;
                    fg[3] = *fg_ptr++;

                    int alpha = 
                        gradient_alpha.calculate(
                            color_alpha->calculate(*covers++, 
                                                   fg[Order::R], 
                                                   fg[Order::G], 
                                                   fg[Order::B],
                                                   fg[Order::A]));

                    if(alpha == 255)
                    {
                        *bk_ptr++ = fg[0];
                        *bk_ptr++ = fg[1];
                        *bk_ptr++ = fg[2];
                        *bk_ptr++ = fg[3];
                    }
                    else
                    {
                        int bk0 = bk_ptr[0];
                        int bk1 = bk_ptr[1];
                        int bk2 = bk_ptr[2];
                        int bk3 = bk_ptr[3];
                        *bk_ptr++ = (((fg[0] - bk0) * alpha) + (bk0 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[1] - bk1) * alpha) + (bk1 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[2] - bk2) * alpha) + (bk2 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[3] - bk3) * alpha) + (bk3 << 8) + 0x80) >> 8;
                    }
                }
                else
                {
                    bk_ptr += 4;
                    covers++;
                }

                ++span;
                gradient_alpha.step();

            } while(--count);
        }
    };


    template<class Attribute> class pixfmt_rgba32_image_nn : 
    public pixel_formats_rgba32_image_nn<order_rgba32, Attribute> {};

    template<class Attribute> class pixfmt_argb32_image_nn : 
    public pixel_formats_rgba32_image_nn<order_argb32, Attribute> {};

    template<class Attribute> class pixfmt_bgra32_image_nn : 
    public pixel_formats_rgba32_image_nn<order_bgra32, Attribute> {};

    template<class Attribute> class pixfmt_abgr32_image_nn : 
    public pixel_formats_rgba32_image_nn<order_abgr32, Attribute> {};



    //========================================================================
    template<class Order, class Attribute> 
    class pixel_formats_rgba32_image_bilinear : public pixel_formats_rgba32<Order>
    {
    public:
        typedef Attribute attr_type;

        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int y,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& si)
        {
            const attr_type& attr = si.attribute();
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg[4];

            const unsigned char *fg_ptr;
            const typename Attribute::distortions_type* distortions = attr.m_distortions;
            const typename Attribute::color_alpha_type* color_alpha = attr.m_color_alpha;
            typename Attribute::gradient_alpha_type gradient_alpha(*attr.m_gradient_alpha, x, y, count);

            const rendering_buffer* src = attr.m_src;
            int stride = src->stride() - 2 * 4;

            int maxx = attr.m_src->width() - 2;
            int maxy = attr.m_src->height() - 2;

            do
            {
                int x_hr = span.x();
                int y_hr = span.y();

                distortions->calculate(&x_hr, &y_hr);

                int x_lr = x_hr >> image_subpixel_shift;
                int y_lr = y_hr >> image_subpixel_shift;

                if(x_lr >= 0    && y_lr >= 0 &&
                   x_lr <= maxx && y_lr <= maxy) 
                {
                    fg[0] = 
                    fg[1] = 
                    fg[2] = 
                    fg[3] = image_subpixel_size * image_subpixel_size / 2;

                    int weight;
                    x_hr &= image_subpixel_mask;
                    y_hr &= image_subpixel_mask;
                    fg_ptr = src->row(y_lr) + (x_lr << 2);

                    weight = (image_subpixel_size - x_hr) * 
                             (image_subpixel_size - y_hr);
                    fg[0] += weight * *fg_ptr++;
                    fg[1] += weight * *fg_ptr++;
                    fg[2] += weight * *fg_ptr++;
                    fg[3] += weight * *fg_ptr++;

                    weight = x_hr * (image_subpixel_size - y_hr);
                    fg[0] += weight * *fg_ptr++;
                    fg[1] += weight * *fg_ptr++;
                    fg[2] += weight * *fg_ptr++;
                    fg[3] += weight * *fg_ptr++;

                    fg_ptr += stride;

                    weight = (image_subpixel_size - x_hr) * y_hr;
                    fg[0] += weight * *fg_ptr++;
                    fg[1] += weight * *fg_ptr++;
                    fg[2] += weight * *fg_ptr++;
                    fg[3] += weight * *fg_ptr++;

                    weight = x_hr * y_hr;
                    fg[0] += weight * *fg_ptr++;
                    fg[1] += weight * *fg_ptr++;
                    fg[2] += weight * *fg_ptr++;
                    fg[3] += weight * *fg_ptr++;

                    fg[0] >>= image_subpixel_shift * 2;
                    fg[1] >>= image_subpixel_shift * 2;
                    fg[2] >>= image_subpixel_shift * 2;
                    fg[3] >>= image_subpixel_shift * 2;

                    int alpha = 
                        gradient_alpha.calculate(
                            color_alpha->calculate(*covers++, 
                                                   fg[Order::R], 
                                                   fg[Order::G], 
                                                   fg[Order::B],
                                                   fg[Order::A]));

                    if(alpha == 255)
                    {
                        *bk_ptr++ = fg[0];
                        *bk_ptr++ = fg[1];
                        *bk_ptr++ = fg[2];
                        *bk_ptr++ = fg[3];
                    }
                    else
                    {
                        int bk0 = bk_ptr[0];
                        int bk1 = bk_ptr[1];
                        int bk2 = bk_ptr[2];
                        int bk3 = bk_ptr[3];
                        *bk_ptr++ = (((fg[0] - bk0) * alpha) + (bk0 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[1] - bk1) * alpha) + (bk1 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[2] - bk2) * alpha) + (bk2 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[3] - bk3) * alpha) + (bk3 << 8) + 0x80) >> 8;
                    }
                }
                else
                {
                    bk_ptr += 4;
                    covers++;
                }

                ++span;
                gradient_alpha.step();

            } while(--count);
        }
    };


    template<class Attribute> class pixfmt_rgba32_image_bilinear : 
    public pixel_formats_rgba32_image_bilinear<order_rgba32, Attribute> {};

    template<class Attribute> class pixfmt_argb32_image_bilinear : 
    public pixel_formats_rgba32_image_bilinear<order_argb32, Attribute> {};

    template<class Attribute> class pixfmt_bgra32_image_bilinear : 
    public pixel_formats_rgba32_image_bilinear<order_bgra32, Attribute> {};

    template<class Attribute> class pixfmt_abgr32_image_bilinear : 
    public pixel_formats_rgba32_image_bilinear<order_abgr32, Attribute> {};



    //========================================================================
    template<class Order, class Attribute> 
    class pixel_formats_rgba32_image : public pixel_formats_rgba32<Order>
    {
    public:
        typedef Attribute attr_type;

        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int y,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& si)
        {
            const attr_type& attr = si.attribute();
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg[4];

            const unsigned char *fg_ptr;

            unsigned   dimension    = attr.m_filter->dimension();
            int        start        = attr.m_filter->start();
            const int* weight_array = attr.m_filter->weight_array_int();

            const typename Attribute::distortions_type* distortions = attr.m_distortions;
            const typename Attribute::color_alpha_type* color_alpha = attr.m_color_alpha;
            typename Attribute::gradient_alpha_type gradient_alpha(*attr.m_gradient_alpha, x, y, count);
            const rendering_buffer* src = attr.m_src;
            int stride = src->stride() - (dimension << 2);

            int maxx = attr.m_src->width() + start - 2;
            int maxy = attr.m_src->height() + start - 2;

            do
            {
                int x_hr = span.x();
                int y_hr = span.y();

                distortions->calculate(&x_hr, &y_hr);

                int x_lr = x_hr >> image_subpixel_shift;
                int y_lr = y_hr >> image_subpixel_shift;

                if(x_lr >= -start && y_lr >= -start &&
                   x_lr <= maxx   && y_lr <= maxy) 
                {
                    fg[0] = fg[1] = fg[2] = fg[3] = image_filter_size / 2;

                    int x_fract = x_hr & image_subpixel_mask;
                    unsigned y_count = dimension;

                    y_hr = image_subpixel_mask - (y_hr & image_subpixel_mask);
                    fg_ptr = src->row(y_lr + start) + ((x_lr + start) << 2);

                    do
                    {
                        unsigned x_count = dimension;
                        int weight_y = weight_array[y_hr];
                        x_hr = image_subpixel_mask - x_fract;

                        do
                        {
                            int weight = (weight_y * weight_array[x_hr] + 
                                         image_filter_size / 2) >> 
                                         image_filter_shift;
            
                            fg[0] += *fg_ptr++ * weight;
                            fg[1] += *fg_ptr++ * weight;
                            fg[2] += *fg_ptr++ * weight;
                            fg[3] += *fg_ptr++ * weight;

                            x_hr += image_subpixel_size;

                        } while(--x_count);

                        y_hr += image_subpixel_size;
                        fg_ptr += stride;

                    } while(--y_count);

                    fg[0] >>= image_filter_shift;
                    fg[1] >>= image_filter_shift;
                    fg[2] >>= image_filter_shift;
                    fg[3] >>= image_filter_shift;

                    if(fg[0] < 0) fg[0] = 0;
                    if(fg[1] < 0) fg[1] = 0;
                    if(fg[2] < 0) fg[2] = 0;
                    if(fg[3] < 0) fg[3] = 0;

                    if(fg[0] > 255) fg[0] = 255;
                    if(fg[1] > 255) fg[1] = 255;
                    if(fg[2] > 255) fg[2] = 255;
                    if(fg[3] > 255) fg[3] = 255;

                    int alpha = 
                        gradient_alpha.calculate(
                            color_alpha->calculate(*covers++, 
                                                   fg[Order::R], 
                                                   fg[Order::G], 
                                                   fg[Order::B],
                                                   fg[Order::A]));
                    if(alpha == 255)
                    {
                        *bk_ptr++ = fg[0];
                        *bk_ptr++ = fg[1];
                        *bk_ptr++ = fg[2];
                        *bk_ptr++ = fg[3];
                    }
                    else
                    {
                        int bk0 = bk_ptr[0];
                        int bk1 = bk_ptr[1];
                        int bk2 = bk_ptr[2];
                        int bk3 = bk_ptr[3];
                        *bk_ptr++ = (((fg[0] - bk0) * alpha) + (bk0 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[1] - bk1) * alpha) + (bk1 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[2] - bk2) * alpha) + (bk2 << 8) + 0x80) >> 8;
                        *bk_ptr++ = (((fg[3] - bk3) * alpha) + (bk3 << 8) + 0x80) >> 8;
                    }
                }
                else
                {
                    bk_ptr += 4;
                    covers++;
                }

                ++span;
                gradient_alpha.step();

            } while(--count);
        }
    };

    template<class Attribute> class pixfmt_rgba32_image : 
    public pixel_formats_rgba32_image<order_rgba32, Attribute> {};

    template<class Attribute> class pixfmt_argb32_image : 
    public pixel_formats_rgba32_image<order_argb32, Attribute> {};

    template<class Attribute> class pixfmt_bgra32_image : 
    public pixel_formats_rgba32_image<order_bgra32, Attribute> {};

    template<class Attribute> class pixfmt_abgr32_image : 
    public pixel_formats_rgba32_image<order_abgr32, Attribute> {};

}


#endif



