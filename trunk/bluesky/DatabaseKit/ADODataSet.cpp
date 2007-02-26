//ADODataSet.cpp
#include "DatabaseKit.h"
#include "ADODataSet.h"
#include "vcf/ApplicationKit/Win32HResult.h"



#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\




using namespace VCF;
using namespace comet;
using namespace comet::ADODB;





ADODataSet::ADODataSet():
	DataSet()
{

	//Note that we are initializing COM with the 
	//COINIT_APARTMENTTHREADED flag here. This may
	//make multi-threaded support problematic. See
	//the MSDN docs for CoInitializeEx
	if( FAILED(::CoInitializeEx(0,COINIT_APARTMENTTHREADED)) ) {  
		throw DatabaseError("Unable to initialize COM for ADO data set");
	}

	setProvider( "Microsoft.Jet.OLEDB.4.0" );
}

ADODataSet::~ADODataSet()
{
	dbConnection_ = NULL;

	::CoUninitialize();
}


AnsiString ADODataSet::generateSQL()
{
	AnsiString result;

	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified, unable to generate SQL statement!");
	}

	if ( fields_->empty() ) {
		throw DatabaseError("No Fields in data set, unable to generate SQL statement!");
	}	

	result += "select ";
	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* field = fields_()[i];
		if ( i > 0 ) {
			result += ", ";
		}
		result += field->getName();
	}

	result += " from ";

	result += tableName;


	result += ";";


	return result;
}

void ADODataSet::internal_open()
{
	internal_initFieldDefinitions();

	try {
		if ( getDefaulFields() ) {
			createFields();
		}

		_ConnectionPtr connection = getConnection();

		AnsiString sql = generateSQL();
		
		currentRecordSet_ = NULL; //pitch the old record set...

		_CommandPtr cmd = Command::create();

		cmd->PutActiveConnection( connection );
		cmd->PutCommandText( sql.c_str() );

		variant_t recordsAffected;
		currentRecordSet_ = cmd->Execute( recordsAffected, variant_t::missing(), adCmdText);

		currentRecordSet_->MoveFirst();
	}
	catch ( BasicException& ) {
		
	}
}


comet::ADODB::_ConnectionPtr ADODataSet::getConnection()
{
	if ( dbConnection_.is_null() ) {
		dbConnection_ = Connection::create();
		
		String dbName = getDatabaseName();
		
		if ( dbName.empty() ) {
			throw DatabaseError("No Database Name specified!");
		}

		String provider = getProvider();
		
		if ( provider.empty() ) {
			throw DatabaseError("No Provider specified!");
		}

		

		bstr_t connectionStr;
		connectionStr += "Provider=";
		connectionStr += provider;
		connectionStr += ";";

		connectionStr += "Data Source=";
		connectionStr += dbName;
		connectionStr += ";";
		connectionStr += "Persist Security Info=False";

		dbConnection_->Open( connectionStr.in() );		
	}

	return dbConnection_;
}

void ADODataSet::internal_close()
{
	_ConnectionPtr connect = getConnection();

	currentRecordSet_ = NULL; //pitch the old record set...

	connect->Close();
}

void ADODataSet::addFieldDef( FieldPtr& field, size_t fieldIndex )
{
	String colName = AnsiString(field->GetName());
	String fieldName = colName;
	String name = fieldName;
	int i = 1;
	while ( fieldDefs_->indexOf( name ) >= 0 ) {
		name = Format("%s%d") % fieldName % i;
		i++;
	}

	fieldName = name;	


	DataFieldType dataType = dftUnknown;
	DataTypeEnum type = field->GetType();
	switch ( type ) {
		case adInteger : {
			dataType = dftInteger;
		}
		break;

		case adChar : {
			dataType = dftString;
		}
		break;

		case adBSTR : {
			dataType = dftString;
		}
		break;

		case adWChar : case adVarWChar : {
			dataType = dftString;
		}
		break;
	}


	if ( dataType != dftUnknown ) {
		FieldDefinition fieldDef;
		fieldDef.name = fieldName;
		fieldDef.dataType = dataType;
		fieldDef.fieldNumber = fieldIndex;

		fieldDef.size = field->GetDefinedSize();


		switch ( fieldDef.dataType ) {
			case dftString : {
				fieldDef.size = 0;
			}
			break;
		}

		fieldDefs_->add( fieldDef );
	}

}

