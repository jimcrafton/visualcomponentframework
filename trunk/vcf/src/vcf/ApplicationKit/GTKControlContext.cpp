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
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* GTKControlContext::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.5  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


