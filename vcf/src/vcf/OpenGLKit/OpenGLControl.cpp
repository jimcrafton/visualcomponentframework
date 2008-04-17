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
	CustomControl( true )
{
	
	//context_ = NULL;
	//context_ = new OpenGLControlContext( this );

	setDoubleBuffered( false );
}

OpenGLControl::~OpenGLControl()
{

}

void OpenGLControl::paint(GraphicsContext * context)
{
//	Do NOT call CustomControl::paint because it results in flashing, possibly due to the
//	CustomControl clearing the space with the color, and then the OpenGLControl reclearing it.
//	CustomControl::paint( context );

	// These initialize the context, if necesary (check is in initGL), and then make it current
	OpenGLControlContext* glCtx = NULL;//dynamic_cast<OpenGLControlContext*>(context_);
	if ( NULL != glCtx ){
		glCtx->initGL();
		glCtx->makeCurrent();
	}
}

void OpenGLControl::swapBuffers(){
	OpenGLControlContext* glCtx = NULL;//dynamic_cast<OpenGLControlContext*>(context_);
	if ( NULL != glCtx ){
		glCtx->swapBuffers();
	}
}

void OpenGLControl::afterCreate( ComponentEvent* event )
{
	CustomControl::afterCreate( event );
}


/**
$Id$
*/
