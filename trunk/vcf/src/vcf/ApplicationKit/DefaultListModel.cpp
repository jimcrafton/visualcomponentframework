//DefaultListModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultListModel.h"



using namespace VCF;


DefaultListModel::DefaultListModel()
{

}

DefaultListModel::~DefaultListModel()
{

}

void DefaultListModel::empty()
{
	ListModelEvent itemEvent( this, LIST_MODEL_ITEM_DELETED );

	std::vector<VariantData>::iterator it = data_.begin();
	while ( it != data_.end() ) {
		itemEvent.item = &(*it);
		ItemDeleted( &itemEvent );
		++it;
	}
	data_.clear();

	ListModelEvent event( this, LIST_MODEL_CONTENTS_DELETED );
	ContentsChanged( &event );
}

void DefaultListModel::addItem( const VariantData& item )
{
	data_.push_back( item );
	ListModelEvent event( this, LIST_MODEL_ITEM_ADDED );
	event.item = &data_.back();
	ItemAdded( &event );
}

void DefaultListModel::insertItem( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );

	ListModelEvent event( this, LIST_MODEL_ITEM_ADDED );
	event.item = &data_[index];
	ItemAdded( &event );
}

void DefaultListModel::deleteItem( const VariantData& item )
{
	Array<VariantData>::iterator found = 
		std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, LIST_MODEL_ITEM_DELETED );
		itemEvent.item = &(*found);
		ItemDeleted( &itemEvent );

		data_.erase( found );
	}
}

void DefaultListModel::deleteItemAtIndex( const uint32 & index )
{
	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, LIST_MODEL_ITEM_DELETED );
		itemEvent.item = &(*found);
		ItemDeleted( &itemEvent );

		data_.erase( found );
	}
}

VariantData DefaultListModel::getItem( const uint32& index )
{
	return data_[index];
}

uint32 DefaultListModel::getItemIndex( const VariantData& item )
{
	uint32 result = IndexNotFound;
	Array<VariantData>::iterator found = std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		result = found - data_.begin();
	}

	return result;
}

String DefaultListModel::getItemAsString( const uint32& index )
{
	VariantData result = data_[index];
	return result.toString();
}

void DefaultListModel::setItem( const uint32& index, const VariantData& item )
{
	data_[index] = item;
	ListModelEvent itemEvent( this, LIST_MODEL_ITEM_CHANGED );
	itemEvent.item = &data_[index];
	ContentsChanged( &itemEvent );
}

void DefaultListModel::setItemAsString( const uint32& index, const String& item )
{
	data_[index].setFromString(item);
	ListModelEvent itemEvent( this, LIST_MODEL_ITEM_CHANGED );
	itemEvent.item = &data_[index];
	ContentsChanged( &itemEvent );
}

bool DefaultListModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool DefaultListModel::getItems( const uint32& start, const uint32& end, std::vector<VariantData>& items )
{
	VCF_ASSERT( end - start <= data_.size() );
	VCF_ASSERT( data_.begin() + start != data_.end() );
	VCF_ASSERT( data_.begin() + end != data_.end() );

	items.assign( data_.begin() + start, data_.begin() + end );

	return !items.empty();
}

Enumerator<VariantData>* DefaultListModel::getItems()
{
	return data_.getEnumerator();
}

uint32 DefaultListModel::getCount()
{
	return data_.size();
}

bool DefaultListModel::supportsSubItems() 
{
	return false;
}

VariantData DefaultListModel::getSubItem( const uint32& index, const uint32& subItemIndex )
{
	return VariantData::null();
}

String DefaultListModel::getSubItemAsString( const uint32& index, const uint32& subItemIndex )
{
	return String();
}


void DefaultListModel::saveToStream( OutputStream * stream )
{

}


void DefaultListModel::loadFromStream( InputStream * stream )
{

}


/**
$Id$
*/
