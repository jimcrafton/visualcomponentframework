//SQLiteDataSet.cpp
#include "DatabaseKit.h"
#include "SQLiteDataSet.h"
#include "SQLiteDatabase.h"
#include "SQLiteDatabase.h"


#define SQLITE_TABLEINFO_COLCOUNT		6
#define SQLITE_TABLEINFO_CID			0
#define SQLITE_TABLEINFO_NAME			1
#define SQLITE_TABLEINFO_TYPE			2
#define SQLITE_TABLEINFO_NOTNULL		3
#define SQLITE_TABLEINFO_DEFLTVAL		4
#define SQLITE_TABLEINFO_PK				5


using namespace VCF;


static std::map<String, DataFieldType> colTypeMap;



SQLiteDataSet::SQLiteDataSet():
	DataSet(),
	dbHandle_(NULL),
	currentStmt_(NULL),
	currentRow_(0)
{
	if ( colTypeMap.empty() ) {
		colTypeMap["varchar"] = dftString;
		colTypeMap["text"] = dftString;
		colTypeMap["int"] = dftInteger;
		colTypeMap["integer"] = dftInteger;
		colTypeMap["real"] = dftFloat;
		colTypeMap["blob"] = dftBlob;		
	}
}

size_t SQLiteDataSet::calculateRecordSize()
{
	size_t result = 0;
	//recordSize_ = 0;

	VCF_ASSERT( NULL != currentStmt_ );

	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* field = fields_()[i];

		switch ( field->getDataType() ) {
			case dftString : {				
				int res = sqlite3_column_bytes( currentStmt_, i ) + 1; //adds 1 for trailing \0
				VCF_ASSERT( res >= 0 );
				result += res;
			}
			break;

			case dftUnicodeString : {
				int res = sqlite3_column_bytes16( currentStmt_, i ) + 1; //adds 1 for trailing \0
				VCF_ASSERT( res >= 0 );
				result += res;
			}
			break;

			default : {
				result += field->getSize();
			}
			break;

		}
	}

	//recordSize_ = result;

	return result;
}

void SQLiteDataSet::internal_open()
{
	internal_initFieldDefinitions();

	currentRow_ = 0;
	currentStmt_ = NULL;

	try {
		if ( getDefaultFields() ) {
			createFields();
		}

		AnsiString sql = generateSQL();
		const char* tail=0;
		sqlite3* dbHandle = getHandle();

		
		int res = sqlite3_prepare_v2(dbHandle, sql.c_str(), sql.size(), &currentStmt_, &tail );

		if ( res != SQLITE_OK ) {
			sqlite3_finalize(currentStmt_);
			throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
		}
		
		res = sqlite3_step(currentStmt_);
		if ( (res != SQLITE_DONE) && (res != SQLITE_ROW) ) {
			sqlite3_finalize(currentStmt_);
			throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
		}

	}
	catch ( BasicException& ) {
		
	}
}

void SQLiteDataSet::internal_initNewRecord( Record* record )
{
	size_t currentSz = 0;

	for ( size_t j=0;j<fields_->size();j++ ) {
		DataField* field = fields_()[j];

		switch ( field->getDataType() ) {
			case dftString : {
				currentSz += 1;
			}
			break;

			case dftUnicodeString : {
				currentSz += 1;
			}
			break;

			case dftFloat : {
				currentSz += field->getSize();
			}
			break;
			
			case dftWord : case dftSmallint : case dftInteger : {
				currentSz += field->getSize();
			}
			break;
		}
	}

	VCF_ASSERT( currentSz > 0 ) ;


	record->setSize( currentSz );
	memset( record->buffer, 0, record->size );

	size_t bufferOffset = 0;

	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* field = fields_()[i];
		
		switch ( field->getDataType() ) {
			case dftString : {
				const char* text = "";
				int txtSz = 0;
				memcpy( &record->buffer[bufferOffset], text, txtSz );

				record->buffer[bufferOffset+txtSz] = 0;

				field->setSize( txtSz + 1 );

				bufferOffset += field->getSize();
			}
			break;

			case dftUnicodeString : {
				
			}
			break;

			case dftFloat : {
				double res = 0.0;

				memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

				bufferOffset += field->getSize();
			}
			break;
			
			case dftWord : case dftSmallint : case dftInteger : {
				int res = 0;

				memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

				bufferOffset += field->getSize();
			}
			break;
		}
	}
}

