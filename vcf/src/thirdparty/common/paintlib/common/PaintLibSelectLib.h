#ifndef _PAINTLIB_SELECT_LIB_H__
#define _PAINTLIB_SELECT_LIB_H__
//PaintLibSelectLib.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**
*Helps linking with the right library
*/



#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef __BORLANDC__
#  define _LIB_CPLVERNUM "bcc"
#  endif
# endif



#ifdef USE_PAINTLIB_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "paintlib_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "paintlib_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_PAINTLIB_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "paintlib_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "paintlib_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // PAINTLIB_LIB


#ifdef USE_LIBJPEG_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_LIBJPEG_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static link library
#endif // LIBJPEG_LIB


#ifdef USE_LIBMNG_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "LibMNG_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "LibMNG_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_LIBMNG_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "LibMNG_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "LibMNG_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static link library
#endif // LIBMNG_LIB



#ifdef USE_LIBPNG_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_LIBPNG_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static link library
#endif // LIBPNG_LIB


#ifdef USE_LIBTIFF_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "LIBTIFF_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "LIBTIFF_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_LIBTIFF_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "LIBTIFF_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "LIBTIFF_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static link library
#endif // LIBTIFF_LIB


#ifdef USE_ZLIB_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "ZLIB_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "ZLIB_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_ZLIB_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "ZLIB_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "ZLIB_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static link library: in other words don't use any macro if you want to create a static library
#endif // ZLIB_LIB


#endif	//_PAINTLIB_SELECT_LIB_H__

/**
$Id$
*/
