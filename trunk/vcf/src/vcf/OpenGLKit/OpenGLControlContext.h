#ifndef _VCF_OPENGLCONTROLCONTEXT_H__
#define _VCF_OPENGLCONTROLCONTEXT_H__
//OpenGLControlContext.h

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

class OPENGLKIT_API OpenGLControlContext : public ControlGraphicsContext{
public:
	/**
	*Creates a context based on the component. The context is attached to the component
	*for the duration of it's lifetime.
	*/
	OpenGLControlContext( Control* control );

	virtual ~OpenGLControlContext();

	void initGL();

	void init();

	void swapBuffers();

	void makeCurrent();
private:
	OpenGLPeer* glPeer_;
};

}; //end of namespace VCF


#endif // _VCF_OPENGLCONTROLCONTEXT_H__

/**
$Id$
*/
