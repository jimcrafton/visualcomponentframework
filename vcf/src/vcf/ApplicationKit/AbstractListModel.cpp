//AbstractListModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListItem.h"
#include "vcf/ApplicationKit/AbstractListModel.h"

using namespace VCF;

AbstractListModel::AbstractListModel()
{
	listContainer_.initContainer( listItems_ );
}

AbstractListModel::~AbstractListModel()
{
	std::vector<ListItem*>::iterator it = listItems_.begin();
	while ( it != listItems_.end() ){
		delete *it;
		it ++;
	}
	listItems_.clear();
}

void AbstractListModel::addItem( ListItem* item )
{
	this->listItems_.push_back( item );
	item->setIndex( listItems_.size() - 1 );
	ListModelEvent event( dynamic_cast<Object*>(this), item );
	ItemAdded.fireEvent( &event );
}

void AbstractListModel::deleteItemAtIndex( const unsigned long& index )
{
	ListItem* item = listItems_[index];
	item->setIndex( index );
	ListModelEvent event( dynamic_cast<Object*>(this), item );
	ItemDeleted.fireEvent( &event );

	delete item;
	listItems_.erase( listItems_.begin() + index );
}

void AbstractListModel::deleteItem( ListItem* item )
{
	std::vector<ListItem*>::iterator it = std::find( listItems_.begin(), listItems_.end(), item );
	if ( it != listItems_.end() ){

		item->setIndex( listItems_.begin() - it );

		ListModelEvent event( dynamic_cast<Object*>(this), item );
		ItemDeleted.fireEvent( &event );
		delete *it;
		listItems_.erase( it );
	}
}

void AbstractListModel::empty()
{
	Object* source = dynamic_cast<Object*>(this);

	std::vector<ListItem*>::iterator it = listItems_.begin();
	ListModelEvent itemEvent( source, LIST_MODEL_ITEM_DELETED );
	while ( it != listItems_.end() ){
		itemEvent.setListItem( *it );
		ItemDeleted.fireEvent( &itemEvent );
		delete *it;
		it ++;
	}
	listItems_.clear();

	ListModelEvent event( source, LIST_MODEL_CONTENTS_DELETED );
	ContentsChanged.fireEvent( &event );
}

void AbstractListModel::insertItem( const unsigned long& index, ListItem* item )
{
	listItems_.insert( listItems_.begin() + index, item );
	item->setIndex( index );
	ListModelEvent event( dynamic_cast<Object*>(this), item );
	ItemAdded.fireEvent( &event );
}


ListItem* AbstractListModel::getItemFromIndex( const unsigned long& index )
{
	ListItem* result = NULL;
	if ( index < listItems_.size() ){
		result = listItems_[index];
	}
	return result;
}

ulong32 AbstractListModel::getItemIndex( ListItem* item )
{
	std::vector<ListItem*>::iterator found = std::find( listItems_.begin(), listItems_.end(), item );
	if ( found != listItems_.end() ) {
		return ( found - listItems_.begin() );
	}
	return 0;
}

Enumerator<ListItem*>* AbstractListModel::getItems()
{
	return listContainer_.getEnumerator();
}

unsigned long AbstractListModel::getCount()
{
	return this->listItems_.size();
}

void AbstractListModel::saveToStream( OutputStream * stream )
{
	Enumerator<ListItem*>* items = this->getItems();
	long count = this->getCount();
	stream->write( count );
	while ( items->hasMoreElements() ){
		ListItem* item = items->nextElement();
		if ( NULL != item ){
			Persistable* persistableItem = dynamic_cast<Persistable*>(item);
			if ( NULL != persistableItem ){
				stream->write( persistableItem );
			}
			else {
				String caption = item->getCaption();
				stream->write( caption );
			}
		}
	}
}

void AbstractListModel::loadFromStream( InputStream * stream )
{
	long count = 0;
	stream->read( count );
	for (int i=0;i<count;i++){
		String s = "";
		stream->read( s );
	}
}


/**
$Id$
*/
