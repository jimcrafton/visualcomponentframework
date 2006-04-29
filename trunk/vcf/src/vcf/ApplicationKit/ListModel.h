#ifndef _VCF_LISTMODEL_H__
#define _VCF_LISTMODEL_H__
//ListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF{

class ListItem;


/**
\class ListModel ListModel.h "vcf/ApplicationKit/ListModel.h"
The List model is a interface for describing what a model that implements
a list of items should do. It does not \emnot inherit from the Model class
directly. This is to allow different implementations different base classes.
For example, you might have a simple list model that inherits/implements the 
Model class, and the ListModel class. This would be suitable for most controls.
However you might want a fancier implementation, perhaps that is based 
off of the Document and ListModel classes. This would still allow you to 
use the same control with either style.
*/
class APPLICATIONKIT_API ListModel  {
public:

	ListModel(){

	};

	virtual ~ListModel(){};

    virtual void addContentsChangedHandler(EventHandler * handler) = 0;

	virtual void removeContentsChangedHandler(EventHandler * handler) = 0;

	virtual void addItemAddedHandler(EventHandler * handler) = 0;

	virtual void removeItemAddedHandler(EventHandler * handler) = 0;

	virtual void addItemDeletedHandler(EventHandler * handler) = 0;

	virtual void removeItemDeletedHandler(EventHandler * handler) = 0;

	virtual void deleteItem(ListItem * item) = 0;

	virtual void deleteItemAtIndex(const unsigned long & index) = 0;

	virtual void insertItem(const unsigned long & index, ListItem * item) = 0;

    virtual void addItem(ListItem * item) = 0;

	virtual ListItem* getItemFromIndex( const unsigned long& index ) = 0;

	virtual Enumerator<ListItem*>* getItems() = 0;

	/**
	*returns the number of the items in the model
	*/
	virtual unsigned long getCount() = 0;
};

}


#endif // _VCF_LISTMODEL_H__

/**
$Id$
*/
