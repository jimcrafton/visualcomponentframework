//DataLink.cpp

#include "DatabaseKit.h"
#include "DataLink.h"


using namespace VCF;


DataLink::DataLink():	
	dataSource_(NULL),
	dataSrcFixed_(false),
	active_(false),
	editing_(false),
	readOnly_(false),
	updating_(false)
{

}



size_t DataLink::getRecordCount()
{
	size_t result = 0;

	if ( NULL != dataSource_ ) {
		if ( dssSetKey == dataSource_->getState() ) {
			result = dataSource_->getDataSet()->getRecordCount();
		}
	}

	return result;
}

void DataLink::setDataSource( DataSource* val )
{
	if ( dataSource_ != val ) {
		if ( dataSrcFixed_ ) {
			throw DatabaseError( "Unable to change a data source on a fixed link!" );
		}

		if ( NULL != dataSource_ ) {
			dataSource_->removeDataLink( this );
		}

		if ( NULL != val ) {
			val->addDataLink( this );
		}
	}
}

void DataLink::setDataSourceFixed( bool val )
{
	dataSrcFixed_ = val;
}

void DataLink::setReadOnly( bool val )
{
	if ( val != readOnly_ ) {
		readOnly_ = val;
		updateState();
	}
}

void DataLink::setEditing( bool val )
{
	if ( val != editing_ ) {
		editing_ = val;		
		
		editingStateChanged();
	}
}

void DataLink::updateRecord()
{
	updating_ = true;
	try {
		updateData();
	}
	catch (...){

	}

	updating_ = false;
}

DataSet* DataLink::getDataSet()
{
	DataSet* result = NULL;

	if ( NULL != dataSource_ ) {
		result = dataSource_->getDataSet();
	}

	return result;
}

void DataLink::handleDataEvent( Event* e )
{
	
}

void DataLink::updateState()
{
	bool active = false;
	bool editing = false;


	if ( NULL != dataSource_ ) {
		if ( dataSource_->getState() != dssInactive ) {
			active = true;
		}
	}
	
	setActive( active );

	if ( NULL != dataSource_ ) {
		if ( (dataSource_->getState() & dssEdit) ||
				(dataSource_->getState() & dssInsert) ||
				(dataSource_->getState() & dssSetKey) ) {
			if ( !readOnly_ ) {
				editing = true;
			}
		}
	}

	setActive( editing );
}

void DataLink::setActive( bool val )
{
	if ( active_ != val ) {
		active_ = val;

		activeStateChanged();
	}
}

void DataLink::dataSetChanged()
{
	recordChanged(NULL);
}

void DataLink::dataSetScrolled( int distance )
{
	dataSetChanged();
}

void DataLink::layoutChanged()
{
	dataSetChanged();
}

bool DataLink::edit()
{
	if ( !readOnly_ && (NULL != dataSource_ ) ) {
		dataSource_->edit();
	}

	return editing_;
}