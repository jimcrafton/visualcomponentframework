//OpenGLControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"
using namespace VCF;

OpenGLControl::OpenGLControl():
	CustomControl( true ),
	glContext_(NULL)
{
	glContext_ = new OpenGLContext( this );

	setDoubleBuffered( false );
}

OpenGLControl::~OpenGLControl()
{
	delete glContext_;
}

void OpenGLControl::paint(GraphicsContext * context)
{
//	Do NOT call CustomControl::paint because it results in flashing, possibly due to the
//	CustomControl clearing the space with the color, and then the OpenGLControl reclearing it.
//	CustomControl::paint( context );

	// These initialize the context, if necesary (check is in initGL), and then make it current
	
	if ( NULL != glContext_ ){
		glContext_->initGL(context);
		glContext_->makeCurrent();
	}
}

void OpenGLControl::swapBuffers(){
	if ( NULL != glContext_ ){
		glContext_->swapBuffers();
	}
}

void OpenGLControl::makeCurrent()
{
	if ( NULL != glContext_ ){
		glContext_->makeCurrent();
	}
}

void OpenGLControl::shareWith( OpenGLControl* control )
{
	if ( NULL != glContext_ ){
		glContext_->shareWith(control->glContext_);
	}
}

/**
$Id$
*/
