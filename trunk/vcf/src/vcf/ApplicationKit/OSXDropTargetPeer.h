#ifndef _VCF_OSXDROPTARGETPEER_H__
#define _VCF_OSXDROPTARGETPEER_H__
//OSXDropTargetPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {



class OSXDropTargetPeer :	public DropTargetPeer, public Object  {
public:
	OSXDropTargetPeer();

	virtual ~OSXDropTargetPeer();

	virtual void registerTarget( Control* control );

	virtual void unregisterTarget( Control* control );

	virtual DropTarget* getDropTarget();

	virtual void setDropTarget( DropTarget* dropTarget );

protected:
	DropTarget* dropTarget_;
	EventHandlerRef eventHandlerRef_;
	DataObject* currentDataObj_;
	
	static OSStatus handleDropTargetEvents(EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void *inUserData);
};


};


#endif // _VCF_OSXDROPTARGETPEER_H__

/**
$Id$
*/
