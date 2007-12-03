//DefaultListItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/ListModel.h"


using namespace VCF;



DefaultListItem::DefaultListItem()
{
	init();
}

DefaultListItem::DefaultListItem( ListModel* model )
{
	init();
	model_ = model;
}


DefaultListItem::~DefaultListItem()
{
	std::vector<SubItem*>::iterator it = subItems_.begin();
	while ( it != subItems_.end() ) {
		SubItem* subItem = *it;

		delete subItem;
		subItem = NULL;

		it ++;
	}
}

void DefaultListItem::init()
{
	itemState_ = Item::idsNone;
	tag_ = -1;
	model_ = NULL;
	owningControl_ = NULL;
	imageIndex_ = 0;
	data_ = NULL;
	index_ = 0;
	model_ = NULL;
	selected_ = false;

	bounds_.setRect( 0.0, 0.0, 0.0, 0.0 );

	subItemsContainer_.initContainer( subItems_ );

}

bool DefaultListItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}

uint32 DefaultListItem::getIndex()
{
	return index_;
}

void DefaultListItem::setIndex( const uint32& index )
{
	index_ = index;
}

void* DefaultListItem::getData()
{
	return data_;
}

void DefaultListItem::setData( void* data )
{
	data_ = data;
}

String DefaultListItem::getCaption()
{
	//control's getUseLocaleStrings() takes precedence over ours
	Control* control = getControl();
	ListModel* lm = (ListModel*) getModel();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( lm->getItemAsString( index_ ) );
	}
	return lm->getItemAsString( index_ );
}

void DefaultListItem::setCaption( const String& caption )
{
	ListModel* lm = (ListModel*) getModel();
	lm->setItemAsString( index_, caption );

	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged( &event );
}

void DefaultListItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	ItemEvent event( this, context );
	ItemPaint( &event );
}

bool DefaultListItem::isSelected()
{
	return selected_;
}

void DefaultListItem::setSelected( const bool& selected )
{
	selected_ = selected;
	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemSelected( &event );
}

void DefaultListItem::setImageIndex( const int32& imageIndex )
{
	imageIndex_ = imageIndex;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged( &event );
}

void DefaultListItem::addSubItem( const String& caption, void* data )
{
	ListItem::SubItem* newSubItem = new ListItem::SubItem( this );
	newSubItem->setCaption( caption );
	newSubItem->setData( data );
	addSubItem( newSubItem );
}

void DefaultListItem::addSubItem( ListItem::SubItem* subItem )
{
	subItems_.push_back( subItem );

	ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_ADDED );
	SubItemAdded( &event );
}

void DefaultListItem::removeSubItem( const uint32& index )
{
	std::vector<SubItem*>::iterator found = subItems_.begin() + index;
	if ( found != subItems_.end() ) {
		SubItem* subItem = *found;
		ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_DELETED );
		SubItemDeleted( &event );

		subItems_.erase( found );

		delete subItem;
		subItem = NULL;
	}
}


Enumerator<ListItem::SubItem*>* DefaultListItem::getSubItems()
{
	return subItemsContainer_.getEnumerator();
}

ListItem::SubItem* DefaultListItem::getSubItem( const uint32& index )
{
    ListItem::SubItem* result = NULL;
    if ( index < subItems_.size() ) {
        result = subItems_[index];
    }
	return result;
}

uint32 DefaultListItem::getSubItemCount()
{
	return subItems_.size();
}

void DefaultListItem::subItemChanged( ListItem::SubItem* item )
{
	ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_CHANGED );
	SubItemChanged( &event );
}

void DefaultListItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}


/**
$Id$
*/
