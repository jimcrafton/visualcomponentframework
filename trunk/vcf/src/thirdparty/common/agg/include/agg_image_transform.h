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
// Image transformations basic definitions,
// Filtering classes (image_filter_base, image_filter),
// Attribute classes (image_transform_attr, image_transform_filter_attr),
// Basic filter shape classes:
//    image_filter_bilinear,
//    image_filter_bicubic,
//    image_filter_spline16,
//    image_filter_spline36,
//    image_filter_sinc64,
//    image_filter_sinc144,
//    image_filter_sinc196,
//    image_filter_sinc256
//
//----------------------------------------------------------------------------
#ifndef AGG_IMAGE_TRANSFORM_INCLUDED
#define AGG_IMAGE_TRANSFORM_INCLUDED

#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"
#include "thirdparty/common/agg/include/agg_affine_span.h"
#include "thirdparty/common/agg/include/agg_gradient_attr.h"


namespace agg
{

    enum
    {
        image_filter_shift = 15,
        image_filter_size  = 1 << image_filter_shift,
        image_filter_mask  = image_filter_size - 1,

        image_subpixel_shift = 8,
        image_subpixel_size  = 1 << image_subpixel_shift,
        image_subpixel_mask  = image_subpixel_size - 1
    };


    typedef affine_span<image_subpixel_shift> image_span;
    typedef image_span::interpolator          image_interpolator;

    //--------------------------------------------------------------------
    class image_filter_base
    {
    public:
        ~image_filter_base();

        image_filter_base(unsigned dimension);

        unsigned      dimension()        const { return m_dimension;        }
        int           start()            const { return m_start;            }
        const double* weight_array_dbl() const { return m_weight_array_dbl; }
        const int*    weight_array_int() const { return m_weight_array_int; }

    protected:
        void     weight(unsigned idx, double val);
        double   calc_x(unsigned idx) const;
        void     normalize();

    private:
        unsigned m_dimension;
        int      m_start;
        double*  m_weight_array_dbl;
        int*     m_weight_array_int;
    };



    //--------------------------------------------------------------------
    template<class FilterF> class image_filter : public image_filter_base
    {
    public:
        image_filter() :
            image_filter_base(FilterF::dimension()),
            m_filter_function()
        {
            unsigned i;
            unsigned dim = dimension() << image_subpixel_shift;
            for(i = 0; i < dim; i++)
            {
                weight(i, m_filter_function.calc_weight(calc_x(i)));
            }
            normalize();
        }
    private:
        FilterF m_filter_function;
    };



    //--------------------------------------------------------------------
    class null_distortions
    {
    public:
        static void calculate(int*, int*) {}
    };

    //--------------------------------------------------------------------
    class null_color_alpha
    {
    public:
        static int calculate(int alpha, int, int, int, int) { return alpha; }
    };

    //--------------------------------------------------------------------
    class null_gradient_alpha
    {
    public:
        null_gradient_alpha() {}
        null_gradient_alpha(const null_gradient_alpha&,
                            int, int, unsigned) {}
        static int  calculate(int a) { return a; }
        static void step() {}
    };


    //--------------------------------------------------------------------
    class image_brightness_alpha_rgb8
    {
    public:
        enum
        {
            array_size = 256 * 3
        };

        image_brightness_alpha_rgb8(const unsigned char* alpha_array) :
            m_alpha_array(alpha_array)
        {
        }

        int calculate(int alpha, int r, int g, int b, int) const
        {
            return (alpha * m_alpha_array[r + g + b]) >> 8;
        }

    private:
        const unsigned char* m_alpha_array;
    };


    //--------------------------------------------------------------------
    class image_brightness_alpha_rgba8
    {
    public:
        enum
        {
            array_size = 256 * 3
        };

        image_brightness_alpha_rgba8(const unsigned char* alpha_array) :
            m_alpha_array(alpha_array)
        {
        }

        int calculate(int alpha, int r, int g, int b, int a) const
        {
            return (alpha * m_alpha_array[r + g + b] * a) >> 16;
        }

    private:
        const unsigned char* m_alpha_array;
    };


   
    //--------------------------------------------------------------------
    class image_alpha_rgba8
    {
    public:
        static int calculate(int alpha, int, int, int, int a)
        {
            return (alpha * a) >> 8;
        }
    };



