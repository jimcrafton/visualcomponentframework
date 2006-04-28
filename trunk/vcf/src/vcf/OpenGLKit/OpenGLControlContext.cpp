//OpenGLControlContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"


using namespace VCF;

OpenGLControlContext::OpenGLControlContext( Control* control ):
	ControlGraphicsContext( control )
{
	this->init();
}

OpenGLControlContext::~OpenGLControlContext()
{
	if ( NULL != glPeer_ ){
		delete glPeer_;
		glPeer_ = NULL;
	}
}

void OpenGLControlContext::initGL()
{
	glPeer_->initGL();
}

void OpenGLControlContext::init()
{
	glPeer_ = OpenGLToolkit::createOpenGLPeer( this, dynamic_cast<OpenGLControl*>(getOwningControl()) );
}

void OpenGLControlContext::swapBuffers()
{
	glPeer_->swapBuffers();
}

void OpenGLControlContext::makeCurrent()
{
	glPeer_->makeCurrent();
}


/**
$Id$
*/
