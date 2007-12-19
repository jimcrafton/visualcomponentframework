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



namespace VCF {

	class TabPage;


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
	TabModelEvent( Object * source, TabPage* p ): Event(source), page(p) {}

	TabModelEvent( Object* source, const uint32& eventType, TabPage* p )
		: Event(source,eventType), page(p) {}

	TabModelEvent( const TabModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~TabModelEvent(){}


	TabModelEvent& operator= ( const TabModelEvent& rhs ) {
		Event::operator =( rhs );

		page = rhs.page;

		return *this;
	}

	TabPage* page;

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

class APPLICATIONKIT_API TabModel : public Model  {
public:

	TabModel(){};

	virtual ~TabModel(){}

	/**
	@delegate TabPageAdded this is fired when a new tab page item is
	added to the model.
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_ADDED
	*/
	DELEGATE(TabModelDelegate,TabPageAdded)

	/**
	@delegate
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_REMOVED
	*/
	DELEGATE(TabModelDelegate,TabPageRemoved)

	/**
	@delegate TabModelEvent - this is fired when a tab page is selected by calling
	the setSelectedPage() method
	@event TabModelEvent
	@eventtype TAB_MODEL_EVENT_ITEM_SELECTED
	@see setSelectedPage()
	*/
	DELEGATE(TabModelDelegate,TabPageSelected)
	
	virtual void addTabPage( TabPage* page ) {
		insertTabPage( 0, page );
	}

	virtual void insertTabPage( const uint32& index, TabPage* page ) = 0;

	virtual void deleteTabPage( TabPage* page ) = 0;

	virtual void deleteTabPage( const uint32& index ) = 0;

	virtual TabPage* getPageFromPageName( const String& pageName ) = 0;

	virtual TabPage* getPageAt( const uint32& index ) = 0;

	virtual uint32 getItemIndex( TabPage* item ) = 0;

	virtual TabPage* getSelectedPage() = 0;

	virtual void setSelectedPage( TabPage* page ) = 0;

	virtual void setSelectedPage( const uint32& index ) = 0;

	virtual Enumerator<TabPage*>* getPages() = 0;

	virtual uint32 getPageCount() = 0;
};

};


#endif // _VCF_TABMODEL_H__

/**
$Id$
*/
