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


#define ABSTRACTCONTAINER_CLASSID		"80cafd13-cd05-4b48-a1c3-6c4d9811361c"

/**
\class AbstractContainer AbstractContainer.h "vcf/ApplicationKit/AbstractContainer.h"
AbstractContainer implements the basics of a
container with the exception of actual layout rules,
therefore resizeChildren is not implemented. It
is left to implementers to decide on their own
what the layout rules for resizeChildren() are.

It responds to all mouse and paint events
of the Control to which is attached to, and forwards
them correctly to the child controls. This event
forwarding only takes place if the child control
is a lighweight control.

When the attached control is resized, the AbstractContainer
will detect this as well and call resizeChildren() where
appropriate.
*/
class APPLICATIONKIT_API AbstractContainer : public Container {
public:
	AbstractContainer();

	AbstractContainer( Component* owner );

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

	virtual void clear();

	virtual void sendControlToFront( Control* child );

	virtual void sendControlToBack( Control* child );

	virtual void setContainerControl( Control* control );

	virtual Control* getContainerControl(){
		return controlContainer_;
	}
protected:
	std::vector<Control*> controls_;
	EnumeratorContainer<std::vector<Control*>, Control*> controlsContainer_;
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
*Revision 1.5  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.4.2.1  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.4  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.4.2  2005/03/14 04:17:22  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.3.4.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3  2004/08/08 22:09:32  ddiego
*final checkin before the 0-6-5 release
*
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