void ADODataSet::internal_initFieldDefinitions()
{
	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified!");
	}
	
	_ConnectionPtr connect = getConnection();

	fieldDefs_->clear();


	_RecordsetPtr rs = Recordset::create();

	bstr_t tn = tableName.c_str();
	variant_t cnVar = connect;

	try {
		//rs->CacheSize = 100;

		rs->Open( tn.in(), cnVar, adOpenForwardOnly, adLockReadOnly, adCmdTable );		

		FieldsPtr fields = rs->GetFields();

		if ( !fields.is_null() ) {
			variant_t index;
			for (int i = 0; i < (int)fields->GetCount(); i++) {
				index = i;
				addFieldDef( fields->GetItem( index ), (size_t)i );
			}
		}

		rs->Close();
	}
	catch ( std::exception& e ) {
		throw DatabaseError(Format("Error initializing fields from ADO database!\nError: %s") % e.what() );
	}	
}

void ADODataSet::internal_first()
{
	currentRecordSet_->MoveFirst();
	
}
	
size_t ADODataSet::calculateRecordSize() 
{
	size_t result = 0;

	try {
		FieldsPtr fields = currentRecordSet_->GetFields();

		if ( !fields.is_null() ) {
			variant_t index;
			for (int i = 0; i < (int)fields->GetCount(); i++) {
				index = i;
				FieldPtr field = fields->GetItem( index );

				result += field->GetActualSize();
			}
		}
	}
	catch ( std::exception& ) {
		
	}

	return result;
}

GetResultType ADODataSet::getRecord( DataSet::Record* record, GetRecordMode mode )
{
	GetResultType result = grFailed;	


	if ( currentRecordSet_->GetEOF() ) {
		eof_ = true;
		result = grEOF;
	}
	else {
		size_t bufferOffset = 0;

		int res = 0;	

		size_t currentSz = calculateRecordSize();

		record->setSize( currentSz );

		FieldsPtr rsFields = currentRecordSet_->GetFields();

		variant_t fldIndex;

		for ( size_t i=0;i<fields_->size();i++ ) {
			DataField* field = fields_()[i];

			fldIndex = (int)i;
			FieldPtr adoField = rsFields->GetItem( fldIndex );

			variant_t fieldVal = adoField->GetValue();


			size_t as = adoField->GetActualSize();

			switch ( field->getDataType() ) {
				case dftString : {
					bstr_t s = fieldVal;
					AnsiString as = s.s_str();
					const char* text = as.c_str();
					int txtSz = as.size();
					memcpy( &record->buffer[bufferOffset], text, txtSz );				

					field->setSize( adoField->GetActualSize() );

					bufferOffset += field->getSize();
				}
				break;

				case dftUnicodeString : {
					
				}
				break;

				case dftFloat : {
					double res = fieldVal;
					memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

					bufferOffset += field->getSize();
				}
				break;
				
				case dftWord : case dftSmallint : case dftInteger : {
					int res = fieldVal;

					memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

					bufferOffset += field->getSize();
				}
				break;
			}
		}

		VCF_ASSERT( bufferOffset == record->size );

		switch ( mode ) {
			case grmCurrent : {

			}
			break;

			case grmNext : {
				try {
					currentRecordSet_->MoveNext();
					result = grOK;
					bool eof = currentRecordSet_->GetEOF();
					if ( eof ) {
						result = grEOF;
					}
				}
				catch ( std::exception& e ) {
					result = grFailed;
				}
			}
			break;
		}
	}

	return result;
}

void ADODataSet::internal_next()
{

}

DataSet::Record* ADODataSet::allocateRecordData()
{
	DataSet::Record* result = NULL;

	result = new DataSet::Record();

	return result;
}


String ADODataSet::getTableName()
{
	return getParam( "tablename" );
}

void ADODataSet::setTableName( const String& val )
{
	setParam( "tablename", val );
}

String ADODataSet::getDatabaseName()
{
	return getParam( "databasename" );
}

void ADODataSet::setDatabaseName( const String& val )
{
	setParam( "databasename", val );
}

String ADODataSet::getProvider()
{
	return getParam( "provider" );
}

void ADODataSet::setProvider( const String& val )
{
	setParam( "provider", val );
}


bool ADODataSet::isCursorOpen()
{
	return !currentRecordSet_.is_null();
}