    //--------------------------------------------------------------------
    template<class GradientF> class gradient_u8
    {
    public:
        enum
        {
            array_shift = 8,
            array_size  = 1 << array_shift,
            array_mask  = array_size - 1,

            value_shift = 8,
            value_size  = 1 << value_shift,
            value_mask  = value_size - 1
        };

        gradient_u8(const affine_matrix& mtx,
                    const GradientF& gradient_function,
                    const unsigned char* gradient_array,
                    double r1, double r2) :
            m_mtx(&mtx),
            m_gradient_function(&gradient_function),
            m_gradient_array(gradient_array),
            m_d1(int(r1 * gradient_subpixel_size)),
            m_d2(int(r2 * gradient_subpixel_size)),
            m_span(gradient_span(0, 0, 1, mtx))
        {
        }

        gradient_u8(const gradient_u8& gr,
                    int x, int y, unsigned count) :
            m_mtx(gr.m_mtx),
            m_gradient_function(gr.m_gradient_function),
            m_gradient_array(gr.m_gradient_array),
            m_d1(gr.m_d1),
            m_d2(gr.m_d2),
            m_span(gradient_span(x, y, count, *m_mtx))
        {
        }

        int calculate(int a) const
        {
            int dd = m_d2 - m_d1;
            int d = m_gradient_function->calculate(m_span.x(), 
                                                   m_span.y(), 
                                                   dd);
            d = ((d - m_d1) << array_shift) / dd;
            if(d < 0) d = 0;
            if(d > array_mask) d = array_mask;
            return (a * m_gradient_array[d]) >> value_shift;
        }

        void step() { ++m_span; }

    private:
        const affine_matrix*  m_mtx;
        const GradientF*      m_gradient_function;
        const unsigned char*  m_gradient_array;
        int                   m_d1;
        int                   m_d2;
        gradient_interpolator m_span;
    };



    //--------------------------------------------------------------------
    template<class DistortionsF, class ColorAlphaF, class GradientAlphaF> 
    struct image_transform_attr
    {
        typedef DistortionsF    distortions_type;
        typedef ColorAlphaF     color_alpha_type;
        typedef GradientAlphaF  gradient_alpha_type;

        image_transform_attr() {}
        image_transform_attr(const rendering_buffer& src, 
                             const affine_matrix& amtx,
                             const DistortionsF& distortions,
                             const ColorAlphaF& color_alpha,
                             const GradientAlphaF& gradient_alpha) :
            m_src(&src),
            m_amtx(&amtx),
            m_distortions(&distortions),
            m_color_alpha(&color_alpha),
            m_gradient_alpha(&gradient_alpha)
        {
        }

        const rendering_buffer*  m_src;
        const affine_matrix*     m_amtx;
        const DistortionsF*      m_distortions;
        const ColorAlphaF*       m_color_alpha;
        const GradientAlphaF*    m_gradient_alpha;
    };


    //--------------------------------------------------------------------
    template<class DistortionsF, class ColorAlphaF, class GradientAlphaF> 
    struct image_transform_filter_attr
    {
        typedef DistortionsF    distortions_type;
        typedef ColorAlphaF     color_alpha_type;
        typedef GradientAlphaF  gradient_alpha_type;

        image_transform_filter_attr() {}
        image_transform_filter_attr(const rendering_buffer& src, 
                                    const affine_matrix& amtx,
                                    const image_filter_base& filter,
                                    const DistortionsF& distortions,
                                    const ColorAlphaF& color_alpha,
                                    const GradientAlphaF& gradient_alpha) :
            m_src(&src),
            m_amtx(&amtx),
            m_filter(&filter),
            m_distortions(&distortions),
            m_color_alpha(&color_alpha),
            m_gradient_alpha(&gradient_alpha)
        {
        }

        const rendering_buffer*  m_src;
        const affine_matrix*     m_amtx;
        const image_filter_base* m_filter;
        const DistortionsF*      m_distortions;
        const ColorAlphaF*       m_color_alpha;
        const GradientAlphaF*    m_gradient_alpha;
    };




    //--------------------------------------------------------------------
    class image_filter_bilinear
    {
    public:
        static unsigned dimension() { return 2; }

        static double calc_weight(double x)
        {
            return (x <= 0.0) ? x + 1.0 : 1.0 - x;
        }
    };


    
    //--------------------------------------------------------------------
    class image_filter_bicubic
    {
        static double pow3(double x)
        {
            return (x <= 0.0) ? 0.0 : x * x * x;
        }

    public:
        static unsigned dimension() { return 4; }

        static double calc_weight(double x)
        {
            return
                (1.0/6.0) * 
                (pow3(x + 2) - 4 * pow3(x + 1) + 6 * pow3(x) - 4 * pow3(x - 1));
        }
    };




