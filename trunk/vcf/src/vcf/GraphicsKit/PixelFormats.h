#ifndef _VCF_PIXELFORMATS_H__
#define _VCF_PIXELFORMATS_H__
//PixelFormats.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#if defined(AGG_GRAY8)

#include "thirdparty/common/agg/include/agg_pixfmt_gray.h"
#define pix_format agg::pix_format_gray8
typedef agg::pixfmt_gray8 pixformat;
typedef agg::pixfmt_gray8_pre pixfmt_pre;
typedef agg::gray8 color_type;


#elif defined(AGG_BGR24)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb.h"
#define pix_format agg::pix_format_bgr24
typedef agg::pixfmt_bgr24 pixfmt;
typedef agg::pixfmt_bgr24_pre pixfmt_pre;
#define pixfmt_gamma agg::pixfmt_bgr24_gamma
typedef agg::rgba8 color_type;
typedef agg::order_bgr component_order;

#elif defined(AGG_RGB24)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb.h"
#define pix_format agg::pix_format_rgb24
typedef agg::pixfmt_rgb24 pixfmt;
typedef agg::pixfmt_rgb24_pre pixfmt_pre;
#define pixfmt_gamma agg::pixfmt_rgb24_gamma
typedef agg::rgba8 color_type;
typedef agg::order_rgb component_order;

#elif defined(AGG_BGRA32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba.h"
#define pix_format agg::pix_format_bgra32
typedef agg::pixfmt_bgra32 pixfmt;
typedef agg::pixfmt_bgra32_pre pixfmt_pre;
typedef agg::rgba8 color_type;
typedef agg::order_bgra component_order;

#elif defined(AGG_RGBA32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba.h"
#define pix_format agg::pix_format_rgba32
typedef agg::pixfmt_rgba32 pixfmt;
typedef agg::pixfmt_rgba32_pre pixfmt_pre;
typedef agg::rgba8 color_type;
typedef agg::order_rgba component_order;

#elif defined(AGG_ARGB32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_argb32
typedef agg::pixfmt_argb32 pixfmt;
typedef agg::pixfmt_argb32_pre pixfmt_pre;
typedef agg::rgba8 color_type;
typedef agg::order_argb component_order;

#elif defined(AGG_ABGR32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_abgr32
typedef agg::pixfmt_abgr32 pixfmt;
typedef agg::pixfmt_abgr32 pixfmt;
typedef agg::pixfmt_abgr32_pre pixfmt_pre;
typedef agg::rgba8 color_type;
typedef agg::order_argb component_order;

#elif defined(AGG_RGB565)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb_packed.h"
#define pix_format agg::pix_format_rgb565
typedef agg::pixfmt_rgb565 pixfmt;
typedef agg::pixfmt_rgb565_pre pixfmt_pre;
typedef agg::rgba8 color_type;

#elif defined(AGG_RGB555)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb_packed.h"
#define pix_format agg::pix_format_rgb555
typedef agg::pixfmt_rgb555 pixfmt;
typedef agg::pixfmt_rgb555_pre pixfmt_pre;
typedef agg::rgba8 color_type;

#else
#error Please define pixel format: \
AGG_GRAY8, AGG_BGR24, AGG_RGB24, \
AGG_BGRA32, AGG_RGBA32, AGG_ARGB32, \
AGG_ABGR32, AGG_RGB565, or AGG_RGB555
#endif


#endif // _VCF_PIXELFORMATS_H__

/**
$Id$
*/
