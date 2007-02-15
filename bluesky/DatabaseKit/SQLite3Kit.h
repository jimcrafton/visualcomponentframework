#ifndef _SQLITE3KIT_H__
#define	_SQLITE3KIT_H__

#include "sqliteInt.h"

//simple wrapper for SQLite in C++

namespace Test {

class DBException : public std::exception {
public:
	DBException(sqlite3* dbHandle): 
		std::exception(sqlite3_errmsg(dbHandle)) {}

	DBException(const std::string& s): 
		std::exception(s.c_str()) {}
};


class Column {
public:
	enum ColumnType{
		ctInteger = SQLITE_INTEGER,
		ctFloat = SQLITE_FLOAT,
		ctText = SQLITE_TEXT,
		ctBlob = SQLITE_BLOB,
		ctNull = SQLITE_NULL
	};

	Column(sqlite3_stmt* stmt, size_t index):stmt_(stmt),index_(index)  {}



	Column& operator= ( const int& rhs ) {
		sqlite3_bind_int( stmt_, index_, rhs );
		return *this;
	}

	Column& operator= ( const sqlite_int64& rhs ) {
		sqlite3_bind_int64( stmt_, index_, rhs );
		return *this;
	}		

	Column& operator= ( const double& rhs ) {
		sqlite3_bind_double( stmt_, index_, rhs );
		return *this;
	}

	Column& operator= ( const std::string& rhs ) {
		int res = sqlite3_bind_text( stmt_, index_, rhs.c_str(), rhs.size(), SQLITE_TRANSIENT );

		return *this;
	}

	operator std::string () const {
		const char* text = (const char*)sqlite3_column_text(stmt_,index_);
		return (text != NULL) ? std::string(text) : std::string();
	}

	operator int () const {
		return sqlite3_column_int(stmt_,index_);
	}

	operator double () const {
		return sqlite3_column_double(stmt_,index_);
	}

	operator sqlite_int64 () const {
		return sqlite3_column_int64(stmt_, index_);
	}

	ColumnType type() const {
		return (ColumnType)sqlite3_column_type(stmt_,index_);
	}

	std::string name() const {
		return sqlite3_column_name(stmt_,index_);
	}
protected:
	sqlite3_stmt* stmt_;
	size_t index_;
};

class ResultSet {
public:

	ResultSet():stmt_(NULL),dbHandle_(NULL),eof_(false),rowCount_(0) {

	}

	ResultSet( sqlite3_stmt* stmt, sqlite3* handle ):stmt_(stmt), 
		dbHandle_(handle),eof_(false),rowCount_(0) {
		/*
		int res = sqlite3_step(stmt_);
		if ( res != SQLITE_ROW ) {
			eof_ = true;
		}
		rowCount_ ++;
		*/
	}

	ResultSet( const ResultSet& rhs ):
		stmt_(rhs.stmt_), dbHandle_(rhs.dbHandle_),eof_(false),rowCount_(rhs.rowCount_){

	}


	~ResultSet() {
		
	}
	
	ResultSet& operator= (const ResultSet& rhs ) {
		stmt_ = rhs.stmt_;
		dbHandle_ = rhs.dbHandle_;
		eof_ = rhs.eof_;
		rowCount_ = rhs.rowCount_;
		return *this;
	}

	size_t getColumnCount() const {
		return sqlite3_column_count(stmt_);
	}

	size_t getRowCount() const {
		return rowCount_;
	}

	ResultSet& operator++() {		// prefix
		next();
		return *this;
	}

	ResultSet& operator++(int) {		// postfix
		next();
		return *this;
	}

	bool next() {
		eof_ = false;
		int res = sqlite3_step(stmt_);
		if ( res != SQLITE_ROW ) {
			eof_ = true;
			return false;
		}
		rowCount_ ++;

		return true;
	}

	void close() {
		if ( NULL != stmt_ ) {
			sqlite3_finalize(stmt_);
			stmt_ = NULL;
		}
	}

	bool isOpen() const {
		return NULL != stmt_;
	}

	bool eof() const {
		return eof_;
	}

	void reset() {
		if ( NULL != stmt_ ) {
			sqlite3_reset( stmt_ );
		}
	}

	Column operator[]( const std::string& columnName ) {
		if ( columnNames_.empty() ) {
			size_t colCount = sqlite3_column_count(stmt_);
			for (size_t i=0;i<colCount;i++ ) {
				columnNames_[ (char *)sqlite3_column_name(stmt_, i) ] = i;
			}
		}


		ColumnNameMap::iterator found = columnNames_.find( columnName );
		if ( found == columnNames_.end() ) {
			throw DBException("Invalid Column name");
		}

		size_t colIndex = found->second;

		return (*this)[ colIndex ];
	}

