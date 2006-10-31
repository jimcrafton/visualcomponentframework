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

	protected:
        virtual void internal_open();

        virtual void internal_close();

		virtual void internal_initFieldDefinitions();

		virtual void internal_first();
		
		virtual GetResultType getRecord();

		virtual void internal_next();

		virtual void clearRecordData();

		sqlite3* getHandle();
		void closeHandle();

		bool verifyTableColums(sqlite3_stmt* stmt);

		void addFieldDef( sqlite3_stmt* stmt, size_t fieldIndex );
	private:
		sqlite3* dbHandle_;
	};
};

#endif //_VCF_SQLITEDATASET_H__

