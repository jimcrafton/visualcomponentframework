//DataLink.cpp

#include "DatabaseKit.h"
#include "DataLink.h"


using namespace VCF;


DataLink::DataLink():	
	dataSource_(NULL),
	dataSrcFixed_(false),
	active_(false),
	editing_(false),
	readOnly_(false)
{

}



size_t DataLink::getRecordCount()
{

	if ( NULL != dataSource_ ) {
		if ( dssSetKey == dataSource_->getState() ) {
			//dataSource_->getDataSet()->getR
		}
	}

	return 0;
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
	readOnly_ = val;
}

void DataLink::setEditing( bool val )
{
	editing_ = val;
}

void DataLink::updateRecord()
{

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

}
