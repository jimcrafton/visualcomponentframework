#ifndef _VCF_TREEMODELEVENT_H__
#define _VCF_TREEMODELEVENT_H__
//TreeModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class TreeItem;

/**
\class TreeModelEvent TreeModelEvent.h "vcf/ApplicationKit/TreeModelEvent.h" 
*/
class APPLICATIONKIT_API TreeModelEvent : public Event
{
public:
	TreeModelEvent( Object* source, const ulong32& type ) : 
	  Event(source,type){}

	TreeModelEvent( Object* source, TreeItem* item, const ulong32& type ) : 
	  Event(source,type), item_(item){}
		

	TreeModelEvent( const TreeModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~TreeModelEvent() {}

	TreeModelEvent& operator= ( const TreeModelEvent& rhs ) {
		Event::operator =( rhs );

		item_ = rhs.item_;

		return *this;
	}
	
	TreeItem* getTreeItem(){
		return item_;
	}
	
	void setTreeItem( TreeItem* item ){
		item_ = item;
	}

	virtual Object* clone( bool deep=false ) {
		return new TreeModelEvent(*this);
	}
private:
	TreeItem* item_;
};





/**
*TreeModelEventHandler
*handles the following:
*onRootNodeChanged
*onNodeAdded
*onNodeDeleted
*/
template <class SOURCE_TYPE>
class TreeModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,TreeModelEvent> {
public:
	TreeModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TreeModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TreeModelEvent>( source, handlerMethod, handlerName ) {

	}

};

};


#endif // _VCF_TREEMODELEVENT_H__

/**
$Id$
*/
