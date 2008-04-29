//TreeListModel.cpp
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TreeListModel.h"

using namespace VCF;

void TreeListModel::empty()
{
	SubItemMap::iterator it = subItemData_.begin();
	if ( shouldDeleteVarObjects() ) {
		while ( it != subItemData_.end() ) {
			VariantData& data = it->second;
			if ( data.type == pdObject ) {
				Object* obj = data;
				if ( NULL != obj ) {
					deleteVariantObject( obj );
				}
			}
			++it;
		}
	}

	subItemData_.clear();
	DefaultTreeModel::empty();
}

bool TreeListModel::doInsertSubItem( const Key& key, const uint32 & subItemIndex, const VariantData& value ) 
{
	SubItemPair val(key,value);
	subItemData_.insert( val );
	return true;
}

bool TreeListModel::doRemoveSubItem( const Key& key, const uint32 & subItemIndex )
{
	SubItemIteratorPair res = subItemData_.equal_range( key );
	
	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == subItemIndex ) {
			notifySubItemRemoved( key, subItemIndex );
			
			subItemData_.erase( res.first );
			
			return true;
		}
		si ++;
		++res.first;
	}
	return false;
}

VariantData TreeListModel::getSubItem( const Key& key, const uint32& subItemIndex ) 
{
	SubItemIteratorPair res = subItemData_.equal_range( key );
	
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

bool TreeListModel::doSetSubItem( const Key& key, const uint32& subItemIndex, const VariantData& value )
{
	size_t count = getSubItemsCount(key) ;
	if ( subItemIndex >= count ) {
		while ( count <= subItemIndex ) {
			
			SubItemPair val(key,VariantData::null());
			subItemData_.insert( val );
			
			count ++;
		}
		
		notifySubItemAdded( key,  subItemIndex );		
	}
	
	SubItemIteratorPair res = subItemData_.equal_range( key );
	
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

uint32 TreeListModel::getSubItemsCount( const Key& key ) 
{
	uint32 result = 0;
	
	SubItemIteratorPair res = subItemData_.equal_range( key );
	
	while ( res.first != res.second ) {
		result ++;
		++res.first;
	}
	
	return result;
}

bool TreeListModel::getSubItems( const Key& key, std::vector<VariantData>& items )
{
	
	SubItemIteratorPair res = subItemData_.equal_range( key );
	
	while ( res.first != res.second ) {
		items.push_back( res.first->second );
		++res.first;
	}
	
	return !items.empty();
}