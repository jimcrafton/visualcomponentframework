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
	protected:
		DataSource* dataSource_;
		bool dataSrcFixed_;
		bool active_;
		bool editing_;
		bool readOnly_;
		bool updating_;

	};



	class DATABASEKIT_API FieldDataLink : public DataLink {
	public:
		FieldDataLink();

	};

};

#endif //_VCF_DATALINK_H__