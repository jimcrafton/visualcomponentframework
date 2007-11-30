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
	data_.clear();
}

void DefaultListModel::addItem( const VariantData& item )
{
	data_.push_back( item );
}

void DefaultListModel::insertItem( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );
}

void DefaultListModel::deleteItem( const VariantData& item )
{
	Array<VariantData>::iterator found = 
		std::find( data_.begin(), data_.end(), item );
	if ( found != data_.end() ) {
		data_.erase( found );
	}
}

void DefaultListModel::deleteItemAtIndex( const uint32 & index )
{
	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		data_.erase( found );
	}
}

VariantData DefaultListModel::getItem( const uint32& index )
{
	return data_[index];
}

String DefaultListModel::getItemAsString( const uint32& index )
{
	VariantData result = data_[index];
	return result.toString();
}

void DefaultListModel::setItem( const uint32& index, const VariantData& item )
{
	data_[index] = item;
}

void DefaultListModel::setItemAsString( const uint32& index, const String& item )
{
	data_[index].setFromString(item);
}

bool DefaultListModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

uint32 DefaultListModel::getCount()
{
	return data_.size();
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
