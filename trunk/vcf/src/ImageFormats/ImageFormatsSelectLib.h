#ifndef _IMAGEFORMATS_SELECT_LIB_H__
#define _IMAGEFORMATS_SELECT_LIB_H__

//FreeImageSelectLib.h

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
#  define  _LIB_CPLVERNUM "bcc"
#  endif
# endif


#ifdef USE_IMAGEFORMATS_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "ImageFormats_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "ImageFormats_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_IMAGEFORMATS_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "ImageFormats_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "ImageFormats_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // IMAGEFORMATS_LIB


#endif	//_IMAGEFORMATS_SELECT_LIB_H__

/**
$Id$
*/
