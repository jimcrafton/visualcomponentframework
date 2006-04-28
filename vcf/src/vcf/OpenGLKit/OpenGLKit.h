#ifndef _VCF_OPENGLKIT_H__
#define _VCF_OPENGLKIT_H__
//OpenGLKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
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
have to do is pull in this one file (OpenGLKit.h) and we'll automatically
link to the correct library! This does mean that our app that uses this
kit needs to have either "USE_OPENGLKIT_DLL" defined or "USE_OPENGLKIT_LIB"
defined to use the DLL or static libraries.
*/
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_OPENGLKIT_DLL
		// using dynamic link library
		#ifdef _DEBUG
			#pragma comment(lib, "OpenGLKit_"_LIB_CPLVERNUM"_d.lib")
		#else
			#pragma comment(lib, "OpenGLKit_"_LIB_CPLVERNUM".lib")
		#endif
	#elif defined USE_OPENGLKIT_LIB
		// using statically linked library
		#ifdef _DEBUG
			#pragma comment(lib, "OpenGLKit_"_LIB_CPLVERNUM"_sd.lib")
		#else
			#pragma comment(lib, "OpenGLKit_"_LIB_CPLVERNUM"_s.lib")
		#endif
	#endif

	//make sure to link to the open gl libs
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")
#endif //_MSC_VER


#include "vcf/ApplicationKit/ApplicationKit.h"

#include "vcf/OpenGLKit/OpenGLPeer.h"
#include "vcf/OpenGLKit/OpenGLControlContext.h"
#include "vcf/OpenGLKit/OpenGLControl.h"


namespace VCF {

/**
\par
 The OpenGLKit is used to initialize (and terminate)
the OpenGL system on the OS the vCF is being run on.
\par
At the moment it doesn't need to be called, but this 
will change in upcoming releases.
*/
class  OPENGLKIT_API OpenGLKit {
public:
	/**
	Initializes the OpenGLKit
	*/
	static void init( int argc, char** argv ){;}

	/**
	Terminates the OpenGLKit, and frees any resources that were 
	allocated by the init() call.
	*/
	static void terminate(){;}
};

};


#endif // _VCF_OPENGLKIT_H__

/**
$Id$
*/
