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



/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:34:57  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/11/02 04:38:23  obirsoy
*changes required for vc80 support.
*
*Revision 1.2  2004/08/07 02:48:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:40:17  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/06/29 03:17:16  marcelloptr
*minor fixes on import/export library macros
*
*Revision 1.1.2.1  2004/04/28 00:27:44  ddiego
*migration towards new directory structure
*
*Revision 1.6.2.1  2004/04/07 21:56:52  marcelloptr
*some changes related to _LIB_CPLVERNUM
*
*Revision 1.6  2004/03/03 09:40:12  augusto_roman
*Added support for the Intel Compiler v7.1.  Mostly added new project files (icl7), plus support in select lib header files.  Also fixed GraphicsToolKit::getAvailableImageTypes
*
*Revision 1.5  2003/12/18 05:15:47  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.1  2003/08/23 19:09:29  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.4  2003/05/17 20:35:52  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:12  marcelloptr
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
*Revision 1.1.2.1  2002/07/02 06:49:59  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*
*/


#endif	//_IMAGEFORMATS_SELECT_LIB_H__


