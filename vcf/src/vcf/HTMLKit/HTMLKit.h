#ifndef _VCF_HTMLKIT_H__
#define _VCF_HTMLKIT_H__
//HTMLKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ApplicationKit.h"



#ifdef USE_HTMLKIT_DLL
#	 ifndef HTMLKIT_DLL
#		define HTMLKIT_DLL
#	 endif
#endif

/**
Handle the extension based on the compiler
*/
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
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif


/**
All of this is here so that if we use this kit in our programs, all we
have to do is pull in this one file (HTMLKit.h) and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "USE_HTMLKIT_DLL" defined or "USE_HTMLKIT_LIB"
defined to use the DLL or static libraries.
*/
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_HTMLKIT_DLL
		// using dynamic link library
		#ifdef _DEBUG
			#pragma comment(lib, "HTMLKit_"_LIB_CPLVERNUM"_d.lib")
		#else
			#pragma comment(lib, "HTMLKit_"_LIB_CPLVERNUM".lib")
		#endif
	#elif defined USE_HTMLKIT_LIB
		// using statically linked library
		#ifdef _DEBUG
			#pragma comment(lib, "HTMLKit_"_LIB_CPLVERNUM"_sd.lib")
		#else
			#pragma comment(lib, "HTMLKit_"_LIB_CPLVERNUM"_s.lib")
		#endif
	#endif

	
	
#endif //_MSC_VER


#if defined(VCF_MINGW)
	#ifdef HTMLKIT_DLL
	#	if defined(HTMLKIT_EXPORTS)
	#		define HTMLKIT_API __declspec(dllexport)
	#	else
	#		define HTMLKIT_API
	#	endif
	#else
	#	define HTMLKIT_API
	#endif
#else
	#ifdef HTMLKIT_DLL
		#if defined(HTMLKIT_EXPORTS)
			#define HTMLKIT_API __declspec(dllexport)
		#else
			#define HTMLKIT_API __declspec(dllimport)
		#endif
	#else
		#define HTMLKIT_API
	#endif //HTMLKIT_DLL	
#endif












#include "vcf/HTMLKit/HTMLBrowserPeer.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"
#include "vcf/HTMLKit/HTMLDOMElements.h"
#include "vcf/HTMLKit/HTMLToolkit.h"

namespace VCF {

/**
\class HTMLKit HTMLKit.h "vcf/HTMLKit/HTMLKit.h"
The HTMLKit is used to provide support for rendering 
HTML in a control (as well as connecting to the HTML resource
if it's not on the local machine), and for enumerating
the various HTML DOM elements. 
\par
For Win32 this is a very thin wrapper around 
Internet Explorer's IWebBrowser2 COM interface. The code 
as written provide the ability for a number of advanced
customizations for providing HTML support to your application.
@see HTMLBrowserControl
@see HTMLElement
@see HTMLDocument
@see HTMLElementCollection
*/
class  HTMLKIT_API HTMLKit {
public:
	/**
	Initialize the HTML Kit. Argc and argv may both
	be 0 and NULL respectively.
	*/
	static void init( int argc, char** argv );

	/**
	Terminate the HTML Kit.
	*/
	static void terminate();
};

};




#endif //_VCF_HTMLKIT_H__