void SQLiteDataSet::closeHandle()
{
	sqlite3* dbHandle = getHandle();
	int res = ::sqlite3_close( dbHandle );
	dbHandle_ = NULL;

	if ( res == SQLITE_ERROR ) {
		throw DatabaseError( SQLiteDatabase::errorMessageFromHandle(dbHandle) );
	}
}

void SQLiteDataSet::internal_close()
{
	sqlite3_finalize(currentStmt_);
	currentStmt_ = NULL;

	closeHandle();
}

void SQLiteDataSet::internal_initFieldDefinitions()
{
	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified!");
	}

	sqlite3* dbHandle = getHandle();

	/*
	SQL: pragma table_info(tableName);
	Should return something like this:
	----------------------------------------------------
	cid name		type	notnull		dflt_value	pk
	----------------------------------------------------
	0	LastName	varchar	0						0			
	1	FirstName	varchar	0						0
	2	Address		varchar	0						0
	3	Age			int		0						0
	----------------------------------------------------
	*/

	AnsiString sql = (String)(Format("PRAGMA TABLE_INFO(%s);") % tableName);

	size_t colCount = 0;


	fieldDefs_->clear();

	sqlite3_stmt* stmt;
	const char* tail=0;
	
	int res = sqlite3_prepare_v2(dbHandle, sql.c_str(), sql.size(), &stmt, &tail );

	if ( res != SQLITE_OK ) {
		sqlite3_finalize(stmt);
		throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
	}

	res = sqlite3_step(stmt);


	if ( res == SQLITE_ROW && verifyTableColums(stmt) ) {
		while ( res == SQLITE_ROW ) {

			addFieldDef( stmt, colCount );

			colCount ++;
			res = sqlite3_step(stmt);
		}
	}

	sqlite3_finalize(stmt);
}

bool SQLiteDataSet::verifyTableColums(sqlite3_stmt* stmt)
{
	bool result = false;

	size_t colCount = sqlite3_column_count(stmt);
	if ( colCount == SQLITE_TABLEINFO_COLCOUNT ) {
		result = true;
	}

	return result;
}

void SQLiteDataSet::addFieldDef( sqlite3_stmt* stmt, size_t fieldIndex )
{
	String colName = (const char*)sqlite3_column_text( stmt, SQLITE_TABLEINFO_NAME );
	String fieldName = colName;
	String name = fieldName;
	int i = 1;
	while ( fieldDefs_->indexOf( name ) >= 0 ) {
		name = Format("%s%d") % fieldName % i;
		i++;
	}

	fieldName = name;


	String typeName = (const char*)sqlite3_column_text( stmt, SQLITE_TABLEINFO_TYPE );

	DataFieldType dataType = colTypeMap[ StringUtils::lowerCase(typeName) ];


	if ( dataType != dftUnknown ) {

		sqlite3* dbHandle = getHandle();
		
		String dbName = getDatabaseName();
		String tableName = getTableName();

		int notNull, primKey, autoInc;
		notNull = primKey = autoInc = 0;


		sqlite3_table_column_metadata( dbHandle, 
										dbName.ansi_c_str(), 
										tableName.ansi_c_str(), 
										colName.ansi_c_str(),
										NULL,
										NULL,
										&notNull,
										&primKey,
										&autoInc );





		FieldDefinition fieldDef;
		fieldDef.name = fieldName;
		fieldDef.dataType = dataType;
		fieldDef.fieldNumber = fieldIndex;
		switch ( fieldDef.dataType ) {
			case dftString : {
				fieldDef.size = 0;
			}
			break;

			case dftInteger : {
				fieldDef.size = sizeof(int);
			}
			break;

			case dftWord : {
				fieldDef.size = sizeof(int);
			}
			break;

			case dftSmallint : {
				fieldDef.size = sizeof(int);
			}
			break;

			case dftBoolean : {
				fieldDef.size = sizeof(bool);
			}
			break;

			case dftDate : {
				fieldDef.size = sizeof(VCF::uint64);
			}
			break;

			case dftTime : {
				fieldDef.size = sizeof(VCF::uint64);
			}
			break;

			case dftDateTime : {
				fieldDef.size = sizeof(VCF::uint64);
			}
			break;

			case dftFloat : {
				fieldDef.size = sizeof(double);
			}
			break;

			case dftBlob : {
				//????
			}
			break;
		}


		fieldDefs_->add( fieldDef );
	}
}

