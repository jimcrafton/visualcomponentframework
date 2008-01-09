#ifndef _VCF_TABMODEL_H__
#define _VCF_TABMODEL_H__
//TabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_SIMPLELISTMODEL_H__
#	include "vcf/ApplicationKit/SimpleListModel.h"
#endif // _VCF_LISTMODEL_H__


namespace VCF {

	


#define TABMODELEVENT_CONST						232

	enum TabModelEvents {
		tmeItemAdded = CUSTOM_EVENT_TYPES + TABMODELEVENT_CONST + 1 ,
		tmeItemRemoved,
		tmeItemSelected
	};




/**
\class TabModelEvent TabModel.h "vcf/ApplicationKit/TabModel.h"
* the event class for events specific of tabbed pages
* It containes the pointer to the specific tab page 
* associated to this event.
*@see 
*/
class APPLICATIONKIT_API TabModelEvent : public Event {
public:
	TabModelEvent( Object * source, uint32 i ): Event(source), index(i) {}

	TabModelEvent( Object* source, const uint32& eventType, uint32 i )
		: Event(source,eventType), index(i) {}

	TabModelEvent( const TabModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~TabModelEvent(){}


	TabModelEvent& operator= ( const TabModelEvent& rhs ) {
		Event::operator =( rhs );

		index = rhs.index;

		return *this;
	}

	uint32 index;

	virtual Object* clone( bool deep=false ) {
		return new TabModelEvent(*this);
	}
	

};





/**
The handler class for a TabModelEvent.
 
handles the following:

	\li onTabPageAdded
	\li onTabPageRemoved
	\li onTabPageSelected
*/
typedef Delegate1<TabModelEvent*> TabModelDelegate; 
typedef TabModelDelegate::ProcedureType TabModelHandler;









#define TABMODEL_CLASSID	"4A9D66D7-3B26-11d4-B54C-00C04F0196DA"

/**
\class TabModel TabModel.h "vcf/ApplicationKit/TabModel.h"
The Tab model is a interface for describing what a model that implements
a series of tabs should do. It does not \emnot inherit from the Model class
directly. This is to allow different implementations different base classes.
For example, you might have a simple list model that inherits/implements the 
Model class, and the TabModel class. This would be suitable for most controls.
However you might want a fancier implementation, perhaps that is based 
off of the Document and TabModel classes. This would still allow you to 
use the same control with either style.
@delegates	
	@del TabModel::TabPageAdded
	@del TabModel::TabPageRemoved
	@del TabModel::TabPageSelected
*/

class APPLICATIONKIT_API TabModel : public SimpleListModel  {
public:

	TabModel();

	virtual ~TabModel();

	enum {
		NoPageSelected = (uint32)-1
	};

	/**
	@delegate TabModelEvent - this is fired when a tab page is selected by calling
	the setSelectedPage() method
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_SELECTED
	@see setSelectedPage()
	*/
	DELEGATE(TabModelDelegate,TabPageSelected)	

	virtual void empty() {
		SimpleListModel::empty();
	}

	virtual bool supportsSubItems() {
		return false;
	}

	void setSelectedPage( const uint32& index );

	uint32 getSelectedPageIndex() {
		return selectedIndex_;
	}

protected:
	uint32 selectedIndex_;
	
};

};


#endif // _VCF_TABMODEL_H__

/**
$Id$
*/
