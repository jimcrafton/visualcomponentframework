//DataTable.cpp


#include "DatabaseUIKit.h"
#include "DataTable.h"

using namespace VCF;


DataTable::DataTable():
	dataSet_(NULL)
{

}

DataTable::~DataTable()
{
	if ( NULL != dataSet_ ) {
		dataSet_->free();
	}
}

Delegate& DataTable::getAfterCancel()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterClose()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterDelete()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterEdit()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterInsert()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterOpen()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterPost()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getAfterScroll()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeCancel()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeClose()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeDelete()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeEdit()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeInsert()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeOpen()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforePost()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getBeforeScroll()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getCalcFields()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getDeleteError()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getEditError()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getNewRecord()
{
	return dataSet_->getAfterCancel();
}

Delegate& DataTable::getPostError()
{
	return dataSet_->getAfterCancel();
}

String DataTable::getTableName()
{
	return dataSet_->getParam( "tablename" );
}

void DataTable::setTableName( const String& val )
{
	dataSet_->setParam( "tablename", val );
}

String DataTable::getDatabaseName()
{
	return dataSet_->getParam( "databasename" );
}

void DataTable::setDatabaseName( const String& val )
{
	dataSet_->setParam( "databasename", val );
}

void DataTable::setDataSetType( const String& val )
{
	if ( dataSetType_ != val ) {
		dataSetType_ = val;

		if ( NULL != dataSet_ ) {
			dataSet_->free();
		}
		
		dataSet_ = DatabaseToolkit::createDataSet( dataSetType_ ); 		
	}
}

void DataTable::setActive( bool active )
{
	dataSet_->setActive( active );
}

bool DataTable::isActive()
{
	return dataSet_->isActive();
}

DataSetState DataTable::getState()
{
	return dataSet_->getState();
}

void DataTable::setState( DataSetState val )
{
	dataSet_->setState( val );
}

bool DataTable::canModify()
{
	return dataSet_->canModify();
}

bool DataTable::isBOF()
{
	return dataSet_->isBOF();
}

bool DataTable::isEOF()
{
	return dataSet_->isEOF();
}

bool DataTable::isModified()
{
	return dataSet_->isModified();
}

bool DataTable::getDefaultFields()
{
	return dataSet_->getDefaultFields();
}

bool DataTable::isFiltered()
{
	return dataSet_->isFiltered();
}

void DataTable::setFiltered( bool val )
{
	dataSet_->setFiltered( val );
}

String DataTable::getFilter()
{
	return dataSet_->getFilter();
}

void DataTable::setFilter( const String& val )
{
	dataSet_->setFilter( val );
}

FilterOptions DataTable::getFilterOptions()
{
	return dataSet_->getFilterOptions();
}

void DataTable::setFilterOptions( int val )
{
	dataSet_->setFilterOptions( val );
}

Enumerator<DataField*>* DataTable::getFields()
{
	return dataSet_->getFields();
}

DataField* DataTable::fieldByName( const String& fieldName )
{
	return dataSet_->fieldByName( fieldName );
}

void DataTable::first()
{
	dataSet_->first();
}

void DataTable::next()
{
	dataSet_->next();
}

void DataTable::refresh()
{
	dataSet_->refresh();
}

void DataTable::edit()
{
	dataSet_->edit();
}

void DataTable::appendRecord()
{
	dataSet_->appendRecord();
}

void DataTable::deleteRecord()
{
	dataSet_->deleteRecord();
}

void DataTable::post()
{
	dataSet_->post();
}

void DataTable::cancel()
{
	dataSet_->cancel();
}



