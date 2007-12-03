//ColumnModel.cpp

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ColumnModel.h"


using namespace VCF;

ColumnModel::ColumnModel()
{

}


void ColumnModel::empty()
{
	data_.clear();
}

void ColumnModel::addItem( const VariantData& item )
{
	data_.push_back( item );
}

void ColumnModel::insertItem( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );
}

void ColumnModel::deleteItem( const VariantData& item )
{
	Array<VariantData>::iterator found = 
		std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		data_.erase( found );
	}
}

void ColumnModel::deleteItemAtIndex( const uint32 & index )
{
	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		data_.erase( found );
	}
}

VariantData ColumnModel::getItem( const uint32& index )
{
	return data_[index];
}

uint32 ColumnModel::getItemIndex( const VariantData& item )
{
	uint32 result = ListModel::IndexNotFound;
	Array<VariantData>::iterator found = std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		result = found - data_.begin();
	}

	return result;
}

String ColumnModel::getItemAsString( const uint32& index )
{
	VariantData result = data_[index];
	return result.toString();
}

void ColumnModel::setItem( const uint32& index, const VariantData& item )
{
	data_[index] = item;
}

void ColumnModel::setItemAsString( const uint32& index, const String& item )
{
	data_[index].setFromString(item);
}

bool ColumnModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool ColumnModel::getItems( const uint32& start, const uint32& end, std::vector<VariantData>& items )
{
	VCF_ASSERT( end - start <= data_.size() );
	VCF_ASSERT( data_.begin() + start != data_.end() );
	VCF_ASSERT( data_.begin() + end != data_.end() );

	items.assign( data_.begin() + start, data_.begin() + end );

	return !items.empty();
}

Enumerator<VariantData>* ColumnModel::getItems()
{
	return data_.getEnumerator();
}

uint32 ColumnModel::getCount()
{
	return data_.size();
}

