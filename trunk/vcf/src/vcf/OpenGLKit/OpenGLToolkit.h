#ifndef _VCF_OPENGLTOOLKIT_H__
#define _VCF_OPENGLTOOLKIT_H__
//OpenGLToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class OpenGLPeer;

class GraphicsContext;

class OPENGLKIT_API OpenGLToolkit{
public:
	static OpenGLPeer* createOpenGLPeer(GraphicsContext *context);
};

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


#endif // _VCF_OPENGLTOOLKIT_H__


