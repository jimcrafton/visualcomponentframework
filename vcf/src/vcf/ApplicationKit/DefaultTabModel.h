#ifndef _VCF_DEFAULTTABMODEL_H__
#define _VCF_DEFAULTTABMODEL_H__
//DefaultTabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABMODEL_H__
#	include "vcf/ApplicationKit/TabModel.h"
#endif // _VCF_TABMODEL_H__

#ifndef _VCF_TABPAGE_H__
#	include "vcf/ApplicationKit/TabPage.h"
#endif // _VCF_TABPAGE_H__


#ifndef _VCF_TABMODELEVENT_H__
#	include "vcf/ApplicationKit/TabModelEvent.h"
#endif // _VCF_TABMODELEVENT_H__


namespace VCF {

#define DEFAULTTABMODEL_CLASSID		"86F02174-3E7F-11d4-8EA7-00207811CFAB"

/**
\class DefaultTabModel DefaultTabModel.h "vcf/ApplicationKit/DefaultTabModel.h"
This class represents a default, basic implementation of
the TabModel class.
@delegates
	@del DefaultTabModel::ModelEmptied
	@del DefaultTabModel::ModelValidate
	@del DefaultTabModel::TabPageAdded
	@del DefaultTabModel::TabPageRemoved
	@del DefaultTabModel::TabPageSelected
*/
class APPLICATIONKIT_API DefaultTabModel : public Model, public TabModel {
public:

	DefaultTabModel();

	virtual ~DefaultTabModel();

	/**
	@delegate ModelEmptied fired when the model's empty() method is
	called.
	@event ModelEvent
	@see empty()
	*/
	DELEGATE(ModelDelegate,ModelEmptied)

	

    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate.remove(handler);
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied.remove(handler);
	}

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

	virtual void addTabPageAddedHandler( EventHandler* handler ) {
		TabPageAdded += handler;
	}

	virtual void removeTabPageAddedHandler( EventHandler* handler ) {
		TabPageAdded.remove(handler);
	}

	virtual void addTabPageRemovedHandler( EventHandler* handler ) {
		TabPageRemoved += handler;
	}

	virtual void removeTabPageRemovedHandler( EventHandler* handler ) {
		TabPageRemoved.remove(handler);
	}

	virtual void addTabPageSelectedHandler( EventHandler* handler ) {
		TabPageSelected += handler;
	}

	virtual void removeTabPageSelectedHandler( EventHandler* handler ) {
		TabPageSelected.remove(handler);
	}

	virtual void addTabPage( TabPage* page );

	virtual void insertTabPage( const uint32& index, TabPage* page );

	virtual void deleteTabPage( TabPage* page );

	virtual void deleteTabPage( const uint32& index );

	virtual void clearTabPages();

	virtual TabPage* getPageAt( const uint32& index );

	virtual TabPage* getPageFromPageName( const String& pageName );

	virtual uint32 getItemIndex( TabPage* item );

	virtual TabPage* getSelectedPage();

	virtual void setSelectedPage( TabPage* page );

	virtual void setSelectedPage( const uint32& index );

	virtual Enumerator<TabPage*>* getPages();

    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate(){};

    /**
     * clears out the model's data
     */
    virtual void empty(){};

	virtual uint32 getPageCount() {
		return pages_.size();
	}

	bool isFirstPage( TabPage* page );

	bool isLastPage( TabPage* page );

	TabPage* nextPage( TabPage* page );

	TabPage* previousPage( TabPage* page );
protected:
	std::vector<TabPage*> pages_;
	EnumeratorContainer<std::vector<TabPage*>, TabPage*> container_;
	void tabPageChange( ItemEvent* e );
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABMODEL_H__

/**
$Id$
*/
