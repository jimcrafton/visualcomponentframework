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


#endif // _VCF_ABSTRACTCONTAINER_H__

/**
$Id$
*/
