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
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_OSXDRAGDROPPEER_H__


