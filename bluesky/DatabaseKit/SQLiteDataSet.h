//SQLiteDataSet.h

#ifndef _VCF_SQLITEDATASET_H__
#define _VCF_SQLITEDATASET_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "sqliteInt.h"



namespace VCF {
	class SQLiteDataSet : public DataSet {
	public:

		SQLiteDataSet();

		String getTableName();

		void setTableName( const String& val );

		String getDatabaseName();

		void setDatabaseName( const String& val );
		
		virtual bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize );

		virtual void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize );
	protected:
        virtual void internal_open();

        virtual void internal_close();

		virtual void internal_initFieldDefinitions();

		virtual void internal_first();

		virtual void internal_post();

		virtual void internal_refresh();

		virtual void internal_edit();
		
		virtual GetResultType getRecord( Record* record, GetRecordMode mode );

		virtual void internal_next();

		virtual Record* allocateRecordData();

		virtual bool isCursorOpen();

		sqlite3* getHandle();
		void closeHandle();

		bool verifyTableColums(sqlite3_stmt* stmt);

		void addFieldDef( sqlite3_stmt* stmt, size_t fieldIndex );

		AnsiString generateSQL();
		
		size_t calculateRecordSize();

	private:
		sqlite3* dbHandle_;
		sqlite3_stmt* currentStmt_;
		String  updateWhereClause_;
	};
};

#endif //_VCF_SQLITEDATASET_H__

