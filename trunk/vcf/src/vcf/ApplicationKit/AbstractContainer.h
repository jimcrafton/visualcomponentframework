#ifndef _VCF_ABSTRACTCONTAINER_H__
#define _VCF_ABSTRACTCONTAINER_H__
//AbstractContainer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;

class ControlEvent;

class MouseEvent;

class GraphicsContext;

class MouseHandler;

class Rect;


/**
AbstractContainer implements the basics of a
container with the exception of actual layout rules,
therefore resizeChildren is not implemented. It
isleft to implementers to decide on there own
layout rules for resizeChildren().
It responds to all mouse and paint events
of the Control to which is attached to, and forwards
them correctly to the child controls. This is event
forwarding only takes place if the child control
is a lighweight control.
When the attached control is resized, the AbstractContainer
will detect this as well and call resizeChildren() where
appropriate.
*/
class APPLICATIONKIT_API AbstractContainer : public Container, public ObjectWithEvents,
									public EnumeratorContainer<std::vector<Control*>, Control*>{
public:



	AbstractContainer();

	virtual ~AbstractContainer();

	void init();

	virtual void add( Control * child );

    virtual void add( Control * child, const AlignmentType& alignment );

	virtual void remove( Control* child );

	virtual void paintChildren( GraphicsContext* context );

	virtual Enumerator<Control*>* getChildren();

	virtual unsigned long getChildCount();

	virtual Control* findControl( const String& controlName );

	virtual Control* getControlAtIndex( const ulong32& index );

	virtual long getControlIndex( Control* control );

	virtual void updateTabOrder( Control* child, ulong32& newTabOrder );

	virtual void getTabList( std::vector<Control*>& tabList );

	virtual void insertBeforeControl( Control * child, const AlignmentType& alignment, Control* afterControl );

	virtual void insertAtIndex( Control * child, const AlignmentType& alignment, const ulong32& index );

	virtual void sendControlToFront( Control* child );

	virtual void sendControlToBack( Control* child );

	virtual void setContainerControl( Control* control );

	virtual Control* getContainerControl(){
		return controlContainer_;
	}
protected:
	std::vector<Control*> controls_;
	std::map<long,Control*> tabOrderMap_;
	long currentTabControlIndex_;
	Control* controlContainer_;
	EventHandler* controlHandler_;
	EventHandler* mouseHandler_;

	void containerResized( ControlEvent* event );
	void onMouseEvent( MouseEvent* event );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.1.2.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*/


#endif // _VCF_ABSTRACTCONTAINER_H__


