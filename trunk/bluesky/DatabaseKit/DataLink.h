#ifndef _VCF_DATALINK_H__
#define _VCF_DATALINK_H__

//DataLink.h

/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

	class DataSet;
	class DataSource;

	/**
	\class DataLink DataLink.h "vcf/DatabaseKit/DataLink.h"
	*/
	class DATABASEKIT_API DataLink : public Object {
	public:
		DataLink();

		bool isActive() {
			return active_;
		}

		DataSet* getDataSet();


		DataSource* getDataSource() {
			return dataSource_;
		}

		bool isDataSourceFixed() {
			return dataSrcFixed_;
		}

		bool isEditing() {
			return editing_;
		}

		bool isReadOnly() {
			return readOnly_;
		}

		size_t getRecordCount();

		void setRecordCount( size_t val );

		size_t getActiveRecord();

		void setActiveRecord( size_t val );

		void setDataSource( DataSource* val );

		void setDataSourceFixed( bool val );

		void setReadOnly( bool val );

		void setEditing( bool val );

		void updateRecord();

		void updateState();

		void setActive( bool val );

		bool edit();

		virtual void handleDataEvent( Event* e );

		virtual void activeStateChanged(){};

		virtual void editingStateChanged(){};

		virtual void checkBrowseMode(){};

		virtual void dataSetChanged();

		virtual void recordChanged( DataField* field ){};

		virtual void dataSetScrolled( int distance );

		virtual void layoutChanged();

		virtual void updateData(){};

		friend class DataSource;
		friend class DataSet;
	protected:

		virtual void destroy();

		DataSource* dataSource_;
		bool dataSrcFixed_;
		bool active_;
		bool editing_;
		bool readOnly_;
		bool updating_;
		size_t recordCount_;
		size_t firstRecord_;
	};



	class DATABASEKIT_API FieldDataLink : public DataLink {
	public:
		FieldDataLink();

		DELEGATE(EventDelegate,DataChange);
		DELEGATE(EventDelegate,EditingChange);
		DELEGATE(EventDelegate,UpdatedData);
		DELEGATE(EventDelegate,ActiveChange);

		virtual void recordChanged( DataField* field );

		virtual void updateData();

		virtual void activeStateChanged();

		virtual void editingStateChanged();

		DataField* getField();

		void setField( DataField* val );

		bool isModifiable();

		String getFieldName() {
			return fieldName_;
		}

		void setFieldName( const String& val );
	protected:
		bool modified_;
		DataField* field_;
		String fieldName_;

		void updateField();
	};

};

#endif //_VCF_DATALINK_H__