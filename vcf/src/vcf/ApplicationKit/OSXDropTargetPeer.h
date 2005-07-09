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
*/


#endif // _VCF_OSXDROPTARGETPEER_H__


