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

	DragActionType result = daNone;

	clipDataObj_ = cdo;

	dataObj_->setDataObject( clipDataObj_ );

	dragDropEffect_ = 0;

	HRESULT hr = ::DoDragDrop( dataObj_, comDragSrc_,
									DROPEFFECT_COPY | DROPEFFECT_MOVE | DROPEFFECT_LINK,
									&dragDropEffect_ );


    DragSourceEvent eventEnd(dragSrc_, clipDataObj_);
	eventEnd.setType( DragSource::DRAG_END );

	dragSrc_->SourceEnd( &eventEnd );

	if (hr == DRAGDROP_S_DROP) {
	    DragSourceEvent eventDropped(dragSrc_,  clipDataObj_);
		eventDropped.setType( DragSource::DRAG_DROPPED );
		dragSrc_->SourceDropped( &eventDropped );


		if ( dragDropEffect_ & DROPEFFECT_COPY ) {
			result = daCopy;
		}

		if ( dragDropEffect_ & DROPEFFECT_MOVE ) {
			result = daMove;
		}

		if ( dragDropEffect_ & DROPEFFECT_LINK ) {
			result = daLink;
		}

		
	}

	return result;

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

	::POINT pt = {0};
	::GetCursorPos(&pt);
	event.setPoint( Point(pt.x,pt.y) );

	dragSrc_->SourceGiveFeedback( &event );

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

    dragSrc_->SourceCanContinueDragOp( &event );

	HRESULT result = S_OK;
	if ( fEscapePressed ){
		result =  DRAGDROP_S_CANCEL ;
	}

	if ( !(grfKeyState & MK_LBUTTON) ) {
		result = DRAGDROP_S_DROP;
	}

	return result;
}


/**
$Id$
*/
