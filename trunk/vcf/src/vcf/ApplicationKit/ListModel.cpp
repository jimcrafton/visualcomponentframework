//ListModel.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ListModel.h"


using namespace VCF;


void ListModel::insert( const uint32 & index, const VariantData& item )
{
	if ( doInsert( index, item ) ) {
		
		ListModelEvent event( this, lmeItemAdded );
		event.item = (VariantData*) &item;
		event.index = index;
		ItemAdded( &event );
		
		event.setType( lmeItemAdded );
		ModelChanged( &event );
	}
}

void ListModel::remove( const uint32& index )
{
	if ( doRemove( index ) ) {
		
	}
}

void ListModel::set( const uint32& index, const VariantData& item )
{
	if ( doSet( index, item ) ) {
		ListModelEvent itemEvent( this, lmeItemChanged );
		itemEvent.item = (VariantData*)&item;
		itemEvent.index = index;
		ModelChanged( &itemEvent );
	}
}

void ListModel::insertSubItem( const uint32& index, const uint32 & subItemIndex, const VariantData& value )
{	
	if ( doInsertSubItem( index, subItemIndex, value ) ) {
		ListModelEvent itemEvent( this, lmeSubItemAdded );
		itemEvent.item = (VariantData*) &value;
		itemEvent.index = index;
		itemEvent.subIndex = subItemIndex;
		ModelChanged( &itemEvent );
	}
}

void ListModel::removeSubItem( const uint32& index, const uint32 & subItemIndex )
{
	if ( doRemoveSubItem( index, subItemIndex ) ) {
		
	}
}

void ListModel::setSubItem( const uint32& index, const uint32& subItemIndex, const VariantData& value )
{
	if ( doSetSubItem( index, subItemIndex, value ) ) {
		ListModelEvent itemEvent( this, lmeSubItemChanged );
		itemEvent.item = (VariantData*)&value;
		itemEvent.index = index;
		itemEvent.subIndex = subItemIndex;
		ModelChanged( &itemEvent );
	}
}
