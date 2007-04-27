//ADODataSetPeer.h

#ifndef _VCF_ADODATASETPEER_H__
#define _VCF_ADODATASETPEER_H__



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
	class ADODataSetPeer : public DataSetPeer {
	public:

		ADODataSetPeer();

		virtual ~ADODataSetPeer();

		String getTableName();

		void setTableName( const String& val );

		String getDatabaseName();

		void setDatabaseName( const String& val );

		String getProvider();

		void setProvider( const String& val );
		
		virtual void setDataSet( DataSet* dataSet );

		virtual bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize );

		virtual void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize );
	protected:
        virtual void open();

        virtual void close();

		virtual void initFieldDefinitions();

		virtual void first();

		virtual void post();

		virtual void refresh();

		virtual void edit();

		virtual void deleteRecord();

		virtual void cancel();
		
		virtual GetResultType getRecord( DataSet::Record* record, GetRecordMode mode );

		virtual void next();

		virtual void initNewRecord( DataSet::Record* record );

		virtual DataSet::Record* allocateRecordData();

		virtual bool isCursorOpen();

		comet::ADODB::_ConnectionPtr getConnection();
		
		void addFieldDef( comet::ADODB::FieldPtr& field, size_t fieldIndex );

		AnsiString generateSQL();

		size_t calculateRecordSize();
	private:
		DataSet* dataSet_;
		String updateWhereClause_;		
		comet::ADODB::_ConnectionPtr dbConnection_;
		comet::ADODB::_RecordsetPtr currentRecordSet_;
		comet::ADODB::_RecordsetPtr updateRecordSet_;
	};
};

#endif //_VCF_ADODATASETPEER_H__

