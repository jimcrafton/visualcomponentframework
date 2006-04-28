#ifndef _VCF_WIN32HTMLBROWSERSELECTLIB_H__
#define _VCF_WIN32HTMLBROWSERSELECTLIB_H__
//Win32HTMLBrowserSelectLib.h

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
#   ifdef __BORLANDC__
#   define _LIB_CPLVERNUM "bcc"
#   endif
#	ifdef __MWERKS__
#	define _LIB_CPLVERNUM "cw"
#	endif
#	ifdef __MINGW32__
#	define _LIB_CPLVERNUM "mingw"
#	endif
# endif


// We don't need any of this if we've disabled pragma linking
#ifndef VCF_DISABLE_PRAGMA_LINKING
#   ifdef _DEBUG
#       define WIN32HTMLBROWSER_DYNLIB		"Win32HTMLBrowser_"_LIB_CPLVERNUM"_d.dll"
#   else
#       define WIN32HTMLBROWSER_DYNLIB		"Win32HTMLBrowser_"_LIB_CPLVERNUM".dll"
#   endif
#else
#   define STRINGIZE(lex) #lex
#   define STRINGIZE2(lex) STRINGIZE(lex)
#   define WIN32HTMLBROWSER_DYNLIB STRINGIZE2(WIN32HTMLBROWSER_DYNLIB_UNQUOTED)
#endif



#ifdef WIN32HTMLBROWSER_DLL
	#if defined(WIN32HTMLBROWSER_EXPORTS)
		#define WIN32HTMLBROWSER_API __declspec(dllexport)
		#define WIN32HTMLBROWSER_EXPIMP_TEMPLATE
	#else
		#define WIN32HTMLBROWSER_API __declspec(dllimport)
		#define WIN32HTMLBROWSER_EXPIMP_TEMPLATE extern
	#endif
#else
	#define WIN32HTMLBROWSER_API
#endif //WIN32HTMLBROWSER_DLL


// does not preload the library if defined
#ifndef RUNTIME_LOADLIBRARY



#ifdef USE_WIN32HTMLBROWSER_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_WIN32HTMLBROWSER_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "Win32HTMLBrowser_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // WIN32HTMLBROWSER_LIB

#endif // RUNTIME_LOADLIBRARY


#endif // _VCF_WIN32HTMLBROWSERSELECTLIB_H__

/**
$Id$
*/
