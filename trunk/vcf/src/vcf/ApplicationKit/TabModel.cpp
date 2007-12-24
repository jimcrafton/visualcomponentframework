//TabModel.cpp

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TabModel.h"


using namespace VCF;


TabModel::TabModel():
	selectedIndex_(0)
{

}

TabModel::~TabModel()
{

}

void TabModel::empty()
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

void TabModel::add( const VariantData& item )
{
	data_.push_back( item );
	ListModelEvent event( this, lmeItemAdded );
	event.item = &data_.back();
	event.index = data_.size() - 1;
	ItemAdded( &event );

	ListModelEvent event2( this, lmeItemAdded );
	ModelChanged( &event2 );
}

void TabModel::insert( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );

	ListModelEvent event( this, lmeItemAdded );
	event.item = &data_[index];
	event.index = index;
	ItemAdded( &event );

	ListModelEvent event2( this, lmeItemAdded );
	ModelChanged( &event2 );
}

void TabModel::remove( const VariantData& item )
{
	Array<VariantData>::iterator found = 
		std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, lmeItemRemoved );
		itemEvent.item = &(*found);
		itemEvent.index = found - data_.begin();
		ItemRemoved( &itemEvent );

		data_.erase( found );

		ListModelEvent event( this, lmeItemRemoved );
		ModelChanged( &event );
	}
}

void TabModel::removeAtIndex( const uint32 & index )
{
	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		ListModelEvent itemEvent( this, lmeItemRemoved );
		itemEvent.item = &(*found);
		itemEvent.index = index;
		ItemRemoved( &itemEvent );

		data_.erase( found );

		ListModelEvent event( this, lmeItemRemoved );
		ModelChanged( &event );
	}
}

VariantData TabModel::get( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	return data_[index];
}

uint32 TabModel::getIndexOf( const VariantData& item )
{
	uint32 result = IndexNotFound;
	Array<VariantData>::iterator found = std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		result = found - data_.begin();
	}

	return result;
}

String TabModel::getAsString( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	VariantData result = data_[index];
	return result.toString();
}

void TabModel::set( const uint32& index, const VariantData& item )
{
	data_[index] = item;
	ListModelEvent itemEvent( this, lmeItemChanged );
	itemEvent.item = &data_[index];
	ModelChanged( &itemEvent );
}

void TabModel::setAsString( const uint32& index, const String& item )
{
	data_[index].setFromString(item);
	ListModelEvent itemEvent( this, lmeItemChanged );
	itemEvent.item = &data_[index];
	ModelChanged( &itemEvent );
}

bool TabModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool TabModel::getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items )
{
	VCF_ASSERT( end - start <= data_.size() );
	VCF_ASSERT( data_.begin() + start != data_.end() );
	VCF_ASSERT( data_.begin() + end != data_.end() );

	items.assign( data_.begin() + start, data_.begin() + end );

	return !items.empty();
}

Enumerator<VariantData>* TabModel::getItems()
{
	return data_.getEnumerator();
}

uint32 TabModel::getCount()
{
	return data_.size();
}

void TabModel::setSelectedPage( const uint32& index )
{
	if ( selectedIndex_ != index ) {
		selectedIndex_ = index;
		TabModelEvent event(this, index);
		TabPageSelected( &event );
	}
}
