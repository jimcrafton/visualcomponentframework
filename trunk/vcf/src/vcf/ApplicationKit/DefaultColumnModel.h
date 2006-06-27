#ifndef _VCF_DEFAULTCOLUMNMODEL_H__
#define _VCF_DEFAULTCOLUMNMODEL_H__
//DefaultColumnModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__

#ifndef _VCF_COLUMNMODELEVENT_H__
#	include "vcf/ApplicationKit/ColumnModelEvent.h"
#endif // _VCF_COLUMNMODELEVENT_H__


#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__






#define DEFAULTCOLUMNMODEL_CLASSID		"14b09dc3-777d-48cb-86d9-a311364cc41b"


namespace VCF  {

/**
\class DefaultColumnModel DefaultColumnModel.h "vcf/ApplicationKit/DefaultColumnModel.h"
*Class DefaultColumnModel documentation
*/
class APPLICATIONKIT_API DefaultColumnModel : public ColumnModel, public Persistable {
public:

	DefaultColumnModel();

	virtual ~DefaultColumnModel();

	void init();


    virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate += handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -= handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelEmptied += handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelEmptied -= handler;
	}

    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate();

    /**
    * clears out the model's data
    */
    virtual void empty();

	virtual void removeListModelHandler(EventHandler * handler) {
		ModelEmptied -= handler;
	}

	virtual void addListModelHandler(EventHandler * handler) {
		ModelEmptied += handler;
	}

	/**
	*ColumnModel Handlers
	*/
	DELEGATE(ContentsChanged)
	DELEGATE(ItemAdded)
	DELEGATE(ItemDeleted)

	DELEGATE(ModelValidate)
	DELEGATE(ModelEmptied)

	virtual void addContentsChangedHandler(EventHandler * handler) {
		ContentsChanged += handler;
	}

	virtual void removeContentsChangedHandler(EventHandler * handler) {
		ContentsChanged -= handler;
	}

	virtual void addItemAddedHandler(EventHandler * handler) {
		ItemAdded += handler;
	}

	virtual void removeItemAddedHandler(EventHandler * handler) {
		ItemAdded -= handler;
	}

	virtual void addItemDeletedHandler(EventHandler * handler) {
		ItemDeleted += handler;
	}

	virtual void removeItemDeletedHandler(EventHandler * handler) {
		ItemDeleted -= handler;
	}


    virtual void deleteItem( ColumnItem* item);

    virtual void deleteItem(const uint32 & index);

    virtual void insertItem(const uint32 & index, ColumnItem * item);

    virtual void addItem( ColumnItem* item);

	virtual ColumnItem* getItemFromIndex( const uint32& index );

	virtual Enumerator<ColumnItem*>* getItems();

	virtual uint32 getCount();

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );

protected:
	std::vector<ColumnItem*> columnItems_;
	EnumeratorContainer<std::vector<ColumnItem*>, ColumnItem*> columnContainer_;
};


}; //end of namespace VCF


#endif // _VCF_DEFAULTCOLUMNMODEL_H__

/**
$Id$
*/
