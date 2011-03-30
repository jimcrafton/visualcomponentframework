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
	std::vector<VariantData>::iterator it = data_.begin();
	while ( it != data_.end() ) {
		VariantData& v = *it;
		if ( v.type == pdObject && shouldDeleteVarObjects() ) {
			Object* obj = v;
			if ( NULL != obj ) {
				this->deleteVariantObject( obj );
			}
		}
		++it;
	}
	data_.clear();
}

void SimpleListModel::copy( Object* source )
{
	ListModel* lm = dynamic_cast<ListModel*>( source );
	if ( NULL != lm ) {
		empty();
		for (uint32 i=0;i<lm->getCount();i++ ) {
			add( lm->get(i) );
		}
	}
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


bool SimpleListModel::doInsert( const uint32 & index, const VariantData& item )
{
	data_.insert( data_.begin() + index, item );

	return true;
}

bool SimpleListModel::doRemove( const uint32 & index )
{
	if ( IndexNotFound == index ) {
		return false;
	}

	Array<VariantData>::iterator found = data_.begin() + index;		
	if ( found != data_.end() ) {
		VariantData v = *found;
		data_.erase( found );	

		notifyRemove( index, v );

		if ( v.type == pdObject && shouldDeleteVarObjects() ) {
			Object* obj = v;
			if ( NULL != obj ) {
				deleteVariantObject( obj );
			}
		}

		
		return true;
	}

	return false;
}

VariantData SimpleListModel::get( const uint32& index )
{
	if ( ListModel::InvalidIndex == index ) {
		return VariantData::null();
	}

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

bool SimpleListModel::doSet( const uint32& index, const VariantData& item )
{
	size_t missing = 0;
	if ( (index+1) > data_.size() ) {
		missing = (index+1) - data_.size();
	}
	
	if ( missing > 0 ) {
		data_.resize( missing + data_.size() );
	}	

	data_[index] = item;

	if ( missing > 0 ) {
		for (size_t i=index;i<data_.size();i++ ) {
			notifyAdded( i, data_[i] );
		}
	}

	return true;	
}


bool SimpleListModel::getItems( std::vector<VariantData>& items )
{
	items = data_;
	return !items.empty();
}

bool SimpleListModel::verifyRange( const uint32& start, const uint32& end )
{
	bool result = false;

	if ( end < data_.size() ) {
		result = true;
	}

	return result;
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
