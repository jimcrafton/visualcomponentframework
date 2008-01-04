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

void DefaultListModel::saveToStream( OutputStream * stream )
{

}


void DefaultListModel::loadFromStream( InputStream * stream )
{

}

void DefaultListModel::insertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value )
{
	SubItemPair val(index,value);
	subItemData_.insert( val );

	ListModelEvent itemEvent( this, lmeSubItemAdded );
	itemEvent.item = &data_[index];
	itemEvent.index = index;
	itemEvent.subIndex = subItemIndex;
	ModelChanged( &itemEvent );
}

void DefaultListModel::removeSubItem( const uint32& index, const uint32 & subItemIndex )
{
	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {
			subItemData_.erase( res.first );

			ListModelEvent itemEvent( this, lmeSubItemRemoved );
			itemEvent.item = &data_[index];
			itemEvent.index = index;
			itemEvent.subIndex = subItemIndex;
			ModelChanged( &itemEvent );

			break;
		}
		si ++;
		++res.first;
	}
}


VariantData DefaultListModel::getSubItem( const uint32& index, const uint32& subItemIndex ) 
{	
	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {			
			return res.first->second;
		}
		si ++;
		++res.first;
	}

	return VariantData::null();
}

String DefaultListModel::getSubItemAsString( const uint32& index, const uint32& subItemIndex ) 
{
	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {			
			return res.first->second.toString();
		}
		si ++;
		++res.first;
	}

	return String();
}

void DefaultListModel::setSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value, bool addMissingValues )
{
	size_t count = getSubItemsCount(index) ;
	if ( subItemIndex >= count ) {
		while ( count <= subItemIndex ) {

			SubItemPair val(index,VariantData::null());
			subItemData_.insert( val );

			count ++;
		}

		ListModelEvent itemEvent( this, lmeSubItemAdded );
		itemEvent.item = &data_[index];
		itemEvent.index = index;
		ModelChanged( &itemEvent );
	}

	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {			
			res.first->second = value;

			ListModelEvent itemEvent( this, lmeSubItemChanged );
			itemEvent.item = &data_[index];
			itemEvent.index = index;
			itemEvent.subIndex = subItemIndex;
			ModelChanged( &itemEvent );
			break;
		}
		si ++;
		++res.first;
	}	
}

void DefaultListModel::setSubItemAsString( const uint32& index, const uint32& subItemIndex, const String& value, bool addMissingValues )
{
	VariantData v;
	v.setFromString( value );

	setSubItem( index, subItemIndex, v, addMissingValues );
}

bool DefaultListModel::getSubItems( const uint32& index, std::vector<VariantData>& items )
{
	SubItemIteratorPair res = subItemData_.equal_range( index );

	while ( res.first != res.second ) {
		items.push_back( res.first->second );
		++res.first;
	}

	return !items.empty();
}

uint32 DefaultListModel::getSubItemsCount( const uint32& index )
{
	uint32 result = 0;

	SubItemIteratorPair res = subItemData_.equal_range( index );

	while ( res.first != res.second ) {
		result ++;
		++res.first;
	}

	return result;
}

/**
$Id$
*/
