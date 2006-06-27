//Win32ControlContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "vcf/ApplicationKit/Win32ControlContext.h"

using namespace VCF;

Win32ControlContext::Win32ControlContext( ControlPeer* controlPeer )
{
	Win32Context::init();
	if ( NULL == controlPeer ){
		//throw exception
	}

	//dc_ = GetDC( (HWND)controlPeer->getHandleID() );
}

Win32ControlContext::~Win32ControlContext()
{

}

void Win32ControlContext::setContext( GraphicsContext* context )
{
	Win32Context::setContext ( context );
	owningControlCtx_  = (ControlGraphicsContext*)( context );
}

Control* Win32ControlContext::getOwningControl()
{
	Control* result = NULL;

	if ( NULL != owningControlCtx_ ){
		result = owningControlCtx_->getOwningControl();
	}
	return result;
}

void Win32ControlContext::checkHandle()
{
	if ( NULL != owningControlCtx_->getOwningControl() ){
		Control* owningControl = owningControlCtx_->getOwningControl();
		ControlPeer* peer = owningControl->getPeer();
		dc_ = ::GetDC( (HWND)peer->getHandleID() );

		if ( NULL == dc_ ){
			//throw exception !!!!!!
			throw RuntimeException( MAKE_ERROR_MSG_2("Win32 Context has NULL Device Context") );
		}

		//check to see if we need to offset the origin
		if ( true == owningControl->isLightWeight() ) {
			Rect bounds = owningControl->getBounds();
			double originX = bounds.left_;
			double originY = bounds.top_;
			POINT oldOrigin = {0,0};
			BOOL result = ::SetViewportOrgEx( dc_, (int32)originX, (int32)originY, &oldOrigin );
			if ( FALSE == result ) {
				throw RuntimeException( MAKE_ERROR_MSG_2("SetViewportOrgEx() failed for win32 Context") );
			}
			oldOrigin_.x_ = oldOrigin.x;
			oldOrigin_.y_ = oldOrigin.y;
		}
	}
}

void Win32ControlContext::releaseHandle()
{
	Win32Context::releaseHandle();

	if ( (NULL != owningControlCtx_->getOwningControl()) && (NULL != dc_) ){
		Control* owningControl = owningControlCtx_->getOwningControl();
		ControlPeer* peer = owningControl->getPeer();
		if ( true == owningControl->isLightWeight() ) {
			BOOL result = ::SetViewportOrgEx( dc_, (int32)oldOrigin_.x_, (int32)oldOrigin_.y_, NULL );
			if ( FALSE == result ) {
				throw RuntimeException( MAKE_ERROR_MSG_2("SetViewportOrgEx() failed for win32 Context") );
			}
		}


		::ReleaseDC( (HWND)peer->getHandleID(), dc_ );
		dc_ = NULL;
	}	
}


/**
$Id$
*/
