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

#include "thirdparty/common/agg/include/agg_pixfmt_gray8.h"
#define pix_format agg::pix_format_gray8
typedef agg::pixfmt_gray8 pixformat;

#elif defined(AGG_BGR24)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb24.h"
#define pix_format agg::pix_format_bgr24
typedef agg::pixfmt_bgr24 pixfmt;

#elif defined(AGG_RGB24)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb24.h"
#define pix_format agg::pix_format_rgb24
typedef agg::pixfmt_rgb24 pixfmt;

#elif defined(AGG_BGRA32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_bgra32
typedef agg::pixfmt_bgra32 pixfmt;

#elif defined(AGG_RGBA32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_rgba32
typedef agg::pixfmt_rgba32 pixfmt;

#elif defined(AGG_ARGB32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_argb32
typedef agg::pixfmt_argb32 pixfmt;

#elif defined(AGG_ABGR32)

#include "thirdparty/common/agg/include/agg_pixfmt_rgba32.h"
#define pix_format agg::pix_format_abgr32
typedef agg::pixfmt_abgr32 pixfmt;

#elif defined(AGG_RGB565)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb565.h"
#define pix_format agg::pix_format_rgb565
typedef agg::pixfmt_rgb565 pixfmt;

#elif defined(AGG_RGB555)

#include "thirdparty/common/agg/include/agg_pixfmt_rgb555.h"
#define pix_format agg::pix_format_rgb555
typedef agg::pixfmt_rgb555 pixfmt;

#else
#error Please define pixel format: \
AGG_GRAY8, AGG_BGR24, AGG_RGB24, \
AGG_BGRA32, AGG_RGBA32, AGG_ARGB32, \
AGG_ABGR32, AGG_RGB565, or AGG_RGB555
#endif


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*/


#endif // _VCF_PIXELFORMATS_H__


