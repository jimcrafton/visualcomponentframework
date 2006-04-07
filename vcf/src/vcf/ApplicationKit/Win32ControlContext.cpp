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
			BOOL result = ::SetViewportOrgEx( dc_, (long)originX, (long)originY, &oldOrigin );
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
			BOOL result = ::SetViewportOrgEx( dc_, (long)oldOrigin_.x_, (long)oldOrigin_.y_, NULL );
			if ( FALSE == result ) {
				throw RuntimeException( MAKE_ERROR_MSG_2("SetViewportOrgEx() failed for win32 Context") );
			}
		}


		::ReleaseDC( (HWND)peer->getHandleID(), dc_ );
		dc_ = NULL;
	}	
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.1  2006/03/01 04:34:56  ddiego
*fixed tab display to use themes api.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/11/07 19:32:19  marcelloptr
*more documentation
*
*Revision 1.2.2.1  2004/10/31 15:32:05  ddiego
*fixed a bug in the way Win32ControlContext::releaseHandle() worked that was causing a problem in Win32Font::getPointSize().
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.16  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.15.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.15  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:12:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.13.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.13.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.13  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:52:28  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.12.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


