#ifndef _FREEIMAGE_SELECT_LIB_H__
#define _FREEIMAGE_SELECT_LIB_H__
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
#   if (_MSC_VER >= 1310)
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



#ifdef USE_FREEIMAGE_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "FreeImage_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "FreeImage_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_FREEIMAGE_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "FreeImage_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "FreeImage_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // FREEIMAGE_LIB


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



/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:48:33  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:32:25  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/06/29 03:17:40  marcelloptr
*minor fixes on import/export library macros
*
*Revision 1.1.2.1  2004/04/28 00:27:45  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/07 21:58:20  marcelloptr
*some changes related to _LIB_CPLVERNUM
*
*Revision 1.4  2004/03/03 09:40:26  augusto_roman
*Added support for the Intel Compiler v7.1.  Mostly added new project files (icl7), plus support in select lib header files.  Also fixed GraphicsToolKit::getAvailableImageTypes
*
*Revision 1.3  2003/12/18 05:16:07  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.1  2003/08/23 19:09:44  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.2  2003/08/09 02:56:50  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.1  2003/05/20 02:57:09  ddiego
*added the pcre and FreeImage libraries to the vcf/thirdparty/common directory
*
*Revision 1.4  2003/05/17 20:35:52  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:13  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:20  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.8.1  2002/12/27 23:03:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/09/12 03:25:52  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/07/02 06:50:00  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*
*/


#endif	//_FREEIMAGE_SELECT_LIB_H__


