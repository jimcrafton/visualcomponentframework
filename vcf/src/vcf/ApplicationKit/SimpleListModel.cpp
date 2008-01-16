//SimpleListModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SimpleListModel.h"



using namespace VCF;


SimpleListModel::SimpleListModel()
{

}

SimpleListModel::~SimpleListModel()
{

}

void SimpleListModel::empty()
{
	ListModelEvent itemEvent( this, lmeItemRemoved );

	std::vector<VariantData>::iterator it = data_.begin();
	while ( it != data_.end() ) {
		itemEvent.item = &(*it);
		itemEvent.index = it - data_.begin();
		ItemRemoved( &itemEvent );

		if ( itemEvent.item->type == pdObject && shouldDeleteVarObjects() ) {
			Object* obj = *itemEvent.item;
			if ( NULL != obj ) {
				this->deleteVariantObject( obj );
			}
		}
		++it;
	}
	data_.clear();

	ListModelEvent event( this, lmeContentsDeleted );
	ModelChanged( &event );
}

void SimpleListModel::add( const VariantData& item )
{
	insert( data_.size(), item );
}

void SimpleListModel::insert( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );

	ListModelEvent event( this, lmeItemAdded );
	event.item = &data_[index];
	event.index = index;
	ItemAdded( &event );

	event.setType( lmeItemAdded );
	ModelChanged( &event );
}

void SimpleListModel::remove( const VariantData& item )
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

void SimpleListModel::removeAtIndex( const uint32 & index )
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

VariantData SimpleListModel::get( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	return data_[index];
}

uint32 SimpleListModel::getIndexOf( const VariantData& item )
{
	uint32 result = IndexNotFound;
	Array<VariantData>::iterator found = std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		result = found - data_.begin();
	}

	return result;
}

String SimpleListModel::getAsString( const uint32& index )
{
	VCF_ASSERT( index < data_.size() );

	VariantData result = data_[index];
	return result.toString();
}

void SimpleListModel::set( const uint32& index, const VariantData& item, bool addMissingValues )
{
	size_t missing = (index+1) - data_.size();

	if ( addMissingValues ) {
		if ( missing > 0 ) {
			data_.resize( missing + data_.size() );
		}
	}

	data_[index] = item;

	if ( addMissingValues && missing > 0 ) {
		for (size_t i=index;i<data_.size();i++ ) {
			ListModelEvent event( this, lmeItemAdded );
			event.item = &data_[i];
			event.index = i;
			ItemAdded( &event );
		}
	}

	ListModelEvent itemEvent( this, lmeItemChanged );
	itemEvent.item = &data_[index];
	itemEvent.index = index;
	ModelChanged( &itemEvent );
}

void SimpleListModel::setAsString( const uint32& index, const String& item, bool addMissingValues )
{
	VariantData v;
	v.setFromString( item );
	set( index, v, addMissingValues );
}

bool SimpleListModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool SimpleListModel::getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items )
{
	VCF_ASSERT( end - start <= data_.size() );
	VCF_ASSERT( data_.begin() + start != data_.end() );
	VCF_ASSERT( data_.begin() + end != data_.end() );

	items.assign( data_.begin() + start, data_.begin() + end );

	return !items.empty();
}

Enumerator<VariantData>* SimpleListModel::getItems()
{
	return data_.getEnumerator();
}

uint32 SimpleListModel::getCount()
{
	return data_.size();
}


/**
$Id: SimpleListModel.cpp 3315 2007-12-24 05:16:23Z ddiego $
*/