    //--------------------------------------------------------------------
    class image_filter_spline16
    {
    public:
        static unsigned dimension() { return 4; }
        static double calc_weight(double x)
        {
            if(x < 0.0) x = -x;
            if(x < 1.0)
            {
                return ((x - 9.0/5.0 ) * x - 1.0/5.0 ) * x + 1.0;
            }
            return ((-1.0/3.0 * (x-1) + 4.0/5.0) * (x-1) - 7.0/15.0 ) * (x-1);
        }
    };



    //--------------------------------------------------------------------
    class image_filter_spline36
    {
    public:
        static unsigned dimension() { return 6; }
        static double calc_weight(double x)
        {
           if(x < 0.0) x = -x;

           if(x < 1.0)
           {
              return ((13.0/11.0 * x - 453.0/209.0) * x - 3.0/209.0) * x + 1.0;
           }
           if(x < 2.0)
           {
              return ((-6.0/11.0 * (x-1) + 270.0/209.0) * (x-1) - 156.0/ 209.0) * (x-1);
           }
   
           return ((1.0/11.0 * (x-2) - 45.0/209.0) * (x-2) +  26.0/209.0) * (x-2);
        }
    };


    //--------------------------------------------------------------------
    class image_filter_sinc36
    {
    public:
        static unsigned dimension() { return 6; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x3 = x * (1.0/3.0);
           return (sin(x) / x) * (sin(x3) / x3);
        }
    };


    
    //--------------------------------------------------------------------
    class image_filter_sinc64
    {
    public:
        static unsigned dimension() { return 8; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x4 = x * 0.25;
           return (sin(x) / x) * (sin(x4) / x4);
        }
    };


    //--------------------------------------------------------------------
    class image_filter_sinc100
    {
    public:
        static unsigned dimension() { return 10; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x5 = x * 0.2;
           return (sin(x) / x) * (sin(x5) / x5);
        }
    };


    //--------------------------------------------------------------------
    class image_filter_sinc144
    {
    public:
        static unsigned dimension() { return 12; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x6 = x * (1.0/6.0);
           return (sin(x) / x) * (sin(x6) / x6);
        }
    };



    //--------------------------------------------------------------------
    class image_filter_sinc196
    {
    public:
        static unsigned dimension() { return 14; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x7 = x * (1.0/7.0);
           return (sin(x) / x) * (sin(x7) / x7);
        }
    };



    //--------------------------------------------------------------------
    class image_filter_sinc256
    {
    public:
        static unsigned dimension() { return 16; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x8 = x * 0.125;
           return (sin(x) / x) * (sin(x8) / x8);
        }
    };


    //--------------------------------------------------------------------
    class image_filter_blackman36
    {
    public:
        static unsigned dimension() { return 6; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x3 = x * (1.0/3.0);
           return (sin(x) / x) * (0.42 + 0.5*cos(x3) + 0.08*cos(2*x3));
        }
    };


    //--------------------------------------------------------------------
    class image_filter_blackman64
    {
    public:
        static unsigned dimension() { return 8; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x4 = x * 0.25;
           return (sin(x) / x) * (0.42 + 0.5*cos(x4) + 0.08*cos(2*x4));
        }
    };


    //--------------------------------------------------------------------
    class image_filter_blackman100
    {
    public:
        static unsigned dimension() { return 10; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x5 = x * 0.2;
           return (sin(x) / x) * (0.42 + 0.5*cos(x5) + 0.08*cos(2*x5));
        }
    };


    //--------------------------------------------------------------------
    class image_filter_blackman144
    {
    public:
        static unsigned dimension() { return 12; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x6 = x * (1.0/6.0);
           return (sin(x) / x) * (0.42 + 0.5*cos(x6) + 0.08*cos(2*x6));
        }
    };



    //--------------------------------------------------------------------
    class image_filter_blackman196
    {
    public:
        static unsigned dimension() { return 14; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x7 = x * (1.0/7.0);
           return (sin(x) / x) * (0.42 + 0.5*cos(x7) + 0.08*cos(2*x7));
        }
    };



    //--------------------------------------------------------------------
    class image_filter_blackman256
    {
    public:
        static unsigned dimension() { return 16; }
        static double calc_weight(double x)
        {
           if(x == 0.0) return 1.0;
           x *= pi;
           double x8 = x * 0.125;
           return (sin(x) / x) * (0.42 + 0.5*cos(x8) + 0.08*cos(2*x8));
        }
    };



}

#endif
