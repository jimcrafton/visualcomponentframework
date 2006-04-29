//X11ControlContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Control.h"
#include "vcf/ApplicationKit/X11ControlContext.h"


using namespace VCF;

X11ControlContext::X11ControlContext( ControlPeer* controlPeer )
{
	X11Context::init();
}

X11ControlContext::~X11ControlContext()
{

}


void X11ControlContext::setContext( GraphicsContext* context )
{
	X11Context::setContext ( context );
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* X11ControlContext::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void X11ControlContext::checkHandle()
{
	X11Context::checkHandle();
}

void X11ControlContext::releaseHandle()
{
	X11Context::releaseHandle();
}


/**
$Id$
*/
