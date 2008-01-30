//TreeItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TreeItem.h"

using namespace VCF;

String TreeSubItem::getCaption()
{
	return "";
}

void TreeSubItem::setCaption( const String& caption )
{

}


TreeItem::TreeItem():
	Item(),
	font_(NULL),
	key_(TreeModel::InvalidKey),
	selectedImageIndex_(-1),
	expandedImageIndex_(-1),
	stateImageIndex_(-1)
{

}

TreeItem::~TreeItem()
{
	delete font_;
}

void TreeItem::setKey( TreeModel::Key val )
{
	key_ = val;
	TreeController* controller = getController();
	if ( controller ) {
		controller->setItemKey( this, val );
	}
}

Font* TreeItem::getFont()
{
	if ( NULL == font_ ) {
		font_ = new Font();
	}
	return font_;
}

void TreeItem::setFont( Font* val )
{
	Font* f = getFont();
	*f = *val;
}

void TreeItem::expand( const bool& val )
{
	if ( val ) {
		setDisplayState( getDisplayState() | tisExpanded );
	}
	else {
		setDisplayState( getDisplayState() & ~tisExpanded );
	}
	
	Event e(this,tieExpanding);
	getControl()->handleEvent( &e );
}

void TreeItem::expandAllChildren( const bool& isExpanded )
{

}

TreeItem* TreeItem::getParent()
{
	return getController()->getItemParent( this );
}

void TreeItem::setParent( TreeItem* parent )
{
	getController()->setItemParent( this, parent );
}

TreeItem* TreeItem::getNextChildNodeItem()
{
	TreeModel::Key key = getTreeModel()->getNextSibling( getKey() );
	return getController()->getItemFromKey( key );
}

TreeItem* TreeItem::getPrevChildNodeItem()
{
	TreeModel::Key key = getTreeModel()->getPrevSibling( getKey() );
	return getController()->getItemFromKey( key );
}

bool TreeItem::getChildren( std::vector<TreeItem*>& children )
{
	return getController()->getItemChildren( this, children );
}

String TreeItem::getCaption()
{
	return getTreeModel()->getAsString( this->getKey() );
}

uint32 TreeItem::getLevel()
{
	uint32 result = 0;

	TreeItem* parent = getParent();
	while ( NULL != parent ) {
		result ++;
		parent = parent->getParent();
	}

	return result;
}

void TreeItem::setCaption( const String& caption )
{
	getTreeModel()->setAsString( getKey(), caption );
}

uint32 TreeItem::getChildCount()
{
	return getTreeModel()->getChildCount( getKey() );
}

void TreeItem::addChild( TreeItem* child )
{
	this->getController()->addChildItem( this, child );
}

void TreeItem::removeChild( TreeItem* child )
{
	getController()->removeChildItem( this, child );
}

void TreeItem::clearChildren()
{
	getTreeModel()->clearChildren( this->getKey() );
}

void TreeItem::setSelectedImageIndex( const int32& selectedImageIndex )
{
	selectedImageIndex_ = selectedImageIndex;
}

void TreeItem::setExpandedImageIndex( const int32& expandedImageIndex )
{
	expandedImageIndex_ = expandedImageIndex;
}

TreeSubItem* TreeItem::addSubItem( const String& caption, void* data )
{
	TreeSubItem* result = new TreeSubItem(this);

	addSubItem( result );

	return result;
}

void TreeItem::addSubItem( TreeSubItem* subItem )
{
	getController()->insertItemSubItem( this, getController()->getItemSubItemCount(this), subItem );
}

void TreeItem::removeSubItem( const uint32& index )
{
	getController()->removeItemSubItem( this, getController()->getItemSubItem(this, index) );
}

bool TreeItem::getSubItems( std::vector<TreeSubItem*>& subItems )
{
	return getController()->getItemSubItems( this, subItems );
}

TreeSubItem* TreeItem::getSubItem( const uint32& index )
{
	return getController()->getItemSubItem(this, index);
}

uint32 TreeItem::getSubItemCount()
{
	return getController()->getItemSubItemCount(this);
}

void TreeItem::subItemChanged( TreeSubItem* item )
{

}
