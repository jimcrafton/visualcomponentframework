#ifndef _VCF_OPENGLCONTEXT_H__
#define _VCF_OPENGLCONTEXT_H__
//OpenGLContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;

class OpenGLPeer;

class OPENGLKIT_API OpenGLContext {
public:
	OpenGLContext ( Control* control );

	virtual ~OpenGLContext();

	void initGL( GraphicsContext * context );

	void init();

	void swapBuffers();

	void makeCurrent();

	void shareWith( OpenGLContext* ctx );
private:
	OpenGLPeer* glPeer_;
};

}; //end of namespace VCF


#endif // _VCF_OPENGLCONTEXT_H__

/**
$Id: OpenGLContext.h 2654 2006-04-28 17:31:05Z kdmix $
*/
