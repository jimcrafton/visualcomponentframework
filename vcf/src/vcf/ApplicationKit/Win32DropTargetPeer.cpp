//Win32DropTargetPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32DropTargetPeer.h"
#include "vcf/ApplicationKit/Win32COMUtils.h"

using namespace VCF;
using namespace VCFCOM;

Win32DropTargetPeer::Win32DropTargetPeer():
	currentDataObj_(NULL),
	dropTarget_(NULL)

{
	comDropTarget_ = new COMDropTarget(this);
}

Win32DropTargetPeer::~Win32DropTargetPeer()
{
	delete comDropTarget_;
}

void Win32DropTargetPeer::registerTarget( Control* control )
{


	if ( NULL != control ){
		ControlPeer* peer = control->getPeer();
		if ( NULL != peer ){
			HWND hwnd = (HWND)peer->getHandleID();
			if ( NULL != hwnd ){

				HRESULT result = RegisterDragDrop( hwnd, comDropTarget_ );
				switch ( result ){
					case S_OK :{
						StringUtils::trace("RegisterDragDrop returned S_OK\n");
					}
					break;

					case DRAGDROP_E_INVALIDHWND :{
						StringUtils::trace("RegisterDragDrop returned DRAGDROP_E_INVALIDHWND\n");
					}
					break;

					case DRAGDROP_E_ALREADYREGISTERED:{
						StringUtils::trace("RegisterDragDrop returned DRAGDROP_E_ALREADYREGISTERED\n");
					}
					break;

					default :{
						StringUtils::trace("RegisterDragDrop returned some other error\n");
					}
					break;
				}
			}
		}
	}
}

void Win32DropTargetPeer::unregisterTarget( Control* control )
{
	if ( NULL != control ){
		ControlPeer* peer = control->getPeer();
		if ( NULL != peer ){
			HWND hwnd = (HWND)peer->getHandleID();
			if ( NULL != hwnd ){
				RevokeDragDrop( hwnd );
			}
		}
	}
}

VCF::DropTarget* Win32DropTargetPeer::getDropTarget()
{
	return dropTarget_;
}

void Win32DropTargetPeer::setDropTarget( VCF::DropTarget* dropTarget )
{
	dropTarget_ = dropTarget;
}


HRESULT Win32DropTargetPeer::DragEnter( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect )
{
	HRESULT result = E_FAIL;

	if ( NULL != currentDataObj_ ) {
		delete currentDataObj_;
		currentDataObj_ = NULL;
	}

	dataObject_=NULL;

    if ( keyState & MK_SHIFT ) {
	   *effect = DROPEFFECT_MOVE;
	}
	else if ( keyState & MK_ALT ) {
	   *effect = DROPEFFECT_LINK;
	}
	else if ( keyState & MK_CONTROL ) {
	   *effect = DROPEFFECT_COPY;
	}

    dataObject_ = dataObject;

	if ( NULL != dataObject_ ){
		dataObject_->AddRef();
	}

	currentDataObj_ = new VCF::DataObject();

	IEnumFORMATETC* enumFMT = NULL;

	HRESULT hr = dataObject_->EnumFormatEtc( DATADIR_GET, &enumFMT );
	if ( (SUCCEEDED(hr)) && (NULL != enumFMT) ){
		FORMATETC fmtETC;
		memset( &fmtETC, 0, sizeof(FORMATETC) );
		ULONG fetched = 0;

		hr = enumFMT->Next( 1, &fmtETC, &fetched );

		while ( (1 == fetched) && (SUCCEEDED(hr)) ){
			String dataType = VCFCOM::COMUtils::translateWin32ClipboardFormat(fmtETC);
			if ( !dataType.empty() ) {
				currentDataObj_->addSupportedDataType( dataType, NULL );
			}

			enumFMT->Next( 1, &fmtETC, &fetched );
		}
	}

	VCF::DropTargetEvent event( getDropTarget(), currentDataObj_ );

	if ( (*effect) & DROPEFFECT_NONE )  {
		event.setActionType( daNone );
	}
	else if ( (*effect) & DROPEFFECT_COPY )  {
		event.setActionType( daCopy );
	}
	else if ( (*effect) & DROPEFFECT_MOVE )  {
		event.setActionType( daMove );
	}
	else if ( (*effect) & DROPEFFECT_LINK )  {
		event.setActionType( daLink );
	}

	event.setType( DropTarget::DRAG_ENTERED );

	POINT pt = {point.x,point.y};
	::ScreenToClient( (HWND)getDropTarget()->getTarget()->getPeer()->getHandleID(),
					&pt );
	point.x = pt.x;
	point.y = pt.y;



	Point dropPt( point.x, point.y );

	event.setDropPoint( dropPt );


	getDropTarget()->handleEvent( &event );

	*effect = COMUtils::translateActionType( event.getAction() );

	if ( event.getAction() == daNone ) {
		result = E_FAIL;
		DragLeave();
	}
	else {
		result = NOERROR;
	}

	return result;
}

