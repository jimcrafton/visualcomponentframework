//ADODataSet.h

#ifndef _VCF_ADODATASET_H__
#define _VCF_ADODATASET_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "ADODB.h"


#define ADOTYPE	"ADOType"


namespace VCF {
	class ADODataSet : public DataSet {
	public:

		ADODataSet();

		virtual ~ADODataSet();

		String getTableName();

		void setTableName( const String& val );

		String getDatabaseName();

		void setDatabaseName( const String& val );

		String getProvider();

		void setProvider( const String& val );
		
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

		virtual void internal_delete();

		virtual void internal_cancel();
		
		virtual GetResultType getRecord( Record* record, GetRecordMode mode );

		virtual void internal_next();

		virtual void internal_initNewRecord( Record* record );

		virtual Record* allocateRecordData();

		virtual bool isCursorOpen();

		comet::ADODB::_ConnectionPtr getConnection();
		
		void addFieldDef( comet::ADODB::FieldPtr& field, size_t fieldIndex );

		AnsiString generateSQL();

		size_t calculateRecordSize();
	private:
		String updateWhereClause_;		
		comet::ADODB::_ConnectionPtr dbConnection_;
		comet::ADODB::_RecordsetPtr currentRecordSet_;
	};
};

#endif //_VCF_ADODATASET_H__

