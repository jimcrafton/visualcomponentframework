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
	dbHandle_(NULL)
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

void SQLiteDataSet::internal_open()
{
	internal_initFieldDefinitions();

	try {
		if ( getDefaulFields() ) {
			createFields();
		}	
	}
	catch ( BasicException& ) {
		
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

	AnsiString sql = (String)(Format("pragma table_info(%s);") % tableName);

	size_t colCount = 0;


	fieldDefs_->clear();

	sqlite3_stmt* stmt;
	const char* tail=0;
	int res = sqlite3_prepare(dbHandle, sql.c_str(), sql.size(), &stmt, &tail );

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
				fieldDef.size = 0;
			}
			break;

			case dftFloat : {
				fieldDef.size = 0;
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

}
		
GetResultType SQLiteDataSet::getRecord()
{
	GetResultType result = grFailed;

	return result;
}

void SQLiteDataSet::internal_next()
{

}

DataSet::RecordDataHandle SQLiteDataSet::allocateRecordData()
{
	DataSet::RecordDataHandle result = NULL;

	return result;
}

void SQLiteDataSet::clearRecordData()
{

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
			throw DatabaseError( SQLiteDatabase::errorMessageFromHandle(dbHandle_) );
		}	
	}

	return dbHandle_;
}