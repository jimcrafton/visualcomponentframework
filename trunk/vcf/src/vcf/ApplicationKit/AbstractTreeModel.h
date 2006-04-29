#ifndef _VCF_ABSTRACTTREEMODEL_H__
#define _VCF_ABSTRACTTREEMODEL_H__
//AbstractTreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

#ifndef _VCF_TREEMODELEVENT_H__
#	include "vcf/ApplicationKit/TreeModelEvent.h"
#endif // _VCF_TREEMODELEVENT_H__

#ifndef _VCF_TREEITEM_H__
#	include "vcf/ApplicationKit/TreeItem.h"
#endif // _VCF_TREEITEM_H__

namespace VCF{

#define ABSTRACTTREEMODEL_CLASSID		"3126B227-2819-11d4-B53A-00C04F0196DA"


/**
\class AbstractTreeModel AbstractTreeModel.h "vcf/ApplicationKit/AbstractTreeModel.h"
*AbstractTreeModel is a basic implementation of Treemodel. It used for
*deriving classes to have a starting point for implementing
*a concrete TreeModel class.
*For more information on the methods implemented here please see TreeModel.
*
*@see TreeModel
*@see DefaultTreeModel
*@version 1.0
*@author Jim Crafton
@delegates
	@del AbstractTreeModel::ModelEmptied
	@del AbstractTreeModel::ModelValidate
*/
class APPLICATIONKIT_API AbstractTreeModel : public TreeModel {
public:


    AbstractTreeModel();

	virtual ~AbstractTreeModel();

	void init();

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) {
	}

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) {
	}

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) {
	}

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) {
	}

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) {
	}

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) {
	}

	

    /**
     * clears out the model's data
     */
    void empty();

	virtual Enumerator<TreeItem*>* getRootItems();

    virtual void insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter);

    virtual void deleteNodeItem(TreeItem * nodeToDelete);

    virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL );

    virtual void sort();

	virtual void onItemPaint( ItemEvent* event );

    virtual void onItemChanged( ItemEvent* event );

    virtual void onItemSelected( ItemEvent* event );

	virtual void onItemAdded( ItemEvent* event );

	virtual void onItemDeleted( ItemEvent* event );
protected:
	std::vector<TreeItem*> rootNodes_;
	EnumeratorContainer<std::vector<TreeItem*>,TreeItem*> treeItemContainer_;
private:

};

};


#endif // _VCF_ABSTRACTTREEMODEL_H__

/**
$Id$
*/