void SQLiteDataSet::internal_first()
{
	VCF_ASSERT( NULL != dbHandle_ );
	VCF_ASSERT( NULL != currentStmt_ );

	sqlite3_finalize(currentStmt_);
	currentStmt_ = NULL;

	currentRow_ = 0;

	AnsiString sql = generateSQL();

	VCF_ASSERT( !sql.empty() );

	VCF_ASSERT( sql[sql.size()-1] == ';' );

	const char* tail=0;
	sqlite3* dbHandle = getHandle();
	
	int res = sqlite3_prepare_v2(dbHandle, sql.c_str(), sql.size(), &currentStmt_, &tail );

	if ( res != SQLITE_OK ) {
		sqlite3_finalize(currentStmt_);
		throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
	}

	res = sqlite3_step(currentStmt_);
	if ( (res != SQLITE_DONE) && (res != SQLITE_ROW) ) {
		sqlite3_finalize(currentStmt_);
		throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
	}
}
		
GetResultType SQLiteDataSet::getRecord( DataSet::Record* record, GetRecordMode mode )
{
	GetResultType result = grFailed;

	VCF_ASSERT( NULL != currentStmt_ );

	size_t bufferOffset = 0;

	int res = 0;	

	size_t currentSz = calculateRecordSize();

	VCF_ASSERT( currentSz > 0 ) ;


	record->setSize( currentSz );

	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* field = fields_()[i];

		switch ( field->getDataType() ) {
			case dftString : {
				const char* text = (const char*)sqlite3_column_text(currentStmt_,i);
				int txtSz = sqlite3_column_bytes( currentStmt_, i );
				memcpy( &record->buffer[bufferOffset], text, txtSz );

				record->buffer[bufferOffset+txtSz] = 0;

				field->setSize( txtSz + 1 );

				bufferOffset += field->getSize();
			}
			break;

			case dftUnicodeString : {
				
			}
			break;

			case dftFloat : {
				double res = sqlite3_column_double(currentStmt_,i);

				memcpy( &record->buffer[bufferOffset], &res, sizeof(res) );

				bufferOffset += field->getSize();
			}
			break;
			
			case dftWord : case dftSmallint : case dftInteger : {
				int res = sqlite3_column_int( currentStmt_, i );

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
			res = sqlite3_step(currentStmt_);	
			currentRow_ ++;
		}
		break;
	}

	switch ( res ) {
		case SQLITE_ROW : {
			result = grOK;
		}
		break;

		case SQLITE_DONE : {
			result = grEOF;
		}
		break;

		case SQLITE_ERROR : {
			result = grFailed;
		}
		break;

		case SQLITE_BUSY : {
			result = grFailed;
		}
		break;

		case SQLITE_MISUSE : {
			result = grFailed;
		}
		break;
	}	

	return result;
}

void SQLiteDataSet::internal_next()
{

}

DataSet::Record* SQLiteDataSet::allocateRecordData()
{
	DataSet::Record* result = NULL;

	calculateRecordSize();

	result = new DataSet::Record();


	return result;
}


String SQLiteDataSet::getTableName()
{
	return getParam( "tablename" );
}

void SQLiteDataSet::setTableName( const String& val )
{
	setParam( "tablename", val );
}

String SQLiteDataSet::getDatabaseName()
{
	return getParam( "databasename" );
}

void SQLiteDataSet::setDatabaseName( const String& val )
{
	setParam( "databasename", val );
}

