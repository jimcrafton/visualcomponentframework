//Win32DropTargetPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32DropTargetPeer.h"
#include "vcf/ApplicationKit/COMUtils.h"

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
		currentDataObj_->free();
		currentDataObj_ = NULL;
	}

	dataObject_=NULL;

    if(keyState & MK_CONTROL){
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
	HRESULT result = NOERROR;

	if ( NULL == dataObject_ )
	{
        *effect=DROPEFFECT_NONE;
        result =  NOERROR;
	}

    //We can always drop; return effect flags based on keys.
	/*
    effect=DROPEFFECT_MOVE;
	*/

    if ( keyState & MK_CONTROL ) {
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
		currentDataObj_->free();
		currentDataObj_ = NULL;
	}


    result = NO_ERROR;

	return result;
}

HRESULT Win32DropTargetPeer::Drop( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect )
{
	HRESULT result = E_FAIL;

	if ( NULL != currentDataObj_ ) {
		currentDataObj_->free();
		currentDataObj_ = NULL;
	}

	/*
    *pdwEffect=DROPEFFECT_NONE;
	*/
    if ( NULL != dataObject_ ){

		DragLeave();

		dataObject_ = dataObject;
		dataObject_->AddRef();

		VCF::DropTarget* target = getDropTarget();
		unsigned long size = 0;


		IEnumFORMATETC* enumFMT = NULL;

		HRESULT result = dataObject_->EnumFormatEtc( DATADIR_GET, &enumFMT );
		if ( (SUCCEEDED(result)) && (NULL != enumFMT) ){


			FORMATETC fmtETC;
			memset( &fmtETC, 0, sizeof(FORMATETC) );
			ULONG fetched = 0;



			HRESULT res = enumFMT->Next( 1, &fmtETC, &fetched );



			while ( (1 == fetched) && (SUCCEEDED(res)) ){
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

			event.setType( DropTarget::DRAG_DROPPED );
			getDropTarget()->handleEvent( &event );

			if ( NULL != currentDataObj_ ) {
				currentDataObj_->free();
				currentDataObj_ = NULL;
			}
		}


		//*effect = DROPEFFECT_MOVE;

		if ( keyState & MK_CONTROL ){
			*effect = DROPEFFECT_COPY;
		}

		dataObject_->Release();
		result = NOERROR;
	}
	else {
		result = E_FAIL;
	}
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.1  2004/03/26 01:38:11  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.12  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.5  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.11.2.4  2003/09/17 21:23:24  ddiego
*added adjustmnents to win32 tree peer and drop target
*
*Revision 1.11.2.3  2003/09/03 23:50:40  marcelloptr
*newlines at the EOF
*
*Revision 1.11.2.2  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.11.2.1  2003/08/27 20:11:49  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.11  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.2  2003/05/25 20:01:08  ddiego
*oops - missed some #include changes from moving the files from one directory to
*the other! This fixes that (related to the drag-drop bug fixing and clean up)
*
*Revision 1.10.2.1  2003/05/25 19:07:14  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.10  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:12:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.1  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:30  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


