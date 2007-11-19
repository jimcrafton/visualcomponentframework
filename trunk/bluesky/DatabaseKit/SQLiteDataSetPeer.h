//SQLiteDataSetPeer.h

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
	class SQLiteDataSetPeer : public DataSetPeer {
	public:

		SQLiteDataSetPeer();		

		String getTableName();

		void setTableName( const String& val );

		String getDatabaseName();

		void setDatabaseName( const String& val );
		
		virtual void setDataSet( DataSet* dataSet );

		virtual bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize );

		virtual void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize );
	
        virtual void open();

        virtual void close();

		virtual void initFieldDefinitions();

		virtual void first();

		virtual void post();

		virtual void refresh();

		virtual void edit();

		virtual void deleteRecord();

		virtual void cancel();

		virtual void initNewRecord( DataSet::Record* record );
		
		virtual GetResultType getRecord( DataSet::Record* record, GetRecordMode mode );

		virtual DataSet::Record* allocateRecordData();

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
		size_t currentRow_;
		DataSet* dataSet_;
	};
};

#endif //_VCF_SQLITEDATASET_H__

