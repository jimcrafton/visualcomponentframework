//TreeModel.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTreeModel.h"


using namespace VCF;


TreeModel::Key TreeModel::insert( const VariantData& value, const TreeModel::Key& parentKey )
{
	TreeModel::Key result = doInsert( value, parentKey );
	
	TreeModelEvent e(this, TreeModel::ItemAdded);
	e.key = result;
	e.parentKey = parentKey;

	NodeAdded( &e );

	TreeModelEvent e2(this, TreeModel::ItemAdded);
	e2.key = result;
	e2.parentKey = parentKey;
	ModelChanged( &e2 );

	return result;
}


void TreeModel::remove( const TreeModel::Key& key )
{
	TreeModel::Key parentKey = doRemove( key );	

	TreeModelEvent e(this, TreeModel::ItemRemoved);
	e.key = key;
	e.parentKey = parentKey;

	ModelChanged( &e );
}


void TreeModel::set( const TreeModel::Key& key, const VariantData& value )
{
	if ( doSet( key, value ) ) {
		TreeModelEvent itemEvent( this, TreeModel::ItemChanged );
		itemEvent.key = key;
		ModelChanged( &itemEvent );
	}
}


bool TreeModel::move( const TreeModel::Key& srcKey, const TreeModel::Key& destParentKey )
{
	bool result = false;
	TreeModel::Key k = doMove( srcKey,destParentKey );
	if ( k != InvalidKey ) {		
		TreeModelEvent e(this, TreeModel::ItemMoved);
		e.key = k;
		e.parentKey = destParentKey;
		ModelChanged(&e);
		result = true;
	}

	return result;
}

bool TreeModel::copy( const Key& srcKey, const Key& destKey, bool deepCopy )
{
	bool result = false;
	TreeModel::Key k = doCopy( srcKey, destKey, deepCopy );
	if ( k != InvalidKey ) {
		TreeModelEvent e(this, TreeModel::ItemAdded);

		e.key = k;
		e.parentKey = destKey;
		ModelChanged(&e);
		result = true;
	}
	return result;
}

void TreeModel::clearChildren( const Key& key )
{	
	if ( doClearChildren( key ) ) {

		TreeModelEvent e(this, TreeModel::ChildItemsRemoved);
		e.key = key;

		ModelChanged( &e );
	}
}