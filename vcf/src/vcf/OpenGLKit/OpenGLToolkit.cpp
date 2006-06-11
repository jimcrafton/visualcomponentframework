//OpenGLToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"

#ifdef VCF_WIN
#	include "vcf/OpenGLKit/Win32OpenGLPeer.h"
#endif

using namespace VCF;

OpenGLPeer *OpenGLToolkit::createOpenGLPeer(GraphicsContext *context, OpenGLControl* owningControl){
#ifdef VCF_WIN
	return new Win32OpenGLPeer(context,owningControl);
#else
	throw BasicException("OpenGLToolkit::createOpenGLPeer: Unsupported on this platform");
#endif
}


/**
$Id$
*/
