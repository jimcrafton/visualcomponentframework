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
	ListModelEvent itemEvent( this, lmeItemRemoved );

	std::vector<VariantData>::iterator it = data_.begin();
	while ( it != data_.end() ) {
		itemEvent.item = &(*it);
		itemEvent.index = it - data_.begin();
		ItemRemoved( &itemEvent );
		++it;
	}
	data_.clear();

	ListModelEvent event( this, lmeContentsDeleted );
	ModelChanged( &event );
}

void DefaultListModel::add( const VariantData& item )
{
	data_.push_back( item );
	ListModelEvent event( this, lmeItemAdded );
	event.item = &data_.back();
	event.index = data_.size()-1;
	ItemAdded( &event );

	event.setType( lmeItemAdded );
	ModelChanged( &event );
}

void DefaultListModel::insert( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );

	ListModelEvent event( this, lmeItemAdded );
	event.item = &data_[index];
	event.index = index;
	ItemAdded( &event );

	event.setType( lmeItemAdded );
	ModelChanged( &event );
}

void DefaultListModel::remove( const VariantData& item )
{
	Array<VariantData>::iterator found = 
		std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, lmeItemRemoved );
		itemEvent.item = &(*found);
		itemEvent.index = found - data_.begin();
		ItemRemoved( &itemEvent );

		data_.erase( found );
	}
}

void DefaultListModel::removeAtIndex( const uint32 & index )
{
	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, lmeItemRemoved );
		itemEvent.item = &(*found);
		itemEvent.index = index;
		ItemRemoved( &itemEvent );

		data_.erase( found );

		itemEvent.setType( lmeItemRemoved );
		ModelChanged( &itemEvent );
	}
}

VariantData DefaultListModel::get( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	return data_[index];
}

uint32 DefaultListModel::getIndexOf( const VariantData& item )
{
	uint32 result = IndexNotFound;
	Array<VariantData>::iterator found = std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		result = found - data_.begin();
	}

	return result;
}

String DefaultListModel::getAsString( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	VariantData result = data_[index];
	return result.toString();
}

void DefaultListModel::set( const uint32& index, const VariantData& item, bool addMissingValues )
{
	data_[index] = item;
	ListModelEvent itemEvent( this, lmeItemChanged );
	itemEvent.item = &data_[index];
	itemEvent.index = index;
	ModelChanged( &itemEvent );
}

void DefaultListModel::setAsString( const uint32& index, const String& item, bool addMissingValues )
{
	data_[index].setFromString(item);
	ListModelEvent itemEvent( this, lmeItemChanged );
	itemEvent.item = &data_[index];
	itemEvent.index = index;
	ModelChanged( &itemEvent );
}

bool DefaultListModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool DefaultListModel::getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items )
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