	Column operator[]( size_t columnIndex ) {
		Column result(stmt_,columnIndex);

		return result;
	}	

	bool columnExists( const std::string& columnName ) const {
		bool result = false;

		if ( columnNames_.empty() ) {
			size_t colCount = sqlite3_column_count(stmt_);
			for (size_t i=0;i<colCount;i++ ) {
				columnNames_[ (char *)sqlite3_column_name(stmt_, i) ] = i;
			}
		}

		result = columnNames_.find( columnName ) != columnNames_.end();

		return result;
	}

protected:

	sqlite3_stmt* stmt_;
	sqlite3* dbHandle_;
	bool eof_;
	size_t rowCount_;
	typedef std::map<std::string,int> ColumnNameMap;
	mutable ColumnNameMap columnNames_;

};

class DB {
public:

	DB():dbHandle_(NULL),transactionStarted_(false){}

	DB( const std::string& fileName ):dbHandle_(NULL),transactionStarted_(false) {
		if ( SQLITE_OK != open( fileName ) ) {
			throw DBException(dbHandle_);
		}
	}

	~DB() {
		if ( NULL != dbHandle_ ) {
			close();
		}
	}

	int open( const std::string& fileName ) {
		return sqlite3_open( fileName.c_str(), &dbHandle_ );
	}

	int close() {
		int res = sqlite3_close( dbHandle_ );
		dbHandle_ = NULL;
		return res;
	}

	bool isOpen() const {
		return NULL != dbHandle_;
	}


	operator sqlite3* () {
		return dbHandle_;
	}

	std::string getLastErrorMsg() {
		std::string result = sqlite3_errmsg(*this);
		return result;
	}

	int execSQL( const std::string& sql, std::string* errMsg=NULL ) {

		int result = 0;
		char* errStr;

		if ( transactionStarted_ ) {
			sqlite3_stmt* stmt;
			const char* tail=0;
			result = sqlite3_prepare(dbHandle_, sql.c_str(), sql.size(), &stmt, &tail );
			
			if ( result != SQLITE_OK ) {
				sqlite3_finalize(stmt);
				throw DBException(dbHandle_);
			}

			result = sqlite3_step(stmt);
			if ( (result != SQLITE_DONE) && (result != SQLITE_ROW) ) {
				sqlite3_finalize(stmt);
				throw DBException(dbHandle_);
			}				

			sqlite3_finalize(stmt);
		}
		else {
			result = sqlite3_exec( dbHandle_, sql.c_str(), DB::execCallback, this, &errStr );
			if ( (NULL != errMsg) && (NULL != errStr) ) {
				*errMsg = errStr;
			}
			if ( NULL != errStr ) {
				sqlite3_free( errStr );
			}
		}
		return result;
	}

	bool beginTransation() {
		transactionStarted_ = false;

		if ( SQLITE_OK == sqlite3_exec( dbHandle_, "begin transaction;", NULL,0,NULL ) ) {
			transactionStarted_ = true;
		}			

		return transactionStarted_;
	}

	bool commitTransation() {
		
		if ( !transactionStarted_ ) {
			throw DBException("Are you sure you set up this correctly? It appears that either a call to beginTransation() was never made, or it failed.");
		}

		if ( SQLITE_OK != sqlite3_exec( dbHandle_, "commit transaction;", NULL,0,NULL ) ) {
			return false;
		}

		transactionStarted_ = false;

		return true;
	}

	ResultSet execSQLWithResults( const std::string& sql ) {

		sqlite3_stmt* stmt;
		const char* tail=0;
		int res = sqlite3_prepare(dbHandle_, sql.c_str(), sql.size(), &stmt, &tail );

		if ( res != SQLITE_OK ) {
			sqlite3_finalize(stmt);
			throw DBException(dbHandle_);
		}

		ResultSet result(stmt,dbHandle_);
		return result;
	}

	bool inAutoCommitMode() const {
		if ( sqlite3_get_autocommit(dbHandle_) ) {
			return true;
		}

		return false;
	}

	static bool validSQL( const std::string& sql ) {
		if ( sqlite3_complete( sql.c_str() ) ) {
			return true;
		}

		return false;
	}

protected:	
	static int execCallback(void* arg1, 
							int numberOfCols, 
							char** columnValues, 
							char** columnNames ) {
		DB* thisPtr = (DB*)arg1;


		return 0;
	}
	bool transactionStarted_;
	sqlite3* dbHandle_;
};



};

#endif //_SQLITE3KIT_H__