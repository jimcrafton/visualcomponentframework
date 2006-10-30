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

        void open();

        void close();

		void setActive( bool active );

		bool isActive();

		DataSetState getState() {
			return state_;
		}

		void setState( DataSetState val );

        StringList* getSelectSQL();

		void updateFieldDefs();

		Class* getFieldClass( int fieldType );

		void createFields();

		virtual void initFieldDefinitions();

		void addDataSource( DataSource* source );

		void removeDataSource( DataSource* source );

		void edit();
    protected:
        virtual void internalOpen() = 0;

        virtual void internalClose() = 0;

		virtual void internal_initFieldDefinitions() = 0;

		bool active_;
        Database* db_;
        Transaction* tr_;
        StringList* selectSQL_;
        int columnCount;
		DataSetState state_;
        std::map<String, VariantData> params_;

		typedef std::vector<DataSource*> DataSourceArray;
		DataSourceArray dataSources_;

		FieldDefinitions* fieldDefs_;
        
    };

};

#endif  //_VCF_DATASET_H__
