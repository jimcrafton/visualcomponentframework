#ifndef _VCF_DATASET_H__
#define _VCF_DATASET_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

    class Database;
    class Transaction;
    class StringList;
	class FieldDefinitions;
	class DataSource;
	class DataField;

	enum DataSetState {
		dssInactive = 0, 
		dssBrowse, 
		dssEdit, 
		dssInsert, 
		dssSetKey, 
		dssCalcFields,
		dssUpdateNew,
		dssUpdateOld,
		dssFilter
	};

	enum DataEventType {
		deUnknown = 0,
		deFieldChange = 'data', 
		deRecordChange, 
		deDataSetChange,
		deDataSetScroll, 
		deLayoutChange, 
		deUpdateRecord, 
		deUpdateState,
		deCheckBrowseMode,
		dePropertyChange, 
		deFieldListChange, 
		deFocusControl
	};


	enum GetResultType {
		grFailed = 0,
		grOK,
		grBOF,
		grEOF,
	};

    class DATABASEKIT_API DataSet : public Object {
    public:

        DataSet();

        virtual ~DataSet();


		DELEGATE(AfterCancel);
		DELEGATE(AfterClose);
		DELEGATE(AfterDelete);
		DELEGATE(AfterEdit);
		DELEGATE(AfterInsert);
		DELEGATE(AfterOpen);
		DELEGATE(AfterPost);
		DELEGATE(AfterScroll);

		DELEGATE(BeforeCancel);
		DELEGATE(BeforeClose);
		DELEGATE(BeforeDelete);
		DELEGATE(BeforeEdit);
		DELEGATE(BeforeInsert);
		DELEGATE(BeforeOpen);
		DELEGATE(BeforePost);
		DELEGATE(BeforeScroll);

		DELEGATE(CalcFields);
		DELEGATE(DeleteError);
		DELEGATE(EditError);
		DELEGATE(NewRecord);
		DELEGATE(PostError);




        void setDatabase( Database* database );

        void setTransaction( Transaction* transaction );

		void setParam( const String& param, VariantData value );

        VariantData getParam ( const String& );

        void open();

        void close();

		void setActive( bool active );

		bool isActive();

		DataSetState getState() {
			return state_;
		}

		void setState( DataSetState val );

		bool canModify() {
			return canModify_;
		}

		bool isBOF() {
			return bof_;
		}

		bool isEOF() {
			return eof_;
		}

		bool isModified() {
			return modified_;
		}

		bool getDefaulFields() {
			return defaultFields_;
		}

		
		Enumerator<DataField*>* getFields();


        StringList* getSelectSQL();

		void updateFieldDefs();

		Class* getFieldClass( int fieldType );

		void createFields();

		virtual void initFieldDefinitions();

		void addDataSource( DataSource* source );

		void removeDataSource( DataSource* source );

		

		//navigation functions...

		void first();

		void next();

		void refresh();

		//modification functions...
		void edit();

		void appendRecord();

		void deleteRecord();

		void post();

		void cancel();


		

    protected:
        virtual void internal_open() = 0;

        virtual void internal_close() = 0;

		virtual void internal_initFieldDefinitions() = 0;

		virtual void internal_first() = 0;
		
		virtual void internal_next() = 0;

		virtual GetResultType getRecord() = 0;

		virtual void clearRecordData() = 0;
		

		virtual void handleDataEvent( Event* e );



		virtual void openCursor( bool query );

		virtual void closeCursor();


		void openData();

		void deleteFields();

		bool active_;
        Database* db_;
        Transaction* tr_;
        StringList* selectSQL_;
        int columnCount;
		DataSetState state_;
		bool canModify_;
		bool bof_;
		bool eof_;
		bool modified_;
		bool defaultFields_;




        std::map<String, VariantData> params_;

		typedef std::vector<DataSource*> DataSourceArray;
		typedef VectorEnum<DataField*> DataFieldArray;

		DataSourceArray dataSources_;

		FieldDefinitions* fieldDefs_;
		DataFieldArray fields_;
        
    };

};

#endif  //_VCF_DATASET_H__
