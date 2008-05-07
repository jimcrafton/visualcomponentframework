
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"


#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"

#if defined(VCF_WIN)
#include "vcf/FoundationKit/Win32ResourceBundle.h"
#endif 


#include "AggControlContextPeer.h"

using namespace VCF;

AggControlContextPeer::AggControlContextPeer( ControlPeer* controlPeer )
{
	AggContextPeer::init();
}

AggControlContextPeer::~AggControlContextPeer()
{
}

void AggControlContextPeer::setContext( GraphicsContext* context )
{
	AggContextPeer::setContext ( context );
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* AggControlContextPeer::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void AggControlContextPeer::checkHandle()
{
	AggContextPeer::checkHandle();
}

void AggControlContextPeer::releaseHandle()
{
	AggContextPeer::releaseHandle();
}

/**
$Id$
*/

