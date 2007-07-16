#ifndef _VCF_DEFAULTTREEMODEL_H__
#define _VCF_DEFAULTTREEMODEL_H__
//DefaultTreeModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#ifndef _VCF_ABSTRACTMODEL_H__
#	include "vcf/ApplicationKit/AbstractModel.h"
#endif // _VCF_ABSTRACTMODEL_H__


#ifndef _VCF_ABSTRACTTREEMODEL_H__
#include "vcf/ApplicationKit/AbstractTreeModel.h"
#endif //_VCF_ABSTRACTTREEMODEL_H__



namespace VCF{

#define DEFAULTTREEMODEL_CLASSID		"3126B226-2819-11d4-B53A-00C04F0196DA"

/**
\class DefaultTreeModel DefaultTreeModel.h "vcf/ApplicationKit/DefaultTreeModel.h"
*/
class APPLICATIONKIT_API DefaultTreeModel : public AbstractModel, public AbstractTreeModel {
public:
	/**
	@delegate RootNodeChanged
	@event
	*/
	DELEGATE(TreeModelDelegate,RootNodeChanged)

	/**
	@delegate NodeAdded
	@event
	*/
	DELEGATE(TreeModelDelegate,NodeAdded)

	/**
	@delegate NodeDeleted
	@event
	*/
	DELEGATE(TreeModelDelegate,NodeDeleted)

	virtual void addTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged += handler;
	}

	virtual void removeTreeRootNodeChangedHandler( EventHandler* handler ) {
		RootNodeChanged.remove(handler);
	}

	virtual void addTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded += handler;
	}

	virtual void removeTreeNodeAddedHandler( EventHandler* handler ) {
		NodeAdded.remove(handler);
	}

	virtual void addTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted += handler;
	}

	virtual void removeTreeNodeDeletedHandler( EventHandler* handler ) {
		NodeDeleted.remove(handler);
	}

	DefaultTreeModel();

	virtual ~DefaultTreeModel();

	void init();

	virtual void empty() {
		AbstractTreeModel::empty();

		AbstractModel::empty();
	}

    virtual void insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter);

    virtual void deleteNodeItem(TreeItem * nodeToDelete);

    virtual void addNodeItem( TreeItem * node, TreeItem * nodeParent=NULL );

protected:

	virtual void onItemPaint( ItemEvent* event );

    virtual void onItemChanged( ItemEvent* event );

    virtual void onItemSelected( ItemEvent* event );

	virtual void onItemAdded( ItemEvent* event );

	virtual void onItemDeleted( ItemEvent* event );

	
};

};


#endif // _VCF_DEFAULTTREEMODEL_H__

/**
$Id$
*/
