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

#ifndef AGG_SPAN_BGRA32_IMAGE_INCLUDED
#define AGG_SPAN_BGRA32_IMAGE_INCLUDED

#include "thirdparty/common/agg/include/agg_image_transform.h"

namespace agg
{

    //--------------------------------------------------------------------
    template<class Attribute> class span_bgra32_image_simple
    {
    public:
        typedef Attribute attr_type;

        static void prepare(const Attribute&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}
        static void render(unsigned char* ptr, 
                           int x, int y,
                           unsigned count, 
                           const unsigned char* covers, 
                           const Attribute& attr)
        {
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg_r;
            int fg_g;
            int fg_b;
            int fg_a;

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
                    fg_b = *fg_ptr++;
                    fg_g = *fg_ptr++;
                    fg_r = *fg_ptr++;
                    fg_a = *fg_ptr++;

                    int alpha = gradient_alpha.calculate(
                        color_alpha->calculate(*covers++, fg_r, fg_g, fg_b)) * fg_a;

                    if(alpha == 255*255)
                    {
                        *bk_ptr++ = fg_b;
                        *bk_ptr++ = fg_g;
                        *bk_ptr++ = fg_r;
                        *bk_ptr++ = fg_a;
                    }
                    else
                    {
                        int bk_b = bk_ptr[0];
                        int bk_g = bk_ptr[1];
                        int bk_r = bk_ptr[2];
                        int bk_a = bk_ptr[3];
                        *bk_ptr++ = (((fg_b - bk_b) * alpha) + (bk_b << 16)) >> 16;
                        *bk_ptr++ = (((fg_g - bk_g) * alpha) + (bk_g << 16)) >> 16;
                        *bk_ptr++ = (((fg_r - bk_r) * alpha) + (bk_r << 16)) >> 16;
                        *bk_ptr++ = (((fg_a - bk_a) * alpha) + (bk_a << 16)) >> 16;
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




    //--------------------------------------------------------------------
    template<class Attribute> class span_bgra32_image_bilinear
    {
    public:
        typedef Attribute attr_type;

        static void prepare(const Attribute&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}
        static void render(unsigned char* ptr, 
                           int x, int y,
                           unsigned count, 
                           const unsigned char* covers, 
                           const Attribute& attr)
        {
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg_r;
            int fg_g;
            int fg_b;
            int fg_a;

            const unsigned char *fg_ptr;
            const typename Attribute::distortions_type* distortions = attr.m_distortions;
            const typename Attribute::color_alpha_type* color_alpha = attr.m_color_alpha;
            typename Attribute::gradient_alpha_type gradient_alpha(*attr.m_gradient_alpha, x, y, count);

            const rendering_buffer* src = attr.m_src;
            int stride = src->row_bytes() - 2 * 4;

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
                    fg_r = 
                    fg_g = 
                    fg_b = 
                    fg_a = image_subpixel_size * image_subpixel_size - 1;

                    int weight;
                    x_hr &= image_subpixel_mask;
                    y_hr &= image_subpixel_mask;
                    fg_ptr = src->row(y_lr) + (x_lr << 2);

                    weight = (image_subpixel_mask - x_hr) * 
                             (image_subpixel_mask - y_hr);
                    fg_b += weight * *fg_ptr++;
                    fg_g += weight * *fg_ptr++;
                    fg_r += weight * *fg_ptr++;
                    fg_a += weight * *fg_ptr++;

                    weight = x_hr * (image_subpixel_mask - y_hr);
                    fg_b += weight * *fg_ptr++;
                    fg_g += weight * *fg_ptr++;
                    fg_r += weight * *fg_ptr++;
                    fg_a += weight * *fg_ptr++;

                    fg_ptr += stride;

                    weight = (image_subpixel_mask - x_hr) * y_hr;
                    fg_b += weight * *fg_ptr++;
                    fg_g += weight * *fg_ptr++;
                    fg_r += weight * *fg_ptr++;
                    fg_a += weight * *fg_ptr++;

                    weight = x_hr * y_hr;
                    fg_b += weight * *fg_ptr++;
                    fg_g += weight * *fg_ptr++;
                    fg_r += weight * *fg_ptr++;
                    fg_a += weight * *fg_ptr++;

                    fg_r >>= image_subpixel_shift * 2;
                    fg_g >>= image_subpixel_shift * 2;
                    fg_b >>= image_subpixel_shift * 2;
                    fg_a >>= image_subpixel_shift * 2;

                    int alpha = gradient_alpha.calculate(
                        color_alpha->calculate(*covers++, fg_r, fg_g, fg_b)) * fg_a;

                    if(alpha == 255*255)
                    {
                        *bk_ptr++ = fg_b;
                        *bk_ptr++ = fg_g;
                        *bk_ptr++ = fg_r;
                        *bk_ptr++ = fg_a;
                    }
                    else
                    {
                        int bk_b = bk_ptr[0];
                        int bk_g = bk_ptr[1];
                        int bk_r = bk_ptr[2];
                        int bk_a = bk_ptr[3];
                        *bk_ptr++ = (((fg_b - bk_b) * alpha) + (bk_b << 16)) >> 16;
                        *bk_ptr++ = (((fg_g - bk_g) * alpha) + (bk_g << 16)) >> 16;
                        *bk_ptr++ = (((fg_r - bk_r) * alpha) + (bk_r << 16)) >> 16;
                        *bk_ptr++ = (((fg_a - bk_a) * alpha) + (bk_a << 16)) >> 16;
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




    //--------------------------------------------------------------------
    template<class Attribute> class span_bgra32_image
    {
    public:
        typedef Attribute attr_type;

        static void prepare(const Attribute&) {}
        static void prepare_y(int y) {}
        static void prepare_x(int x, unsigned count) {}
        static void render(unsigned char* ptr, 
                           int x, int y,
                           unsigned count, 
                           const unsigned char* covers, 
                           const Attribute& attr)
        {
            image_interpolator span(image_span(x, y, count, *attr.m_amtx));
            unsigned char* bk_ptr = ptr + (x << 2);

            int fg_r;
            int fg_g;
            int fg_b;
            int fg_a;

            const unsigned char *fg_ptr;

            unsigned   dimension    = attr.m_filter->dimension();
            int        start        = attr.m_filter->start();
            const int* weight_array = attr.m_filter->weight_array_int();

            const typename Attribute::distortions_type* distortions = attr.m_distortions;
            const typename Attribute::color_alpha_type* color_alpha = attr.m_color_alpha;
            typename Attribute::gradient_alpha_type gradient_alpha(*attr.m_gradient_alpha, x, y, count);
            const rendering_buffer* src = attr.m_src;
            int stride = src->row_bytes() - (dimension << 2);

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
                    fg_r = fg_g = fg_b = fg_a = image_filter_size / 2;

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
            
                            fg_b += *fg_ptr++ * weight;
                            fg_g += *fg_ptr++ * weight;
                            fg_r += *fg_ptr++ * weight;
                            fg_a += *fg_ptr++ * weight;

                            x_hr += image_subpixel_size;

                        } while(--x_count);

                        y_hr += image_subpixel_size;
                        fg_ptr += stride;

                    } while(--y_count);

                    fg_r >>= image_filter_shift;
                    fg_g >>= image_filter_shift;
                    fg_b >>= image_filter_shift;
                    fg_a >>= image_filter_shift;

                    if(fg_r < 0) fg_r = 0;
                    if(fg_g < 0) fg_g = 0;
                    if(fg_b < 0) fg_b = 0;
                    if(fg_a < 0) fg_a = 0;

                    if(fg_r > 255) fg_r = 255;
                    if(fg_g > 255) fg_g = 255;
                    if(fg_b > 255) fg_b = 255;
                    if(fg_a > 255) fg_a = 255;

                    int alpha = gradient_alpha.calculate(
                        color_alpha->calculate(*covers++, fg_r, fg_g, fg_b)) * fg_a;


                    if(alpha == 255*255)
                    {
                        *bk_ptr++ = fg_b;
                        *bk_ptr++ = fg_g;
                        *bk_ptr++ = fg_r;
                        *bk_ptr++ = fg_a;
                    }
                    else
                    {
                        int bk_b = bk_ptr[0];
                        int bk_g = bk_ptr[1];
                        int bk_r = bk_ptr[2];
                        int bk_a = bk_ptr[3];
                        *bk_ptr++ = (((fg_b - bk_b) * alpha) + (bk_b << 16)) >> 16;
                        *bk_ptr++ = (((fg_g - bk_g) * alpha) + (bk_g << 16)) >> 16;
                        *bk_ptr++ = (((fg_r - bk_r) * alpha) + (bk_r << 16)) >> 16;
                        *bk_ptr++ = (((fg_a - bk_a) * alpha) + (bk_a << 16)) >> 16;
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


}


#endif



