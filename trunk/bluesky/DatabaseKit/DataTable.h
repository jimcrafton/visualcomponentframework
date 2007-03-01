#ifndef _VCF_DATATABLE_H__
#define _VCF_DATATABLE_H__

/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF {


	#define DATATABLE_CLASSID		"17915aa8-0ac0-4c15-92d5-9091c65013b1"

	class DATABASEUIKIT_API DataTable : public Component {
	public:
		DataTable();
		virtual ~DataTable();

		
		//forwarding functions for the internal dataset's delegates		
		Delegate& getAfterCancel();
		Delegate& getAfterClose();
		Delegate& getAfterDelete();
		Delegate& getAfterEdit();
		Delegate& getAfterInsert();
		Delegate& getAfterOpen();
		Delegate& getAfterPost();
		Delegate& getAfterScroll();

		Delegate& getBeforeCancel();
		Delegate& getBeforeClose();
		Delegate& getBeforeDelete();
		Delegate& getBeforeEdit();
		Delegate& getBeforeInsert();
		Delegate& getBeforeOpen();
		Delegate& getBeforePost();
		Delegate& getBeforeScroll();

		Delegate& getCalcFields();
		Delegate& getDeleteError();
		Delegate& getEditError();
		Delegate& getNewRecord();
		Delegate& getPostError();


		String getTableName();
		void setTableName( const String& val );

		String getDatabaseName();
		void setDatabaseName( const String& val );

		String getDataSetType() {
			return dataSetType_;
		}

		void setDataSetType( const String& val );

		void setActive( bool active );
		bool isActive();

		DataSetState getState();
		void setState( DataSetState val );

		bool canModify();

		bool isBOF();
		bool isEOF();

		bool isModified();

		bool getDefaultFields();
		
		bool isFiltered();		
		void setFiltered( bool val );


		String getFilter();
		void setFilter( const String& val );

		FilterOptions getFilterOptions();
		void setFilterOptions( int val );

		Enumerator<DataField*>* getFields();

		DataField* fieldByName( const String& fieldName );


		void first();
		void next();
		void refresh();
		void edit();
		void appendRecord();
		void deleteRecord();
		void post();
		void cancel();

		DataSet* getDataSet() {
			return dataSet_;
		}

	protected:
		DataSet* dataSet_;
		String dataSetType_;

	};


};


#endif //_VCF_DATATABLE_H__