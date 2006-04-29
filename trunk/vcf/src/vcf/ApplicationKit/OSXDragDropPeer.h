#ifndef _VCF_OSXDRAGDROPPEER_H__
#define _VCF_OSXDRAGDROPPEER_H__
//OSXDragDropPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF {

class OSXDragDropPeer : public DragDropPeer, public Object {
public:

	OSXDragDropPeer();
	virtual ~OSXDragDropPeer();

    virtual DragActionType startDragDrop( DataObject* data );

	virtual DragSource* getDragSource() {
		return dragSrc_;
	}

	virtual void setDragSource( VCF::DragSource* dragSource );

	void setActionType( const DragActionType& actionType );

protected:
	VCF::DragSource * dragSrc_;
	VCF::DataObject * dataObj_;
	DragActionType actionType_;
	
	static OSErr DragInputFunction ( ::Point * mouse, SInt16 * modifiers, void * dragInputRefCon, DragRef theDrag);
};

};


#endif // _VCF_OSXDRAGDROPPEER_H__

/**
$Id$
*/
