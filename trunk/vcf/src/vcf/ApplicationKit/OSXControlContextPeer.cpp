//OSXControlContextPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXControlContextPeer.h"


using namespace VCF;

OSXControlContextPeer::OSXControlContextPeer( ControlPeer* controlPeer )
{
	OSXContext::init();
}

OSXControlContextPeer::~OSXControlContextPeer()
{

}


void OSXControlContextPeer::setContext( GraphicsContext* context )
{
	OSXContext::setContext ( context );
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* OSXControlContextPeer::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void OSXControlContextPeer::checkHandle()
{
	OSXContext::checkHandle();
}

void OSXControlContextPeer::releaseHandle()
{
	OSXContext::releaseHandle();
}


/**
$Id$
*/
