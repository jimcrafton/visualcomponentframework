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
	updating_(false),
	recordCount_(1)
{

}

void DataLink::destroy()
{
	active_ = false;
	editing_ = false;
	dataSrcFixed_ = false;
	
	setDataSource( NULL );

	Object::destroy();
}


size_t DataLink::getRecordCount()
{
	size_t result = 0;

	if ( NULL != dataSource_ ) {
		if ( dssSetKey == dataSource_->getState() ) {
			result = 1;
		}
		else {
			result = dataSource_->getDataSet()->getRecordCount();
			if ( result > recordCount_ ) {
				result = recordCount_;
			}
		}
	}

	return result;
}

void DataLink::setRecordCount( size_t val )
{
	if ( val != recordCount_ ) {
		recordCount_ = val;
		if ( isActive() ) {
			this->getDataSet()->updateRecordSize();
		}
	}
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
	switch ( e->getType() ) {
		case deUpdateState : {
			updateState();
		}
		break;

		default : {
			if ( active_ ) {
				switch ( e->getType() ) {
					case deFieldChange: case deRecordChange : {
						if ( !updating_ ) {
							recordChanged( (DataField*)e->getSource() );
						}
					}
					break;

					case deDataSetChange: case deDataSetScroll: case deLayoutChange: {
						int count = 0;
						if ( NULL != this->dataSource_ ) {
							if ( dataSource_->getState() != dssSetKey ) { 
								
								//figure out what the first record is - ignored for now...
							}
						}
						switch ( e->getType() ) {
							case deDataSetChange: {
								dataSetChanged();
							}
							break;

							case deDataSetScroll: {
								dataSetScrolled(count);
							}
							break;

							case deLayoutChange: {
								layoutChanged();
							}
							break;
						}
					}
					break;

					case deUpdateRecord: {
						updateRecord();
					}
					break;


					case deCheckBrowseMode: {
						checkBrowseMode();
					}
					break;
					
				}
			}
		}
		break;
	}
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




FieldDataLink::FieldDataLink():
	DataLink(),
	modified_(false),
	field_(NULL)
{

}

void FieldDataLink::recordChanged( DataField* field )
{
	if ( NULL == field || (field == field_) ) {
		Event e(this,0);
		DataChange.fireEvent( &e );
		
		modified_ = false;
	}
}

void FieldDataLink::updateData()
{
	if ( modified_ ) {
		if ( NULL != field_ ) {
			Event e(this,0);
			UpdatedData.fireEvent( &e );
		}

		modified_ = false;
	}
}

void FieldDataLink::activeStateChanged()
{
	updateField();

	Event e(this,0);
	ActiveChange.fireEvent( &e );
}

void FieldDataLink::updateField()
{
	setField( NULL );

	if ( isActive() && !fieldName_.empty() ) {

		VCF_ASSERT( NULL != getDataSource() );
		VCF_ASSERT( NULL != getDataSource()->getDataSet() );

		DataField* field = getDataSource()->getDataSet()->fieldByName( fieldName_ );

		setField( field );
	}
}

DataField* FieldDataLink::getField()
{
	return field_;
}

void FieldDataLink::setField( DataField* val )
{
	if ( field_ != val ) {
		field_ = val;

		editingStateChanged();
		recordChanged( NULL );
	}
}

void FieldDataLink::editingStateChanged()
{
	setEditing( DataLink::isEditing() && isModifiable() );
}

bool FieldDataLink::isModifiable()
{
	return false;
}

void FieldDataLink::setFieldName( const String& val )
{
	if ( val != fieldName_ ) {
		fieldName_ = val;
		updateField();
	}
}