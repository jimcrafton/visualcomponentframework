//OSXDropTargetPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXDropTargetPeer.h"
#include "vcf/ApplicationKit/OSXClipboard.h"



using namespace VCF;

OSXDropTargetPeer::OSXDropTargetPeer():
	dropTarget_(NULL),
	eventHandlerRef_(NULL),
	currentDataObj_(NULL)
{
	
}

OSXDropTargetPeer::~OSXDropTargetPeer()
{
	
}

void OSXDropTargetPeer::registerTarget( Control* control )
{
	static EventTypeSpec dropTargetEvents[] =
			{
				{ kEventClassControl, kEventControlDragEnter },
				{ kEventClassControl, kEventControlDragWithin },
				{ kEventClassControl, kEventControlDragLeave },
				{ kEventClassControl, kEventControlDragReceive }
			};
			
	ControlRef ctrlRef = (ControlRef) control->getPeer()->getHandleID();
	
	InstallEventHandler(GetControlEventTarget(ctrlRef), OSXDropTargetPeer::handleDropTargetEvents, 
						sizeof(dropTargetEvents)/sizeof(EventTypeSpec), 
						dropTargetEvents, this, &eventHandlerRef_ );
						
	SetControlDragTrackingEnabled( ctrlRef, true );
	SetAutomaticControlDragTrackingEnabledForWindow( GetControlOwner(ctrlRef), true );
}

void OSXDropTargetPeer::unregisterTarget( Control* control )
{
	RemoveEventHandler( eventHandlerRef_ );
	ControlRef ctrlRef = (ControlRef) control->getPeer()->getHandleID();
	SetControlDragTrackingEnabled( ctrlRef, false );
}

VCF::DropTarget* OSXDropTargetPeer::getDropTarget()
{
	return dropTarget_;
}

void OSXDropTargetPeer::setDropTarget( VCF::DropTarget* dropTarget )
{
	dropTarget_ = dropTarget;
}

OSStatus OSXDropTargetPeer::handleDropTargetEvents (EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData)
{
	OSStatus result = eventNotHandledErr;	
	
	OSXDropTargetPeer* peer = (OSXDropTargetPeer*)inUserData;
	VCF::DropTarget* target = peer->getDropTarget();
	
	EventClass	eventClass = GetEventClass( inEvent );
	EventKind	eventKind = GetEventKind( inEvent );
	::Point mousePos;
	GetEventParameter( inEvent, kEventParamMouseLocation, typeQDPoint, NULL,
                                sizeof (mousePos), NULL, &mousePos);
								
	VCF::Point dragPt( mousePos.h ,
						   mousePos.v );
						   
	UInt32 keyboardModifier = 0;
	GetEventParameter( inEvent, kEventParamKeyModifiers, typeUInt32, NULL,
                                sizeof (keyboardModifier), NULL, &keyboardModifier);
	
	DragActionType action = daNone;
															
	if ( (keyboardModifier & cmdKey) && (keyboardModifier & optionKey) ) {
		//link
		action = daLink;
    }
	else if ( keyboardModifier & optionKey ) {
		//copy
		action = daCopy;
	}
	else {
		//move
		action = daMove;
	}
	
	switch( eventClass ) {
		case kEventClassControl : {
			switch ( eventKind ) {
				case kEventControlDragEnter : {					
					
								
					peer->currentDataObj_ = new VCF::DataObject();
					
					VCF::DropTargetEvent event( target, peer->currentDataObj_ );
					
					event.setType( DropTarget::DRAG_ENTERED );
					event.setActionType( action );
					event.setDropPoint( dragPt );
					target->handleEvent( &event );
					
					if ( event.getAction() == daNone ) {
						
					}
				}
				break;
				
				case kEventControlDragWithin : {					
					VCF::DropTargetEvent event( target, peer->currentDataObj_ );
					event.setType( DropTarget::DRAGGING_OVER );
					event.setDropPoint( dragPt );
					event.setActionType( action );
					target->handleEvent( &event );
				}
				break;
				
				//this is the last event in the series
				//clean up the currentDataObj_ instance
				case kEventControlDragLeave : {					
					VCF::DropTargetEvent event( target, NULL );
					event.setType( DropTarget::DRAG_LEFT );
					target->handleEvent( &event );
					
					if ( NULL != peer->currentDataObj_ ) {
						peer->currentDataObj_->free();
						peer->currentDataObj_ = NULL;
					}
				}
				break;
				
				//clean up the currentDataObj_ instance
				//recreate a new instance, this time with data
				case kEventControlDragReceive : {					
					if ( NULL != peer->currentDataObj_ ) {
						peer->currentDataObj_->free();
						peer->currentDataObj_ = NULL;
					}
					DragRef drag = NULL;
					GetEventParameter( inEvent, kEventParamDragRef, typeDragRef, NULL,
                                sizeof (drag), NULL, &drag);
								
					PasteboardRef   pasteboard;
					if ( noErr == GetDragPasteboard( drag, &pasteboard ) ) {
						peer->currentDataObj_ = OSXClipboard::createDataObjectFromPasteBoard( pasteboard );
						
						VCF::DropTargetEvent event( target, peer->currentDataObj_ );
						
						event.setType( DropTarget::DRAG_DROPPED );
						target->handleEvent( &event );
						
						if ( NULL != peer->currentDataObj_ ) {
							peer->currentDataObj_->free();
							peer->currentDataObj_ = NULL;
						}
					}
				}
				break;
			}
		}
		break;
	}
		
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.2  2005/06/27 03:28:54  ddiego
*more osx work.
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*
*/


