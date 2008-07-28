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
	Component::destroy();
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

		Event e(this,deUpdateState);
		notifyDataLinks(&e);

		Event e1(this,0);
		StateChanged( &e1 );

		if ( dssInactive == oldVal ) {
			Event e2(this,0);
			DataChanged( &e2 );
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
	if ( e->getType() == deUpdateState ) {
		updateState();
	}
	else if ( this->state_ != dssInactive ) {
		notifyDataLinks( e );
		switch ( e->getType() ) {
			case deFieldChange : {
				Event e2( this, e->getType() );
				//source should be a DataField instance???
				e2.setUserData( e->getSource() );
				DataChanged( &e2 );
			}
			break;

			case deRecordChange : case deDataSetChange : case deDataSetScroll : case deLayoutChange :{
				Event e2( this, e->getType() );
				DataChanged( &e2 );
			}
			break;

			case deUpdateRecord : {
				Event e2( this, e->getType() );
				UpdatedData( &e2 );
			}
			break;
		}
	}
}

void DataSource::notifyDataLinks( Event* e )
{		
	DataLinkArray::iterator it = dataLinks_.begin();
	while ( it != dataLinks_.end() ) {
		DataLink* dataLink = *it;
		//if buffer/record count == 1

		if ( dataLink->recordCount_ == 1 ) {
			dataLink->handleDataEvent( e );
		}

		++ it;
	}

	it = dataLinks_.begin();
	while ( it != dataLinks_.end() ) {
		DataLink* dataLink = *it;
		//if buffer/record count > 1

		if ( dataLink->recordCount_ > 1 ) {
			dataLink->handleDataEvent( e );
		}

		++ it;
	}
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