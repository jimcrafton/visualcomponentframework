#ifndef _VCF_COLUMNMODEL_H__
#define _VCF_COLUMNMODEL_H__
//ColumnModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define COLUMNMODEL_CLASSID		"997ee959-661c-437a-9879-b884f593a864"


namespace VCF  {

class ColumnItem;
/**
*The ColumnModel is a model that represent's 0 or more ColumnItems.
*You can add, remove, and insert column items in the model. In addition
*you can get an item by index, or retrieve an Enumerator of all of the
*items the model currently has in it.
*@see Model
*/
class APPLICATIONKIT_API ColumnModel : public Model {
public:

	virtual ~ColumnModel(){};

	/**
	*adds a new handler that is notified whenever the contents of the model
	*change. This can happen anytime an item is added or removed.
	*@param EventHandler the handler to add for future notifications
	*/
	virtual void addContentsChangedHandler(EventHandler * handler) = 0;

	/**
	*removes a handler that was interested in changes to the model.
	*@param EventHandler the handler to remove from future notifications
	*/
	virtual void removeContentsChangedHandler(EventHandler * handler) = 0;

	/**
	*adds a new handler that is notified whenever an item is added.
	*@param EventHandler the handler to add for future notifications
	*/
	virtual void addItemAddedHandler(EventHandler * handler) = 0;

	/**
	*removes a handler that was interested in item additions to the model.
	*@param EventHandler the handler to remove from future notifications
	*/
	virtual void removeItemAddedHandler(EventHandler * handler) = 0;

	/**
	*adds a new handler that is notified whenever an item is removed.
	*@param EventHandler the handler to add for future notifications
	*/
	virtual void addItemDeletedHandler(EventHandler * handler) = 0;

	/**
	*removes a handler that was interested in item deletions to the model.
	*@param EventHandler the handler to remove from future notifications
	*/
	virtual void removeItemDeletedHandler(EventHandler * handler) = 0;

	/**
	*deletes the item from the model's collection of items.
	*Causes a notification to be sent to all listeners of the models ItemDeleted
	*events and the model's ContentsChanged event.
	*@param ColumnItem the item to delete.
	*/
	virtual void deleteItem( ColumnItem * item) = 0;

	/**
	*deletes the item from the model's collection of items.
	*Causes a notification to be sent to all listeners of the models ItemDeleted
	*events and the model's ContentsChanged event.
	*@param unsigned long the index of the item to delete.
	*/
	virtual void deleteItem(const unsigned long & index) = 0;

	/**
	*Inserts an item into the model's collection of items.
	*Causes a notification to be sent to all listeners of the models ItemAdded
	*events and the model's ContentsChanged event.
	*@param unsigned long the insertion index for the item
	*@param ColumnItem the item to insert
	*/
	virtual void insertItem(const unsigned long & index, ColumnItem* item) = 0;

	/**
	*Adds an item into the model's collection of items.
	*Causes a notification to be sent to all listeners of the models ItemAdded
	*events and the model's ContentsChanged event.
	*@param ColumnItem the item to add
	*/
    virtual void addItem(ColumnItem* item) = 0;

	/**
	*Returns the item with the specified index in the model's collection.
	*@param unsigned long teh index of the requested item to return
	*@return ColumnItem the item at the position specified in index. This
	*may be NULL if the index is out of bounds, or the model collection is
	*empty
	*/
	virtual ColumnItem* getItemFromIndex( const unsigned long& index ) = 0;

	/**
	*Returns an Enumerator of all the items in the model's collection.
	*For example:
	<pre>
		ColumnModel* model = ...

		Enumerator<ColumnItem*>* items = model->getItems();

		while ( true == items->hasMoreElements() ) {
			ColumnItem* item = items->nextElemnt();
			//do something ...
		}
	</pre>
	*@return Enumerator<ColumnItem*> the enumerator of items. The caller is <b>not</b>
	*responsible for the returned pointer and should not delete it.
	*@see Enumerator
	*/
	virtual Enumerator<ColumnItem*>* getItems() = 0;

	/**
	*returns the number of the items in the model
	*@return unsigned long the count of items
	*/
	virtual unsigned long getCount() = 0;

protected:

private:
};


}; //end of namespace VCF


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
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.26.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3  2002/02/17 01:07:14  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COLUMNMODEL_H__


