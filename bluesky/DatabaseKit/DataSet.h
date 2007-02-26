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
	class DataLink;
	class DataSet;


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

	enum CheckModeState {
		cmsBrowse = 1,
		cmsActive,
		cmsInactive
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

	enum GetRecordMode {
		grmNext = 1,
		grmCurrent
	};

	enum GetResultType {
		grFailed = 0,
		grOK,
		grBOF,
		grEOF,
	};

	enum ResyncMode {
		rmNone = 0,
		rmExact = 0x01, 
		rmCenter = 0x02
	};


	enum FilterOptions {
		foNoOptions = 0,
		foCaseInsensitive = 0x01,
		foNoPartialCompare = 0x02
	};


	class DATABASEKIT_API FilterRecordEvent : public Event {
	public:
		FilterRecordEvent( Object* source ) : Event(source,0),accept(false){}

		FilterRecordEvent( const FilterRecordEvent& rhs ):Event(rhs),accept(false){
			accept = rhs.accept;
		}

		virtual Object* clone( bool deep = false ) {
			return new FilterRecordEvent(*this);
		}

		bool accept;
	};


	class DATABASEKIT_API DataErrorEvent : public Event {
	public:
		DataErrorEvent( Object* source ) : Event(source,0){}

		DataErrorEvent( const DataErrorEvent& rhs ):Event(rhs){
			reason = rhs.reason;
		}

		virtual Object* clone( bool deep = false ) {
			return new DataErrorEvent(*this);
		}

		String reason;
	};


    class DATABASEKIT_API DataSet : public Object {
    public:
		struct Record {
			Record(): buffer(NULL), size(0){}			

			~Record() {
				delete [] buffer;
				buffer = NULL;
				size = 0;
			}

			void setSize( size_t val ) {
				if ( val != size ) {
					
					if ( NULL != buffer ) {
						delete [] buffer;
					}
					
					size = val;
					
					if ( size > 0 ) {
						buffer = new unsigned char[size];
						memset( buffer, 0, size );
					}
				}
			}

			unsigned char* buffer;
			size_t size;
		};

		enum {
			NoRecPos = (size_t)-1,
			NoFieldPos = (size_t)-1,
		};

		typedef std::vector<DataSource*> DataSourceArray;
		typedef VectorEnum<DataField*> DataFieldArray;
		typedef std::vector<Record*> RecordsArray;
		typedef std::vector<DataLink*> DataLinkArray;





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


		DELEGATE(FilterRecord);		


        void setDatabase( Database* database );

		void setParam( const String& param, VariantData value );

        VariantData getParam ( const String& );

		Locale* getLocale();

		void setLocale( Locale* val );

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
		
		bool isFiltered() {
			return filtered_;
		}
		
		void setFiltered( bool val );


		String getFilter() {
			return filter_;
		}

		void setFilter( const String& val );

		FilterOptions getFilterOptions() {
			return filterOptions_;
		}

		void setFilterOptions( int val );

		//fields

		bool getFieldNames( std::vector<String>& fieldNames );

		const FieldDefinitions& getFieldDefinitions() {
			return *fieldDefs_;
		}

		Enumerator<DataField*>* getFields();

		std::vector<DataField*>& getFieldsArray() {
			return fields_;
		}

		void updateFieldDefs();

		Class* getFieldClass( int fieldType );

		void createFields();

		virtual void initFieldDefinitions();

		void checkFieldName( const String& fieldName );

		DataField* findField( const String& fieldName );

		DataField* fieldByName( const String& fieldName );


		size_t indexOfField( DataField* field );
		

		VariantData getFieldValue( const String& fieldName );
		void setFieldValue( const String& fieldName, VariantData& val );

		void addField( const String& fieldName );
		void removeField( const String& fieldName );


		void addDataSource( DataSource* source );

		void removeDataSource( DataSource* source );

		size_t getRecordCount();

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
		

		virtual bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize ) = 0;

		virtual void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize ) = 0;

		virtual void handleDataEvent( Event* e );
    protected:

		friend class DataLink;

        virtual void internal_open() = 0;

        virtual void internal_close() = 0;

		virtual void internal_initFieldDefinitions() = 0;

		virtual void internal_first() = 0;
		
		virtual void internal_next() = 0;

		virtual void internal_post() = 0;

		virtual void internal_refresh() = 0;

		virtual void internal_edit() = 0;

		virtual void internal_delete() = 0;

		virtual void internal_cancel() = 0;

		virtual void internal_initNewRecord( Record* record ) = 0;

		virtual GetResultType getRecord( Record* record, GetRecordMode mode ) = 0;		

		virtual Record* allocateRecordData() = 0;

		virtual bool isCursorOpen() = 0;

		virtual void openCursor( bool query );

		virtual void closeCursor();

		virtual void resync( int mode );

		virtual void handleNewRecord();

		virtual void initNewRecord( Record* record );

		void openData();

		void deleteFields();

		void updateRecordSize();

		void clearRecords();
		void activateRecords();

		void setRecordCount( size_t numberOfRecords );

		size_t getNextRecords();

		bool getNextRecord();

		void checkMode( CheckModeState mode );		

		void updateRecord();

		void freeFieldBuffers();

		void cursorPositionChanged();

		void checkRequiredFields();

		void setRecordData( Record* record, size_t offset, size_t column, const unsigned char* buffer, size_t bufferSize );

		void beginNewRecord();

		void endNewRecord();

		virtual void destroy();

		bool active_;
        Database* db_;
		DataSetState state_;
		bool canModify_;
		bool bof_;
		bool eof_;
		bool modified_;
		bool defaultFields_;
		bool filtered_;
		String filter_;
		FilterOptions filterOptions_;		


        std::map<String, VariantData> params_;

		

		DataSourceArray dataSources_;

		FieldDefinitions* fieldDefs_;
		DataFieldArray fields_;

		size_t recordCount_;
		RecordsArray records_;
		size_t activeRecordIndex_; //we may not need this...
		size_t currentRecordIndex_;
        
		Locale* locale_;

		DataLinkArray dataLinks_;
    };

};

#endif  //_VCF_DATASET_H__