sqlite3* SQLiteDataSet::getHandle()
{
	if ( NULL == dbHandle_ ) {
		String dbName = getDatabaseName();

		if ( dbName.empty() ) {
			throw DatabaseError("No Database Name specified!");
		}

		int res = ::sqlite3_open( dbName.ansi_c_str(), &dbHandle_ );
		if ( res == SQLITE_ERROR ) {
			dbHandle_ = NULL;
			throw DatabaseError( SQLiteDatabase::errorMessageFromHandle(dbHandle_) );
		}	
	}

	return dbHandle_;
}

AnsiString SQLiteDataSet::generateSQL()
{
	AnsiString result;

	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified, unable to generate SQL statement!");
	}

	if ( fields_->empty() ) {
		throw DatabaseError("No Fields in data set, unable to generate SQL statement!");
	}

	sqlite3* dbHandle = getHandle();

	result += "SELECT ";
	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* field = fields_()[i];
		if ( i > 0 ) {
			result += ", ";
		}
		result += field->getName();
	}

	result += " FROM ";

	result += tableName;


	result += ";";


	return result;
}

bool SQLiteDataSet::isCursorOpen()
{
	return currentStmt_ != NULL;	
}

bool SQLiteDataSet::getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize )
{
	VCF_ASSERT( activeRecordIndex_ != DataSet::NoRecPos );

	bool result = false;

	size_t bufferOffset = 0;

	for ( size_t i=0;i<fields_->size();i++ ) {
		DataField* aField = fields_()[i];		

		if ( field->getFieldNumber() == i ) {
			DataSet::Record* record = records_[ activeRecordIndex_ ];

			VCF_ASSERT( NULL != record->buffer );

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
				result = true;
			}
			
			break;
		}
		
		bufferOffset += aField->getSize();
	}

	return result;
}

void SQLiteDataSet::setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize )
{
	VCF_ASSERT( NULL != field );
	VCF_ASSERT( activeRecordIndex_ != DataSet::NoRecPos );


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

				if ( !( (state_ == dssCalcFields) || (state_ == dssFilter) /*|| (state_ & dssNewValue)*/ ) ) {
					Event e(field,deFieldChange);
					e.setUserData(this);
					handleDataEvent(&e);
				}
				break;
			}
			else {
				bufferOffset += aField->getSize();
			}
		}
	}
}

