//AbstractTreeModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractTreeModel.h"


using namespace VCF;

AbstractTreeModel::AbstractTreeModel()
{
	init();
}

AbstractTreeModel::~AbstractTreeModel()
{
	std::vector<TreeItem*>::iterator it = rootNodes_.begin();
	while ( it != rootNodes_.end() ) {
		TreeItem* rootItem = *it;
		if ( NULL != rootItem ) {
			//rootItem->clearChildren();
			delete rootItem;
		}
		rootItem = NULL;
		it ++;
	}
	rootNodes_.clear();
}

void AbstractTreeModel::init()
{
	treeItemContainer_.initContainer( rootNodes_ );
}

void AbstractTreeModel::empty()
{
	std::vector<TreeItem*>::iterator it = rootNodes_.begin();
	while ( it != rootNodes_.end() ) {
		TreeItem* rootItem = *it;
		if ( NULL != rootItem ) {
			rootItem->clearChildren();
			delete rootItem;
		}
		rootItem = NULL;
		it ++;
	}
	rootNodes_.clear();
}

void AbstractTreeModel::insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter)
{
}

void AbstractTreeModel::deleteNodeItem(TreeItem * nodeToDelete)
{
}

void AbstractTreeModel::addNodeItem( TreeItem * node, TreeItem * nodeParent )
{
}

void AbstractTreeModel::sort()
{

}

void AbstractTreeModel::onItemPaint( ItemEvent* event )
{

}

void AbstractTreeModel::onItemChanged( ItemEvent* event )
{
	if ( NULL != event ){
		switch ( event->getType() ){
			case ITEM_EVENT_TEXT_CHANGED:{

			}
			break;
		}
	}
}

void AbstractTreeModel::onItemSelected( ItemEvent* event )
{

}

void AbstractTreeModel::onItemAdded( ItemEvent* event )
{

}


void AbstractTreeModel::onItemDeleted( ItemEvent* event )
{

}

Enumerator<TreeItem*>* AbstractTreeModel::getRootItems()
{
	return treeItemContainer_.getEnumerator();
}


/**
$Id$
*/
