#ifndef _VCF_ABSTRACTLISTMODEL_H__
#define _VCF_ABSTRACTLISTMODEL_H__
//AbstractListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__

namespace VCF{

class Stream;

#define ABSTRACTLISTMODEL_CLASSID		"ED88C0A7-26AB-11d4-B539-00C04F0196DA"

/**
\class AbstractListModel AbstractListModel.h "vcf/ApplicationKit/AbstractListModel.h"
*The AbstractListModel is basic implementation of ListModel.
*Deriving classes can use it as starting point in their own
*implementation. See ListModel for more information on the methods
*implemented here.
*
*@see ListModel
*@see DefaultListModel
*@version 1.0
*@author Jim Crafton
@delegates
	@del AbstractListModel::ModelEmptied
	@del AbstractListModel::ModelValidate
	@del AbstractListModel::ContentsChanged
	@del AbstractListModel::ItemAdded
	@del AbstractListModel::ItemDeleted

*/
class APPLICATIONKIT_API AbstractListModel : public ListModel, public Persistable {
public:

	AbstractListModel();

	virtual ~AbstractListModel();

    

    /**
    * clears out the model's data
    */
    void empty();

	/**
	@delegate  ContentsChanged
	@event ListModelEvent
	@eventtype LIST_MODEL_CONTENTS_DELETED
	*/
	DELEGATE(ListModelDelegate,ContentsChanged)

	/**
	@delegate ItemAdded fired when an item is added to the list model
	@event ListModelEvent
	*/
	DELEGATE(ListModelDelegate,ItemAdded)

	/**
	@delegate ItemDeleted fired when an item is removed from the list model
	@event ListModelEvent
	*/
	DELEGATE(ListModelDelegate,ItemDeleted)

	virtual void addContentsChangedHandler(EventHandler * handler) {
		ContentsChanged += handler;
	}

	virtual void removeContentsChangedHandler(EventHandler * handler) {
		ContentsChanged.remove(handler);
	}

	virtual void addItemAddedHandler(EventHandler * handler) {
		ItemAdded += handler;
	}

	virtual void removeItemAddedHandler(EventHandler * handler) {
		ItemAdded.remove(handler);
	}

	virtual void addItemDeletedHandler(EventHandler * handler) {
		ItemDeleted += handler;
	}

	virtual void removeItemDeletedHandler(EventHandler * handler) {
		ItemDeleted.remove(handler);
	}

    virtual void deleteItem(ListItem * item);

    virtual void deleteItemAtIndex(const uint32 & index);

    virtual void insertItem(const uint32 & index, ListItem * item);

    virtual void addItem(ListItem * item);

	virtual ListItem* getItemFromIndex( const uint32& index );

	virtual uint32 getItemIndex( ListItem* item );

	virtual Enumerator<ListItem*>* getItems();

	virtual uint32 getCount();

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );
private:

    /**
    * @supplierCardinality 0..*
   */
	std::vector<ListItem*> listItems_;
	EnumeratorContainer<std::vector<ListItem*>, ListItem*> listContainer_;
};

};


#endif // _VCF_ABSTRACTLISTMODEL_H__

/**
$Id$
*/
