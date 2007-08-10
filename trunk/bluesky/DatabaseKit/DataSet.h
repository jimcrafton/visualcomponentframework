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
	class DataSetPeer;


	/**
	This enumeration describes the possible
	states a DataSet instance can be in, at 
	any given moment.
	*/
	enum DataSetState {
		/**
		The dataset is not active, and it 
		will not be connected to the actual data
		base (if one is being used). 
		*/
		dssInactive = 0, 
		
		/**
		The dataset is in a browse state. This will allow the
		dataset to iterate through items/records in the dataset.
		*/
		dssBrowse, 
		
		/**
		The dataset is in an edit state. This allows the dataset
		to attempt to modify the fields of a specific row (or record), 
		or executing some command that will modify many rows of the
		dataset.
		*/
		dssEdit, 
		
		/**
		The dataset is in an insert state. This happens when the dataset
		attempts to add or insert a record.
		*/
		dssInsert, 
		
		/**
		*/
		dssSetKey, 
		
		/**
		*/
		dssCalcFields,
		
		/**
		*/
		dssUpdateNew,
		
		/**
		*/
		dssUpdateOld,
		
		/**
		*/
		dssFilter
	};

	/**
	This enumeration indicates what kind of 
	state to check for. 
	*/
	enum CheckModeState {
		cmsBrowse = 1,
		cmsActive,
		cmsInactive
	};

	/**
	This enumeration is used to describe the type of 
	data event that is fired during certain operations 
	on a dataset.
	*/
	enum DataEventType {
		deUnknown = 0,
		
		/**
		An event that indicates a field's value 
		was changed.
		*/
		deFieldChange = 'data', 
		
		/**
		An event to indicate that a complete record was changed.
		*/
		deRecordChange, 
		
		/**
		An event indicating that some property or state of the 
		dataset changed.
		*/
		deDataSetChange,
		
		/**
		An event that indicates the dataset has successfully iterated 
		to the next record in the dataset.
		*/
		deDataSetScroll, 
		
		/**
		*/
		deLayoutChange, 
		
		/**
		An event that indicates the record was updated
		*/
		deUpdateRecord, 
		
		/**
		An event that indicates that the dataset's state changed.
		*/
		deUpdateState,
		
		/**
		*/
		deCheckBrowseMode,
		
		/**
		*/
		dePropertyChange, 
		
		/**
		*/
		deFieldListChange, 
		
		/**
		*/
		deFocusControl
	};

	/**
	An enumeration that indicates how to retrieve a record. Either 
	the next record is retrieved or the current record is retreived.
	*/
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

	typedef Delegate1<FilterRecordEvent*> FilterRecordDelegate; 


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

	typedef Delegate1<DataErrorEvent*> DataErrorDelegate; 


	#define DATASET_CLASSID	"76ab89f0-66d1-4ba3-998e-4ec874faa6e1"

    class DATABASEKIT_API DataSet : public Component {
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


		DELEGATE(EventDelegate,AfterCancel);
		DELEGATE(EventDelegate,AfterClose);
		DELEGATE(EventDelegate,AfterDelete);
		DELEGATE(EventDelegate,AfterEdit);
		DELEGATE(EventDelegate,AfterInsert);
		DELEGATE(EventDelegate,AfterOpen);
		DELEGATE(EventDelegate,AfterPost);
		DELEGATE(EventDelegate,AfterScroll);

		DELEGATE(EventDelegate,BeforeCancel);
		DELEGATE(EventDelegate,BeforeClose);
		DELEGATE(EventDelegate,BeforeDelete);
		DELEGATE(EventDelegate,BeforeEdit);
		DELEGATE(EventDelegate,BeforeInsert);
		DELEGATE(EventDelegate,BeforeOpen);
		DELEGATE(EventDelegate,BeforePost);
		DELEGATE(EventDelegate,BeforeScroll);

		DELEGATE(EventDelegate,CalcFields);
		DELEGATE(EventDelegate,DeleteError);
		DELEGATE(EventDelegate,EditError);
		DELEGATE(EventDelegate,NewRecord);
		DELEGATE(DataErrorDelegate,PostError);


		DELEGATE(FilterRecordDelegate,FilterRecord);		

		String getPeerType() {
			return peerType_;
		}

		void setPeerType( const String& val );

        void setDatabase( Database* database );

		void setParam( const String& param, VariantData value );

        VariantData getParam ( const String& );

		Locale* getLocale();

		void setLocale( Locale* val );

        void open();

        void close();

		void setActive( bool active );

		bool isActive();

		void checkInactive();

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

		bool getDefaultFields() {
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

		const FieldDefinitions& getFieldDefinitions() const {
			return *fieldDefs_;
		}

		FieldDefinitions& getFieldDefinitions() {
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

		void addField( DataField* field );
		void removeField( DataField* field );


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
		

		bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize );

		void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize );

		virtual void handleDataEvent( Event* e );

		void setRecordCount( size_t numberOfRecords );

		size_t getActiveRecordIndex() const {
			return activeRecordIndex_;
		}

		const RecordsArray& getRecords() const {
			return records_;
		}

		RecordsArray& getRecords() {
			return records_;
		}

		void internal_setRecordData( Record* record, size_t offset, size_t column, const unsigned char* buffer, size_t bufferSize );

    protected:

		friend class DataLink;

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

		

		size_t getNextRecords();

		bool getNextRecord();

		void checkMode( CheckModeState mode );		

		void updateRecord();

		void swapRecord( size_t fromIndex, size_t toIndex );

		void freeFieldBuffers();

		void cursorPositionChanged();

		void checkRequiredFields();		

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
		size_t usableRecordCount_; //number of slots in the records_ vector that we actually use
		RecordsArray records_;
		size_t activeRecordIndex_; //we may not need this...
		size_t currentRecordIndex_;
        
		Locale* locale_;

		DataLinkArray dataLinks_;

		DataSetPeer* peer_;
		String peerType_;
    };





	class DATABASEKIT_API DataSetPeer  {
	public:
		virtual ~DataSetPeer(){}

		virtual void setDataSet( DataSet* dataSet ) = 0;

		virtual void open() = 0;

        virtual void close() = 0;

		virtual void initFieldDefinitions() = 0;

		virtual void first() = 0;
		
		virtual void next() = 0;

		virtual void post() = 0;

		virtual void refresh() = 0;

		virtual void edit() = 0;

		virtual void deleteRecord() = 0;

		virtual void cancel() = 0;

		virtual void initNewRecord( DataSet::Record* record ) = 0;

		virtual GetResultType getRecord( DataSet::Record* record, GetRecordMode mode ) = 0;		

		virtual DataSet::Record* allocateRecordData() = 0;

		virtual bool isCursorOpen() = 0;

		virtual bool getFieldData( DataField* field, unsigned char* buffer, size_t bufferSize ) = 0;

		virtual void setFieldData( DataField* field, const unsigned char* buffer, size_t bufferSize ) = 0;
	};

};

#endif  //_VCF_DATASET_H__

