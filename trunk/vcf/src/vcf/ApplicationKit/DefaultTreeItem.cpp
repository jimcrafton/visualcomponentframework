//DefaultTreeItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"
#include "vcf/ApplicationKit/TreeModel.h"

using namespace VCF;

DefaultTreeItem::DefaultTreeItem()
{
	init();
}

DefaultTreeItem::DefaultTreeItem( const String& caption )
{
	init();
	caption_ = caption;
}

DefaultTreeItem::DefaultTreeItem( const String& caption, Control* owningControl, TreeModel* model )
{
	init();
	owningControl_ = owningControl;
	model_ = dynamic_cast<Model*>(model);
	setCaption( caption );
}

DefaultTreeItem::~DefaultTreeItem()
{
	std::vector<TreeItem::SubItem*>::iterator subIt = subItems_.begin();
	while ( subIt != subItems_.end() ) {
		(*subIt)->release();
		subIt++;
	}
	subItems_.clear();

	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	while ( it != childNodeItems_.end() ){
		delete *it;
		it++;
	}
	childNodeItems_.clear();
}

void DefaultTreeItem::init()
{
	imageIndex_ = 0;
	isExpanded_ = false;
	tag_ = -1;
	selectedImageIndex_ = -1;
	expandedImageIndex_ = -1;
	stateImageIndex_ = -1;

	selected_ = false;

	itemState_ = Item::idsNone;

	bounds_.setRect(0.0,0.0,0.0,0.0);
	owningControl_ = NULL;
	caption_ = "";
	childNodeItems_.clear();
	parent_ = NULL;
	textBold_ = false;

	TextColor_ = *GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW_TEXT );

	userData_ = NULL;
	enumContainer_.initContainer( childNodeItems_ );

	enumSubItemsContainer_.initContainer( subItems_ );

}

bool DefaultTreeItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}


unsigned long DefaultTreeItem::getIndex()
{
	return index_;
}

void DefaultTreeItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void* DefaultTreeItem::getData()
{
	return userData_;
}

