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


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:48  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/03/12 22:01:46  ddiego
*doc updates.
*
*Revision 1.4.2.1  2005/11/02 04:38:23  obirsoy
*changes required for vc80 support.
*
*Revision 1.4  2005/07/09 23:15:17  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/06/28 21:39:27  pallindo
*Removed now reduncent OPENGLKIT_API definition.
*
*Revision 1.3  2004/12/01 04:31:45  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/11/01 18:17:02  marcelloptr
*minor change on automatic lib selection
*
*Revision 1.2.2.1  2004/10/27 22:42:47  augusto_roman
*Changed Win32 peer to create GL Rendering Context (RC) based off of the Win32 window handle of the control instead of the paintDC.  Also enforced error checking. - aroman
*
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/30 17:31:22  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.7  2004/07/21 20:18:39  pallindo
*Removed some unused files, and cleaned up the interface to the OpenGLControl
*
*Revision 1.1.2.6  2004/07/06 20:09:43  pallindo
*Added missing "defined" in lib selection code
*
*Revision 1.1.2.5  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


#endif // _VCF_OPENGLKIT_H__


