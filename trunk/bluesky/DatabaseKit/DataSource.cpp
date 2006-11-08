//DataSource.cpp

#include "DatabaseKit.h"
#include "DataLink.h"


using namespace VCF;

DataSource::DataSource():
	dataSet_(NULL),
	enabled_(false),
	state_(dssInactive)
{

}

void DataSource::destroy()
{
	setDataSet(NULL);
	Object::destroy();
}

void DataSource::setDataSet( DataSet* val )
{
	if ( dataSet_ != val ) {

		DataSet* old = dataSet_;
		dataSet_ = val;

		if ( old != NULL ) {
			old->removeDataSource( this );
		}		

		if ( NULL != dataSet_ ) {
			dataSet_->addDataSource(this);
		}
	}
}

void DataSource::setEnabled( bool val )
{
	enabled_ = val;
	updateState();
}

void DataSource::setState( DataSetState val )
{
	if ( state_ != val ) {
		DataSetState oldVal = state_;

		state_ = val;

		Event e(this,0);
		StateChanged.fireEvent( &e );

		if ( dssInactive == oldVal ) {
			Event e2(this,0);
			DataChanged.fireEvent( &e2 );
		}

	}
}

void DataSource::updateState()
{
	if ( this->isEnabled() && (NULL != dataSet_) ) {
		setState( dataSet_->getState() );
	}
	else {
		setState( dssInactive );
	}
}

void DataSource::edit()
{
	if ( dssBrowse == state_ && (NULL != dataSet_) ) {
		dataSet_->edit();
	}
}

void DataSource::handleDataEvent( Event* e )
{
	
}

void DataSource::addDataLink( DataLink* val )
{	
	if ( std::find( dataLinks_.begin(), dataLinks_.end(), val ) == dataLinks_.end() ) {
		dataLinks_.push_back( val );

		val->dataSource_ = this;

		if ( NULL != dataSet_ ) {
			//dataSet_->updateRecordSize
		}

		val->updateState();
	}
}

void DataSource::removeDataLink( DataLink* val )
{
	val->dataSource_ = NULL;

	DataLinkArray::iterator found = std::find( dataLinks_.begin(), dataLinks_.end(), val );
	if ( found != dataLinks_.end() ) {
		dataLinks_.erase( found );
	}

	val->updateState();

	if ( NULL != dataSet_ ) {
		//dataSet_->updateRecordSize
	}
}