bool ADODataSet::getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize )
{
	bool result = false;

	size_t bufferOffset = 0;

	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* aField = fields_()[i];		

		if ( field->getFieldNumber() == i ) {
			DataSet::Record* record = records_[ activeRecordIndex_ ];

			if ( (NULL != buffer) && (bufferSize > 0 ) ) {
				size_t len = minVal<>( bufferSize, (size_t)field->getSize() );
				memcpy( buffer, &record->buffer[bufferOffset], len );
				
				if ( dftString == field->getDataType() ) {
					buffer[len-1] = 0;
				}
			}

			//we need to determine if the data actually has any "content",
			//in other words is it NULL. For the moment we'll loop
			//through all the bytes and see if they are all zeroed out.
			//this is potentiall kind of stupid, so maybe there is a better
			//way???
			if ( dftString == field->getDataType() ) {
				for (int i=0;i<field->getSize();i++ ) {
					if ( record->buffer[bufferOffset+i] > 0 ) {
						result = true;
						break;
					}
				}
			}
			else {
				result= true;
			}
			
			break;
		}
		
		bufferOffset += aField->getSize();
	}

	return result;
}

void ADODataSet::setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize )
{
	VCF_ASSERT( NULL != field );



	if ( !(state_ & dssEdit) ) {
		throw DatabaseError( "This data set is not in editing mode." );
	}

	
	if ( NULL != field ) {
		if ( (state_ & dssSetKey) && ((field->getFieldNumber() < 0) /*add index checks here|| ()*/) ) {
			throw DatabaseError( "This field is not editable." );
		}		

		DataSet::Record* record = records_[ activeRecordIndex_ ];

		size_t bufferOffset = 0;
		for ( size_t i=0;i<fields_->size();i++ ) {
			DataField* aField = fields_()[i];

			if ( aField == field ) {

				field->validate( buffer, bufferSize );
		
				setRecordData( record, bufferOffset, i, buffer, bufferSize );

				if ( !( (state_ == dssCalcFields) || (state_ == dssFilter) ) ) {
					Event e(field,deFieldChange);
					e.setUserData(this);
					handleDataEvent(&e);
				}
				break;
			}
		}
	}
}

void ADODataSet::internal_post()
{
	if ( dssEdit == state_ ) {

		DataSet::Record* record = records_[ activeRecordIndex_ ];

		size_t bufferOffset = 0;

		int res = 0;

		FieldsPtr rsFields = currentRecordSet_->GetFields();
		variant_t fldIndex;

		for ( size_t i=0;i<fields_->size();i++ ) {
			DataField* field = fields_()[i];
			fldIndex = (int)i;
			FieldPtr adoField = rsFields->GetItem( fldIndex );


			switch ( field->getDataType() ) {
				case dftString : {
					const char* text = (const char*)&record->buffer[bufferOffset];

					
				}
				break;

				case dftFloat : {
					double val = 0;
					memcpy( &val, &record->buffer[bufferOffset], field->getSize() );
					
				}
				break;

				case dftWord : case dftSmallint : case dftInteger : {
					int val = 0;
					memcpy( &val, &record->buffer[bufferOffset], field->getSize() );
					
				}
				break;
			}

	//		if ( res != SQLITE_OK ) {
	//			throw DatabaseError( Format("Error writing to field \"%s\". Error returned was %s.") );
	//		}
			bufferOffset += field->getSize();
		}

		VCF_ASSERT( bufferOffset == record->size );
	}
}

void ADODataSet::internal_refresh()
{

}

void ADODataSet::internal_edit()
{
	updateWhereClause_ = "WHERE ";
	std::vector<DataField*>::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;

		if ( !field->isBinaryType() ) {

			if ( it != fields_->begin() ) {
				updateWhereClause_ += " AND ";
			}	
			
			
			updateWhereClause_ += field->getName() + " = ";
			
			if ( field->isStringType() ) {
				updateWhereClause_ += "'";
			}

			updateWhereClause_ += field->getAsString();

			if ( field->isStringType() ) {
				updateWhereClause_ += "'";
			}
		}

		++it;
	}
}

void ADODataSet::internal_initNewRecord( Record* record )
{

}

void ADODataSet::internal_delete()
{

}

void ADODataSet::internal_cancel()
{

}
