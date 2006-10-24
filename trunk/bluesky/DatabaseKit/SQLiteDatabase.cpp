#include "DatabaseKit.h"
#include "SQLiteDatabase.h"


using namespace VCF;

SQLiteDatabase::SQLiteDatabase()
    : Database(),
	dbHandle_(NULL)
{
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