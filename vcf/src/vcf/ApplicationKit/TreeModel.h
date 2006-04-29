#ifndef _VCF_TREEMODEL_H__
#define _VCF_TREEMODEL_H__
//TreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class TreeItem;



/**
\class TreeModel TreeModel.h "vcf/ApplicationKit/TreeModel.h" 
*/
class APPLICATIONKIT_API TreeModel  {
public:


	TreeModel(){

	};

	virtual ~TreeModel(){};


	enum TreeModelEvents {
		TREEITEM_ADDED = Model::MODEL_LAST_EVENT + 2000,
		TREEITEM_DELETED
	};


	virtual Enumerator<TreeItem*>* getRootItems() = 0;

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) = 0;

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) = 0;

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) = 0;

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) = 0;

	virtual void insertNodeItem( TreeItem * node, TreeItem * nodeToInsertAfter ) = 0;


	virtual void deleteNodeItem( TreeItem * nodeToDelete ) = 0;

	virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL ) = 0;

	virtual void sort() = 0;
};


}; //namespace VCF


#endif // _VCF_TREEMODEL_H__

/**
$Id$
*/
