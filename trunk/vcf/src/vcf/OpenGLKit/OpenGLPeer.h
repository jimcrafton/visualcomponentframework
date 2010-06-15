#ifndef _VCF_OPENGLPEER_H__
#define _VCF_OPENGLPEER_H__
//OpenGLPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class  OPENGLKIT_API OpenGLPeer {

public:
	OpenGLPeer(){};

	virtual ~OpenGLPeer(){};

	virtual void initGL( GraphicsContext * context ) = 0;

	virtual void initGL( Control* control ) = 0;

	virtual void swapBuffers() = 0;

	virtual void makeCurrent() = 0;

	virtual void shareWith( OpenGLPeer* peer ) = 0;
};

}; //end of namespace VCF


#endif // _VCF_OPENGLPEER_H__

/**
$Id$
*/
