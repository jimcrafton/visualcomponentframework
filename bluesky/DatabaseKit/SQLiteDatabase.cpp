#include "DatabaseKit.h"
#include "SQLiteDatabase.h"


using namespace VCF;

SQLiteDatabase::SQLiteDatabase()
    : Database(),
	dbHandle_(NULL)
{
	sqlBased_ = true;
}

SQLiteDatabase::~SQLiteDatabase()
{
}

void SQLiteDatabase::internal_connect()
{
	collateParams();

	::sqlite3_open( databaseName_.ansi_c_str(), &dbHandle_ );
}

void SQLiteDatabase::internal_disconnect()
{
	int res = ::sqlite3_close( dbHandle_ );
	dbHandle_ = NULL;

	if ( res == SQLITE_ERROR ) {
		throw DatabaseError( getErrorMessage() );
	}	
}

int SQLiteDatabase::collateParams()
{
	
	return 0;
}

OSHandleID SQLiteDatabase::getHandle()
{
	return (OSHandleID) dbHandle_;
}

String SQLiteDatabase::errorMessageFromHandle( sqlite3* dbHandle )
{
	return String( sqlite3_errmsg(dbHandle) );
}

String SQLiteDatabase::getErrorMessage() const
{
	return SQLiteDatabase::errorMessageFromHandle( dbHandle_ );
}

void SQLiteDatabase::flushSchemaCache( const String& tableName )
{

}

void SQLiteDatabase::setHandle( OSHandleID handle )
{
}

void SQLiteDatabase::rollback()
{
	if ( !transactionStarted_ ) {
		throw DatabaseError("Are you sure you set up this correctly? It appears that either a call to beginTransation() was never made, or it failed.");
	}
	
	if ( SQLITE_OK != sqlite3_exec( dbHandle_, "rollback transaction;", NULL,0,NULL ) ) {
		throw DatabaseError( getErrorMessage() );
	}

	transactionStarted_ = false;
}

void SQLiteDatabase::startTransaction()
{
	transactionStarted_ = false;

	if ( SQLITE_OK == sqlite3_exec( dbHandle_, "begin transaction;", NULL,0,NULL ) ) {
		transactionStarted_ = true;
	}
}

void SQLiteDatabase::commit()
{
	if ( !transactionStarted_ ) {
		throw DatabaseError("Are you sure you set up this correctly? It appears that either a call to beginTransation() was never made, or it failed.");
	}
	
	if ( SQLITE_OK != sqlite3_exec( dbHandle_, "commit transaction;", NULL,0,NULL ) ) {
		throw DatabaseError( getErrorMessage() );
	}

	transactionStarted_ = false;
}