void DefaultTreeItem::setData( void* data )
{
	userData_ = data;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

Color* DefaultTreeItem::getTextColor()
{
	return &TextColor_;
}

void DefaultTreeItem::setTextColor(Color* color)
{
	TextColor_ = *color;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

void DefaultTreeItem::setTextBold(const bool& bold)
{
	textBold_ = bold;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

bool DefaultTreeItem::getTextBold()
{
	return textBold_;
}

bool DefaultTreeItem::isRoot()
{
	return ( NULL == parent_ );
}

bool DefaultTreeItem::isLeaf()
{
	return  childNodeItems_.empty();
}

TreeItem* DefaultTreeItem::getParent()
{
	return parent_;
}

void DefaultTreeItem::setParent( TreeItem* parent )
{
	parent_ = parent;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

TreeItem* DefaultTreeItem::getNextChildNodeItem()
{
	if ( NULL != parent_ ) {
		DefaultTreeItem* dtParent = dynamic_cast<DefaultTreeItem*>(parent_);
		if ( NULL != dtParent ) {
			std::vector<TreeItem*>::iterator it = std::find( dtParent->childNodeItems_.begin(),
															 dtParent->childNodeItems_.end(),
															 this );

			it ++;
			if ( it != dtParent->childNodeItems_.end() ) {
				return *it;
			}
		}
	}
	return NULL;
}

TreeItem* DefaultTreeItem::getPrevChildNodeItem()
{
	if ( NULL != parent_ ) {
		DefaultTreeItem* dtParent = dynamic_cast<DefaultTreeItem*>(parent_);
		if ( (NULL != dtParent) && (index_ > 0) ) {
			std::vector<TreeItem*>::iterator it = std::find( dtParent->childNodeItems_.begin(),
															 dtParent->childNodeItems_.end(),
															 this );
			it --;

			if ( (it != dtParent->childNodeItems_.end()) && ( it >= dtParent->childNodeItems_.begin() ) ) {
				return *it;
			}
		}
	}
	return NULL;
}

String DefaultTreeItem::getCaption()
{
	Control* control = getControl();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( caption_ );
	}

	return caption_;
}

void DefaultTreeItem::setCaption( const String& caption )
{
	caption_ = caption;

	changed( ITEM_EVENT_TEXT_CHANGED );
}

uint32 DefaultTreeItem::getChildCount()
{
	return childNodeItems_.size();
}

Enumerator<TreeItem*>* DefaultTreeItem::getChildren()
{
	return enumContainer_.getEnumerator();
}

void DefaultTreeItem::addChild( TreeItem* child )
{
//	StringUtils::trace( "Adding child " + child->getCaption() + "\n" );
	childNodeItems_.push_back( child );
	child->setParent( this );
	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
}

void DefaultTreeItem::insertChild( const unsigned long& index, TreeItem* child )
{
	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	childNodeItems_.insert( it + index, child );
	child->setParent( this );
	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
	it = childNodeItems_.begin() + index;
	int i = index;
	while ( it != childNodeItems_.end() ) {
		TreeItem* item = *it;
		item->setIndex( i );
		it ++;
		i++;
	}
}

void DefaultTreeItem::deleteChild( TreeItem* child )
{
	std::vector<TreeItem*>::iterator found = std::find( childNodeItems_.begin(), childNodeItems_.end(), child );
	if ( found != childNodeItems_.end() ) {
		int index = found - childNodeItems_.begin();
		TreeItem* item = *found;
		ItemEvent event( child, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );
		delete item;
		item = NULL;
		childNodeItems_.erase ( found );
		int i = index;
		std::vector<TreeItem*>::iterator it = childNodeItems_.begin() + index;
		while ( it != childNodeItems_.end() ) {
			item = *it;
			item->setIndex( i );
			it ++;
			i ++;
		}
	}
}

void DefaultTreeItem::deleteChildAtIndex( const unsigned long& index )
{
	std::vector<TreeItem*>::iterator found =  childNodeItems_.begin() + index;
	if ( found != childNodeItems_.end() ) {
		TreeItem* item = *found;
		ItemEvent event( item, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );
		childNodeItems_.erase ( found );
		delete item;
		item = NULL;
		int i = index;
		std::vector<TreeItem*>::iterator it = childNodeItems_.begin() + index;
		while ( it != childNodeItems_.end() ) {
			item = *it;
			item->setIndex( i );
			it ++;
			i ++;
		}
	}
}

void DefaultTreeItem::clearChildren()
{
	for (std::vector<TreeItem*>::iterator it = childNodeItems_.begin(); it != childNodeItems_.end(); it ++ ){
		TreeItem* item = *it;
		item->clearChildren();
		ItemEvent deleteEvent( item, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &deleteEvent );
		delete item;
	}
	childNodeItems_.clear();

	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}


void DefaultTreeItem::setModel( Model* model )
{
	Item::setModel( model );
	for (std::vector<TreeItem*>::iterator it = childNodeItems_.begin(); it != childNodeItems_.end(); it ++ ){
		(*it)->setModel( model );
	}
}

void DefaultTreeItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	ItemEvent event( this, context );
	ItemPaint.fireEvent( &event );
}

bool DefaultTreeItem::isSelected()
{
	return selected_;
}

void DefaultTreeItem::setSelected( const bool& selected )
{
	selected_ = selected;
	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemSelected.fireEvent( &event );
}

void DefaultTreeItem::expand( const bool& isExpanded )
{
	isExpanded_ = isExpanded;
	changed( DefaultTreeItem::teItemExpanded );
}

void DefaultTreeItem::expandAllChildren( const bool& isExpanded )
{
	expand( isExpanded );

	Enumerator<TreeItem*>* children = getChildren();
	while ( children->hasMoreElements() ) {
		TreeItem* item = children->nextElement();

		item->expandAllChildren( isExpanded );
	}
}

ulong32 DefaultTreeItem::getLevel()
{
	ulong32 result = 0;

	if ( false == isRoot() ) {
		TreeItem* parent = getParent();
		if ( NULL != parent ) {
			result = parent->getLevel();
			result ++;
		}
	}
	return result;
}

void DefaultTreeItem::setControl( Control* control )
{
	Item::setControl( control );

	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	while ( it != childNodeItems_.end() ){
		TreeItem* item = *it;
		item->setControl( control );
		it++;
	}
}

void DefaultTreeItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultTreeItem::setSelectedImageIndex( const long& selectedImageIndex )
{
	selectedImageIndex_ = selectedImageIndex;
	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::setExpandedImageIndex( const long& expandedImageIndex )
{
	expandedImageIndex_ = expandedImageIndex;
	changed( ITEM_EVENT_CHANGED );
}


void DefaultTreeItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}

void DefaultTreeItem::setStateImageIndex( const long& index )
{
	stateImageIndex_ = index;
	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::addSubItem( const String& caption, void* data )
{
	SubItem* subItem = new SubItem(this);
	subItems_.push_back( subItem );
	subItem->setCaption( caption );
	subItem->setData( data );

	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::addSubItem( TreeItem::SubItem* subItem )
{
	subItems_.push_back( subItem );

	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::removeSubItem( const ulong32& index )
{
	std::vector<SubItem*>::iterator found = subItems_.begin() + index;
	if ( found != subItems_.end() ) {
		changed( ITEM_EVENT_CHANGED );

		subItems_.erase( found );
	}
}

TreeItem::SubItem* DefaultTreeItem::getSubItem( const ulong32& index )
{
	SubItem* result = NULL;
	if ( index < subItems_.size() ) {
		result = subItems_[index];
	}
	return result;
}

void DefaultTreeItem::subItemChanged( TreeItem::SubItem* item )
{

}

void DefaultTreeItem::changed( const ulong32& eventType )
{
	if ( NULL != getModel() ) {
		getModel()->updateAllViews();
	}
	else {

		//throw InvalidPointerException( MAKE_ERROR_MSG_2("This tree item has no model!") );
	}
	ItemEvent event( this, eventType );
	ItemChanged.fireEvent( &event );
}


/**
$Id$
*/
