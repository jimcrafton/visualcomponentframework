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
	uint64 key = 0;
	//SubItemPair val(key,
}

void DefaultListModel::removeSubItem( const uint32& index, const uint32 & subItemIndex )
{

}


VariantData DefaultListModel::getSubItem( const uint32& index, const uint32& subItemIndex ) 
{		
	return VariantData::null();
}

String DefaultListModel::getSubItemAsString( const uint32& index, const uint32& subItemIndex ) 
{
	return String();
}

void DefaultListModel::setSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value )
{

}

void DefaultListModel::setSubItemAsString( const uint32& index, const uint32& subItemIndex, const String& value )
{

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
