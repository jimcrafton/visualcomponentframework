//DefaultColumnModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DefaultColumnModel.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"


using namespace VCF;



DefaultColumnModel::DefaultColumnModel()
{
	init();
}

DefaultColumnModel::~DefaultColumnModel()
{
	std::vector<ColumnItem*>::iterator it = columnItems_.begin();

	while ( it != columnItems_.end() ) {
		ColumnItem* item = *it;
		delete item;
		item = NULL;
		it ++;
	}

	columnItems_.clear();
}

void DefaultColumnModel::init()
{
	columnContainer_.initContainer( columnItems_ );
}

void DefaultColumnModel::validate()
{

}

void DefaultColumnModel::empty()
{
	std::vector<ColumnItem*>::reverse_iterator it = columnItems_.rbegin();
	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED );
	while ( it != columnItems_.rend() ) {
		ColumnItem* item = *it;
		event.setColumnItem( item );
		ItemDeleted( &event );
		delete item;
		item = NULL;
		it ++;
	}

	columnItems_.clear();
}

void DefaultColumnModel::deleteItem( ColumnItem* item)
{
	std::vector<ColumnItem*>::iterator found = std::find( columnItems_.begin(), columnItems_.end(), item );
	if ( found != columnItems_.end() ) {

		ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED, item );
		ItemDeleted( &event );

		columnItems_.erase( found );

		delete item;
	}
}

void DefaultColumnModel::deleteItem(const uint32 & index)
{
	if ( index < columnItems_.size() ) {
		std::vector<ColumnItem*>::iterator found = columnItems_.begin() + index;
		if ( found != columnItems_.end() ) {
			std::vector<ColumnItem*>::iterator it = found+1;
			//hack - this is probably not a good idea
			//the point is to reset all the indices of the
			//items, but this is extremely slow on large data sets
			while ( it != columnItems_.end() ) {
				ColumnItem* item = *it;
				item->setIndex( item->getIndex()-1 );
				it ++;
			}

			ColumnItem* item = *found;
			ColumnModelEvent event( this, COLUMN_MODEL_ITEM_DELETED, item );
			ItemDeleted( &event );
			columnItems_.erase( found );
			delete item;
			item = NULL;
		}
	}
}

void DefaultColumnModel::insertItem(const uint32 & index, ColumnItem * item)
{
	columnItems_.insert( columnItems_.begin() + index, item );
	item->setIndex( index );
	item->setModel( this );

	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_ADDED, item );
	ItemAdded( &event );
}

void DefaultColumnModel::addItem( ColumnItem* item)
{
	columnItems_.push_back( item );
	item->setIndex( columnItems_.size() - 1 );
	item->setModel( this );
	ColumnModelEvent event( this, COLUMN_MODEL_ITEM_ADDED, item );
	ItemAdded( &event );
}

ColumnItem* DefaultColumnModel::getItemFromIndex( const uint32& index )
{
	ColumnItem* result = NULL;
	if ( index < columnItems_.size() ) {
        result = columnItems_[index];
	}
	return result;
}

Enumerator<ColumnItem*>* DefaultColumnModel::getItems()
{
	return columnContainer_.getEnumerator();
}

uint32 DefaultColumnModel::getCount()
{
	return columnItems_.size();
}

void DefaultColumnModel::saveToStream( OutputStream * stream )
{
	Enumerator<ColumnItem*>* items = this->getItems();
	int32 count = this->getCount();
	stream->write( count );
	while ( items->hasMoreElements() ){
		ColumnItem* item = items->nextElement();
		if ( NULL != item ){
			Persistable* persistableItem = dynamic_cast<Persistable*>(item);
			stream->write( (bool)(persistableItem != NULL) );
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

void DefaultColumnModel::loadFromStream( InputStream * stream )
{
	int32 count = 0;
	stream->read( count );
	for (int i=0;i<count;i++){
		bool isPersistentItem = false;
		stream->read( isPersistentItem );		
	}
}


/**
$Id$
*/
