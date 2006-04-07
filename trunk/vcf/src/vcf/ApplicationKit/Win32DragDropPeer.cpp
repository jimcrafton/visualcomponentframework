//Win32DragDropPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Win32DragDropPeer.h"
#include "vcf/ApplicationKit/Win32COMUtils.h"

using namespace VCF;
using namespace VCFCOM;

Win32DragDropPeer::Win32DragDropPeer()
{
	comDragSrc_ = new COMDragSource(this);
	dataObj_ = new VCFCOM::COMDataObject();
}

Win32DragDropPeer::~Win32DragDropPeer()
{
	delete comDragSrc_;
}

DragActionType Win32DragDropPeer::startDragDrop( DataObject* cdo )
{

	clipDataObj_ = cdo;

	dataObj_->setDataObject( clipDataObj_ );

	dragDropEffect_ = 0;

	dragDropResult_ = ::DoDragDrop( dataObj_, comDragSrc_,
									COMUtils::translateActionType( dragSrc_->getActionType() ),
									&dragDropEffect_ );


    DragSourceEvent eventEnd(dragSrc_, clipDataObj_);
	eventEnd.setType( DragSource::DRAG_END );

	dragSrc_->SourceEnd.fireEvent( &eventEnd );

	if (dragDropResult_ == DRAGDROP_S_DROP) {
	    DragSourceEvent eventDropped(dragSrc_,  clipDataObj_);
		eventDropped.setType( DragSource::DRAG_DROPPED );
		dragSrc_->SourceDropped.fireEvent( &eventDropped );
	}

	return (DragActionType) dragDropResult_;

}

void Win32DragDropPeer::setActionType(const VCF::DragActionType& actionType )
{
	actionType_ = actionType;
}


void Win32DragDropPeer::setDragSource(VCF::DragSource* DragSrc)
{
	dragSrc_ = DragSrc;
}

VCF::DragSource* Win32DragDropPeer::getDragSource()
{
	return dragSrc_;
}


HRESULT Win32DragDropPeer::GiveFeedback( DWORD dwEffect )
{
	DragSourceEvent event(dragSrc_, clipDataObj_);
	event.setType( DragSource::DRAG_GIVEFEEDBACK );

	dragSrc_->SourceGiveFeedback.fireEvent( &event );

	/**
	NOTE!!!
	To customize the cursor we should make some sort of call here
	and return NOT DRAGDROP_S_USEDEFAULTCURSORS, but just S_OK
	*/

	return DRAGDROP_S_USEDEFAULTCURSORS;
}

HRESULT Win32DragDropPeer::QueryContinueDrag( BOOL fEscapePressed, DWORD grfKeyState )
{
	DragSourceEvent event(dragSrc_, clipDataObj_);
	event.setType( DragSource::DRAG_CANCONTINUE );

    dragSrc_->SourceCanContinueDragOp.fireEvent( &event );

	HRESULT result = NO_ERROR;
	if ( true == ( 0 != fEscapePressed ) ){
		result =  DRAGDROP_S_CANCEL ;
	}

	if ( true != (grfKeyState & MK_LBUTTON) ) {
		result = DRAGDROP_S_DROP;
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/02/19 19:38:12  ddiego
*adjusted some comet code to make it compile again. renamed some of the COM utility files to have a Win32 prefix.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


