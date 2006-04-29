//DefaultTreeModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTreeModel.h"


using namespace VCF;

DefaultTreeModel::DefaultTreeModel()
{

}

DefaultTreeModel::~DefaultTreeModel()
{

}

void DefaultTreeModel::init()
{

}

void DefaultTreeModel::onItemPaint( ItemEvent* event )
{

}

void DefaultTreeModel::onItemChanged( ItemEvent* event )
{

}

void DefaultTreeModel::onItemSelected( ItemEvent* event )
{

}

void DefaultTreeModel::onItemAdded( ItemEvent* event )
{

}

void DefaultTreeModel::onItemDeleted( ItemEvent* event )
{

}

void DefaultTreeModel::insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter)
{
	TreeItem* parent = nodeToInsertAfter->getParent();
	if ( NULL != parent ) {
		parent->insertChild( nodeToInsertAfter->getIndex(), node );
		TreeModelEvent event(dynamic_cast<Object*>(this), node, TreeModel::TREEITEM_ADDED );
		NodeAdded.fireEvent( &event );
	}
	else {
		//bad call throw exception
	}
}

void DefaultTreeModel::deleteNodeItem(TreeItem * nodeToDelete)
{
	TreeItem* parent = nodeToDelete->getParent();

	TreeModelEvent event(dynamic_cast<Object*>(this), nodeToDelete, TreeModel::TREEITEM_DELETED );
	NodeDeleted.fireEvent( &event );

	if ( NULL != parent ){
		parent->deleteChild( nodeToDelete );
	}
	else {
		std::vector<TreeItem*>::iterator found = std::find( rootNodes_.begin(), rootNodes_.end(), nodeToDelete );
		if ( found != rootNodes_.end() ) {
			TreeItem* item = *found;
			rootNodes_.erase( found );			

			delete item;
			item = NULL;
		}
	}
}

void DefaultTreeModel::addNodeItem( TreeItem * node, TreeItem * nodeParent )
{
	node->setModel( dynamic_cast<Model*>(this) );
	if ( NULL == nodeParent ){
		rootNodes_.push_back( node );
		TreeModelEvent event(dynamic_cast<Object*>(this), node, TreeModel::TREEITEM_ADDED );
		RootNodeChanged.fireEvent( &event );
	}
	else {
		nodeParent->addChild( node );
	}

	TreeModelEvent event(dynamic_cast<Object*>(this), node, TreeModel::TREEITEM_ADDED );
	NodeAdded.fireEvent( &event );
}


/**
$Id$
*/
