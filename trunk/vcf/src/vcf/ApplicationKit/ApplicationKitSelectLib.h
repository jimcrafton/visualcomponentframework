#ifndef _VCF_APPLICATIONKITSELECTLIB_H__
#define _VCF_APPLICATIONKITSELECTLIB_H__
//ApplicationKitSelectLib.h

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

//If using the All-in-1 library, then this task has already been done
#if !defined(VCF_USE_ALLIN1_DLL) && !defined(VCF_USE_ALLIN1_LIB)

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
#   ifdef __BORLANDC__
#   define _LIB_CPLVERNUM "bcc"
#   endif
# endif


/**
All of this is here so that if we use this kit in our programs, all we
have to do is pull in this one file (OpenGLKit.h) and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "USE_OPENGLKIT_DLL" defined or "USE_OPENGLKIT_LIB"
defined to use the DLL or static libraries.
*/
#if defined(_MSC_VER) || defined(__BORLANDC__)

	#ifdef USE_APPLICATIONKIT_DLL
	//	using dynamic link library
	#	ifdef _DEBUG
	#		pragma comment(lib, "ApplicationKit_"_LIB_CPLVERNUM"_d.lib")
	#	else
	#		pragma comment(lib, "ApplicationKit_"_LIB_CPLVERNUM".lib")
	#	endif
	#elif defined USE_APPLICATIONKIT_LIB
	//	using statically linked library
	#	ifdef _DEBUG
	#		pragma comment(lib, "ApplicationKit_"_LIB_CPLVERNUM"_sd.lib")
	#	else
	#		pragma comment(lib, "ApplicationKit_"_LIB_CPLVERNUM"_s.lib")
	#	endif
	#else
	//	creating the static or dynamic link library
	#endif // APPLICATIONKIT_LIB

#endif //_MSC_VER

#endif //VCF_USE_ALLIN1_DLL/LIB
/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/04/11 17:04:50  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/01 18:16:55  marcelloptr
*minor change on automatic lib selection
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/30 17:27:13  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.4  2004/06/29 03:17:40  marcelloptr
*minor fixes on import/export library macros
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.7.2.3  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7.2.2  2004/04/07 21:58:11  marcelloptr
*some changes related to _LIB_CPLVERNUM
*
*Revision 1.7.2.1  2004/04/07 03:25:34  ddiego
*fixed Win32HTMLBrowser ATL assert bug. The problem was a minor
*to teh ATL CComModule.Init() function. In VC6 version it just needed
*an HINSTANCE and and object map, in VC7 it also needs a GUID for the lib.
*Of course this is helpfully set to an INVALID default parameter, which is
*nice, I suppose.
*
*Revision 1.7  2004/03/03 09:40:25  augusto_roman
*Added support for the Intel Compiler v7.1.  Mostly added new project files (icl7), plus support in select lib header files.  Also fixed GraphicsToolKit::getAvailableImageTypes
*
*Revision 1.6  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.1  2003/08/23 02:01:23  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.5  2003/08/09 02:56:42  ddiego
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
*Revision 1.4.2.1  2003/06/01 16:42:23  ddiego
*further GTK support added
*
*Revision 1.4  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.8.1  2002/12/27 23:04:29  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/07/02 06:50:00  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*
*/


#endif // _VCF_APPLICATIONKITSELECTLIB_H__