void SQLiteDataSet::internal_post()
{
	VCF_ASSERT( activeRecordIndex_ != DataSet::NoRecPos );

	DataSet::Record* record = records_[ activeRecordIndex_ ];

	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified, unable to generate SQL statement!");
	}

	if ( fields_->empty() ) {
		throw DatabaseError("No Fields in data set, unable to generate SQL statement!");
	}



	if ( dssEdit == state_ ) {
		size_t bufferOffset = 0;

		int res = 0;
		size_t colIndex = 1;

		String updateSQL;

		
		updateSQL = "UPDATE ";
		updateSQL += tableName + " SET ";

		std::vector<DataField*>::iterator it = fields_->begin();
		while ( it != fields_->end() ) {
			DataField* field = *it;

			//note the sqlite3_bind API's don't seem to work right

			if ( it != fields_->begin() ) {
				updateSQL += ", ";
			}	

			updateSQL += field->getName() + " = ";

			if ( field->isStringType() ){
				updateSQL += "'" + field->getAsString() + "' ";
			}
			else {
				updateSQL += field->getAsString() + " ";
			}

			++it;
		}

		
		


		updateSQL += updateWhereClause_;
		updateSQL += ";";


		AnsiString sql = updateSQL;

		const char* tail=0;
		sqlite3* dbHandle = getHandle();


		sqlite3_stmt *updateStmt = NULL;
		
		res = sqlite3_prepare_v2( dbHandle, sql.c_str(), sql.length(), &updateStmt, &tail );

		if ( res != SQLITE_OK ) {
			sqlite3_finalize(updateStmt);
			throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
		}

	
		res = sqlite3_step( updateStmt );

		sqlite3_finalize( updateStmt );

		switch ( res ) {
			case SQLITE_MISUSE : case SQLITE_ERROR : {
				throw DatabaseError( Format("Error executing SQL. Error returned was %s.") % 
										SQLiteDatabase::errorMessageFromHandle(dbHandle) );
			}
			break;
		}

		internal_first();
	}
	else if ( dssInsert == state_ ) {
		//add a new rec here!

		String insertSQL = "INSERT INTO " + tableName + " ";		

		if ( !fields_->empty() ) {
			insertSQL += "( ";
		}
		std::vector<DataField*>::iterator it = fields_->begin();
		while ( it != fields_->end() ) {
			DataField* field = *it;

			if ( it != fields_->begin() ) {
				insertSQL += ", ";
			}	

			insertSQL += field->getName();

			++it;
		}

		if ( !fields_->empty() ) {
			insertSQL += " ) ";
		}

		insertSQL += "VALUES (";

		it = fields_->begin();
		while ( it != fields_->end() ) {
			DataField* field = *it;

			if ( it != fields_->begin() ) {
				insertSQL += ", ";
			}	

			if ( field->isStringType() ) {
				insertSQL += "'";
				insertSQL += field->getAsString();
				insertSQL += "'";
			}
			else {
				insertSQL += field->getAsString();
			}

			++it;
		}

		insertSQL += " );";		


		int res = 0;
		AnsiString sql = insertSQL;
		const char* tail=0;
		sqlite3* dbHandle = getHandle();


		sqlite3_stmt *insertStmt = NULL;
		
		res = sqlite3_prepare_v2( dbHandle, sql.c_str(), sql.length(), &insertStmt, &tail );

		if ( res != SQLITE_OK ) {
			sqlite3_finalize(insertStmt);
			throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
		}



		res = sqlite3_step( insertStmt );

		sqlite3_finalize( insertStmt );

		switch ( res ) {
			case SQLITE_MISUSE : case SQLITE_ERROR : {
				throw DatabaseError( Format("Error executing SQL. Error returned was %s.") % 
										SQLiteDatabase::errorMessageFromHandle(dbHandle) );
			}
			break;
		}

		internal_first();
	}
	else {
		throw DatabaseError("Dataset not in edit or insert mode!");
	}



	
	
}

void SQLiteDataSet::internal_refresh()
{

}

void SQLiteDataSet::internal_edit()
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

void SQLiteDataSet::internal_delete()
{
	String tableName = getTableName();

	if ( tableName.empty() ) {
		throw DatabaseError("No Table Name specified, unable to generate SQL statement!");
	}


	String deleteSql = "DELETE FROM " + tableName + " WHERE oid = (SELECT oid FROM " + 
						tableName + " WHERE ";		

	std::vector<DataField*>::iterator it = fields_->begin();
	while ( it != fields_->end() ) {
		DataField* field = *it;

		if ( !field->isBinaryType() ) {

			if ( it != fields_->begin() ) {
				deleteSql += " AND ";
			}	
			
			
			deleteSql += field->getName() + " = ";
			
			if ( field->isStringType() ) {
				deleteSql += "'";
			}

			deleteSql += field->getAsString();

			if ( field->isStringType() ) {
				deleteSql += "'";
			}
		}

		++it;
	}

	deleteSql += "LIMIT 1);";

	int res = 0;
	AnsiString sql = deleteSql;
	const char* tail=0;
	sqlite3* dbHandle = getHandle();


	sqlite3_stmt *deleteStmt = NULL;
	
	res = sqlite3_prepare_v2( dbHandle, sql.c_str(), sql.length(), &deleteStmt, &tail );

	if ( res != SQLITE_OK ) {
		sqlite3_finalize(deleteStmt);
		throw DatabaseError(SQLiteDatabase::errorMessageFromHandle(dbHandle));
	}



	res = sqlite3_step( deleteStmt );

	sqlite3_finalize( deleteStmt );

	switch ( res ) {
		case SQLITE_MISUSE : case SQLITE_ERROR : {
			throw DatabaseError( Format("Error executing SQL. Error returned was %s.") % 
									SQLiteDatabase::errorMessageFromHandle(dbHandle) );
		}
		break;
	}
}

void SQLiteDataSet::internal_cancel()
{
		
}