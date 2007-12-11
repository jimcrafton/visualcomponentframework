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


void DefaultListItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	ItemEvent event( this, context );
	ItemPaint( &event );
}

ListItem::SubItem* DefaultListItem::addSubItem( const String& caption, void* data )
{
	ListItem::SubItem* newSubItem = new ListItem::SubItem( this );
	newSubItem->setCaption( caption );
	newSubItem->setData( data );
	addSubItem( newSubItem );
	return newSubItem;
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



/**
$Id$
*/
