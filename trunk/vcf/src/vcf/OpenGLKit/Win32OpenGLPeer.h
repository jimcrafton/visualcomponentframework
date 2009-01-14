#ifndef _VCF_WIN32OPENGLPEER_H__
#define _VCF_WIN32OPENGLPEER_H__
//Win32OpenGLPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class OPENGLKIT_API GraphicsContext;

class OPENGLKIT_API Win32OpenGLPeer : public OpenGLPeer{

public:
	Win32OpenGLPeer( Control* owningControl );

	virtual ~Win32OpenGLPeer();

	virtual void initGL( GraphicsContext * context );

	virtual void initGL( Control* control );

	virtual void swapBuffers();

	virtual void makeCurrent();
private:
	Control* owningControl_;
	HGLRC hrc_;
	bool isInitialized_;
};

}; //end of namespace VCF


#endif // _VCF_WIN32OPENGLPEER_H__

/**
$Id$
*/