HRESULT Win32DropTargetPeer::DragOver( DWORD keyState, POINTL point, LPDWORD effect )
{
	HRESULT result = S_OK;

	if ( NULL == dataObject_ )
	{
        *effect=DROPEFFECT_NONE;
        result =  NOERROR;
	}

    //We can always drop; return effect flags based on keys.
	/*
    effect=DROPEFFECT_MOVE;
	*/

    if ( keyState & MK_SHIFT ) {
	   *effect = DROPEFFECT_MOVE;
	}
	else if ( keyState & MK_ALT ) {
	   *effect = DROPEFFECT_LINK;
	}
	else if ( keyState & MK_CONTROL ) {
	   *effect = DROPEFFECT_COPY;
	}

	VCF::DropTargetEvent event( getDropTarget(), currentDataObj_ );
	event.setType( DropTarget::DRAGGING_OVER );

	POINT pt = {point.x,point.y};
	::ScreenToClient( (HWND)getDropTarget()->getTarget()->getPeer()->getHandleID(),
					&pt );
	point.x = pt.x;
	point.y = pt.y;



	Point dropPt( point.x, point.y );

	event.setDropPoint( dropPt );

	if ( (*effect) & DROPEFFECT_NONE )  {
		event.setActionType( daNone );
	}
	else if ( (*effect) & DROPEFFECT_COPY )  {
		event.setActionType( daCopy );
	}
	else if ( (*effect) & DROPEFFECT_MOVE )  {
		event.setActionType( daMove );
	}
	else if ( (*effect) & DROPEFFECT_LINK )  {
		event.setActionType( daLink );
	}
	
	getDropTarget()->handleEvent( &event );

	

	*effect = COMUtils::translateActionType( event.getAction() );

	return result;
}

HRESULT Win32DropTargetPeer::DragLeave(void)
{
	HRESULT result = E_FAIL;

	VCF::DropTargetEvent event( getDropTarget(), NULL );
	event.setType( DropTarget::DRAG_LEFT );
	getDropTarget()->handleEvent( &event );


	if ( NULL != dataObject_ ){
		dataObject_->Release();
		dataObject_ = NULL;
	}

	if ( NULL != currentDataObj_ ) {
		delete currentDataObj_;
		currentDataObj_ = NULL;
	}


    result = NO_ERROR;

	return result;
}

HRESULT Win32DropTargetPeer::Drop( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect )
{
	HRESULT result = E_FAIL;

	if ( NULL != currentDataObj_ ) {
		delete currentDataObj_;
		currentDataObj_ = NULL;
	}

	if ( keyState & MK_SHIFT ) {
	   *effect = DROPEFFECT_MOVE;
	}
	else if ( keyState & MK_ALT ) {
	   *effect = DROPEFFECT_LINK;
	}
	else if ( keyState & MK_CONTROL ) {
	   *effect = DROPEFFECT_COPY;
	}

	/*
    *pdwEffect=DROPEFFECT_NONE;
	*/
    if ( NULL != dataObject_ ){

		DragLeave();

		dataObject_ = dataObject;
		dataObject_->AddRef();

		VCF::DropTarget* target = getDropTarget();
		uint32 size = 0;


		IEnumFORMATETC* enumFMT = NULL;

		result = dataObject_->EnumFormatEtc( DATADIR_GET, &enumFMT );
		if ( (SUCCEEDED(result)) && (NULL != enumFMT) ){


			FORMATETC fmtETC;
			memset( &fmtETC, 0, sizeof(FORMATETC) );
			ULONG fetched = 0;



			result = enumFMT->Next( 1, &fmtETC, &fetched );

			while ( (1 == fetched) && (SUCCEEDED(result)) ){
				String dataType = VCFCOM::COMUtils::translateWin32ClipboardFormat(fmtETC);
				if ( !dataType.empty() ) {
					if ( NULL == currentDataObj_ ) {
						currentDataObj_ = VCFCOM::COMUtils::getDataObjectFromOLEDataObject( dataType,
																		dataObject_,
																		&fmtETC );
					}
					else {
						Persistable* persistable = VCFCOM::COMUtils::getPersistableFromOLEDataObject(dataType,
																							dataObject_,
																							&fmtETC );
						currentDataObj_->addSupportedDataType( dataType, persistable );
					}
				}

				enumFMT->Next( 1, &fmtETC, &fetched );
			}

			VCF::DropTargetEvent event( target, currentDataObj_ );
			
			POINT pt = {point.x,point.y};
			::ScreenToClient( (HWND)getDropTarget()->getTarget()->getPeer()->getHandleID(),
				&pt );
			point.x = pt.x;
			point.y = pt.y;
			
			
			
			Point dropPt( point.x, point.y );
			
			event.setDropPoint( dropPt );
			
			event.setType( DropTarget::DRAG_DROPPED );


			if ( (*effect) & DROPEFFECT_NONE )  {
				event.setActionType( daNone );
			}
			else if ( (*effect) & DROPEFFECT_COPY )  {
				event.setActionType( daCopy );
			}
			else if ( (*effect) & DROPEFFECT_MOVE )  {
				event.setActionType( daMove );
			}
			else if ( (*effect) & DROPEFFECT_LINK )  {
				event.setActionType( daLink );
			}

			getDropTarget()->handleEvent( &event );

			*effect = COMUtils::translateActionType( event.getAction() );

			if ( NULL != currentDataObj_ ) {
				delete currentDataObj_;
				currentDataObj_ = NULL;
			}
		}
		

		dataObject_->Release();
		result = S_OK;
	}
	else {
		result = E_FAIL;
	}
	return result;
}


/**
$Id$
*/
