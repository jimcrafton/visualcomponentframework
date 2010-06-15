//OpenGLContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"


using namespace VCF;

OpenGLContext::OpenGLContext( Control* control )	
{
	glPeer_ = OpenGLToolkit::createOpenGLPeer( dynamic_cast<OpenGLControl*>(control) );
}

OpenGLContext::~OpenGLContext()
{
	if ( NULL != glPeer_ ){
		delete glPeer_;
		glPeer_ = NULL;
	}
}

void OpenGLContext::initGL( GraphicsContext * context )
{
	glPeer_->initGL(context);
}


void OpenGLContext::swapBuffers()
{
	glPeer_->swapBuffers();
}

void OpenGLContext::makeCurrent()
{
	glPeer_->makeCurrent();
}

void OpenGLContext::shareWith( OpenGLContext* ctx )
{
	glPeer_->shareWith(ctx->glPeer_);
}


/**
$Id: OpenGLContext.cpp 2654 2006-04-28 17:31:05Z kdmix $
*/
