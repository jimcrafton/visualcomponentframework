//OSXDragDropPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXDragDropPeer.h"

using namespace VCF;




   
OSXDragDropPeer::OSXDragDropPeer():
	dragSrc_(NULL),
	dataObj_(NULL),
	actionType_(0)
{
	
}

OSXDragDropPeer::~OSXDragDropPeer()
{
	
}

DragActionType OSXDragDropPeer::startDragDrop( DataObject* cdo )
{

	dataObj_ = cdo;

	//init pasteboard
	CFRefObject<PasteboardRef>   pasteboard;
	if ( noErr != PasteboardCreate( kPasteboardUniqueName, &pasteboard ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("PasteboardCreate Failed to create pasteboard with kPasteboardUniqueName.") );
	}
	PasteboardClear( pasteboard );
	PasteboardSynchronize( pasteboard );
	
	//transfer data
	CFTextString flavor;
	Enumerator<String>* dataTypes = cdo->getSupportedDataTypes();
	while ( dataTypes->hasMoreElements() ) {
		CFTextString type;
		type = dataTypes->nextElement();
		/*
		if ( type == STRING_DATA_TYPE ) {
			flavor = CFSTR("com.apple.traditional-mac-plain-text");
		}
		else if ( type == RTF_DATA_TYPE ) {
			flavor = CFSTR("");
		}
		else if ( type == INTEGER_DATA_TYPE ) {
			//flavor = kUTTypeRTF;
		}
		else if ( type == OBJECT_DATA_TYPE ) {
			//flavor = kUTTypeRTF;
		}
		else if ( type == FILE_DATA_TYPE ) {
			flavor = CFSTR("");
		}
		else if ( type == BYTE_STREAM_DATA_TYPE ) {
			//flavor = kUTTypeFileURL;
		}
		else if ( type == IMAGE_DATA_TYPE ) {
			flavor = CFSTR(""); //assume PNG for default image type
		}
		else if ( type == COMPONENT_DATA_TYPE ) {
			//we need a custom type!!!
			//flavor = kUTTypePlainText; //assume PNG for default image type
		}
		*/
		flavor = UTTypeCreatePreferredIdentifierForTag( kUTTagClassMIMEType, type, NULL );

		BasicOutputStream memStream;
		if ( cdo->saveToStream( type, &memStream ) ) {
			memStream.seek( 0, stSeekFromStart );

			CFRefObject<CFDataRef> dataRef = CFDataCreate( NULL, (const UInt8*)memStream.getBuffer(), memStream.getSize() );

			if ( noErr != PasteboardPutItemFlavor( pasteboard, cdo, flavor, dataRef, 0 ) ) {
				throw RuntimeException( MAKE_ERROR_MSG_2("PasteboardPutItemFlavor failed to add new data.") );
			}		
		}
	}
	
	//now prep for the drag
	DragRef			drag;
	::Point			trackPoint,localPoint;
	RgnHandle		theRegion, insetRegion;
	
	if ( noErr != NewDragWithPasteboard( pasteboard, &drag ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("NewDragWithPasteboard failed to create a new drag ref.") );
	}
	
	//adjust the track point by retreiving the 
	//global mouse coordinates
	GetGlobalMouse( &trackPoint );
	
	localPoint.h = trackPoint.h;
	localPoint.v = trackPoint.v;
	GlobalToLocal( &localPoint );
	
	//init the region to use - setup a 10X10 square that will just outline a box
	theRegion = NewRgn();
	insetRegion = NewRgn();
	SetRectRgn( theRegion, localPoint.h - 10, localPoint.v - 10,
				localPoint.h + 10, localPoint.v + 10 );
	CopyRgn( theRegion, insetRegion );
	InsetRgn( insetRegion, 1, 1 );
	DiffRgn(theRegion, insetRegion, theRegion );
	DisposeRgn( insetRegion );
	
	
	//set callbacks here
	SetDragInputProc( drag, OSXDragDropPeer::DragInputFunction, this );
	
	//now init a fake EventRecord to pass to TrackDrag
	EventRecord fakeEvent;
	fakeEvent.what = mouseDown;
	fakeEvent.message = 0;
	fakeEvent.when = TickCount();
	fakeEvent.where.h = localPoint.h;
	fakeEvent.where.v = localPoint.v;
	fakeEvent.modifiers = 0;
	
	
	
	OSStatus err = TrackDrag( drag, &fakeEvent, theRegion );
	
	
	DisposeRgn( theRegion );
	DisposeDrag( drag );
	
	return actionType_;

}

void OSXDragDropPeer::setActionType( const VCF::DragActionType& actionType )
{
	actionType_ = actionType;
}


void OSXDragDropPeer::setDragSource( VCF::DragSource* dragSource )
{
	dragSrc_ = dragSource;
}

OSErr OSXDragDropPeer::DragInputFunction ( ::Point * mouse, SInt16 * modifiers, void * dragInputRefCon, DragRef theDrag)
{
	OSXDragDropPeer* peer = (OSXDragDropPeer*)dragInputRefCon;
	
	DragSourceEvent event(peer->dragSrc_, peer->dataObj_);
	event.setType( DragSource::DRAG_CANCONTINUE );
	
	peer->dragSrc_->SourceCanContinueDragOp.fireEvent( &event );
	
	
	DragSourceEvent event2(peer->dragSrc_, peer->dataObj_);
	event2.setType( DragSource::DRAG_GIVEFEEDBACK );

	peer->dragSrc_->SourceGiveFeedback.fireEvent( &event2 );
	
	return noErr;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.3  2005/06/27 03:28:54  ddiego
*more osx work.
*
*Revision 1.1.2.2  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*/


