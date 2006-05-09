//GTKControlContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKControl.h"
#include "vcf/ApplicationKit/GTKControlContext.h"


using namespace VCF;

GTKControlContext::GTKControlContext( ControlPeer* controlPeer )
{
	GTKContext::init();
}

GTKControlContext::~GTKControlContext()
{
}

void GTKControlContext::setContext( GraphicsContext* context )
{
	GTKContext::setContext ( context );
	owningControlCtx_ = ( ControlGraphicsContext* ) ( context );
}

Control* GTKControlContext::getOwningControl()
{
	Control * result = NULL;

	if ( NULL != owningControlCtx_ ) {
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void GTKControlContext::checkHandle()
{
	GTKContext::checkHandle();
}

void GTKControlContext::releaseHandle()
{
	GTKContext::releaseHandle();
}


/**
$Id$
*/
