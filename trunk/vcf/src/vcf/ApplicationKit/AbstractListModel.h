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


*/
/*
class APPLICATIONKIT_API AbstractListModel  {
public:

	AbstractListModel();
	virtual ~AbstractListModel();
    void empty();
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

    virtual void saveToStream( OutputStream * stream );
    virtual void loadFromStream( InputStream * stream );

};
*/
};


#endif // _VCF_ABSTRACTLISTMODEL_H__

/**
$Id$
*/
