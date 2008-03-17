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

bool DefaultListModel::doInsertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value )
{
	SubItemPair val(index,value);
	subItemData_.insert( val );
	return true;
}

bool DefaultListModel::doRemoveSubItem( const uint32& index, const uint32 & subItemIndex )
{
	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {
			notifySubItemRemoved( index, subItemIndex, res.first->second );

			subItemData_.erase( res.first );

			return true;
		}
		si ++;
		++res.first;
	}
	return false;
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


bool DefaultListModel::doSetSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value )
{
	size_t count = getSubItemsCount(index) ;
	if ( subItemIndex >= count ) {
		while ( count <= subItemIndex ) {

			SubItemPair val(index,VariantData::null());
			subItemData_.insert( val );

			count ++;
		}

		notifySubItemAdded( index, data_[index] );		
	}

	SubItemIteratorPair res = subItemData_.equal_range( index );

	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {			
			res.first->second = value;			
			return true;
		}
		si ++;
		++res.first;
	}	

	return false;
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
