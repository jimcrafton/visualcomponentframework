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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:44  ddiego
*initial OSX ApplicationKit port checkin
*
*/


