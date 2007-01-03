
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBControlContextPeer.h"

using namespace VCF;

XCBControlContextPeer::XCBControlContextPeer( ControlPeer* controlPeer )
{
	XCBContextPeer::init();
}

XCBControlContextPeer::~XCBControlContextPeer()
{
}

void XCBControlContextPeer::setContext( GraphicsContext* context )
{
	XCBContextPeer::setContext ( context );
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* XCBControlContextPeer::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void XCBControlContextPeer::checkHandle()
{
	XCBContextPeer::checkHandle();
}

void XCBControlContextPeer::releaseHandle()
{
	XCBContextPeer::releaseHandle();
}

/**
$Id$
*/

