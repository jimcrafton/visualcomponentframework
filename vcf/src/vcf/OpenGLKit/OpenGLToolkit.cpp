//OpenGLToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"

#ifdef WIN32
#	include "vcf/OpenGLKit/Win32OpenGLPeer.h"
#endif

using namespace VCF;

OpenGLPeer *OpenGLToolkit::createOpenGLPeer(GraphicsContext *context){
#ifdef WIN32
	return new Win32OpenGLPeer(context);
#else
	throw BasicException("OpenGLToolkit::createOpenGLPeer: Unsupported on this platform");
#endif
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


