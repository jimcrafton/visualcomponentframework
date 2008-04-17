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

/**
The OpenGLToolkit is a singleton class
that creates instances of a OpenGLPeer 
specific to the windowing system the
toolkit is running on. 
*/
class OPENGLKIT_API OpenGLToolkit{
public:
	/**
	Creates an instance of the OpenGLPeer. The framework calls this for you,
	you should never need to call this directly.
	*/
	static OpenGLPeer* createOpenGLPeer( OpenGLControl* owningControl);
};

}


#endif // _VCF_OPENGLTOOLKIT_H__

/**
$Id$
*/
