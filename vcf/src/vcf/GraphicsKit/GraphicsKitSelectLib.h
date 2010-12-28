#ifndef _VCF_GRAPHICSKITSELECTLIB_H__
#define _VCF_GRAPHICSKITSELECTLIB_H__
//GraphicsKitSelectLib.h

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

// We don't need any of this if we've disabled pragma linking
#ifdef VCF_DISABLE_PRAGMA_LINKING
#else

//If using the All-in-1 library, then this task has already been done
#if !defined(VCF_USE_ALLIN1_DLL) && !defined(VCF_USE_ALLIN1_LIB)

#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif

#ifdef VCF_WIN32CE
#   define _LIB_CPLVCWINCE "ce"
#else
#   define _LIB_CPLVCWINCE ""
#endif

# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1500)
#     define _LIB_CPLVERNUM "vc90" _LIB_CPLVCWINCE
#   elif (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80" _LIB_CPLVCWINCE
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
#  ifdef VCF_BCC
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif


/**
All of this is here so that if we use this kit in our programs, all we
have to do is pull in this one file (OpenGLKit.h) and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "USE_OPENGLKIT_DLL" defined or "USE_OPENGLKIT_LIB"
defined to use the DLL or static libraries.
*/
#if defined(VCF_MSC) || defined(VCF_BCC)

	//link to libAgg automatically here
	#if !defined(VCF_DISABLE_PRAGMA_LINKING)
	#	ifdef VCF_STATIC_CRT
	#		ifdef _DEBUG
	#			pragma comment(lib, "libAGG_"_LIB_CPLVERNUM"_scrtd.lib")
	#			pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_scrtd.lib")
	#			pragma comment(lib, "ZLib_"_LIB_CPLVERNUM"_scrtd.lib")
	#			pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_scrtd.lib")
	#		else
	#			pragma comment(lib, "libAGG_"_LIB_CPLVERNUM"_scrt.lib")
	#			pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_scrt.lib")
	#			pragma comment(lib, "ZLib_"_LIB_CPLVERNUM"_scrt.lib")
	#			pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_scrt.lib")
	#		endif
	#	else
	#		ifdef _DEBUG
	#			pragma comment(lib, "libAGG_"_LIB_CPLVERNUM"_sd.lib")
	#			pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_sd.lib")
	#			pragma comment(lib, "ZLib_"_LIB_CPLVERNUM"_sd.lib")
	#			pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_sd.lib")
	#		else
	#			pragma comment(lib, "libAGG_"_LIB_CPLVERNUM"_s.lib")
	#			pragma comment(lib, "LibJPEG_"_LIB_CPLVERNUM"_s.lib")
	#			pragma comment(lib, "ZLib_"_LIB_CPLVERNUM"_s.lib")
	#			pragma comment(lib, "LibPNG_"_LIB_CPLVERNUM"_s.lib")
	#		endif
	#	endif
	#endif


	#ifdef USE_GRAPHICSKIT_DLL
	//	using dynamic link library
	#	ifdef _DEBUG
	#		pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM"_d.lib")
	#	else
	#		pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM".lib")
	#	endif
	#elif defined USE_GRAPHICSKIT_LIB
	//	using statically linked library
	#	ifdef VCF_STATIC_CRT
	#		ifdef _DEBUG
	#			pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM"_scrtd.lib")
	#		else
	#			pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM"_scrt.lib")
	#		endif
	#	else
	#		ifdef _DEBUG
	#			pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM"_sd.lib")
	#		else
	#			pragma comment(lib, "GraphicsKit_"_LIB_CPLVERNUM"_s.lib")
	#		endif
	#	endif	
	#else
	//	creating the static or dynamic link library
	#endif // GRAPHICSKIT_LIB

#endif //VCF_MSC


#endif //VCF_USE_ALLIN1_DLL/LIB


#endif
// VCF_DISABLE_PRAGMA_LINKING


#endif // _VCF_GRAPHICSKITSELECTLIB_H__

/**
$Id$
*/
